#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/assetInfo.h"
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
#ifndef FORGE_USD_AR_ASSET_INFO_H
#define FORGE_USD_AR_ASSET_INFO_H

/// \file ar/assetInfo.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/base/vt/value.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// \class ArAssetInfo
///
/// Contains information about a resolved asset.
///
class ArAssetInfo
{
public:
    /// Version of the resolved asset, if any.
    std::string version;

    /// The name of the asset represented by the resolved
    /// asset, if any.
    std::string assetName;

    /// \deprecated
    /// The repository path corresponding to the resolved asset.
    std::string repoPath;

    /// Additional information specific to the active plugin
    /// asset resolver implementation.
    VtValue resolverInfo;
};

/// \relates ArAssetInfo
inline
void swap(ArAssetInfo& lhs, ArAssetInfo& rhs)
{
    lhs.version.swap(rhs.version);
    lhs.assetName.swap(rhs.assetName);
    lhs.repoPath.swap(rhs.repoPath);
    lhs.resolverInfo.Swap(rhs.resolverInfo);
}

/// \relates ArAssetInfo
AR_API
bool
operator==(const ArAssetInfo& lhs, const ArAssetInfo& rhs);

/// \relates ArAssetInfo
AR_API
bool
operator!=(const ArAssetInfo& lhs, const ArAssetInfo& rhs);

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_ASSET_INFO_H
