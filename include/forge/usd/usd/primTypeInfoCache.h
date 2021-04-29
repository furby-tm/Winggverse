#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/primTypeInfoCache.h"
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
#ifndef FORGE_USD_USD_PRIM_TYPE_INFO_CACHE_H
#define FORGE_USD_USD_PRIM_TYPE_INFO_CACHE_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/primTypeInfo.h"
#include "forge/base/tf/token.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_hash_map.h>
#endif /* Q_MOC_RUN */

FORGE_NAMESPACE_BEGIN

// Private class to be used as a singleton by UsdStage to cache the type info
// structures for all distinct prim types used by any prim data.
class Usd_PrimTypeInfoCache {
public:
    using TypeId = UsdPrimTypeInfo::_TypeId;

    Usd_PrimTypeInfoCache()
        : _emptyPrimTypeInfo(&UsdPrimTypeInfo::GetEmptyPrimType()) {}

    // Non-copyable
    Usd_PrimTypeInfoCache(const Usd_PrimTypeInfoCache&) = delete;
    Usd_PrimTypeInfoCache &operator=(const Usd_PrimTypeInfoCache&) = delete;

    // Finds the cached prim type info for the given full prim type ID,
    // creating and caching a new one if it doesn't exist.
    const UsdPrimTypeInfo *FindOrCreatePrimTypeInfo(TypeId &&primTypeId)
    {
        if (primTypeId.IsEmpty()) {
            return GetEmptyPrimTypeInfo();
        }

        if (auto primTypeInfo = _primTypeInfoMap.Find(primTypeId)) {
            return primTypeInfo;
        }

        // If it's not, create the new type info first and then try to insert
        // it. We always return the value found in the cache which may not be
        // the type info we created if another thread happened to create the
        // same type info and managed to insert it first. In that case ours just
        // gets deleted since the hash map didn't take ownership.
        std::unique_ptr<UsdPrimTypeInfo> newPrimTypeInfo(
            new UsdPrimTypeInfo(std::move(primTypeId)));
        return _primTypeInfoMap.Insert(std::move(newPrimTypeInfo));
    }

    // Return the single empty prim type info
    const UsdPrimTypeInfo *GetEmptyPrimTypeInfo() const
    {
        return _emptyPrimTypeInfo;
    }

    // Computes a mapping of invalid prim type name to its valid fallback
    // type name from the provided fallback prim types dictionary.
    void ComputeInvalidPrimTypeToFallbackMap(
        const VtDictionary &fallbackPrimTypesDict,
        TfHashMap<TfToken, TfToken, TfHash> *typeToFallbackTypeMap);

private:
    // Wrapper around the thread safe hash map implementation used by the
    // Usd_PrimTypeInfoCache to cache prim type info
    class _ThreadSafeHashMapImpl {
    public:
        _ThreadSafeHashMapImpl() = default;
        _ThreadSafeHashMapImpl(const _ThreadSafeHashMapImpl&) = delete;

        using KeyType = TypeId;
        using ValueTypePtr = std::unique_ptr<UsdPrimTypeInfo>;

        // Find and return a pointer to the prim type info if it already exists.
        const UsdPrimTypeInfo *Find(const KeyType &key) const
        {
            _HashMap::const_accessor accessor;
            if (_hashMap.find(accessor, key)) {
                return accessor->second.get();
            }
            return nullptr;
        }

        // Inserts and takes ownership of the prim type info only if it isn't
        // already in the hash map. Returns the pointer to the value in the map
        // after insertion regardless.
        const UsdPrimTypeInfo *Insert(ValueTypePtr &&valuePtr)
        {
            const KeyType &key = valuePtr->_GetTypeId();
            _HashMap::accessor accessor;
            if (_hashMap.insert(accessor, key)) {
                accessor->second = std::move(valuePtr);
            }
            return accessor->second.get();
        }

    private:
        struct _TbbHashFunc {
            inline bool equal(const KeyType &l, const KeyType &r) const {
                return l == r;
            }
            inline size_t hash(const KeyType &t) const {
                return t.Hash();
            }
        };

        using _HashMap =
            tbb::concurrent_hash_map<KeyType, ValueTypePtr, _TbbHashFunc>;
        _HashMap _hashMap;
    };

    _ThreadSafeHashMapImpl _primTypeInfoMap;
    const UsdPrimTypeInfo *_emptyPrimTypeInfo;
};

FORGE_NAMESPACE_END

#endif //FORGE_USD_USD_PRIM_TYPE_INFO_CACHE_H
