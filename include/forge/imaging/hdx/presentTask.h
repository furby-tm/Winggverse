#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/presentTask.h"
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
#ifndef FORGE_IMAGING_HDX_PRESENT_TASK_H
#define FORGE_IMAGING_HDX_PRESENT_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"
#include "forge/imaging/hgi/tokens.h"
#include "forge/imaging/hgi/types.h"
#include "forge/imaging/hgiInterop/hgiInterop.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxPresentTaskParams
///
/// PresentTask parameters.
///
struct HdxPresentTaskParams
{
    HdxPresentTaskParams()
        : dstApi(HgiTokens->OpenGL)
        , dstRegion(0)
        , enabled(true)
    {}

    // The graphics lib that is used by the application / viewer.
    // (The 'interopSrc' is determined by checking Hgi->GetAPIName)
    TfToken dstApi;

    /// The framebuffer that the AOVs are presented into. This is a
    /// VtValue that encoding a framebuffer in a dstApi specific
    /// way.
    ///
    /// E.g., a uint32_t (aka GLuint) for framebuffer object for dstApi==OpenGL.
    /// For backwards compatibility, the currently bound framebuffer is used
    /// when the VtValue is empty.
    VtValue dstFramebuffer;

    // Subrectangular region of the framebuffer over which to composite aov
    // contents. Coordinates are (left, BOTTOM, width, height).
    GfVec4i dstRegion;

    // When not enabled, present task does not execute, but still calls
    // Hgi::EndFrame.
    bool enabled;
};

/// \class HdxPresentTask
///
/// A task for taking the final result of the aovs and compositing it over the
/// currently bound framebuffer.
/// This task uses the 'color' and optionally 'depth' aov's in the task
/// context. The 'color' aov is expected to use non-integer
/// (i.e., float or norm) types to keep the interop step simple.
///
class HdxPresentTask : public HdxTask
{
public:
    // Returns true if the format is supported for presentation. This is useful
    // for upstream tasks to prepare the AOV data accordingly, and keeps the
    // interop step simple.
    HDX_API
    static bool IsFormatSupported(HgiFormat aovFormat);

    HDX_API
    HdxPresentTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxPresentTask() override;

    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    HdxPresentTaskParams _params;
    HgiInterop _interop;

    HdxPresentTask() = delete;
    HdxPresentTask(const HdxPresentTask &) = delete;
    HdxPresentTask &operator =(const HdxPresentTask &) = delete;
};



// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxPresentTaskParams& pv);
HDX_API
bool operator==(const HdxPresentTaskParams& lhs,
                const HdxPresentTaskParams& rhs);
HDX_API
bool operator!=(const HdxPresentTaskParams& lhs,
                const HdxPresentTaskParams& rhs);


FORGE_NAMESPACE_END

#endif
