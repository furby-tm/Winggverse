#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/textureUtils.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_TEXTURE_UTILS_H
#define FORGE_USD_IMAGING_USD_IMAGING_TEXTURE_UTILS_H

#include "forge/forge.h"

#include "forge/base/tf/token.h"

#include "forge/usd/sdf/layer.h"

#include "forge/usdImaging/usdImaging/api.h"

#include <tuple>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// The functions below are used by the old texture system where the
/// scene delegates creates the texture resource in
/// GetTextureResource.
///
/// Note: these functions are also not binding the Usd stage's
/// resolver context and thus don't handle some cases (e.g., model
/// search paths) correctly.
///
/// The corresponding functions for the new texture system are in
/// usdImaging/materialParamUtils.cpp and HdPhUdimTextureObject.
///
USDIMAGING_API
std::vector<std::tuple<int, TfToken>>
UsdImaging_GetUdimTiles(
    std::string const& basePath,
    int tileLimit,
    SdfLayerHandle const& layerHandle = SdfLayerHandle());

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_TEXTURE_UTILS_H
