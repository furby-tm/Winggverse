#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/graphicsCmds.h"
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
#ifndef FORGE_IMAGING_HGI_GL_GRAPHICS_CMDS_H
#define FORGE_IMAGING_HGI_GL_GRAPHICS_CMDS_H

#include "forge/forge.h"
#include "forge/base/gf/vec4i.h"
#include "forge/imaging/hgi/graphicsCmds.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/hgi.h"
#include <cstdint>

FORGE_NAMESPACE_BEGIN

struct HgiGraphicsCmdsDesc;
class HgiGLDevice;

/// \class HgiGLGraphicsCmds
///
/// OpenGL implementation of HgiGraphicsCmds.
///
class HgiGLGraphicsCmds final : public HgiGraphicsCmds
{
public:
    HGIGL_API
    ~HgiGLGraphicsCmds() override;

    /// XXX This function is exposed temporarily for Hgi transition.
    /// It allows code that is not yet converted to Hgi (e.g. HdPh) to insert
    /// its opengl calls into the ops-stack of HgiGL to ensure that all commands
    /// execute in the correct order. Once HdPh has transition fully to Hgi we
    /// should remove this function.
    HGIGL_API
    void InsertFunctionOp(std::function<void(void)> const& fn);

    HGIGL_API
    void PushDebugGroup(const char* label) override;

    HGIGL_API
    void PopDebugGroup() override;

    HGIGL_API
    void SetViewport(GfVec4i const& vp) override;

    HGIGL_API
    void SetScissor(GfVec4i const& sc) override;

    HGIGL_API
    void BindPipeline(HgiGraphicsPipelineHandle pipeline) override;

    HGIGL_API
    void BindResources(HgiResourceBindingsHandle resources) override;

    HGIGL_API
    void SetConstantValues(
        HgiGraphicsPipelineHandle pipeline,
        HgiShaderStage stages,
        uint32_t bindIndex,
        uint32_t byteSize,
        const void* data) override;

    HGIGL_API
    void BindVertexBuffers(
        uint32_t firstBinding,
        HgiBufferHandleVector const& buffers,
        std::vector<uint32_t> const& byteOffsets) override;

    HGIGL_API
    void Draw(
        uint32_t vertexCount,
        uint32_t firstVertex,
        uint32_t instanceCount) override;

    HGIGL_API
    void DrawIndirect(
        HgiBufferHandle const& drawParameterBuffer,
        uint32_t drawBufferOffset,
        uint32_t drawCount,
        uint32_t stride) override;

    HGIGL_API
    void DrawIndexed(
        HgiBufferHandle const& indexBuffer,
        uint32_t indexCount,
        uint32_t indexBufferByteOffset,
        uint32_t vertexOffset,
        uint32_t instanceCount) override;

    HGIGL_API
    void DrawIndexedIndirect(
        HgiBufferHandle const& indexBuffer,
        HgiBufferHandle const& drawParameterBuffer,
        uint32_t drawBufferOffset,
        uint32_t drawCount,
        uint32_t stride) override;

    HGIGL_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLGraphicsCmds(
        HgiGLDevice* device,
        HgiGraphicsCmdsDesc const& desc);

    HGIGL_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiGLGraphicsCmds() = delete;
    HgiGLGraphicsCmds & operator=(const HgiGLGraphicsCmds&) = delete;
    HgiGLGraphicsCmds(const HgiGLGraphicsCmds&) = delete;

    /// This performs multisample resolve when needed at the end of recording.
    void _AddResolveToOps(HgiGLDevice* device);

    bool _recording;
    HgiGraphicsCmdsDesc _descriptor;
    HgiPrimitiveType _primitiveType;
    HgiGLOpsVector _ops;
    int _pushStack;

    // Cmds is used only one frame so storing multi-frame state on will not
    // survive.
};

FORGE_NAMESPACE_END

#endif
