#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/task.h"
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
#ifndef FORGE_IMAGING_HDX_TASK_H
#define FORGE_IMAGING_HDX_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hd/task.h"

FORGE_NAMESPACE_BEGIN

class Hgi;


/// \class HdxTask
///
/// Base class for (some) tasks in Hdx that provides common progressive
/// rendering and Hgi functionality.
///
/// Tasks that require neither progressive rendering nor Hgi can continue to
/// derive directly from HdTask.
///
class HdxTask : public HdTask
{
public:
    HDX_API
    HdxTask(SdfPath const& id);

    HDX_API
    ~HdxTask() override;

    /// This function returns true when a (progressive) task considers its
    /// execution results converged. Usually this means that a progressive
    /// render delegate is finished rendering into the HdRenderBuffers used by
    /// this task.
    /// Returns true by default which is a good default for rasterizers.
    ///
    /// Applications with data-driven task lists can determine their convergence
    /// state by determining which tasks are HdxTasks and then querying
    /// specifically those tasks for IsConverged.
    HDX_API
    virtual bool IsConverged() const;

    /// We override HdTask::Sync, but make it 'final' to make sure derived
    /// classes can't override it and instead override _Sync.
    /// This 'non-virtual interface'-like pattern allows us to ensure we always
    /// initialized Hgi during the Sync task so derived classes don't have to.
    void Sync(
        HdSceneDelegate* delegate,
        HdTaskContext* ctx,
        HdDirtyBits* dirtyBits) final;

protected:
    // This is called during the hydra Sync Phase via HdxTask::Sync.
    // Please see HdTask::Sync for Sync Phase documentation.
    virtual void _Sync(
        HdSceneDelegate* delegate,
        HdTaskContext* ctx,
        HdDirtyBits* dirtyBits) = 0;

    // Swaps the color target and colorIntermediate target.
    // This is used when a task wishes to read from the color and also write
    // to it. We use two color targets and ping-pong between them.
    void _ToggleRenderTarget(HdTaskContext* ctx);

    // Return pointer to Hydra Graphics Interface.
    HDX_API
    Hgi* _GetHgi() const;

    Hgi* _hgi;
};

FORGE_NAMESPACE_END

#endif
