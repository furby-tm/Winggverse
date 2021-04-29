#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/renderSetupTask.h"
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
#ifndef FORGE_IMAGING_HDX_RENDER_SETUP_TASK_H
#define FORGE_IMAGING_HDX_RENDER_SETUP_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hd/task.h"
#include "forge/imaging/hd/tokens.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/renderPassState.h"

#include "forge/imaging/cameraUtil/framing.h"

#include "forge/base/gf/vec2f.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/gf/vec4d.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdxRenderSetupTaskSharedPtr =
    std::shared_ptr<class HdxRenderSetupTask>;
using HdPhRenderPassShaderSharedPtr =
    std::shared_ptr<class HdPhRenderPassShader>;
using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;

using HdRenderPassStateSharedPtr = std::shared_ptr<class HdRenderPassState>;

struct HdxRenderTaskParams;
class HdPhRenderPassState;


/// \class HdxRenderSetupTask
///
/// A task for setting up render pass state (camera, renderpass shader, GL
/// states).
///
/// HdxRenderTask depends on the output of this task.  Applications can choose
/// to create a render setup task, and pass it the HdxRenderTaskParams; or they
/// can pass the HdxRenderTaskParams directly to the render task, which will
/// create a render setup task internally.  See the HdxRenderTask documentation
/// for details.
///
class HdxRenderSetupTask : public HdTask
{
public:
    HDX_API
    HdxRenderSetupTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxRenderSetupTask() override;


    // APIs used from HdxRenderTask to manage the sync/prepare process.
    HDX_API
    void SyncParams(HdSceneDelegate* delegate,
                    HdxRenderTaskParams const &params);
    HDX_API
    void PrepareCamera(HdRenderIndex* renderIndex);

    HdRenderPassStateSharedPtr const &GetRenderPassState() const {
        return _renderPassState;
    }

    /// Sync the render pass resources
    HDX_API
    void Sync(HdSceneDelegate* delegate,
              HdTaskContext* ctx,
              HdDirtyBits* dirtyBits) override;

    /// Prepare the tasks resources
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute render pass task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

private:
    HdRenderPassStateSharedPtr _renderPassState;
    HdPhRenderPassShaderSharedPtr _colorRenderPassShader;
    HdPhRenderPassShaderSharedPtr _idRenderPassShader;
    SdfPath _cameraId;
    CameraUtilFraming _framing;
    std::pair<bool, CameraUtilConformWindowPolicy> _overrideWindowPolicy;
    // Used when client did not specify the camera framing (more expressive
    // and preferred).
    GfVec4d _viewport;
    HdRenderPassAovBindingVector _aovBindings;

    void _SetRenderpassShadersForPhoenix(
        HdxRenderTaskParams const& params,
        HdPhRenderPassState *renderPassState);

    HdRenderPassStateSharedPtr &_GetRenderPassState(HdRenderIndex* renderIndex);

    void _PrepareAovBindings(HdTaskContext* ctx, HdRenderIndex* renderIndex);


    HdxRenderSetupTask() = delete;
    HdxRenderSetupTask(const HdxRenderSetupTask &) = delete;
    HdxRenderSetupTask &operator =(const HdxRenderSetupTask &) = delete;
};

/// \class HdxRenderTaskParams
///
/// RenderTask parameters (renderpass state).
///
struct HdxRenderTaskParams
{
    HdxRenderTaskParams()
        // Global Params
        : overrideColor(0.0)
        , wireframeColor(0.0)
        , pointColor(GfVec4f(0,0,0,1))
        , pointSize(3.0)
        , enableLighting(false)
        , enableIdRender(false)
        , alphaThreshold(0.0)
        , enableSceneMaterials(true)
        , enableSceneLights(true)
        // Selection/Masking params
        , maskColor(1.0f, 0.0f, 0.0f, 1.0f)
        , indicatorColor(0.0f, 1.0f, 0.0f, 1.0f)
        , pointSelectedSize(3.0)
        // Phoenix render pipeline state
        , depthBiasUseDefault(true)
        , depthBiasEnable(false)
        , depthBiasConstantFactor(0.0f)
        , depthBiasSlopeFactor(1.0f)
        , depthFunc(HdCmpFuncLEqual)
        , depthMaskEnable(true)
        , stencilFunc(HdCmpFuncAlways)
        , stencilRef(0)
        , stencilMask(~0)
        , stencilFailOp(HdStencilOpKeep)
        , stencilZFailOp(HdStencilOpKeep)
        , stencilZPassOp(HdStencilOpKeep)
        , stencilEnable(false)
        , blendColorOp(HdBlendOpAdd)
        , blendColorSrcFactor(HdBlendFactorOne)
        , blendColorDstFactor(HdBlendFactorZero)
        , blendAlphaOp(HdBlendOpAdd)
        , blendAlphaSrcFactor(HdBlendFactorOne)
        , blendAlphaDstFactor(HdBlendFactorZero)
        , blendConstantColor(0.0f, 0.0f, 0.0f, 0.0f)
        , blendEnable(false)
        , enableAlphaToCoverage(true)
        , useAovMultiSample(true)
        , resolveAovMultiSample(true)
        // Camera framing and viewer state
        , viewport(0.0)
        , cullStyle(HdCullStyleBackUnlessDoubleSided)
        , overrideWindowPolicy{false, CameraUtilFit}
        {}

    // ---------------------------------------------------------------------- //
    // Application rendering state
    // XXX: Several of the parameters below are specific to (or work only with)
    // Phoenix and stem from its integration in Presto and usdview.
    // ---------------------------------------------------------------------- //
    // "Global" parameters while rendering.
    GfVec4f overrideColor;
    GfVec4f wireframeColor;
    GfVec4f pointColor;
    float pointSize;
    bool enableLighting;
    bool enableIdRender;
    float alphaThreshold;
    bool enableSceneMaterials;
    bool enableSceneLights;

    // Selection/Masking params
    GfVec4f maskColor;
    GfVec4f indicatorColor;
    float pointSelectedSize;

    // AOVs to render to
    // XXX: As a transitional API, if this is empty it indicates the renderer
    // should write color and depth to the GL framebuffer.
    HdRenderPassAovBindingVector aovBindings;

    // ---------------------------------------------------------------------- //
    // Render pipeline state for rasterizers.
    // XXX: These are relevant only for Phoenix.
    // ---------------------------------------------------------------------- //
    bool depthBiasUseDefault; // inherit application GL state
    bool depthBiasEnable;
    float depthBiasConstantFactor;
    float depthBiasSlopeFactor;

    HdCompareFunction depthFunc;
    bool depthMaskEnable;

    // Stencil
    HdCompareFunction stencilFunc;
    int stencilRef;
    int stencilMask;
    HdStencilOp stencilFailOp;
    HdStencilOp stencilZFailOp;
    HdStencilOp stencilZPassOp;
    bool stencilEnable;

    // Blending
    HdBlendOp blendColorOp;
    HdBlendFactor blendColorSrcFactor;
    HdBlendFactor blendColorDstFactor;
    HdBlendOp blendAlphaOp;
    HdBlendFactor blendAlphaSrcFactor;
    HdBlendFactor blendAlphaDstFactor;
    GfVec4f blendConstantColor;
    bool blendEnable;

    // AlphaToCoverage
    bool enableAlphaToCoverage;

    // If true (default), render into the multi-sampled AOVs (rather than
    // the resolved AOVs).
    bool useAovMultiSample;

    // If true (default), multi-sampled AOVs will be resolved at the end of a
    // render pass.
    bool resolveAovMultiSample;

    // ---------------------------------------------------------------------- //
    // Viewer & Camera Framing state
    // ---------------------------------------------------------------------- //
    SdfPath camera;
    CameraUtilFraming framing;
    // Only used if framing is invalid.
    GfVec4d viewport;
    HdCullStyle cullStyle;
    std::pair<bool, CameraUtilConformWindowPolicy> overrideWindowPolicy;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxRenderTaskParams& pv);
HDX_API
bool operator==(const HdxRenderTaskParams& lhs, const HdxRenderTaskParams& rhs);
HDX_API
bool operator!=(const HdxRenderTaskParams& lhs, const HdxRenderTaskParams& rhs);


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_RENDER_SETUP_TASK_H
