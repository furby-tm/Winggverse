#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/defaultResolverContext.h"
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
#ifndef FORGE_USD_AR_DEFAULT_RESOLVER_CONTEXT_H
#define FORGE_USD_AR_DEFAULT_RESOLVER_CONTEXT_H

/// \file ar/defaultResolverContext.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/usd/ar/defineResolverContext.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class ArDefaultResolverContext
///
/// Resolver context object that specifies a search path to use during
/// asset resolution. This object is intended for use with the default
/// ArDefaultResolver asset resolution implementation; see documentation for
/// that class for more details on the search path resolution algorithm.
///
/// Example usage:
/// \code
/// ArDefaultResolverContext ctx({"/Local/Models", "/Installed/Models"});
/// {
///     // Bind the context object:
///     ArResolverContextBinder binder(ctx);
///
///    // While the context is bound, all calls to ArResolver::Resolve
///    // (assuming ArDefaultResolver is the underlying implementation being
///    // used) will include the specified paths during resolution.
///    std::string resolvedPath = resolver.Resolve("ModelName/File.txt")
/// }
///
/// // Once the context is no longer bound (due to the ArResolverContextBinder
/// // going out of scope), its search path no longer factors into asset
/// // resolution.
/// \endcode
///
class ArDefaultResolverContext
{
public:
    /// Default construct a context with no search path.
    ArDefaultResolverContext() = default;

    /// Construct a context with the given \p searchPath.
    /// Elements in \p searchPath should be absolute paths. If they are not,
    /// they will be anchored to the current working directory.
    AR_API ArDefaultResolverContext(const std::vector<std::string>& searchPath);

    AR_API bool operator<(const ArDefaultResolverContext& rhs) const;
    AR_API bool operator==(const ArDefaultResolverContext& rhs) const;
    AR_API bool operator!=(const ArDefaultResolverContext& rhs) const;

    /// Return this context's search path.
    const std::vector<std::string>& GetSearchPath() const
    {
        return _searchPath;
    }

    /// Return a string representation of this context for debugging.
    AR_API std::string GetAsString() const;

private:
    std::vector<std::string> _searchPath;
};

AR_API size_t
hash_value(const ArDefaultResolverContext& context);

inline std::string
ArGetDebugString(const ArDefaultResolverContext& context)
{
    return context.GetAsString();
}

AR_DECLARE_RESOLVER_CONTEXT(ArDefaultResolverContext);

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_DEFAULT_RESOLVER_CONTEXT_H
