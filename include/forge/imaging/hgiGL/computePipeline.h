#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/computePipeline.h"
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
#ifndef FORGE_IMAGING_HGIGL_COMPUTE_PIPELINE_H
#define FORGE_IMAGING_HGIGL_COMPUTE_PIPELINE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/computePipeline.h"
#include "forge/imaging/hgiGL/api.h"


FORGE_NAMESPACE_BEGIN


/// \class HgiGLComputePipeline
///
/// OpenGL implementation of HgiComputePipeline.
///
class HgiGLComputePipeline final : public HgiComputePipeline
{
public:
    HGIGL_API
    ~HgiGLComputePipeline() override;

    /// Apply pipeline state
    HGIGL_API
    void BindPipeline();

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLComputePipeline(HgiComputePipelineDesc const& desc);

private:
    HgiGLComputePipeline() = delete;
    HgiGLComputePipeline & operator=(const HgiGLComputePipeline&) = delete;
    HgiGLComputePipeline(const HgiGLComputePipeline&) = delete;
};


FORGE_NAMESPACE_END

#endif
