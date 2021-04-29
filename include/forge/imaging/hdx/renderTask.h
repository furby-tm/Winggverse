#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/renderTask.h"
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
#ifndef FORGE_IMAGING_HDX_RENDER_TASK_H
#define FORGE_IMAGING_HDX_RENDER_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hdx/task.h"
#include "forge/imaging/hdx/renderSetupTask.h"  // for short-term compatibility.
#include "forge/imaging/hdPh/renderPassState.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


class HdSceneDelegate;

using HdRenderPassStateSharedPtr = std::shared_ptr<class HdRenderPassState>;
using HdRenderPassSharedPtr = std::shared_ptr<class HdRenderPass>;
using HdxRenderSetupTaskSharedPtr = std::shared_ptr<class HdxRenderSetupTask>;

/// \class HdxRenderTask
///
/// A task for rendering geometry to pixels.
///
/// Rendering state management can be handled two ways:
/// 1.) An application can create an HdxRenderTask and pass it the
///     HdxRenderTaskParams struct as "params".
/// 2.) An application can create an HdxRenderSetupTask and an
///     HdxRenderTask, and pass params to the setup task. In this case
///     the setup task must run first.
///
/// Parameter unpacking is handled by HdxRenderSetupTask; in case #1,
/// HdxRenderTask creates a dummy setup task internally to manage the sync
/// process.
///
/// Case #2 introduces complexity; the benefit is that by changing which
/// setup task you run before the render task, you can change the render
/// parameters without incurring a hydra sync or rebuilding any resources.
///
class HdxRenderTask : public HdxTask
{
public:
    HDX_API
    HdxRenderTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxRenderTask() override;

    /// Hooks for progressive rendering (delegated to renderpasses).
    HDX_API
    bool IsConverged() const override;

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

protected:
    /// Sync the render pass resources
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

    HDX_API
    HdRenderPassStateSharedPtr _GetRenderPassState(HdTaskContext *ctx) const;

    // XXX: Phoenix specific API
    // While HdDrawItem is currently a core-Hydra concept, it'll be moved
    // to Phoenix. Until then, allow querying the render pass to know if there's
    // draw submission work.

    // Returns whether the render pass has any draw items to submit.
    // For non-Phoenix backends, this returns true.
    // When using with Phoenix tasks, make sure to call it after
    // HdxRenderTask::Prepare().
    HDX_API
    bool _HasDrawItems() const;

private:
    HdRenderPassSharedPtr _pass;
    TfTokenVector _renderTags;

    // Optional internal render setup task, for params unpacking.
    HdxRenderSetupTaskSharedPtr _setupTask;

    // XXX: Phoenix specific API
    // Setup additional state that HdPhRenderPassState requires.
    void _SetHdPhRenderPassState(HdTaskContext *ctx,
                                 HdPhRenderPassState *renderPassState);

    // Inspect the AOV bindings to determine if any of them need to be cleared.
    bool _NeedToClearAovs(HdRenderPassStateSharedPtr const &renderPassState)
        const;

    HdxRenderTask() = delete;
    HdxRenderTask(const HdxRenderTask &) = delete;
    HdxRenderTask &operator =(const HdxRenderTask &) = delete;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_RENDER_TASK_H
