#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/blitCmds.h"
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
#ifndef FORGE_IMAGING_HGI_GL_BLIT_CMDS_H
#define FORGE_IMAGING_HGI_GL_BLIT_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/blitCmds.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/hgi.h"

FORGE_NAMESPACE_BEGIN


/// \class HgiGLBlitCmds
///
/// OpenGL implementation of HgiBlitCmds.
///
class HgiGLBlitCmds final : public HgiBlitCmds
{
public:
    HGIGL_API
    ~HgiGLBlitCmds() override;

    HGIGL_API
    void PushDebugGroup(const char* label) override;

    HGIGL_API
    void PopDebugGroup() override;

    HGIGL_API
    void CopyTextureGpuToCpu(HgiTextureGpuToCpuOp const& copyOp) override;

    HGIGL_API
    void CopyTextureCpuToGpu(HgiTextureCpuToGpuOp const& copyOp) override;

    HGIGL_API
    void CopyBufferGpuToGpu(HgiBufferGpuToGpuOp const& copyOp) override;

    HGIGL_API
    void CopyBufferCpuToGpu(HgiBufferCpuToGpuOp const& copyOp) override;

    HGIGL_API
    void CopyBufferGpuToCpu(HgiBufferGpuToCpuOp const& copyOp) override;

    HGIGL_API
    void CopyTextureToBuffer(HgiTextureToBufferOp const& copyOp) override;

    HGIGL_API
    void CopyBufferToTexture(HgiBufferToTextureOp const& copyOp) override;

    HGIGL_API
    void GenerateMipMaps(HgiTextureHandle const& texture) override;

    HGIGL_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLBlitCmds();

    HGIGL_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiGLBlitCmds & operator=(const HgiGLBlitCmds&) = delete;
    HgiGLBlitCmds(const HgiGLBlitCmds&) = delete;

    HgiGLOpsVector _ops;
    int _pushStack;

    // BlitCmds is used only one frame so storing multi-frame state here will
    // not survive.
};

FORGE_NAMESPACE_END

#endif
