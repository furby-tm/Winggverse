#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/assetPath.h"
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
#ifndef FORGE_USD_SDF_ASSET_PATH_H
#define FORGE_USD_SDF_ASSET_PATH_H

/// \file sdf/assetPath.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"

#include <boost/functional/hash.hpp>
#include <boost/operators.hpp>
#include <iosfwd>
#include <string>

FORGE_NAMESPACE_BEGIN

/// \class SdfAssetPath
///
/// Contains an asset path and an optional resolved path.
///
class SdfAssetPath:
    public boost::totally_ordered<SdfAssetPath>
{
public:
    /// \name Constructors
    /// @{
    ///

    /// Construct an empty asset path.
    SDF_API SdfAssetPath();

    /// Construct asset path with no associated resolved path.
    SDF_API explicit SdfAssetPath(const std::string &path);

    /// Construct an asset path with an associated resolved path.
    SDF_API SdfAssetPath(const std::string &path, const std::string &resolvedPath);

    /// @}

    ///\name Operators
    /// @{

    /// Equality, including the resolved path.
    bool operator==(const SdfAssetPath &rhs) const {
        return _assetPath == rhs._assetPath &&
               _resolvedPath == rhs._resolvedPath;
    }

    /// Ordering first by asset path, then by resolved path.
    SDF_API bool operator<(const SdfAssetPath &rhs) const;

    /// Hash function
    size_t GetHash() const {
        size_t hash = 0;
        boost::hash_combine(hash, _assetPath);
        boost::hash_combine(hash, _resolvedPath);
        return hash;
    }

    /// \class Hash
    struct Hash
    {
        size_t operator()(const SdfAssetPath &ap) const {
            return ap.GetHash();
        }
    };

    friend size_t hash_value(const SdfAssetPath &ap) { return ap.GetHash(); }

    /// @}

    /// \name Accessors
    /// @{

    /// Return the asset path.
    const std::string &GetAssetPath() const {
        return _assetPath;
    }

    /// Return the resolved asset path, if any.
    ///
    /// Note that SdfAssetPath only carries a resolved path if the creator of
    /// an instance supplied one to the constructor.  SdfAssetPath will never
    /// perform any resolution itself.
    const std::string &GetResolvedPath() const {
        return _resolvedPath;
    }

    /// @}

private:
    friend inline void swap(SdfAssetPath &lhs, SdfAssetPath &rhs) {
        lhs._assetPath.swap(rhs._assetPath);
        lhs._resolvedPath.swap(rhs._resolvedPath);
    }

    std::string _assetPath;
    std::string _resolvedPath;
};

/// \name Related
/// @{

/// Stream insertion operator for the string representation of this assetPath.
///
/// \note This always encodes only the result of GetAssetPath().  The resolved
///       path is ignored for the purpose of this operator.  This means that
///       two SdfAssetPath that do not compare equal may produce
///       indistinguishable ostream output.
SDF_API std::ostream& operator<<(std::ostream& out, const SdfAssetPath& ap);

/// @}

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_ASSET_PATH_H
