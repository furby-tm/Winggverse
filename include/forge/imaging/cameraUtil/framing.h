#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/cameraUtil/framing.h"
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
#ifndef FORGE_IMAGING_CAMERA_UTIL_FRAMING_H
#define FORGE_IMAGING_CAMERA_UTIL_FRAMING_H

#include "forge/forge.h"
#include "forge/imaging/cameraUtil/api.h"

#include "forge/imaging/cameraUtil/conformWindow.h"

#include "forge/base/gf/rect2i.h"
#include "forge/base/gf/range2f.h"

FORGE_NAMESPACE_BEGIN

/// \class CameraUtilFraming
///
/// Framing information. That is information determining how the filmback
/// plane of a camera maps to the pixels of the rendered image (displayWindow
/// together with pixelAspectRatio and window policy) and what pixels of the
/// image will be filled by the renderer (dataWindow).
///
/// The concepts of displayWindow and dataWindow are similar to the ones in
/// OpenEXR, including that the x- and y-axis of the coordinate system point
/// left and down, respectively.
///
/// In fact, these windows mean the same here and in OpenEXR if the
/// displayWindow has the same aspect ratio (when accounting for the
/// pixelAspectRatio) as the filmback plane of the camera has (that is the
/// ratio of the horizontalAperture to verticalAperture of, e.g., Usd's Camera
/// or GfCamera).
///
/// In particular, overscan can be achieved by making the dataWindow larger
/// than the displayWindow.
///
/// If the aspect ratios differ, a window policy is applied to the
/// displayWindow to determine how the pixels correspond to the
/// filmback plane.  One such window policy is to take the largest
/// rect that fits (centered) into the displayWindow and has the
/// camera's aspect ratio. For example, if the displayWindow and dataWindow
/// are the same and both have an aspect ratio smaller than the camera, the
/// image is created by enlarging the camera frustum slightly in the bottom
/// and top direction.
///
/// When using the AOVs, the render buffer size is determined
/// independently from the framing info. However, the dataWindow is
/// supposed to be contained in the render buffer rect (in particular,
/// the dataWindow cannot contain pixels withs negative coordinates -
/// this restriction does not apply if, e.g., hdPrman circumvents AOVs
/// and writes directly to EXR). In other words, unlike in OpenEXR,
/// the rect of pixels for which we allocate storage can differ from
/// the rect the renderer fills with data (dataWindow).
///
/// For example, an application can set the render buffer size to match
/// the widget size but use a dataWindow and displayWindow that only fills
/// the render buffer horizontally to have slates at the top and bottom.
///
class CameraUtilFraming final
{
public:
    /// Creates an invalid framing, i.e., with empty display and data
    /// window.
    CAMERAUTIL_API
    CameraUtilFraming();

    /// Creates a framing with given display and data window and pixel
    /// aspect ratio.
    ///
    CAMERAUTIL_API
    CameraUtilFraming(
        const GfRange2f &displayWindow,
        const GfRect2i &dataWindow,
        float pixelAspectRatio = 1.0);

    /// Creates a framing with equal display and data window (and
    /// assuming square pixels).
    ///
    CAMERAUTIL_API
    explicit CameraUtilFraming(
        const GfRect2i &dataWindow);

    /// Is display and data window non-empty.
    CAMERAUTIL_API
    bool IsValid() const;

    CAMERAUTIL_API
    bool operator==(const CameraUtilFraming& other) const;

    CAMERAUTIL_API
    bool operator!=(const CameraUtilFraming& other) const;

    /// Given the projectionMatrix computed from a camera, applies
    /// the framing. To obtain a correct result, a rasterizer needs
    /// to use the resulting projection matrix and set the viewport
    /// to the data window.
    ///
    CAMERAUTIL_API
    GfMatrix4d ApplyToProjectionMatrix(
        const GfMatrix4d &projectionMatrix,
        CameraUtilConformWindowPolicy windowPolicy) const;

    /// The display window. It will be conformed to the camera's
    /// aspect ratio and then mapped to the filmback plane.
    GfRange2f displayWindow;

    /// The data window. That is the rect of pixels that the renderer
    /// will fill.
    GfRect2i dataWindow;

    /// The ratio of the width to the height of a pixel - same as
    /// OpenEXR.
    float pixelAspectRatio;
};

FORGE_NAMESPACE_END

#endif
