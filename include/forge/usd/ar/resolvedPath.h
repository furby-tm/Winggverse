#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/resolvedPath.h"
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
#ifndef FORGE_USD_AR_RESOLVED_PATH_H
#define FORGE_USD_AR_RESOLVED_PATH_H

/// \file ar/resolvedPath.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/base/tf/hash.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// \class ArResolvedPath
/// Represents a resolved asset path.
class ArResolvedPath
{
public:
    /// Construct an ArResolvedPath holding the given \p resolvedPath.
    explicit ArResolvedPath(const std::string& resolvedPath)
        : _resolvedPath(resolvedPath)
    {
    }

    /// \overload
    explicit ArResolvedPath(std::string&& resolvedPath)
        : _resolvedPath(std::move(resolvedPath))
    {
    }

    ArResolvedPath() = default;

    ArResolvedPath(const ArResolvedPath& rhs) = default;
    ArResolvedPath(ArResolvedPath&& rhs) = default;

    ArResolvedPath& operator=(const ArResolvedPath& rhs) = default;
    ArResolvedPath& operator=(ArResolvedPath&& rhs) = default;

    bool operator==(const ArResolvedPath& rhs) const
    { return _resolvedPath == rhs._resolvedPath; }

    bool operator!=(const ArResolvedPath& rhs) const
    { return _resolvedPath != rhs._resolvedPath; }

    bool operator<(const ArResolvedPath& rhs) const
    { return _resolvedPath < rhs._resolvedPath; }

    bool operator>(const ArResolvedPath& rhs) const
    { return _resolvedPath > rhs._resolvedPath; }

    bool operator<=(const ArResolvedPath& rhs) const
    { return _resolvedPath <= rhs._resolvedPath; }

    bool operator>=(const ArResolvedPath& rhs) const
    { return _resolvedPath >= rhs._resolvedPath; }

    bool operator==(const std::string& rhs) const
    { return _resolvedPath == rhs; }

    bool operator!=(const std::string& rhs) const
    { return _resolvedPath != rhs; }

    bool operator<(const std::string& rhs) const
    { return _resolvedPath < rhs; }

    bool operator>(const std::string& rhs) const
    { return _resolvedPath > rhs; }

    bool operator<=(const std::string& rhs) const
    { return _resolvedPath <= rhs; }

    bool operator>=(const std::string& rhs) const
    { return _resolvedPath >= rhs; }

    /// Return hash value for this object.
    size_t GetHash() const { return TfHash()(*this); }

    /// Return true if this object is holding a non-empty resolved path,
    /// false otherwise.
    explicit operator bool() const { return !IsEmpty(); }

    /// Return true if this object is holding an empty resolved path,
    /// false otherwise.
    bool IsEmpty() const { return _resolvedPath.empty(); }

    /// Equivalent to IsEmpty. This exists primarily for backwards
    /// compatibility.
    bool empty() const { return IsEmpty(); }

    /// Return the resolved path held by this object as a string.
    operator const std::string&() const { return GetPathString(); }

    /// Return the resolved path held by this object as a string.
    const std::string& GetPathString() const { return _resolvedPath; }

private:
    std::string _resolvedPath;
};

template <class HashState>
void
TfHashAppend(HashState& h, const ArResolvedPath& p)
{
    h.Append(p.GetPathString());
}

FORGE_NAMESPACE_END

#endif
