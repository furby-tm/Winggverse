#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/oitBufferAccessor.h"
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
#ifndef FORGE_IMAGING_HDX_OIT_BUFFER_ACCESSOR_H
#define FORGE_IMAGING_HDX_OIT_BUFFER_ACCESSOR_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"

#include "forge/imaging/hd/task.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdBufferArrayRangeSharedPtr =
    std::shared_ptr<class HdBufferArrayRange>;

using HdPhRenderPassShaderSharedPtr =
    std::shared_ptr<class HdPhRenderPassShader>;

/// Class for OIT render tasks to access the OIT buffers.
class HdxOitBufferAccessor {
public:
    static bool IsOitEnabled();

    HDX_API
    HdxOitBufferAccessor(HdTaskContext *ctx);

    /// Called during Prepare to indicate that OIT buffers are needed.
    HDX_API
    void RequestOitBuffers();

    /// Called during Excecute before writing to OIT buffers.
    HDX_API
    void InitializeOitBuffersIfNecessary();

    /// Called during Execute to add necessary OIT buffer shader bindings.
    ///
    /// Returns false if the OIT buffers were not allocated.
    HDX_API
    bool AddOitBufferBindings(const HdPhRenderPassShaderSharedPtr &);

private:
    HdBufferArrayRangeSharedPtr const &_GetBar(const TfToken &);

    HdTaskContext * const _ctx;
};

FORGE_NAMESPACE_END

#endif
