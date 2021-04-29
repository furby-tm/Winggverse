#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdAppUtils/frameRecorder.h"
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
#ifndef FORGE_USD_IMAGING_USD_APP_UTILS_FRAME_RECORDER_H
#define FORGE_USD_IMAGING_USD_APP_UTILS_FRAME_RECORDER_H

/// \file usdAppUtils/frameRecorder.h

#include "forge/forge.h"
#include "forge/usdImaging/usdAppUtils/api.h"

#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/token.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usd/timeCode.h"
#include "forge/usd/usdGeom/camera.h"
#include "forge/usdImaging/usdImagingGL/engine.h"

#include <string>


FORGE_NAMESPACE_BEGIN


/// \class UsdAppUtilsFrameRecorder
///
/// A utility class for recording images of USD stages.
///
/// UsdAppUtilsFrameRecorder uses Hydra to produce recorded images of a USD
/// stage looking through a particular UsdGeomCamera on that stage at a
/// particular UsdTimeCode. The images generated will be effectively the same
/// as what you would see in the viewer in usdview.
///
/// Note that it is assumed that an OpenGL context has already been setup.
class UsdAppUtilsFrameRecorder
{
public:
    USDAPPUTILS_API
    UsdAppUtilsFrameRecorder();

    /// Gets the ID of the Hydra renderer plugin that will be used for
    /// recording.
    TfToken GetCurrentRendererId() const {
        return _imagingEngine.GetCurrentRendererId();
    }

    /// Sets the Hydra renderer plugin to be used for recording.
    bool SetRendererPlugin(const TfToken& id) {
        return _imagingEngine.SetRendererPlugin(id);
    }

    /// Sets the width of the recorded image.
    ///
    /// The height of the recorded image will be computed using this value and
    /// the aspect ratio of the camera used for recording.
    ///
    /// The default image width is 960 pixels.
    void SetImageWidth(const size_t imageWidth) {
        if (imageWidth == 0u) {
            TF_CODING_ERROR("Image width cannot be zero");
            return;
        }
        _imageWidth = imageWidth;
    }

    /// Sets the level of refinement complexity.
    ///
    /// The default complexity is "low" (1.0).
    void SetComplexity(const float complexity) {
        _complexity = complexity;
    }

    /// Sets the color correction mode to be used for recording.
    ///
    /// By default, color correction is disabled.
    void SetColorCorrectionMode(const TfToken& colorCorrectionMode) {
        _colorCorrectionMode = colorCorrectionMode;
    }

    /// Sets the UsdGeomImageable purposes to be used for rendering
    ///
    /// We will __always__ include "default" purpose, and by default,
    /// we will also include UsdGeomTokens->proxy.  Use this method
    /// to explicitly enumerate an alternate set of purposes to be
    /// included along with "default".
    USDAPPUTILS_API
    void SetIncludedPurposes(const TfTokenVector& purposes);

    /// Records an image and writes the result to \p outputImagePath.
    ///
    /// The recorded image will represent the view from \p usdCamera looking at
    /// the imageable prims on USD stage \p stage at time \p timeCode.
    ///
    /// If \p usdCamera is not a valid camera, a camera will be computed
    /// to automatically frame the stage geometry.
    ///
    /// Returns true if the image was generated and written successfully, or
    /// false otherwise.
    USDAPPUTILS_API
    bool Record(
            const UsdStagePtr& stage,
            const UsdGeomCamera& usdCamera,
            const UsdTimeCode timeCode,
            const std::string& outputImagePath);

private:
    UsdImagingGLEngine _imagingEngine;
    size_t _imageWidth;
    float _complexity;
    TfToken _colorCorrectionMode;
    TfTokenVector _purposes;
};


FORGE_NAMESPACE_END


#endif
