#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/bufferArrayRegistry.h"
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
#ifndef FORGE_IMAGING_HD_BUFFER_ARRAY_REGISTRY_H
#define FORGE_IMAGING_HD_BUFFER_ARRAY_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"

#include "forge/imaging/hd/bufferArrayRange.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/strategyBase.h"

#include "forge/imaging/hf/perfLog.h"

#include "forge/base/vt/dictionary.h"
#include "forge/base/tf/token.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_unordered_map.h>
#endif /* Q_MOC_RUN */

#include <condition_variable>
#include <memory>
#include <mutex>

FORGE_NAMESPACE_BEGIN


using HdBufferArraySharedPtr = std::shared_ptr<class HdBufferArray>;

/// \class HdBufferArrayRegistry
///
/// Manages the pool of buffer arrays.
///
class HdBufferArrayRegistry
{
public:
    HF_MALLOC_TAG_NEW("new HdBufferArrayRegistry");

    HD_API
    HdBufferArrayRegistry();
    ~HdBufferArrayRegistry()   = default;

    /// Allocate new buffer array range using strategy
    /// Thread-Safe
    HD_API
    HdBufferArrayRangeSharedPtr AllocateRange(
        HdAggregationStrategy *strategy,
        TfToken const &role,
        HdBufferSpecVector const &bufferSpecs,
        HdBufferArrayUsageHint usageHint);

    /// Triggers reallocation on all buffers managed by the registry.
    HD_API
    void   ReallocateAll(HdAggregationStrategy *strategy);

    /// Frees up buffers that no longer contain any allocated ranges.
    HD_API
    void   GarbageCollect();

    /// Generate a report on resources consumed by the managed
    /// buffer array.  The returned size is an esitmate of the
    /// gpu memory consumed by the buffers
    HD_API
    size_t GetResourceAllocation(HdAggregationStrategy *strategy,
                                 VtDictionary &result) const;

    /// Debug dump
    HD_API
    friend std::ostream &operator <<(std::ostream &out,
                                     const HdBufferArrayRegistry& self);

private:

    HdBufferArrayRegistry(const HdBufferArrayRegistry &) = delete;
    HdBufferArrayRegistry &operator=(const HdBufferArrayRegistry &) = delete;

    typedef std::list<HdBufferArraySharedPtr> _HdBufferArraySharedPtrList;

    /// \struct _Entry
    ///
    /// Entry in the buffer array cache.  The list is the buffer arrays which
    /// all have the same format.  There is as a lock for modifications to the
    /// entry and a condition used to determine if the entry has been
    /// construction.
    ///
    /// A constructed entry always has at least 1 buffer array in its list.
    ///
    struct _Entry
    {
        _HdBufferArraySharedPtrList bufferArrays;
        std::mutex                  lock;
        std::condition_variable     emptyCondition;

        // Default / Copy constructors needed for std::make_pair.
        // as the version of TBB doesn't have emplace() yet.
        _Entry() {}
        _Entry(const _Entry &other) { TF_VERIFY(bufferArrays.empty()); }
    };


    /// Predicate class for determine if an entry
    /// has been consturcted (determined by there
    /// being at least 1 entry in the buffer array list.
    class _EntryIsNotEmpty
    {
    public:
        _EntryIsNotEmpty(const _Entry &entry) : _entry(entry) {}

        bool operator()() {
            return (!(_entry.bufferArrays.empty()));
        }

    private:
        const _Entry &_entry;
    };

    typedef tbb::concurrent_unordered_map< HdAggregationStrategy::AggregationId, _Entry> _BufferArrayIndex;

    _BufferArrayIndex _entries;

    /// Concurrently adds a new buffer to an entry in the cache.
    /// If expectedTail differs from the buffer at the end of the
    /// entries list after locking, then this function fails and
    /// does not add a new buffer (because another thread beat it
    /// to it).
    /// strategy is the factory class used to create the BufferArray.
    /// role and bufferSpecs are parameters to the BufferArray creation.
    void _InsertNewBufferArray(_Entry &entry,
                               const HdBufferArraySharedPtr &expectedTail,
                               HdAggregationStrategy *strategy,
                               TfToken const &role,
                               HdBufferSpecVector const &bufferSpecs,
                               HdBufferArrayUsageHint usageHint);
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_BUFFER_ARRAY_REGISTRY_H
