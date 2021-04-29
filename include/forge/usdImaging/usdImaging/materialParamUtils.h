#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/materialParamUtils.h"
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
#ifndef FORGE_USD_IMAGING_MATERIAL_PARAM_UTILS_H
#define FORGE_USD_IMAGING_MATERIAL_PARAM_UTILS_H

#include "forge/forge.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

struct HdMaterialNetworkMap;
class UsdAttribute;
class UsdPrim;
class UsdTimeCode;
class VtValue;

/// Get the value from the usd attribute at given time. If it is an
/// SdfAssetPath containing a UDIM pattern, e.g., //SHOW/myImage.<UDIM>.exr,
/// the resolved path of the SdfAssetPath will be updated to a file path
/// with a UDIM pattern, e.g., /filePath/myImage.<UDIM>.exr.
/// There might be support for different patterns, e.g., myImage._MAPID_.exr,
/// but this function always normalizes it to myImage.<UDIM>.exr.
///
/// The function assumes that the correct ArResolverContext is bound.
///
VtValue
UsdImaging_ResolveMaterialParamValue(
    const UsdAttribute& attr, const UsdTimeCode& time);

/// Builds an HdMaterialNetwork for the usdTerminal prim and
/// populates it in the materialNetworkMap under the terminalIdentifier.
/// This shared implementation is usable for populating material networks for
/// any connectable source including lights and light filters in addition to
/// materials.
void
UsdImaging_BuildHdMaterialNetworkFromTerminal(
    UsdPrim const& usdTerminal,
    TfToken const& terminalIdentifier,
    TfTokenVector const& shaderSourceTypes,
    HdMaterialNetworkMap *materialNetworkMap,
    UsdTimeCode time);

/// Returns whether the material network built by
/// UsdImaging_BuildHdMaterialNetworkFromTerminal for the given usdTerminal
/// prim is time varying.
bool
UsdImaging_IsHdMaterialNetworkTimeVarying(
    UsdPrim const& usdTerminal);

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_MATERIAL_PARAM_UTILS_H
