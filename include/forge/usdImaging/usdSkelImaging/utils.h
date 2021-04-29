#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdSkelImaging/utils.h"
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
#ifndef FORGE_USD_IMAGING_USD_SKEL_IMAGING_UTILS_H
#define FORGE_USD_IMAGING_USD_SKEL_IMAGING_UTILS_H

///  \file usdSkelImaging/utils.h
///
/// Collection of utility methods for imaging skels.
///

#include "forge/forge.h"
#include "forge/usdImaging/usdSkelImaging/api.h"

#include "forge/base/vt/array.h"


FORGE_NAMESPACE_BEGIN


class HdMeshTopology;
class UsdSkelTopology;


/// \defgroup UsdSkelImaging_BoneUtils Bone Utilities
/// Utilities for constructing bone meshes.
/// @{


/// Compute mesh topology for imaging \p skelTopology.
/// The number of points that the mesh is expected to have are return in
/// \p numPoints.
USDSKELIMAGING_API
bool
UsdSkelImagingComputeBoneTopology(const UsdSkelTopology& skelTopology,
                                  HdMeshTopology* meshTopology,
                                  size_t* numPoints);


/// Compute mesh points for imaging a skeleton, given the
/// \p topology of the skeleton and \p skelXforms.
/// The \p numPoints corresponds to the number of points computed by
/// UsdSkelImagingComputeBoneTopology.
USDSKELIMAGING_API
bool
UsdSkelImagingComputeBonePoints(const UsdSkelTopology& topology,
                                const VtMatrix4dArray& jointSkelXforms,
                                size_t numPoints,
                                VtVec3fArray* points);

/// \overload
USDSKELIMAGING_API
bool
UsdSkelImagingComputeBonePoints(const UsdSkelTopology& topology,
                                const GfMatrix4d* jointSkelXforms,
                                GfVec3f* points, size_t numPoints);


/// Compute joint indices corresponding to each point in a bone mesh.
/// This can be used to animate a bone mesh using normal skinning algos.
/// This does not compute joint weights (they would all be 1s).
/// The \p numPoints corresponds to the number of points computed by
/// UsdSkelImagingComputeBoneTopology.
USDSKELIMAGING_API
bool
UsdSkelImagingComputeBoneJointIndices(const UsdSkelTopology& topology,
                                      VtIntArray* jointIndices,
                                      size_t numPoints);


/// \overload
USDSKELIMAGING_API
bool
UsdSkelImagingComputeBoneJointIndices(const UsdSkelTopology& topology,
                                      int* jointIndices, size_t numPoints);

/// @}


FORGE_NAMESPACE_END


#endif // FORGE_USD_IMAGING_USD_SKEL_IMAGING_UTILS_H
