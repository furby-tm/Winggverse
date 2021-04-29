#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/flattenUtils.h"
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
#ifndef FORGE_USD_USD_FLATTEN_UTILS_H
#define FORGE_USD_USD_FLATTEN_UTILS_H

/// \file usd/flattenUtils.h
///
/// Utilities for flattening layer stacks into a single layer.

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/pcp/layerStackIdentifier.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// Flatten \p layerStack into a single layer with the given optional \p tag.
///
/// A composed UsdStage created from this flattened layer will be the same
/// as a composed UsdStage whose root layer stack is the original layer stack.
///
/// Unlike UsdStage::Flatten(), this function does not flatten
/// composition arcs, such as references, payloads, inherits,
/// specializes, or variants.
///
/// Sublayer time offsets on the sublayers will be applied to remap
/// any time-keyed scene description, such as timeSamples and clips.
///
/// Asset paths will be resolved to absolute form, to ensure that
/// they continue to identify the same asset from the output layer.
/// \sa UsdFlattenLayerStackResolveAssetPath
///
/// A few historical scene description features cannot be flattened
/// into a single opinion because they unfortunately encode
/// operations that are not closed under composition.  Specifically,
/// the SdfListOp operations "add" and "reorder" cannot be flattened.
/// Instead, "add" will be converted to "append", and "reorder"
/// will be discarded.
///
USD_API
SdfLayerRefPtr
UsdFlattenLayerStack(const PcpLayerStackRefPtr &layerStack,
                     const std::string& tag = std::string());

/// Callback function for overloaded version of \c UsdFlattenLayerStack.
///
/// The callback is given the \c sourceLayer and the \c assetPath authored in
/// that layer.  It should return the \c std::string that should be authored in
/// the flattened layer.
///
/// \sa UsdFlattenLayerStackResolveAssetPath
using UsdFlattenResolveAssetPathFn = std::function<std::string(
        const SdfLayerHandle& sourceLayer,
        const std::string& assetPath)>;

/// Flatten the \p layerStack into a single layer with
/// the given optional \p tag and using the \p resolveAssetPathFn to resolve
/// asset paths that are encountered.
///
/// This is an advanced version of the above function.
///
///
/// One use case for this version of the function is to flatten a layer stack
/// that contains relative asset paths that we want to preserve as relative
/// paths.  For example:
///
/// \code
/// /source/root.usd # sublayers a.usd and b.usd
/// /source/a.usd    # contains reference to ./subdir/layer.usd
/// /source/b.usd
/// /source/subdir/layer.usd
/// \endcode
///
/// We may want to generate \c "/dest/root.flat.usd" knowing that we will
/// (by some other means) also be copying \c "/source/subdir" into \c
/// "/dest/subdir".  It's useful then to preserve the relative paths.
///
/// Note, only the caller knows the ultimate destination of the flattened layer.
/// So to accomplish this, we can provide a \c resolveAssetPathFn callback that
/// captures the outputDir, tests if the authored path is relative, and if so,
/// computes a new relative path (based on where it will eventually be
/// exported).
USD_API
SdfLayerRefPtr
UsdFlattenLayerStack(const PcpLayerStackRefPtr &layerStack,
                     const UsdFlattenResolveAssetPathFn& resolveAssetPathFn,
                     const std::string& tag = std::string());

/// The default \c UsdUtilsResolvePathFn used by \c UsdUtilsFlattenLayerStack.
/// For paths that the current ArResolver identifies as searchpaths or absolute
/// paths, we return the unmodified path. However, any "Layer relative path"
/// (see SdfComputeAssetPathRelativeToLayer) will be absolutized, because we do
/// not know if the flattened layer's containing directory will be the same as
/// any given source layer's in the incoming layerStack.
USD_API
std::string
UsdFlattenLayerStackResolveAssetPath(
    const SdfLayerHandle& sourceLayer,
    const std::string& assetPath);


FORGE_NAMESPACE_END

#endif /* FORGE_USD_USD_FLATTEN_UTILS_H */
