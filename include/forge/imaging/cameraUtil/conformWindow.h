#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/cameraUtil/conformWindow.h"
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
#ifndef FORGE_IMAGING_CAMERA_UTIL_CONFORM_WINDOW_H
#define FORGE_IMAGING_CAMERA_UTIL_CONFORM_WINDOW_H

#include "forge/forge.h"
#include "forge/imaging/cameraUtil/api.h"

FORGE_NAMESPACE_BEGIN

class GfVec2d;
class GfVec4d;
class GfMatrix4d;
class GfRange2d;
class GfCamera;
class GfFrustum;

/// \enum CameraUtilConformWindowPolicy
///
/// Policy of how to conform a window to the given aspect ratio.
/// An ASCII-art explanation is given in the corresponding .cpp file.
///
enum CameraUtilConformWindowPolicy {
    /// Modify width
    CameraUtilMatchVertically,
    /// Modify height
    CameraUtilMatchHorizontally,
    /// Increase width or height
    CameraUtilFit,
    /// Decrease width or height
    CameraUtilCrop,
    /// Leave unchanged (This can result in stretching/shrinking if not pre-fit)
    CameraUtilDontConform
};

/// Returns a window with aspect ratio \p targetAspect by applying
/// \p policy to \p window where \p window is encoded as GfRange2d.
CAMERAUTIL_API
GfRange2d
CameraUtilConformedWindow(
    const GfRange2d &window,
    CameraUtilConformWindowPolicy policy, double targetAspect);

/// Returns a window with aspect ratio \p targetAspect by applying
/// \p policy to \p window where \p window is encoded as vector
/// (left, right, bottom, top) similarly to RenderMan's RiScreenWindow.
CAMERAUTIL_API
GfVec4d
CameraUtilConformedWindow(
    const GfVec4d &window,
    CameraUtilConformWindowPolicy policy, double targetAspect);

/// Returns a window with aspect ratio \p targetAspect by applying
/// \p policy to \p window where \p window is encoded as vector
/// (width, height).
CAMERAUTIL_API
GfVec2d
CameraUtilConformedWindow(
    const GfVec2d &window,
    CameraUtilConformWindowPolicy policy, double targetAspect);

/// Conforms the given \p projectionMatrix to have aspect ratio \p targetAspect
/// by applying \p policy.
///
/// Note that this function also supports mirroring about the x- or y-axis of
/// the image corresponding to flipping all signs in the second, respectively,
/// third column of the projection matrix. In other words, we get the same
/// result whether we flip the signs in the matrix and then give it to this
/// function or call this function first and flip the signs of the resulting
/// matrix.
CAMERAUTIL_API
GfMatrix4d
CameraUtilConformedWindow(
    const GfMatrix4d &projectionMatrix,
    CameraUtilConformWindowPolicy policy, double targetAspect);

/// Conforms the given \p camera to have aspect ratio \p targetAspect
/// by applying \p policy.
CAMERAUTIL_API
void
CameraUtilConformWindow(
    GfCamera *camera,
    CameraUtilConformWindowPolicy policy, double targetAspect);

/// Conforms the given \p frustum to have aspect ratio \p targetAspect
/// by applying \p policy.
CAMERAUTIL_API
void
CameraUtilConformWindow(
    GfFrustum *frustum,
    CameraUtilConformWindowPolicy policy, double targetAspect);


FORGE_NAMESPACE_END

#endif
