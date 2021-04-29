#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/resolverContextBinder.h"
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
#ifndef FORGE_USD_AR_RESOLVER_CONTEXT_BINDER_H
#define FORGE_USD_AR_RESOLVER_CONTEXT_BINDER_H

/// \file ar/resolverContextBinder.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/usd/ar/resolverContext.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

class ArResolver;

/// \class ArResolverContextBinder
///
/// Helper object for managing the binding and unbinding of
/// ArResolverContext objects with the asset resolver.
///
/// \see \ref ArResolver_context "Asset Resolver Context Operations"
class ArResolverContextBinder
{
public:
    /// Bind the given \p context with the asset resolver.
    ///
    /// Calls ArResolver::BindContext on the configured asset resolver
    /// and saves the bindingData populated by that function.
    AR_API
    ArResolverContextBinder(
        const ArResolverContext& context);

    /// Bind the given \p context to the given \p assetResolver.
    ///
    /// Calls ArResolver::BindContext on the given \p assetResolver
    /// and saves the bindingData populated by that function.
    AR_API
    ArResolverContextBinder(
        ArResolver* assetResolver,
        const ArResolverContext& context);

    /// Unbinds the context specified in the constructor of this
    /// object from the asset resolver.
    ///
    /// Calls ArResolver::UnbindContext on the asset resolver that was
    /// bound to originally, passing the saved bindingData to that function.
    AR_API
    ~ArResolverContextBinder();

private:
    ArResolver* _resolver;
    ArResolverContext _context;
    VtValue _bindingData;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_RESOLVER_CONTEXT_BINDER_H
