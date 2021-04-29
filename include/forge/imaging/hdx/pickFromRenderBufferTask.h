#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/pickFromRenderBufferTask.h"
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
#ifndef FORGE_IMAGING_HDX_PICK_FROM_RENDER_BUFFER_TASK_H
#define FORGE_IMAGING_HDX_PICK_FROM_RENDER_BUFFER_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"

#include "forge/imaging/hd/camera.h"
#include "forge/imaging/hd/renderBuffer.h"
#include "forge/imaging/hdx/pickTask.h"

FORGE_NAMESPACE_BEGIN

/// Pick task params.  This is augmented by HdxPickTaskContextParams, which is
/// passed in on the task context.
struct HdxPickFromRenderBufferTaskParams
{
    HdxPickFromRenderBufferTaskParams()
        : primIdBufferPath()
        , instanceIdBufferPath()
        , elementIdBufferPath()
        , normalBufferPath()
        , depthBufferPath()
        , cameraId()
        , overrideWindowPolicy{false, CameraUtilFit}
        , viewport()
    {}

    SdfPath primIdBufferPath;
    SdfPath instanceIdBufferPath;
    SdfPath elementIdBufferPath;
    SdfPath normalBufferPath;
    SdfPath depthBufferPath;

    // The id of the camera used to generate the id buffers.
    SdfPath cameraId;

    // The framing specifying how the camera frustum in mapped into the
    // render buffers.
    CameraUtilFraming framing;
    // Is application overriding the window policy of the camera.
    std::pair<bool, CameraUtilConformWindowPolicy> overrideWindowPolicy;

    // The viewport of the camera used to generate the id buffers.
    // Only used if framing is invalid - for legacy clients.
    GfVec4d viewport;
};

/// \class HdxPickFromRenderBufferTask
///
/// A task for running picking queries against pre-existing id buffers.
/// This task remaps the "pick frustum", provided by HdxPickTaskContextParams,
/// to the camera frustum used to generate the ID buffers.  It then runs the
/// pick query against the subset of the ID buffers contained by the pick
/// frustum.
class HdxPickFromRenderBufferTask : public HdxTask
{
public:
    HDX_API
    HdxPickFromRenderBufferTask(HdSceneDelegate *delegate, SdfPath const& id);

    HDX_API
    ~HdxPickFromRenderBufferTask() override;

    /// Hooks for progressive rendering.
    bool IsConverged() const override;

    /// Prepare the pick task
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute the pick task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    /// Sync the render pass resources
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    GfMatrix4d _ComputeProjectionMatrix() const;

    HdxPickFromRenderBufferTaskParams _params;
    HdxPickTaskContextParams _contextParams;
    // We need to cache a pointer to the render index so Execute() can
    // map prim ID to paths.
    HdRenderIndex *_index;

    HdRenderBuffer *_primId;
    HdRenderBuffer *_instanceId;
    HdRenderBuffer *_elementId;
    HdRenderBuffer *_normal;
    HdRenderBuffer *_depth;
    const HdCamera *_camera;

    bool _converged;

    HdxPickFromRenderBufferTask() = delete;
    HdxPickFromRenderBufferTask(const HdxPickFromRenderBufferTask &) = delete;
    HdxPickFromRenderBufferTask &operator =(
        const HdxPickFromRenderBufferTask &) = delete;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxPickFromRenderBufferTaskParams& pv);
HDX_API
bool operator==(const HdxPickFromRenderBufferTaskParams& lhs,
                const HdxPickFromRenderBufferTaskParams& rhs);
HDX_API
bool operator!=(const HdxPickFromRenderBufferTaskParams& lhs,
                const HdxPickFromRenderBufferTaskParams& rhs);

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_PICK_FROM_RENDER_BUFFER_TASK_H
