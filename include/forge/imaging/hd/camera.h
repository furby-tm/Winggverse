#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/camera.h"
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
#ifndef FORGE_IMAGING_HD_CAMERA_H
#define FORGE_IMAGING_HD_CAMERA_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/sprim.h"

#include "forge/imaging/cameraUtil/conformWindow.h"

#include "forge/usd/sdf/path.h"
#include "forge/base/tf/staticTokens.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/range1f.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

/// Camera state that can be requested from the scene delegate via
/// GetCameraParamValue(id, token). The parameters below mimic the
/// USD camera schema and GfCamera (with the exception of window
/// policy). All spatial units are in world units though and
/// projection is HdCamera::Projection rather than a token.
#define HD_CAMERA_TOKENS                            \
    /* frustum */                                   \
    (projection)                                    \
    (horizontalAperture)                            \
    (verticalAperture)                              \
    (horizontalApertureOffset)                      \
    (verticalApertureOffset)                        \
    (focalLength)                                   \
    (clippingRange)                                 \
    (clipPlanes)                                    \
                                                    \
    /* depth of field */                            \
    (fStop)                                         \
    (focusDistance)                                 \
                                                    \
    /* shutter/lighting */                          \
    (shutterOpen)                                   \
    (shutterClose)                                  \
    (exposure)                                      \
                                                    \
    /* how to match window with different aspect */ \
    (windowPolicy)                                  \
                                                    \
    /* OpenGL-style matrices, deprecated */         \
    (worldToViewMatrix)                             \
    (projectionMatrix)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdCameraTokens, HD_API, HD_CAMERA_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \class HdCamera
///
/// Hydra schema for a camera that pulls the params (see above) during
/// Sync.
/// Backends that use additional camera parameters can inherit from HdCamera and
/// pull on them.
///
class HdCamera : public HdSprim
{
public:
    using ClipPlanesVector = std::vector<GfVec4d>;

    HD_API
    HdCamera(SdfPath const & id);
    HD_API
    ~HdCamera() override;

    // change tracking for HdCamera
    enum DirtyBits : HdDirtyBits
    {
        Clean                 = 0,
        DirtyTransform        = 1 << 0,
        DirtyViewMatrix       = DirtyTransform, // deprecated
        DirtyProjMatrix       = 1 << 1,         // deprecated
        DirtyWindowPolicy     = 1 << 2,
        DirtyClipPlanes       = 1 << 3,
        DirtyParams           = 1 << 4,
        AllDirty              = (DirtyTransform
                                |DirtyProjMatrix
                                |DirtyWindowPolicy
                                |DirtyClipPlanes
                                |DirtyParams)
    };

    enum Projection {
        Perspective = 0,
        Orthographic
    };

    // ---------------------------------------------------------------------- //
    /// Sprim API
    // ---------------------------------------------------------------------- //

    /// Synchronizes state from the delegate to this object.
    HD_API
    void Sync(HdSceneDelegate *sceneDelegate,
              HdRenderParam   *renderParam,
              HdDirtyBits     *dirtyBits) override;


    /// Returns the minimal set of dirty bits to place in the
    /// change tracker for use in the first sync of this prim.
    /// Typically this would be all dirty bits.
    HD_API
    HdDirtyBits GetInitialDirtyBitsMask() const override;

    // ---------------------------------------------------------------------- //
    /// Camera parameters accessor API
    // ---------------------------------------------------------------------- //

    /// Returns camera transform
    GfMatrix4d const& GetTransform() const {
        return _transform;
    }

    /// Returns whether camera is orthographic and perspective
    Projection GetProjection() const {
        return _projection;
    }

    /// Returns horizontal aperture in world units.
    float GetHorizontalAperture() const {
        return _horizontalAperture;
    }

    /// Returns vertical aperture in world units.
    float GetVerticalAperture() const {
        return _verticalAperture;
    }

    /// Returns horizontal aperture offset in world units.
    float GetHorizontalApertureOffset() const {
        return _horizontalApertureOffset;
    }

    /// Returns vertical aperture offset in world units.
    float GetVerticalApertureOffset() const {
        return _verticalApertureOffset;
    }

    /// Returns focal length in world units.
    float GetFocalLength() const {
        return _focalLength;
    }

    /// Returns near and far plane in world units
    GfRange1f const &GetClippingRange() const {
        return _clippingRange;
    }

    /// Returns any additional clipping planes defined in camera space.
    std::vector<GfVec4d> const& GetClipPlanes() const {
        return _clipPlanes;
    }

    /// Returns fstop of camera
    float GetFStop() const {
        return _fStop;
    }

    /// Returns focus distance in world units.
    float GetFocusDistance() const {
        return _focusDistance;
    }

    double GetShutterOpen() const {
        return _shutterOpen;
    }

    double GetShutterClose() const {
        return _shutterClose;
    }

    float GetExposure() const {
        return _exposure;
    }

    /// Returns the window policy of the camera. If no opinion is authored, we
    /// default to "CameraUtilFit"
    CameraUtilConformWindowPolicy const& GetWindowPolicy() const {
        return _windowPolicy;
    }

    // ---------------------------------------------------------------------- //
    /// Legacy camera parameters accessor API
    // ---------------------------------------------------------------------- //

    /// Returns the matrix transformation from world to camera space.
    /// \deprecated Use GetTransform instead
    HD_API
    GfMatrix4d GetViewMatrix() const;

    /// Returns the matrix transformation from camera to world space.
    /// \deprecated Use GetTransform and invert instead
    HD_API
    GfMatrix4d GetViewInverseMatrix() const;

    /// Returns the projection matrix for the camera.
    /// \deprecated Compute from above physically based attributes
    HD_API
    GfMatrix4d GetProjectionMatrix() const;

protected:
    // frustum
    GfMatrix4d              _transform;
    Projection              _projection;
    float                   _horizontalAperture;
    float                   _verticalAperture;
    float                   _horizontalApertureOffset;
    float                   _verticalApertureOffset;
    float                   _focalLength;
    GfRange1f               _clippingRange;
    std::vector<GfVec4d>    _clipPlanes;

    // focus
    float                   _fStop;
    float                   _focusDistance;

    // shutter/lighting
    double                  _shutterOpen;
    double                  _shutterClose;
    float                   _exposure;

    // Camera's opinion how it display in a window with
    // a different aspect ratio
    CameraUtilConformWindowPolicy _windowPolicy;

    // OpenGL-style matrices
    GfMatrix4d _worldToViewMatrix;
    GfMatrix4d _worldToViewInverseMatrix;
    GfMatrix4d _projectionMatrix;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_CAMERA_H
