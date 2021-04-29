#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/resolverScopedCache.h"
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
#ifndef FORGE_USD_AR_RESOLVER_SCOPED_CACHE_H
#define FORGE_USD_AR_RESOLVER_SCOPED_CACHE_H

/// \file ar/resolverScopedCache.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

/// \class ArResolverScopedCache
///
/// Helper object for managing asset resolver cache scopes.
///
/// A scoped resolution cache indicates to the resolver that results of
/// calls to Resolve should be cached for a certain scope. This is
/// important for performance and also for consistency -- it ensures
/// that repeated calls to Resolve with the same parameters will
/// return the same result.
///
/// \see \ref ArResolver_scopedCache "Scoped Resolution Cache"
class ArResolverScopedCache
{
public:

    // Disallow copies
    ArResolverScopedCache(const ArResolverScopedCache&) = delete;
    ArResolverScopedCache& operator=(const ArResolverScopedCache&) = delete;

    /// Begin an asset resolver cache scope.
    ///
    /// Calls ArResolver::BeginCacheScope on the configured asset resolver
    /// and saves the cacheScopeData populated by that function.
    AR_API
    ArResolverScopedCache();

    /// Begin an asset resolver cache scope that shares data
    /// with the given \p parent scope.
    ///
    /// Calls ArResolver::BeginCacheScope on the configured asset resolver,
    /// saves the cacheScopeData stored in \p parent and passes that to that
    /// function.
    AR_API
    explicit ArResolverScopedCache(const ArResolverScopedCache* parent);

    /// End an asset resolver cache scope.
    ///
    /// Calls ArResolver::EndCacheScope on the configured asset resolver,
    /// passing the saved cacheScopeData to that function.
    AR_API
    ~ArResolverScopedCache();

private:
    VtValue _cacheScopeData;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_RESOLVER_SCOPED_CACHE_H
