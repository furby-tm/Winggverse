#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/simpleLightTask.h"
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
#ifndef FORGE_IMAGING_HDX_SIMPLE_LIGHT_TASK_H
#define FORGE_IMAGING_HDX_SIMPLE_LIGHT_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"

#include "forge/imaging/hd/task.h"

#include "forge/imaging/glf/simpleLight.h"
#include "forge/imaging/glf/simpleMaterial.h"

#include "forge/imaging/cameraUtil/framing.h"

#include "forge/base/gf/vec3f.h"
#include "forge/base/tf/declarePtrs.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdRenderIndex;
class HdSceneDelegate;
class HdCamera;

using HdRenderPassSharedPtr = std::shared_ptr<class HdRenderPass>;
using HdPhSimpleLightingShaderSharedPtr =
    std::shared_ptr<class HdPhSimpleLightingShader>;
using HdxShadowMatrixComputationSharedPtr =
    std::shared_ptr<class HdxShadowMatrixComputation>;

TF_DECLARE_REF_PTRS(GlfSimpleShadowArray);


class HdxSimpleLightTask : public HdTask
{
public:
    HDX_API
    HdxSimpleLightTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxSimpleLightTask() override;

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
    std::vector<GfMatrix4d> _ComputeShadowMatrices(
        const HdCamera * camera,
        HdxShadowMatrixComputationSharedPtr const &computation) const;

    SdfPath _cameraId;
    std::map<TfToken, SdfPathVector> _lightIds;
    SdfPathVector _lightIncludePaths;
    SdfPathVector _lightExcludePaths;
    size_t _numLights;

    // Should be weak ptrs
    HdPhSimpleLightingShaderSharedPtr _lightingShader;
    bool _enableShadows;
    GfVec4f _viewport;
    CameraUtilFraming _framing;
    std::pair<bool, CameraUtilConformWindowPolicy> _overrideWindowPolicy;

    // XXX: compatibility hack for passing some unit tests until we have
    //      more formal material plumbing.
    GlfSimpleMaterial _material;
    GfVec4f _sceneAmbient;

    // For now these are only valid for the lifetime of a single pass of
    // the render graph.  Maybe long-term these could be change-tracked.
    GlfSimpleLightVector _glfSimpleLights;

    size_t _AppendLightsOfType(HdRenderIndex &renderIndex,
                               std::vector<TfToken> const &lightTypes,
                               SdfPathVector const &lightIncludePaths,
                               SdfPathVector const &lightExcludePaths,
                               std::map<TfToken, SdfPathVector> *lights);

    HdxSimpleLightTask() = delete;
    HdxSimpleLightTask(const HdxSimpleLightTask &) = delete;
    HdxSimpleLightTask &operator =(const HdxSimpleLightTask &) = delete;
};

struct HdxSimpleLightTaskParams {
    HdxSimpleLightTaskParams()
        : cameraPath()
        , lightIncludePaths(1, SdfPath::AbsoluteRootPath())
        , lightExcludePaths()
        , enableShadows(false)
        , viewport(0.0f)
        , overrideWindowPolicy{false, CameraUtilFit}
        , material()
        , sceneAmbient(0)
        {}

    SdfPath cameraPath;
    SdfPathVector lightIncludePaths;
    SdfPathVector lightExcludePaths;
    bool enableShadows;
    GfVec4f viewport;
    CameraUtilFraming framing;
    std::pair<bool, CameraUtilConformWindowPolicy> overrideWindowPolicy;

    // XXX: compatibility hack for passing some unit tests until we have
    //      more formal material plumbing.
    GlfSimpleMaterial material;
    GfVec4f sceneAmbient;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxSimpleLightTaskParams& pv);
HDX_API
bool operator==(
    const HdxSimpleLightTaskParams& lhs,
    const HdxSimpleLightTaskParams& rhs);
HDX_API
bool operator!=(
    const HdxSimpleLightTaskParams& lhs,
    const HdxSimpleLightTaskParams& rhs);

struct HdxShadowParams {
    HdxShadowParams()
        : shadowMatrix()
        , bias(0.0)
        , blur(0.0)
        , resolution(0)
        , enabled(false)
        {}

    HdxShadowMatrixComputationSharedPtr shadowMatrix;
    double bias;
    double blur;
    int resolution;
    bool enabled;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxShadowParams& pv);
HDX_API
bool operator==(const HdxShadowParams& lhs, const HdxShadowParams& rhs);
HDX_API
bool operator!=(const HdxShadowParams& lhs, const HdxShadowParams& rhs);


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_SIMPLE_LIGHT_TASK_H
