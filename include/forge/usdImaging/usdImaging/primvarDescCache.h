#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/primvarDescCache.h"
/*
 * Copyright 2021 Forge. All Rights Reserved.
 *
 * The use of this software is subject to the terms of the
 * Forge license agreement provided at the time of installation
 * or download, or which otherwise accompanies this software in
 * either electronic or hard copy form.
 *
 * Portions of this file are derived from original work by Pixar
 * distributed with Universal Scene Description, a project of the
 * Academy Software Foundation (ASWF). https://www.aswf.io/
 *
 * Original Copyright (C) 2016-2021 Pixar.
 * Modifications copyright (C) 2020-2021 ForgeXYZ LLC.
 *
 * Forge. The Animation Software & Motion Picture Co.
 */
#ifndef FORGE_USD_IMAGING_USD_IMAGING_PRIMVARDESC_CACHE_H
#define FORGE_USD_IMAGING_USD_IMAGING_PRIMVARDESC_CACHE_H

/// \file usdImaging/primvarDescCache.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/imaging/hd/sceneDelegate.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_unordered_map.h>
# include <tbb/concurrent_queue.h>
#endif /* Q_MOC_RUN */

FORGE_NAMESPACE_BEGIN

/// \class UsdImagingPrimvarDescCache
///
/// A cache for primvar descriptors.
///
class UsdImagingPrimvarDescCache
{
public:
    UsdImagingPrimvarDescCache(const UsdImagingPrimvarDescCache&) = delete;
    UsdImagingPrimvarDescCache& operator=(const UsdImagingPrimvarDescCache&)
        = delete;

    class Key
    {
        friend class UsdImagingPrimvarDescCache;
        SdfPath _path;
        TfToken _attribute;

     public:
        Key(SdfPath const& path, TfToken const& attr)
            : _path(path)
            , _attribute(attr)
        {}

        inline bool operator==(Key const& rhs) const {
            return _path == rhs._path && _attribute == rhs._attribute;
        }
        inline bool operator!=(Key const& rhs) const {
            return !(*this == rhs);
        }

        struct Hash {
            inline size_t operator()(Key const& key) const {
                size_t hash = key._path.GetHash();
                boost::hash_combine(hash, key._attribute.Hash());
                return hash;
            }
        };

    private:
        static Key Primvars(SdfPath const& path) {
            static TfToken attr("primvars");
            return Key(path, attr);
        }
    };

    UsdImagingPrimvarDescCache()
        : _locked(false)
    { }

private:
    template <typename Element>
    struct _TypedCache
    {
        typedef tbb::concurrent_unordered_map<Key, Element, Key::Hash> _MapType;
        typedef typename _MapType::iterator                            _MapIt;
        typedef typename _MapType::const_iterator                      _MapConstIt;
        typedef tbb::concurrent_queue<_MapIt>                          _QueueType;

        _MapType   _map;
        _QueueType _deferredDeleteQueue;
    };


    /// Locates the requested \p key then populates \p value and returns true if
    /// found.
    template <typename T>
    bool _Find(Key const& key, T* value) const {
        typedef _TypedCache<T> Cache_t;

        Cache_t *cache = nullptr;

        _GetCache(&cache);
        typename Cache_t::_MapConstIt it = cache->_map.find(key);
        if (it == cache->_map.end()) {
            return false;
        }
        *value = it->second;
        return true;
    }

    /// Locates the requested \p key then populates \p value, swap the value
    /// from the entry and queues the entry up for deletion.
    /// Returns true if found.
    /// This function is thread-safe, but Garbage collection must be called
    /// to perform the actual deletion.
    /// Note: second hit on same key will be sucessful, but return whatever
    /// value was passed into the first _Extract.
    template <typename T>
    bool _Extract(Key const& key, T* value) {
        if (!TF_VERIFY(!_locked)) {
            return false;
        }

        typedef _TypedCache<T> Cache_t;
        Cache_t *cache = nullptr;

        _GetCache(&cache);
        typename Cache_t::_MapIt it = cache->_map.find(key);

        if (it == cache->_map.end()) {
            return false;
        }

        // If we're going to erase the old value, swap to avoid a copy.
        std::swap(it->second, *value);
        cache->_deferredDeleteQueue.push(it);
        return true;
    }

    /// Erases the given key from the value cache.
    /// Not thread safe
    template <typename T>
    void _Erase(Key const& key) {
        if (!TF_VERIFY(!_locked)) {
            return;
        }

        typedef _TypedCache<T> Cache_t;

        Cache_t *cache = nullptr;
        _GetCache(&cache);
        cache->_map.unsafe_erase(key);
    }

    /// Returns a reference to the held value for \p key. Note that the entry
    /// for \p key will created with a default-constructed instance of T if
    /// there was no pre-existing entry.
    template <typename T>
    T& _Get(Key const& key) const {
        typedef _TypedCache<T> Cache_t;

        Cache_t *cache = nullptr;
        _GetCache(&cache);

        // With concurrent_unordered_map, multi-threaded insertion is safe.
        std::pair<typename Cache_t::_MapIt, bool> res =
                                cache->_map.insert(std::make_pair(key, T()));

        return res.first->second;
    }

    /// Removes items from the cache that are marked for deletion.
    /// This is not thread-safe and designed to be called after
    /// all the worker threads have been joined.
    template <typename T>
    void _GarbageCollect(_TypedCache<T> &cache) {
        typedef _TypedCache<T> Cache_t;

        typename Cache_t::_MapIt it;

        while (cache._deferredDeleteQueue.try_pop(it)) {
            cache._map.unsafe_erase(it);
        }
    }

public:

    void EnableMutation() { _locked = false; }
    void DisableMutation() { _locked = true; }

    /// Clear all data associated with a specific path.
    void Clear(SdfPath const& path) {
        _Erase<HdPrimvarDescriptorVector>(Key::Primvars(path));
    }

    HdPrimvarDescriptorVector& GetPrimvars(SdfPath const& path) const {
        return _Get<HdPrimvarDescriptorVector>(Key::Primvars(path));
    }

    bool FindPrimvars(SdfPath const& path, HdPrimvarDescriptorVector* value) const {
        return _Find(Key::Primvars(path), value);
    }

    bool ExtractPrimvars(SdfPath const& path, HdPrimvarDescriptorVector* value) {
        return _Extract(Key::Primvars(path), value);
    }

    /// Remove any items from the cache that are marked for defered deletion.
    void GarbageCollect()
    {
        _GarbageCollect(_pviCache);
    }

private:
    bool _locked;

    typedef _TypedCache<HdPrimvarDescriptorVector> _PviCache;
    mutable _PviCache _pviCache;

    void _GetCache(_PviCache **cache) const {
        *cache = &_pviCache;
    }
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_PRIMVARDESC_CACHE_H
