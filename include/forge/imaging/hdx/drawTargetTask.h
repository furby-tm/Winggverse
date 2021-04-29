#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/drawTargetTask.h"
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
#ifndef FORGE_IMAGING_HDX_DRAW_TARGET_TASK_H
#define FORGE_IMAGING_HDX_DRAW_TARGET_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"

#include "forge/imaging/hd/task.h"

#include "forge/base/gf/vec4f.h"
#include "forge/base/tf/declarePtrs.h"

FORGE_NAMESPACE_BEGIN

class HdPhDrawTarget;
class HdPhDrawTargetRenderPassState;
using HdPhRenderPassStateSharedPtr
    = std::shared_ptr<class HdPhRenderPassState>;
using HdPhSimpleLightingShaderSharedPtr
    = std::shared_ptr<class HdPhSimpleLightingShader>;
TF_DECLARE_REF_PTRS(GlfSimpleLightingContext);

// Not strictly necessary here.
// But without it, would require users of the class to include it anyway

class HdxDrawTargetTask  : public HdTask
{
public:
    HDX_API
    HdxDrawTargetTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxDrawTargetTask() override;

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

    /// Collect Render Tags used by the task.
    HDX_API
    const TfTokenVector &GetRenderTags() const override;

private:
    struct _RenderPassInfo;
    struct _CameraInfo;
    using _RenderPassInfoVector = std::vector<_RenderPassInfo>;

    static _RenderPassInfoVector _ComputeRenderPassInfos(
        HdRenderIndex * renderIndex);

    static _CameraInfo _ComputeCameraInfo(
        const HdRenderIndex &renderIndex,
        const HdPhDrawTarget * drawTarget);
    static void _UpdateLightingContext(
        const _CameraInfo &cameraInfo,
        GlfSimpleLightingContextConstRefPtr const &srcContext,
        GlfSimpleLightingContextRefPtr const &ctx);
    void _UpdateRenderPassState(
        const HdRenderIndex &renderIndex,
        const _CameraInfo &cameraInfo,
        HdPhSimpleLightingShaderSharedPtr const &lightingShader,
        const HdPhDrawTargetRenderPassState *srcState,
        HdPhRenderPassStateSharedPtr const &state) const;
    static void _UpdateRenderPass(
        _RenderPassInfo *info);

    unsigned _currentDrawTargetSetVersion;
    _RenderPassInfoVector _renderPassesInfo;

    // Raster State - close match to render task
    // but doesn't have enableHardwareShading
    // as that has to be enabled for draw targets.
//    typedef std::vector<GfVec4d> ClipPlanesVector;
//    ClipPlanesVector _clipPlanes;
    GfVec4f _overrideColor;
    GfVec4f _wireframeColor;
    bool _enableLighting;
    float _alphaThreshold;

    /// Polygon Offset State
    bool _depthBiasUseDefault;
    bool _depthBiasEnable;
    float _depthBiasConstantFactor;
    float _depthBiasSlopeFactor;

    HdCompareFunction _depthFunc;

    // Viewer's Render Style
    HdCullStyle _cullStyle;

    // Alpha sample alpha to coverage
    bool _enableSampleAlphaToCoverage;
    TfTokenVector _renderTags;

    HdxDrawTargetTask() = delete;
    HdxDrawTargetTask(const HdxDrawTargetTask &) = delete;
    HdxDrawTargetTask &operator =(const HdxDrawTargetTask &) = delete;
};

struct HdxDrawTargetTaskParams
{
    HdxDrawTargetTaskParams()
        : overrideColor(0.0)
        , wireframeColor(0.0)
        , enableLighting(false)
        , alphaThreshold(0.0)
        , depthBiasUseDefault(true)
        , depthBiasEnable(false)
        , depthBiasConstantFactor(0.0f)
        , depthBiasSlopeFactor(1.0f)
        , depthFunc(HdCmpFuncLEqual)
        // XXX: When rendering draw targets we need alpha to coverage
        // at least until we support a transparency pass
        , enableAlphaToCoverage(true)
        , cullStyle(HdCullStyleBackUnlessDoubleSided)
        {}

//    ClipPlanesVector clipPlanes;
    GfVec4f overrideColor;
    GfVec4f wireframeColor;
    bool enableLighting;
    float alphaThreshold;

    // Depth Bias Raster State
    // When use default is true - state
    // is inherited and onther values are
    // ignored.  Otherwise the raster state
    // is set using the values specified.

    bool depthBiasUseDefault;
    bool depthBiasEnable;
    float depthBiasConstantFactor;
    float depthBiasSlopeFactor;

    HdCompareFunction depthFunc;

    bool enableAlphaToCoverage;

    // Viewer's Render Style
    HdCullStyle cullStyle;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxDrawTargetTaskParams& pv);
HDX_API
bool operator==(
    const HdxDrawTargetTaskParams& lhs,
    const HdxDrawTargetTaskParams& rhs);
HDX_API
bool operator!=(
    const HdxDrawTargetTaskParams& lhs,
    const HdxDrawTargetTaskParams& rhs);

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_DRAW_TARGET_TASK_H
