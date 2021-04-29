#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/instanceRegistry.h"
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
#ifndef FORGE_IMAGING_HD_INSTANCE_REGISTRY_H
#define FORGE_IMAGING_HD_INSTANCE_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hf/perfLog.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_unordered_map.h>
#endif /* Q_MOC_RUN */

#include <memory>
#include <mutex>

FORGE_NAMESPACE_BEGIN


/// \class HdInstance
///
/// This class is used as an interface to a shared instance in
/// HdInstanceRegistry.
///
/// KeyType is a hashable index type and VALUE is shared_ptr. In most use
/// cases, the client computes a hash key which represents large bulky data
/// (like topology, primvars) and registers it into HdInstanceRegistry. If the
/// key has already been registered, the registry returns HdInstance and the
/// client can use GetValue() without setting/computing actual bulky data. If
/// it doesn't exist, IsFirstInstance() returns true for the first instance
/// and the client needs to populate an appropriate data VALUE into the
/// instance by SetValue().
///
/// In order to support concurrent access to HdInstanceRegistry, this
/// class holds a lock to a mutex in HdInstanceRegistry. This lock will
/// be held until the instance of this interface class is destroyed.
///
template <typename VALUE>
class HdInstance {
public:
    typedef uint64_t KeyType;
    typedef VALUE ValueType;

    typedef KeyType ID;

    struct ValueHolder {
        ValueHolder(ValueType const & value = ValueType())
            : value(value)
            , recycleCounter(0)
        { }
        void ResetRecycleCounter() {
            recycleCounter = 0;
        }

        ValueType value;
        int recycleCounter;
    };
    typedef tbb::concurrent_unordered_map<KeyType, ValueHolder> Dictionary;

    typedef std::mutex RegistryMutex;
    typedef std::unique_lock<RegistryMutex> RegistryLock;

    HdInstance() = delete;

    /// Construct an instance holding a registry lock, representing a value
    /// held in a registry container.
    explicit HdInstance(KeyType const &key,
                        ValueType const &value,
                        RegistryLock &&registryLock,
                        Dictionary *container)
        : _key(key)
        , _value(value)
        , _registryLock(std::move(registryLock))
        , _container(container)
        , _isFirstInstance(!bool(_value))
    { }

    /// Construct an instance with no lock or registry container. This
    /// is used to present a consistent interface to clients in cases
    /// where shared resource registration is disabled.
    explicit HdInstance(KeyType const &key)
        : _key(key)
        , _value(ValueType())
        , _registryLock()
        , _container(nullptr)
        , _isFirstInstance(!bool(_value))
    { }

    /// Returns the key
    KeyType const &GetKey() const { return _key; }

    /// Returns the value
    ValueType const &GetValue() const { return _value; }

    /// Update the value in dictionary indexed by the key.
    void SetValue(ValueType const &value) {
        if (_container) (*_container)[_key] = ValueHolder(value);
        _value = value;
    }

    /// Returns true if the value has not been initialized.
    bool IsFirstInstance() const {
        return _isFirstInstance;
    }

private:
    KeyType       _key;
    ValueType     _value;
    RegistryLock  _registryLock;
    Dictionary   *_container;
    bool          _isFirstInstance;
};

/// \class HdInstanceRegistry
///
/// HdInstanceRegistry is a dictionary container of HdInstance.
/// This class is almost just a dictionary from key to value.
/// For cleaning unused entries, it provides GarbageCollect() API.
/// It sweeps all entries in the dictionary and erase unreferenced entries.
/// When HdInstance::ValueType is shared_ptr, it is regarded as unreferenced
/// if the shared_ptr is unique (use_count==1). Note that Key is not
/// involved to determine the lifetime of entries.
///
template <typename VALUE>
class HdInstanceRegistry {
public:
    typedef HdInstance<VALUE> InstanceType;

    HdInstanceRegistry() = default;

    /// Copy constructor.  Need as HdInstanceRegistry is placed in a map
    /// and mutex is not copy constructable, so can't use default
    HdInstanceRegistry(const HdInstanceRegistry &other)
        : _dictionary(other._dictionary)
        , _registryMutex()  // mutex is not copied
    { }

    /// Returns a shared instance for given key.
    InstanceType GetInstance(
        typename InstanceType::KeyType const &key);

    /// Returns a shared instance for a given key
    /// only if the key exists in the dictionary.
    InstanceType FindInstance(
        typename InstanceType::KeyType const &key, bool *found);

    /// Removes unreferenced entries and returns the count
    /// of remaining entries. When recycleCount is greater than zero,
    /// unreferenced entries will not be removed until GarbageCollect() is
    /// called that many more times, i.e. allowing unreferenced entries to
    /// be recycled if they are needed again.
    size_t GarbageCollect(int recycleCount = 0);

    /// Returns a const iterator being/end of dictionary. Mainly used for
    /// resource auditing.
    typedef typename InstanceType::Dictionary::const_iterator const_iterator;
    const_iterator begin() const { return _dictionary.begin(); }
    const_iterator end() const { return _dictionary.end(); }

    size_t size() const { return _dictionary.size(); }

    void Invalidate();

private:
    template <typename T>
    static bool _IsUnique(std::shared_ptr<T> const &value) {
        return value.unique();
    }

    typename InstanceType::Dictionary _dictionary;
    typename InstanceType::RegistryMutex _registryMutex;

    HdInstanceRegistry &operator =(HdInstanceRegistry &) = delete;
};

// ---------------------------------------------------------------------------
// instance registry impl

template <typename VALUE>
HdInstance<VALUE>
HdInstanceRegistry<VALUE>::GetInstance(
        typename HdInstance<VALUE>::KeyType const &key)
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    // Grab Registry lock
    // (and don't release it in this function, return it instead)
    typename InstanceType::RegistryLock lock(_registryMutex);

    typename InstanceType::Dictionary::iterator it = _dictionary.find(key);
    if (it == _dictionary.end()) {
        // not found. create new one
        it = _dictionary.insert(
            std::make_pair(key, typename InstanceType::ValueHolder())).first;
    }

    it->second.ResetRecycleCounter();
    return InstanceType(key, it->second.value, std::move(lock), &_dictionary);
}

template <typename VALUE>
HdInstance<VALUE>
HdInstanceRegistry<VALUE>::FindInstance(
        typename HdInstance<VALUE>::KeyType const &key, bool *found)
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    // Grab Registry lock
    // (and don't release it in this function, return it instead)
    typename InstanceType::RegistryLock lock(_registryMutex);

    typename InstanceType::Dictionary::iterator it = _dictionary.find(key);
    if (it == _dictionary.end()) {
        *found = false;
        return InstanceType(key, VALUE(), std::move(lock), nullptr);
    } else {
        *found = true;
        it->second.ResetRecycleCounter();
        return InstanceType(key, it->second.value,std::move(lock),&_dictionary);
    }
}

template <typename VALUE>
size_t
HdInstanceRegistry<VALUE>::GarbageCollect(int recycleCount)
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    // Skip garbage collection entirely when then the recycleCount is < 0
    if (recycleCount < 0) {
        return _dictionary.size();
    }

    size_t inUseCount = 0;
    for (typename InstanceType::Dictionary::iterator it = _dictionary.begin();
         it != _dictionary.end();) {

        // erase instance which isn't referred from anyone
        bool isUnique = _IsUnique(it->second.value);
        if (isUnique && (++it->second.recycleCounter > recycleCount)) {
            it = _dictionary.unsafe_erase(it);
        } else {
            ++it;
            ++inUseCount;
        }
    }
    return inUseCount;
}

template <typename VALUE>
void
HdInstanceRegistry<VALUE>::Invalidate()
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    _dictionary.clear();
}


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_INSTANCE_REGISTRY_H
