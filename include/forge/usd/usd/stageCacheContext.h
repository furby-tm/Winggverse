#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/stageCacheContext.h"
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
#ifndef FORGE_USD_USD_STAGE_CACHE_CONTEXT_H
#define FORGE_USD_USD_STAGE_CACHE_CONTEXT_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/base/tf/stacked.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


class UsdStageCache;

// Private helper wrapper class, holds a const reference to a stage cache.
struct Usd_NonPopulatingStageCacheWrapper {
    explicit Usd_NonPopulatingStageCacheWrapper(const UsdStageCache &cache)
        : cache(cache) {}
    const UsdStageCache &cache;
};

// Using a template arg for 'cache' in UsdUseButDoNotPopulateCache enforces
// lvalue requirement: rvalues will not bind to function template non-const
// reference parameters.

/// Indicate that a UsdStageCacheContext should be bound in a read-only fashion.
/// Calls to UsdStage::Open() will attempt to find stages in \p cache when a
/// UsdStageCacheContext is present on the stack.  See UsdStageCacheContext for
/// more details and example use.
template <class StageCache>
Usd_NonPopulatingStageCacheWrapper
UsdUseButDoNotPopulateCache(StageCache &cache) {
    return Usd_NonPopulatingStageCacheWrapper(cache);
}

enum UsdStageCacheContextBlockType
{
    /// Indicate that a UsdStageCacheContext should ignore all currently bound
    /// UsdStageCacheContexts, preventing reading from or writing to their
    /// UsdStageCaches.  See UsdStageCache for more details and example use.
    UsdBlockStageCaches,
    /// Indicate that a UsdStageCacheContext should ignore all currently bound
    /// writable UsdStageCacheContexts, writing to their UsdStageCaches.  See
    /// UsdStageCache for more details and example use.
    UsdBlockStageCachePopulation,

    Usd_NoBlock
};

/// \class UsdStageCacheContext
///
/// A context object that lets the UsdStage::Open() API read from or read
/// from and write to a UsdStageCache instance during a scope of execution.
///
/// Code examples illustrate typical use:
/// \code
/// {
///     // A stage cache to work with.
///     UsdStageCache stageCache;
///
///     // Bind this cache.  UsdStage::Open() will attempt to find a matching
///     // stage in the cache.  If none is found, it will open a new stage and
///     // insert it into the cache.
///     UsdStageCacheContext context(stageCache);
///
///     // Since the cache is currently empty, this Open call will not find an
///     // existing stage in the cache, but will insert the newly opened stage
///     // in it.
///     auto stage = UsdStage::Open(<args>);
///
///     assert(stageCache.Contains(stage));
///
///     // A subsequent Open() call with the same arguments will retrieve the
///     // stage from cache.
///     auto stage2 = UsdStage::Open(<args>);
///     assert(stage2 == stage);
/// }
/// \endcode
///
/// The UsdStage::Open() API examines caches in UsdStageCacheContexts that exist
/// on the stack in the current thread in order starting with the most recently
/// created (deepest in the stack) to the least recently created.
///
/// The UsdUseButDoNotPopulateCache() function makes a cache available for
/// UsdStage::Open() to find stages in, but newly opened stages will not be
/// published to it.  This can be useful if you want to make use of a cache but
/// cannot or do not wish to mutate that cache.
///
/// Passing UsdBlockStageCaches disables cache use entirely (as if no
/// UsdStageCacheContexts exist on the stack), while
/// UsdBlockStageCachePopulation disables writing to all bound caches (as if
/// they were all established with UsdUseButDoNotPopulateCache()).
///
/// Threading note: Different threads have different call stacks, so
/// UsdStageCacheContext objects that exist in one thread's stack do not
/// influence calls to UsdStage::Open() from a different thread.
///
TF_DEFINE_STACKED(UsdStageCacheContext, true, USD_API)
{
public:
    /// Bind a cache for calls to UsdStage::Open() to read from and write to.
    explicit UsdStageCacheContext(UsdStageCache &cache)
        : _rwCache(&cache)
        , _isReadOnlyCache(false)
        , _blockType(Usd_NoBlock) {}

    /// Bind a cache for calls to UsdStage::Open() to read from.
    /// \see UsdUseButDoNotPopulateCache()
    explicit UsdStageCacheContext(Usd_NonPopulatingStageCacheWrapper holder)
        : _roCache(&holder.cache)
        , _isReadOnlyCache(true)
        , _blockType(Usd_NoBlock) {}

    /// Disable cache use completely (with UsdBlockStageCaches) or only
    /// for writing (with UsdBlockStageCacheWrites).
    explicit UsdStageCacheContext(UsdStageCacheContextBlockType blockType)
        : _blockType(blockType) {}

private:
    friend class UsdStage;

    static std::vector<const UsdStageCache *> _GetReadOnlyCaches();
    static std::vector<const UsdStageCache *> _GetReadableCaches();
    static std::vector<UsdStageCache *> _GetWritableCaches();

    // A blocking context is encoded with both members variables null.
    union {
        UsdStageCache *_rwCache;
        const UsdStageCache *_roCache;
    };
    bool _isReadOnlyCache;
    UsdStageCacheContextBlockType _blockType;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_STAGE_CACHE_CONTEXT_H
