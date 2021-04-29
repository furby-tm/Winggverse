#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/computeCmds.h"
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
#ifndef FORGE_IMAGING_HGI_GL_COMPUTE_CMDS_H
#define FORGE_IMAGING_HGI_GL_COMPUTE_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/computeCmds.h"
#include "forge/imaging/hgi/computePipeline.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/hgi.h"
#include <cstdint>

FORGE_NAMESPACE_BEGIN

/// \class HgiGLComputeCmds
///
/// OpenGL implementation of HgiComputeCmds.
///
class HgiGLComputeCmds final : public HgiComputeCmds
{
public:
    HGIGL_API
    ~HgiGLComputeCmds() override;

    HGIGL_API
    void PushDebugGroup(const char* label) override;

    HGIGL_API
    void PopDebugGroup() override;

    HGIGL_API
    void BindPipeline(HgiComputePipelineHandle pipeline) override;

    HGIGL_API
    void BindResources(HgiResourceBindingsHandle resources) override;

    HGIGL_API
    void SetConstantValues(
        HgiComputePipelineHandle pipeline,
        uint32_t bindIndex,
        uint32_t byteSize,
        const void* data) override;

    HGIGL_API
    void Dispatch(int dimX, int dimY) override;

    HGIGL_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLComputeCmds(HgiGLDevice* device);

    HGIGL_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiGLComputeCmds() = delete;
    HgiGLComputeCmds & operator=(const HgiGLComputeCmds&) = delete;
    HgiGLComputeCmds(const HgiGLComputeCmds&) = delete;

    HgiGLOpsVector _ops;
    int _pushStack;

    // Cmds is used only one frame so storing multi-frame state on will not
    // survive.
};

FORGE_NAMESPACE_END

#endif
