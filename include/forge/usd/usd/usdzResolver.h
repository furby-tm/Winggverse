#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/usdzResolver.h"
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
#ifndef FORGE_USD_USD_USDZ_RESOLVER_H
#define FORGE_USD_USD_USDZ_RESOLVER_H

#include "forge/forge.h"
#include "forge/usd/ar/packageResolver.h"
#include "forge/usd/ar/threadLocalScopedCache.h"
#include "forge/usd/usd/zipFile.h"

FORGE_NAMESPACE_BEGIN

class ArAsset;

/// \class Usd_UsdzResolver
///
/// Package resolver responsible for resolving assets in
/// .usdz files.
class Usd_UsdzResolver
    : public ArPackageResolver
{
public:
    Usd_UsdzResolver();

    virtual std::string Resolve(
        const std::string& packagePath,
        const std::string& packagedPath) override;

    virtual std::shared_ptr<ArAsset> OpenAsset(
        const std::string& packagePath,
        const std::string& packagedPath) override;

    virtual void BeginCacheScope(
        VtValue* cacheScopeData) override;

    virtual void EndCacheScope(
        VtValue* cacheScopeData) override;
};

/// \class Usd_UsdzResolverCache
///
/// Singleton thread-local scoped cache used by Usd_UsdzResolver. This
/// allows other clients besides Usd_UsdzResolver to take advantage of
/// caching of zip files while a resolver scoped cache is active.
class Usd_UsdzResolverCache
{
public:
    static Usd_UsdzResolverCache& GetInstance();

    Usd_UsdzResolverCache(const Usd_UsdzResolverCache&) = delete;
    Usd_UsdzResolverCache& operator=(const Usd_UsdzResolverCache&) = delete;

    using AssetAndZipFile = std::pair<std::shared_ptr<ArAsset>, UsdZipFile>;

    /// Returns the ArAsset and UsdZipFile for the given package path.
    /// If a cache scope is active in the current thread, the returned
    /// values will be cached and returned on subsequent calls to this
    /// function for the same packagePath.
    AssetAndZipFile FindOrOpenZipFile(
        const std::string& packagePath);

    /// Open a cache scope in the current thread. While a cache scope
    /// is opened, the results of FindOrOpenZipFile will be cached and
    /// reused.
    void BeginCacheScope(
        VtValue* cacheScopeData);

    /// Close cache scope in the current thread. Once all cache scopes
    /// in the current thread are closed, cached zip files will be
    /// dropped.
    void EndCacheScope(
        VtValue* cacheScopeData);

private:
    Usd_UsdzResolverCache();

    struct _Cache;
    using _ThreadLocalCaches = ArThreadLocalScopedCache<_Cache>;
    using _CachePtr = _ThreadLocalCaches::CachePtr;
    _CachePtr _GetCurrentCache();

    AssetAndZipFile _OpenZipFile(const std::string& packagePath);

    _ThreadLocalCaches _caches;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_USDZ_RESOLVER_H
