#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/layerUtils.h"
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
#ifndef FORGE_USD_SDF_LAYER_UTILS_H
#define FORGE_USD_SDF_LAYER_UTILS_H

/// \file sdf/layerUtils.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/layer.h"

#include <string>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// Returns the path to the asset specified by \p assetPath, using the
/// \p anchor layer to anchor the path if it is relative.  If the result of
/// anchoring \p assetPath to \p anchor's path cannot be resolved and
/// \p assetPath is a search path, \p assetPath will be returned.  If
/// \p assetPath is not relative, \p assetPath will be returned.  Otherwise,
/// the anchored path will be returned.
///
/// Note that if \p anchor is an anonymous layer, we will always return
/// the untouched \p assetPath.
SDF_API std::string
SdfComputeAssetPathRelativeToLayer(
    const SdfLayerHandle& anchor,
    const std::string& assetPath);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_LAYER_UTILS_H
