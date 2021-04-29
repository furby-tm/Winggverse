#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/freeCameraSceneDelegate.h"
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
#ifndef FORGE_IMAGING_HDX_FREE_CAMERA_SCENE_DELEGATE_H
#define FORGE_IMAGING_HDX_FREE_CAMERA_SCENE_DELEGATE_H

#include "forge/forge.h"

#include "forge/imaging/hdx/api.h"

#include "forge/imaging/hd/sceneDelegate.h"
#include "forge/base/gf/camera.h"
#include "forge/imaging/cameraUtil/conformWindow.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxFreeCameraSceneDelegate
///
/// A simple scene delegate adding a camera prim to the given
/// render index.
///
class HdxFreeCameraSceneDelegate : public HdSceneDelegate
{
public:
    /// Constructs delegate and adds camera to render index if
    /// cameras are supported by render delegate.
    HDX_API
    HdxFreeCameraSceneDelegate(HdRenderIndex *renderIndex,
                               SdfPath const &delegateId);
    
    HDX_API
    ~HdxFreeCameraSceneDelegate() override;

    /// Path of added camera (in render index). Empty if cameras are not
    /// supported by render delegate.
    const SdfPath &GetCameraId() const {
        return _cameraId;
    }

    /// Set state of camera from GfCamera.
    HDX_API
    void SetCamera(const GfCamera &camera);
    /// Set window policy of camera.
    HDX_API
    void SetWindowPolicy(CameraUtilConformWindowPolicy policy);
    
    /// For transition, set camera state from OpenGL-style
    /// view and projection matrix. GfCamera is preferred.
    HDX_API
    void SetMatrices(GfMatrix4d const &viewMatrix,
                     GfMatrix4d const &projMatrix);

    /// For transition, set clip planes for camera. GfCamera is preferred.
    HDX_API
    void SetClipPlanes(std::vector<GfVec4f> const &clipPlanes);

    // HdSceneDelegate interface
    HDX_API
    GfMatrix4d GetTransform(SdfPath const &id) override;
    HDX_API
    VtValue GetCameraParamValue(SdfPath const &id, 
                                TfToken const &key) override;

private:
    // Mark camera dirty in render index.
    void _MarkDirty(HdDirtyBits bits);

    // Path of camera in render index.
    const SdfPath _cameraId;

    // State of camera
    GfCamera _camera;
    // Window policy of camera.
    CameraUtilConformWindowPolicy _policy;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_FREE_CAMERA_SCENE_DELEGATE_H
