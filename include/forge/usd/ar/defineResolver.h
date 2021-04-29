#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/defineResolver.h"
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
#ifndef FORGE_USD_AR_DEFINE_RESOLVER_H
#define FORGE_USD_AR_DEFINE_RESOLVER_H

/// \file ar/defineResolver.h
/// Macros for defining a custom resolver implementation.

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/usd/ar/resolver.h"

#include "forge/base/tf/registryManager.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

/// \def AR_DEFINE_RESOLVER
///
/// Performs registrations required for the specified resolver class
/// to be discovered by Ar's plugin mechanism. This typically would be
/// invoked in the source file defining the resolver class. For example:
///
/// \code
/// // in .cpp file
/// AR_DEFINE_RESOLVER(CustomResolverClass, ArResolver);
/// \endcode
#ifdef doxygen
#define AR_DEFINE_RESOLVER(ResolverClass, BaseClass1, ...)
#else
#define AR_DEFINE_RESOLVER(...)       \
TF_REGISTRY_FUNCTION(TfType) {        \
    Ar_DefineResolver<__VA_ARGS__>(); \
}
#endif // doxygen

class Ar_ResolverFactoryBase
    : public TfType::FactoryBase
{
public:
    AR_API
    virtual ArResolver* New() const = 0;
};

template <class T>
class Ar_ResolverFactory
    : public Ar_ResolverFactoryBase
{
public:
    virtual ArResolver* New() const override
    {
        return new T;
    }
};

template <class Resolver, class ...Bases>
void Ar_DefineResolver()
{
    TfType::Define<Resolver, TfType::Bases<Bases...>>()
        .template SetFactory<Ar_ResolverFactory<Resolver> >();
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_DEFINE_RESOLVER_H
