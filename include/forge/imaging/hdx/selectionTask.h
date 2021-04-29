#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/selectionTask.h"
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
#ifndef FORGE_IMAGING_HDX_SELECTION_TASK_H
#define FORGE_IMAGING_HDX_SELECTION_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hd/task.h"

#include "forge/base/gf/vec4f.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


class HdRenderIndex;
class HdSceneDelegate;

struct HdxSelectionTaskParams
{
    bool enableSelection;
    float occludedSelectionOpacity; // lerp factor when blending
                                    // occluded selection
    GfVec4f selectionColor; // "active" selection color
    GfVec4f locateColor; // "rollover" selection color
};

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

/// \class HdxSelectionTask
///
/// The SelectionTask is responsible for setting up render pass global buffers
/// for selection and depositing those buffers into the task context for down
/// stream consumption. Any render pass which wants to display selection may
/// extract those buffers and bind them into the current render pass shader to
/// enable selection highlighting.
///
class HdxSelectionTask : public HdTask
{
public:
    HDX_API
    HdxSelectionTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxSelectionTask() override;

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
    int _lastVersion;
    bool _hasSelection;
    HdxSelectionTaskParams _params;
    HdBufferArrayRangeSharedPtr _selOffsetBar;
    HdBufferArrayRangeSharedPtr _selUniformBar;
    HdBufferArrayRangeSharedPtr _selPointColorsBar;

    HdxSelectionTask() = delete;
    HdxSelectionTask(const HdxSelectionTask &) = delete;
    HdxSelectionTask &operator =(const HdxSelectionTask &) = delete;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out,
                         const HdxSelectionTaskParams& pv);
HDX_API
bool operator==(const HdxSelectionTaskParams& lhs,
                const HdxSelectionTaskParams& rhs);
HDX_API
bool operator!=(const HdxSelectionTaskParams& lhs,
                const HdxSelectionTaskParams& rhs);


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_SELECTION_TASK_H
