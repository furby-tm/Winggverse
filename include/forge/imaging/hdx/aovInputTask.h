#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/aovInputTask.h"
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
#ifndef FORGE_IMAGING_HDX_AOV_INPUT_TASK_H
#define FORGE_IMAGING_HDX_AOV_INPUT_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"
#include "forge/imaging/hgi/texture.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxAovInputTask
///
/// A task for taking input AOV data comming from a render buffer that was
/// filled by render tasks and converting it to a HgiTexture.
/// The aov render buffer can be a GPU or CPU buffer, while the resulting output
/// HgiTexture will always be a GPU texture.
///
/// The HgiTexture is placed in the shared task context so that following tasks
/// maybe operate on this HgiTexture without having to worry about converting
/// the aov data from CPU to GPU.
///
class HdxAovInputTask : public HdxTask
{
public:
    HDX_API
    HdxAovInputTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxAovInputTask() override;

    /// Hooks for progressive rendering.
    bool IsConverged() const override;

    HDX_API
    void Prepare(
        HdTaskContext* ctx,
        HdRenderIndex* renderIndex) override;

    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    HDX_API
    void _Sync(
        HdSceneDelegate* delegate,
        HdTaskContext* ctx,
        HdDirtyBits* dirtyBits) override;

private:
    void _UpdateTexture(
        HdTaskContext* ctx,
        HgiTextureHandle& texture,
        HdRenderBuffer* buffer);

    void _UpdateIntermediateTexture(
        HgiTextureHandle& texture,
        HdRenderBuffer* buffer);

    bool _converged;

    SdfPath _aovBufferPath;
    SdfPath _depthBufferPath;

    HdRenderBuffer* _aovBuffer;
    HdRenderBuffer* _depthBuffer;

    HgiTextureHandle _aovTexture;
    HgiTextureHandle _depthTexture;
    HgiTextureHandle _aovTextureIntermediate;

    HdxAovInputTask() = delete;
    HdxAovInputTask(const HdxAovInputTask &) = delete;
    HdxAovInputTask &operator =(const HdxAovInputTask &) = delete;
};


/// \class HdxAovInputTaskParams
///
/// AovInput parameters.
///
struct HdxAovInputTaskParams
{
    HdxAovInputTaskParams()
        : aovBufferPath()
        , depthBufferPath()
        {}

    SdfPath aovBufferPath;
    SdfPath depthBufferPath;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxAovInputTaskParams& pv);
HDX_API
bool operator==(const HdxAovInputTaskParams& lhs,
                const HdxAovInputTaskParams& rhs);
HDX_API
bool operator!=(const HdxAovInputTaskParams& lhs,
                const HdxAovInputTaskParams& rhs);


FORGE_NAMESPACE_END

#endif
