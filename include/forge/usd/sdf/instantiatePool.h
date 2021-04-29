#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/instantiatePool.h"
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
/*
 * This header is not meant to be included in a .h file.
 * Complain if we see this header twice through.
 */

#ifdef FORGE_USD_SDF_INSTANTIATE_POOL_H
#error This file should only be included once in any given source (.cpp) file.
#endif

#define FORGE_USD_SDF_INSTANTIATE_POOL_H

#include "forge/forge.h"
#include "forge/usd/sdf/pool.h"

FORGE_NAMESPACE_BEGIN

// Helper to reserve a region of virtual address space.
SDF_API char *
Sdf_PoolReserveRegion(size_t numBytes);

// Helper to commit and make read/writable a range of bytes from
// Sdf_PoolReserveRegion.
SDF_API bool
Sdf_PoolCommitRange(char *start, char *end);

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
typename Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_ThreadData
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_threadData;

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
char *
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_regionStarts[NumRegions+1];

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
std::atomic<typename Sdf_Pool<
                Tag, ElemSize, RegionBits, ElemsPerSpan>::_RegionState>
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_regionState;

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
TfStaticData<tbb::concurrent_queue<
    typename Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_FreeList>>
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_sharedFreeLists;


template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
typename Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_RegionState
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_RegionState::
Reserve(unsigned num) const
{
    // Make a new state.  If reserving \p num leaves no free elements, then
    // return the LockedState, since a new region will need to be allocated.
    uint32_t index = GetIndex();
    unsigned region = GetRegion();
    uint32_t avail = MaxIndex - index + 1;
    _RegionState ret;
    if (ARCH_UNLIKELY(avail <= num)) {
        ret._state = LockedState;
    }
    else {
        ret = _RegionState(region, index + num);
    }
    return ret;
}

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
typename Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::Handle
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::Allocate()
{
    _PerThreadData &threadData = _threadData.Get();

    // Check local free-list, or try to take a shared one.
    Handle alloc = threadData.freeList.head;
    if (alloc) {
        threadData.freeList.Pop();
    }
    else if (!threadData.span.empty()) {
        // Allocate new from local span.
        alloc = threadData.span.Alloc();
    }
    else if (_TakeSharedFreeList(threadData.freeList)) {
        // Nothing local.  Try to take a shared free list.
        alloc = threadData.freeList.head;
        threadData.freeList.Pop();
    }
    else {
        // No shared free list -- reserve a new span and allocate from it.
        _ReserveSpan(threadData.span);
        alloc = threadData.span.Alloc();
    }
    return alloc;
}

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
void
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::Free(Handle h)
{
    _PerThreadData &threadData = _threadData.Get();

    // Add to local free list.
    threadData.freeList.Push(h);

    // If our free list is big share the free list for use by other threads.
    if (threadData.freeList.size >= ElemsPerSpan) {
        _ShareFreeList(threadData.freeList);
    }
}

template <class Tag,
          unsigned ElemSize, unsigned RegionBits, unsigned ElemsPerSpan>
void
Sdf_Pool<Tag, ElemSize, RegionBits, ElemsPerSpan>::_ReserveSpan(_PoolSpan &out)
{
    // Read current state.  The state will either be locked, or will have
    // some remaining space available.
    _RegionState state = _regionState.load(std::memory_order_relaxed);
    _RegionState newState;

    // If we read the "init" state, which is region=0, index=0, then try to
    // move to the locked state.  If we take it, then do the initialization
    // and unlock.  If we don't take it, then someone else has done it or is
    // doing it, so we just continue.
    if (state == _RegionState::GetInitState()) {
        // Try to lock.
        newState = _RegionState::GetLockedState();
        if (_regionState.compare_exchange_strong(state, newState)) {
            // We took the lock to initialize.  Create the first region and
            // unlock.  Indexes start at 1 to avoid hash collisions when
            // multiple pool indexes are combined in a single hash.
            _regionStarts[1] =
                Sdf_PoolReserveRegion(ElemsPerRegion * ElemSize);
            _regionState = state = _RegionState(1, 1);
        }
    }

    while (true) {
        // If we're locked, just wait and retry.
        if (ARCH_UNLIKELY(state.IsLocked())) {
            std::this_thread::yield();
            state = _regionState.load(std::memory_order_relaxed);
            continue;
        }

        // Try to take space for the span.  If this would consume all
        // remaining space, try to lock and allocate the next span.
        newState = state.Reserve(ElemsPerSpan);

        if (_regionState.compare_exchange_weak(state, newState)) {
            // We allocated our span.
            break;
        }
    }

    // Now newState is either a normal region & index, or is locked for
    // allocation.  If locked, then allocate a new region and update
    // _regionState.
    if (newState.IsLocked()) {
        // Allocate the next region, or die if out of regions...
        unsigned newRegion = state.GetRegion() + 1;
        if (ARCH_UNLIKELY(newRegion > NumRegions)) {
            TF_FATAL_ERROR("Out of memory in '%s'.",
                           ArchGetDemangled<Sdf_Pool>().c_str());
        }
        _regionStarts[newRegion] =
            Sdf_PoolReserveRegion(ElemsPerRegion * ElemSize);
        // Set the new state accordingly, and unlock.  Indexes start at 1 to
        // avoid hash collisions when multiple pool indexes are combined in
        // a single hash.
        newState = _RegionState(newRegion, 1);
        _regionState.store(newState);
    }

    // Now our span space is indicated by state & newState.  Update the
    // \p out span and ensure the span space is committed (think
    // mprotect(PROT_READ | PROT_WRITE) on posixes.
    out.region = state.GetRegion();
    out.beginIndex = state.GetIndex();
    out.endIndex = newState.GetRegion() == out.region ?
        newState.GetIndex() : MaxIndex;

    // Ensure the new span is committed & read/writable.
    char *startAddr = _GetPtr(out.region, out.beginIndex);
    char *endAddr = _GetPtr(out.region, out.endIndex);
    Sdf_PoolCommitRange(startAddr, endAddr);
}

// Source file definition of an Sdf_Pool instantiation.
#define SDF_INSTANTIATE_POOL(Tag, ElemSize, RegionBits)        \
    template class FORGE_NS_GLOBAL::Sdf_Pool<Tag, ElemSize, RegionBits>


FORGE_NAMESPACE_END
