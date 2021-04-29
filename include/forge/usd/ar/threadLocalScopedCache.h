#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/threadLocalScopedCache.h"
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
#ifndef FORGE_USD_AR_THREAD_LOCAL_SCOPED_CACHE_H
#define FORGE_USD_AR_THREAD_LOCAL_SCOPED_CACHE_H

#include "forge/forge.h"
#include "forge/usd/ar/api.h"

#include "forge/base/vt/value.h"
#include "forge/base/tf/diagnostic.h"

#if !defined(Q_MOC_RUN)
# include <tbb/enumerable_thread_specific.h>
#endif /* Q_MOC_RUN */

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class ArThreadLocalScopedCache
///
/// Utility class for custom resolver implementations. This class wraps up
/// a common pattern for implementing thread-local scoped caches for
/// ArResolver::BeginCacheScope and ArResolver::EndCacheScope.
///
/// \code{.cpp}
/// class MyResolver : public ArResolver {
///     using ResolveCache = ArThreadLocalScopedCache<...>;
///     ResolveCache _cache;
///
///     void BeginCacheScope(VtValue* data) { _cache.BeginCacheScope(data); }
///     void EndCacheScope(VtValue* data) { _cache.EndCacheScope(data); }
///     void Resolve(...) {
///         // If caching is active in this thread, retrieve the current
///         // cache and use it to lookup/store values.
///         if (ResolveCache::CachePtr cache = _cache.GetCurrentCache()) {
///             // ...
///         }
///         // Otherwise, caching is not active
///         // ...
///    }
/// };
/// \endcode
///
/// \see \ref ArResolver_scopedCache "Scoped Resolution Cache"
template <class CachedType>
class ArThreadLocalScopedCache
{
public:
    using CachePtr = std::shared_ptr<CachedType>;

    void BeginCacheScope(VtValue* cacheScopeData)
    {
        // Since this is intended to be used by ArResolver implementations,
        // we expect cacheScopeData to never be NULL and to either be empty
        // or holding a cache pointer that we've filled in previously.
        if (!cacheScopeData ||
            (!cacheScopeData->IsEmpty() &&
             !cacheScopeData->IsHolding<CachePtr>())) {
            TF_CODING_ERROR("Unexpected cache scope data");
            return;
        }

        _CachePtrStack& cacheStack = _threadCacheStack.local();
        if (cacheScopeData->IsHolding<CachePtr>()) {
            cacheStack.push_back(cacheScopeData->UncheckedGet<CachePtr>());
        }
        else {
            if (cacheStack.empty()) {
                cacheStack.push_back(std::make_shared<CachedType>());
            }
            else {
                cacheStack.push_back(cacheStack.back());
            }
        }
        *cacheScopeData = cacheStack.back();
    }

    void EndCacheScope(VtValue* cacheScopeData)
    {
        _CachePtrStack& cacheStack = _threadCacheStack.local();
        if (TF_VERIFY(!cacheStack.empty())) {
            cacheStack.pop_back();
        }
    }

    CachePtr GetCurrentCache()
    {
        _CachePtrStack& cacheStack = _threadCacheStack.local();
        return (cacheStack.empty() ? CachePtr() : cacheStack.back());
    }

private:
    using _CachePtrStack = std::vector<CachePtr>;
    using _ThreadLocalCachePtrStack =
        tbb::enumerable_thread_specific<_CachePtrStack>;
    _ThreadLocalCachePtrStack _threadCacheStack;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_THREAD_LOCAL_SCOPED_CACHE_H
