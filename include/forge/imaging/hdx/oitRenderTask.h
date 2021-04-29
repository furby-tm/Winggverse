#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/oitRenderTask.h"
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
#ifndef FORGE_IMAGING_HDX_OIT_RENDER_TASK_H
#define FORGE_IMAGING_HDX_OIT_RENDER_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hdx/renderTask.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPhRenderPassShaderSharedPtr = std::shared_ptr<HdPhRenderPassShader>;

/// \class HdxOitRenderTask
///
/// A task for rendering transparent geometry into OIT buffers.
/// Its companion task, OITResolveTask, will blend the buffers to screen.
///
class HdxOitRenderTask : public HdxRenderTask
{
public:
    HDX_API
    HdxOitRenderTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxOitRenderTask() override;

    /// Prepare the tasks resources
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute render pass task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    /// Sync the render pass resources
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    HdxOitRenderTask() = delete;
    HdxOitRenderTask(const HdxOitRenderTask &) = delete;
    HdxOitRenderTask &operator =(const HdxOitRenderTask &) = delete;

    HdPhRenderPassShaderSharedPtr _oitTranslucentRenderPassShader;
    HdPhRenderPassShaderSharedPtr _oitOpaqueRenderPassShader;
    const bool _isOitEnabled;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_OIT_RENDER_TASK_H
