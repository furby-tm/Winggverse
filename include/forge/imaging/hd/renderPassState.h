#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/renderPassState.h"
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
#ifndef FORGE_IMAGING_HD_RENDER_PASS_STATE_H
#define FORGE_IMAGING_HD_RENDER_PASS_STATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/aov.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/enums.h"

#include "forge/imaging/cameraUtil/framing.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec2f.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/vec4f.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


using HdRenderPassStateSharedPtr = std::shared_ptr<class HdRenderPassState>;
using HdResourceRegistrySharedPtr = std::shared_ptr<class HdResourceRegistry>;

class HdCamera;

/// \class HdRenderPassState
///
/// A set of rendering parameters used among render passes.
///
/// Parameters are expressed as GL states, uniforms or shaders.
///
class HdRenderPassState
{
public:
    HD_API
    HdRenderPassState();
    HD_API
    virtual ~HdRenderPassState();

    /// Schedule to update renderPassState parameters.
    /// e.g. camera matrix, override color, id blend factor.
    /// Prepare, called once per frame after the sync phase, but prior to
    /// the commit phase.
    HD_API
    virtual void Prepare(HdResourceRegistrySharedPtr const &resourceRegistry);

    // ---------------------------------------------------------------------- //
    /// \name Camera and framing state
    // ---------------------------------------------------------------------- //

    using ClipPlanesVector = std::vector<GfVec4d>;

    /// Camera setter API
    ///
    /// Sets the camera transform (aka view inverse matrix) and physical
    /// parameters, the framing information and a possible overide value
    /// for the window policy used to conform the camera frustum if its
    /// aspect ratio is not matching the display window.
    ///
    /// Note: using std::pair<bool, ...> here instead of std::optional<...>
    /// since the latter is only available in C++17 or later.
    HD_API
    void SetCameraAndFraming(
        HdCamera const *camera,
        CameraUtilFraming const &framing,
        const std::pair<bool, CameraUtilConformWindowPolicy> &
                                            overrideWindowPolicy);

    /// Get camera
    HdCamera const *
    GetCamera() const { return _camera; }

    /// Get framing information determining how the filmback plane maps
    /// to pixels.
    const CameraUtilFraming &
    GetFraming() const { return _framing; }

    /// The override value for the window policy to conform the camera
    /// frustum that can be specified by the application.
    const std::pair<bool, CameraUtilConformWindowPolicy> &
    GetOverrideWindowPolicy() const { return _overrideWindowPolicy; }

    /// The resolved window policy to conform the camera frustum.
    /// This is either the override value specified by the application or
    /// the value from the scene delegate's camera.
    HD_API
    CameraUtilConformWindowPolicy
    GetWindowPolicy() const;

    /// Camera setter API
    /// The view, projection and clipping plane info of the camera will be used.
    ///
    /// \deprecated Use the more expressive SetCameraAndFraming instead.
    HD_API
    void SetCameraAndViewport(HdCamera const *camera,
                              GfVec4d const& viewport);
    /// Camera getter API
    ///
    /// For backwards compatibility, use the worldToView matrix of the HdCamera
    /// if given. Otherwise, use the HdCamera's transform.
    ///
    /// The HdRenderPassState also has a fallback value for the view
    /// matrix that is used if no HdCamera was specified, that can be set with,
    /// e.g.g, HdPhRenderPassState::SetCameraFramingState.
    ///
    HD_API
    GfMatrix4d GetWorldToViewMatrix() const;

    /// It is expected that an HdCamera was specified that has physically based
    /// attributes. The projection matrix is computed from those attributes and
    /// the conform window policy is applied.
    ///
    /// For backwards compatibility with scene and render delegates:
    /// if the HdCamera has no physically based attributes (more precisely,
    /// the scene delegate provided a VtValue for focalLength that is either
    /// empty or 1.0f), the HdCamera's projection matrix is used.
    /// The HdRenderPassState also has a fallback value for the projection
    /// matrix that is used if no HdCamera was specified, that can be set with,
    /// e.g.g, HdPhRenderPassState::SetCameraFramingState.
    ///
    HD_API
    GfMatrix4d GetProjectionMatrix() const;

    /// Only use when clients did not specify a camera framing.
    ///
    /// \deprecated
    GfVec4f const & GetViewport() const { return _viewport; }

    HD_API
    ClipPlanesVector const & GetClipPlanes() const;

    GfMatrix4d GetCullMatrix() const { return _cullMatrix; }

    // ---------------------------------------------------------------------- //
    /// \name Application rendering state
    // ---------------------------------------------------------------------- //

    /// Set an override color for rendering where the R, G and B components
    /// are the color and the alpha component is the blend value
    HD_API
    void SetOverrideColor(GfVec4f const &color);
    const GfVec4f& GetOverrideColor() const { return _overrideColor; }

    /// Set a wireframe color for rendering where the R, G and B components
    /// are the color and the alpha component is the blend value
    HD_API
    void SetWireframeColor(GfVec4f const &color);
    const GfVec4f& GetWireframeColor() const { return _wireframeColor; }

    HD_API
    void SetMaskColor(GfVec4f const &color);
    const GfVec4f& GetMaskColor() const { return _maskColor; }

    HD_API
    void SetIndicatorColor(GfVec4f const &color);
    const GfVec4f& GetIndicatorColor() const { return _indicatorColor; }

    /// Set a point color for rendering where the R, G and B components
    /// are the color and the alpha component is the blend value
    HD_API
    void SetPointColor(GfVec4f const &color);
    const GfVec4f& GetPointColor() const { return _pointColor; }

    /// Set the point size for unselected points.
    HD_API
    void SetPointSize(float size);
    float GetPointSize() const { return _pointSize; }

    /// Set the point size for selected points.
    HD_API
    void SetPointSelectedSize(float size);
    float GetPointSelectedSize() const { return _pointSelectedSize; }

    /// XXX: Hacky way of disabling lighting
    HD_API
    void SetLightingEnabled(bool enabled);
    bool GetLightingEnabled() const { return _lightingEnabled; }

    // ---------------------------------------------------------------------- //
    /// \name Render pipeline state
    // ---------------------------------------------------------------------- //

    /// Set the attachments for this renderpass to render into.
    HD_API
    void SetAovBindings(HdRenderPassAovBindingVector const &aovBindings);
    HD_API
    HdRenderPassAovBindingVector const& GetAovBindings() const;

    /// Returns true if the render pass wants to render into the multi-sample
    /// aovs. Returns false if the render wants to render into the resolve aovs.
    HD_API
    void SetUseAovMultiSample(bool state);
    HD_API
    bool GetUseAovMultiSample() const;

    HD_API
    void SetCullStyle(HdCullStyle cullStyle);
    HD_API
    HdCullStyle GetCullStyle() const { return _cullStyle; }

    HD_API
    void SetAlphaThreshold(float alphaThreshold);
    float GetAlphaThreshold() const { return _alphaThreshold; }

    HD_API
    void SetTessLevel(float level);
    float GetTessLevel() const { return _tessLevel; }

    HD_API
    void SetDrawingRange(GfVec2f const &drawRange);
    GfVec2f GetDrawingRange() const { return _drawRange; } // in pixel
    GfVec2f GetDrawingRangeNDC() const { // in ndc
        return GfVec2f(2*_drawRange[0]/_viewport[2],
                       2*_drawRange[1]/_viewport[3]);
    }

    HD_API
    void SetDepthBiasUseDefault(bool useDefault);
    bool GetDepthBiasUseDefault() const { return _depthBiasUseDefault; }

    HD_API
    void SetDepthBiasEnabled(bool enabled);
    bool GetDepthBiasEnabled() const { return _depthBiasEnabled; }

    HD_API
    void SetDepthBias(float constantFactor, float slopeFactor);

    HD_API
    void SetDepthFunc(HdCompareFunction depthFunc);
    HdCompareFunction GetDepthFunc() const { return _depthFunc; }

    HD_API
    void SetEnableDepthMask(bool state);
    HD_API
    bool GetEnableDepthMask();

    HD_API
    void SetEnableDepthTest(bool enabled);
    HD_API
    bool GetEnableDepthTest() const;

    HD_API
    void SetStencil(HdCompareFunction func, int ref, int mask,
                    HdStencilOp fail, HdStencilOp zfail, HdStencilOp zpass);
    HdCompareFunction GetStencilFunc() const { return _stencilFunc; }
    int GetStencilRef() const { return _stencilRef; }
    int GetStencilMask() const { return _stencilMask; }
    HdStencilOp GetStencilFailOp() const { return _stencilFailOp; }
    HdStencilOp GetStencilDepthFailOp() const { return _stencilZFailOp; }
    HdStencilOp GetStencilDepthPassOp() const { return _stencilZPassOp; }
    HD_API
    void SetStencilEnabled(bool enabled);
    HD_API
    bool GetStencilEnabled() const;

    HD_API
    void SetLineWidth(float width);
    float GetLineWidth() const { return _lineWidth; }

    HD_API
    void SetBlend(HdBlendOp colorOp,
                  HdBlendFactor colorSrcFactor,
                  HdBlendFactor colorDstFactor,
                  HdBlendOp alphaOp,
                  HdBlendFactor alphaSrcFactor,
                  HdBlendFactor alphaDstFactor);
    HdBlendOp GetBlendColorOp() { return _blendColorOp; }
    HdBlendFactor GetBlendColorSrcFactor() { return _blendColorSrcFactor; }
    HdBlendFactor GetBlendColorDstFactor() { return _blendColorDstFactor; }
    HdBlendOp GetBlendAlphaOp() { return _blendAlphaOp; }
    HdBlendFactor GetBlendAlphaSrcFactor() { return _blendAlphaSrcFactor; }
    HdBlendFactor GetBlendAlphaDstFactor() { return _blendAlphaDstFactor; }
    HD_API
    void SetBlendConstantColor(GfVec4f const & color);
    const GfVec4f& GetBlendConstantColor() const { return _blendConstantColor; }
    HD_API
    void SetBlendEnabled(bool enabled);

    HD_API
    void SetAlphaToCoverageEnabled(bool enabled);
    bool GetAlphaToCoverageEnabled() const { return _alphaToCoverageEnabled; }

    HD_API
    void SetColorMaskUseDefault(bool useDefault);
    bool GetColorMaskUseDefault() const { return _colorMaskUseDefault;}

    enum ColorMask {
        ColorMaskNone,
        ColorMaskRGB,
        ColorMaskRGBA
    };

    HD_API
    void SetColorMasks(std::vector<ColorMask> const& masks);
    std::vector<ColorMask> const& GetColorMasks() const { return _colorMasks; }

protected:
    // ---------------------------------------------------------------------- //
    // Camera and framing state
    // ---------------------------------------------------------------------- //
    HdCamera const *_camera;
    GfVec4f _viewport;
    CameraUtilFraming _framing;
    std::pair<bool, CameraUtilConformWindowPolicy> _overrideWindowPolicy;
    // TODO: This is only used for CPU culling, should compute it on the fly.
    GfMatrix4d _cullMatrix;

    // Used by applications setting the view matrix directly instead of
    // using an HdCamera. Will be removed eventually.
    GfMatrix4d _worldToViewMatrix;
    // Used by applications setting the projection matrix directly instead
    // of using an HdCamera. Will be removed eventually.
    GfMatrix4d _projectionMatrix;
    // Used by applications setting the clip planes directly instead
    // of using an HdCamera. Will be removed eventually.
    ClipPlanesVector _clipPlanes;

    // ---------------------------------------------------------------------- //
    // Application rendering state
    // ---------------------------------------------------------------------- //
    GfVec4f _overrideColor;
    GfVec4f _wireframeColor;
    GfVec4f _pointColor;
    float _pointSize;
    bool _lightingEnabled;

    GfVec4f _maskColor;
    GfVec4f _indicatorColor;
    float _pointSelectedSize;

    // ---------------------------------------------------------------------- //
    // Render pipeline state
    // ---------------------------------------------------------------------- //
    float _alphaThreshold;
    float _tessLevel;
    GfVec2f _drawRange;

    bool _depthBiasUseDefault; // inherit existing state, ignore values below.
    bool _depthBiasEnabled;
    float _depthBiasConstantFactor;
    float _depthBiasSlopeFactor;
    HdCompareFunction _depthFunc;
    bool _depthMaskEnabled;
    bool _depthTestEnabled;

    HdCullStyle _cullStyle;

    // Stencil RenderPassState
    HdCompareFunction _stencilFunc;
    int _stencilRef;
    int _stencilMask;
    HdStencilOp _stencilFailOp;
    HdStencilOp _stencilZFailOp;
    HdStencilOp _stencilZPassOp;
    bool _stencilEnabled;

    // Line width
    float _lineWidth;

    // Blending
    HdBlendOp _blendColorOp;
    HdBlendFactor _blendColorSrcFactor;
    HdBlendFactor _blendColorDstFactor;
    HdBlendOp _blendAlphaOp;
    HdBlendFactor _blendAlphaSrcFactor;
    HdBlendFactor _blendAlphaDstFactor;
    GfVec4f _blendConstantColor;
    bool _blendEnabled;

    // alpha to coverage
    bool _alphaToCoverageEnabled;

    bool _colorMaskUseDefault;
    std::vector<ColorMask> _colorMasks;

    HdRenderPassAovBindingVector _aovBindings;
    bool _useMultiSampleAov;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_RENDER_PASS_STATE_H
