#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/oitResolveTask.h"
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
#ifndef FORGE_IMAGING_HDX_OIT_RESOLVE_TASK_H
#define FORGE_IMAGING_HDX_OIT_RESOLVE_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hd/task.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


class HdSceneDelegate;

using HdPhRenderPassStateSharedPtr = std::shared_ptr<class HdPhRenderPassState>;

using HdRenderPassSharedPtr = std::shared_ptr<class HdRenderPass>;
using HdPhRenderPassShaderSharedPtr =
    std::shared_ptr<class HdPhRenderPassShader>;

/// \class HdxOitResolveTask
///
/// A task for resolving previous passes to pixels.
///
/// It is also responsible for allocating the OIT buffers, but it
/// leaves the clearing of the OIT buffers to the OIT render tasks.
/// OIT render tasks coordinate with the resolve task through
/// HdxOitResolveTask::OitBufferAccessor.
///
class HdxOitResolveTask : public HdTask
{
public:
    HDX_API
    static bool IsOitEnabled();

    HDX_API
    HdxOitResolveTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxOitResolveTask() override;

    /// Sync the resolve pass resources
    HDX_API
    void Sync(HdSceneDelegate* delegate,
              HdTaskContext* ctx,
              HdDirtyBits* dirtyBits) override;

    /// Prepare the tasks resources
    ///
    /// Allocates OIT buffers if requested by OIT render task
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute render pass task
    ///
    /// Resolves OIT buffers
    HDX_API
    void Execute(HdTaskContext* ctx) override;

private:
    HdxOitResolveTask() = delete;
    HdxOitResolveTask(const HdxOitResolveTask &) = delete;
    HdxOitResolveTask &operator =(const HdxOitResolveTask &) = delete;

    void _PrepareOitBuffers(
        HdTaskContext* ctx,
        HdRenderIndex* renderIndex,
        GfVec2i const& screenSize);

    void _PrepareAovBindings(
        HdTaskContext* ctx,
        HdRenderIndex* renderIndex);

    HdRenderPassSharedPtr _renderPass;
    HdPhRenderPassStateSharedPtr _renderPassState;
    HdPhRenderPassShaderSharedPtr _renderPassShader;

    GfVec2i _screenSize;
    HdBufferArrayRangeSharedPtr _counterBar;
    HdBufferArrayRangeSharedPtr _dataBar;
    HdBufferArrayRangeSharedPtr _depthBar;
    HdBufferArrayRangeSharedPtr _indexBar;
    HdBufferArrayRangeSharedPtr _uniformBar;
};

FORGE_NAMESPACE_END

#endif
