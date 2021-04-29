#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/engine.h"
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
#ifndef FORGE_IMAGING_HD_ENGINE_H
#define FORGE_IMAGING_HD_ENGINE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"

#include "forge/imaging/hd/task.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdRenderIndex;
class HdRenderDelegate;
class HdResourceRegistry;

using HdRenderPassSharedPtr = std::shared_ptr<class HdRenderPass>;
using HdRenderPassStateSharedPtr = std::shared_ptr<class HdRenderPassState>;

/// \class HdEngine
///
/// The application-facing entry point top-level entry point for accessing Hydra.
/// Typically the application would only create one of these.
class HdEngine {
public:
    HD_API
    HdEngine();
    HD_API
    virtual ~HdEngine();

    /// \name Task Context
    ///
    /// External interface to set data/state in the task context passed to
    /// each task in the render graph
    ///
    /// @{

    /// Adds or updates the value associated with the token.
    /// Only one is supported for each token.
    HD_API
    void SetTaskContextData(const TfToken &id, const VtValue &data);

    /// If found, will return the value from the task context data associated
    /// with the token. Returns false if the data could not be found.
    HD_API
    bool GetTaskContextData(const TfToken &id, VtValue *data) const;

    /// Removes the specified token.
    HD_API
    void RemoveTaskContextData(const TfToken &id);

    /// Removes all keys.
    HD_API
    void ClearTaskContextData();

    /// @}

    /// Execute tasks.
    HD_API
    void Execute(HdRenderIndex *index,
                 HdTaskSharedPtrVector *tasks);


private:
    /// Context containing token-value pairs, that is passed to each
    /// task in the render graph.  The task-context can be pre-populated
    /// and managed externally, so the state is persistent between runs of the
    /// render graph.
    HdTaskContext _taskContext;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_ENGINE_H
