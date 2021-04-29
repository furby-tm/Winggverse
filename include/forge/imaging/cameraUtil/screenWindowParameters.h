#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/cameraUtil/screenWindowParameters.h"
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
#ifndef FORGE_IMAGING_CAMERA_UTIL_SCREEN_WINDOW_PARAMETERS_H
#define FORGE_IMAGING_CAMERA_UTIL_SCREEN_WINDOW_PARAMETERS_H

#include "forge/forge.h"
#include "forge/imaging/cameraUtil/api.h"
#include "forge/base/gf/camera.h"

FORGE_NAMESPACE_BEGIN


/// \class CameraUtilScreenWindowParameters
///
/// Given a camera object, compute parameters suitable for setting up
/// RenderMan.
///
class CameraUtilScreenWindowParameters
{
public:
    /// Constructs screenwindow parameter. The optional \p fitDirection
    /// indicates in which direction the screenwindow will have length 2.
    CAMERAUTIL_API
    CameraUtilScreenWindowParameters(const GfCamera &camera,
                                     GfCamera::FOVDirection fitDirection =
                                     GfCamera::FOVHorizontal);

    /// The vector (left, right, bottom, top) defining the rectangle in the
    /// image plane.
    /// Give these parameters to RiScreenWindow.
    const GfVec4d & GetScreenWindow() const { return _screenWindow; }

    /// The field of view. More precisely, the full angle perspective field
    /// of view (in degrees) between screen space coordinates (-1,0) and
    /// (1,0).
    /// Give these parameters to RiProjection as parameter after
    /// "perspective".
    double GetFieldOfView() const { return _fieldOfView; }

    /// Returns the inverse of the transform for a camera that is y-Up
    /// and z-facing (vs the OpenGL camera that is (-z)-facing).
    /// Write this transform with RiConcatTransform before
    /// RiWorldBegin.
    const GfMatrix4d & GetZFacingViewMatrix() const {
        return _zFacingViewMatrix;
    }

private:
    GfVec4d _screenWindow;
    double _fieldOfView;
    GfMatrix4d _zFacingViewMatrix;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_CAMERA_UTIL_SCREEN_WINDOW_PARAMETERS_H
