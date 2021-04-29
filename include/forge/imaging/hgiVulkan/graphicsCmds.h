#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/graphicsCmds.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_GRAPHICS_CMDS_H
#define FORGE_IMAGING_HGIVULKAN_GRAPHICS_CMDS_H

#include "forge/forge.h"
#include "forge/base/gf/vec4i.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"
#include "forge/imaging/hgi/graphicsCmds.h"
#include <cstdint>
#include <functional>
#include <vector>

FORGE_NAMESPACE_BEGIN

struct HgiGraphicsCmdsDesc;
class HgiVulkan;
class HgiVulkanCommandBuffer;

using HgiVulkanGfxFunction = std::function<void(void)>;
using HgiVulkanGfxFunctionVector = std::vector<HgiVulkanGfxFunction>;


/// \class HgiVulkanGraphicsCmds
///
/// Vulkan implementation of HgiGraphicsEncoder.
///
class HgiVulkanGraphicsCmds final : public HgiGraphicsCmds
{
public:
    HGIVULKAN_API
    ~HgiVulkanGraphicsCmds() override;

    HGIVULKAN_API
    void PushDebugGroup(const char* label) override;

    HGIVULKAN_API
    void PopDebugGroup() override;

    HGIVULKAN_API
    void SetViewport(GfVec4i const& vp) override;

    HGIVULKAN_API
    void SetScissor(GfVec4i const& sc) override;

    HGIVULKAN_API
    void BindPipeline(HgiGraphicsPipelineHandle pipeline) override;

    HGIVULKAN_API
    void BindResources(HgiResourceBindingsHandle resources) override;

    HGIVULKAN_API
    void SetConstantValues(
        HgiGraphicsPipelineHandle pipeline,
        HgiShaderStage stages,
        uint32_t bindIndex,
        uint32_t byteSize,
        const void* data) override;

    HGIVULKAN_API
    void BindVertexBuffers(
        uint32_t firstBinding,
        HgiBufferHandleVector const& buffers,
        std::vector<uint32_t> const& byteOffsets) override;

    HGIVULKAN_API
    void Draw(
        uint32_t vertexCount,
        uint32_t firstVertex,
        uint32_t instanceCount) override;

    HGIVULKAN_API
    void DrawIndirect(
        HgiBufferHandle const& drawParameterBuffer,
        uint32_t drawBufferOffset,
        uint32_t drawCount,
        uint32_t stride) override;

    HGIVULKAN_API
    void DrawIndexed(
        HgiBufferHandle const& indexBuffer,
        uint32_t indexCount,
        uint32_t indexBufferByteOffset,
        uint32_t vertexOffset,
        uint32_t instanceCount) override;

    HGIVULKAN_API
    void DrawIndexedIndirect(
        HgiBufferHandle const& indexBuffer,
        HgiBufferHandle const& drawParameterBuffer,
        uint32_t drawBufferOffset,
        uint32_t drawCount,
        uint32_t stride) override;

    HGIVULKAN_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

    /// Returns the command buffer used inside this cmds.
    HGIVULKAN_API
    HgiVulkanCommandBuffer* GetCommandBuffer();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanGraphicsCmds(HgiVulkan* hgi, HgiGraphicsCmdsDesc const& desc);

    HGIVULKAN_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiVulkanGraphicsCmds() = delete;
    HgiVulkanGraphicsCmds & operator=(const HgiVulkanGraphicsCmds&) = delete;
    HgiVulkanGraphicsCmds(const HgiVulkanGraphicsCmds&) = delete;

    void _ApplyPendingUpdates();
    void _EndRenderPass();
    void _CreateCommandBuffer();

    HgiVulkan* _hgi;
    HgiGraphicsCmdsDesc _descriptor;
    HgiVulkanCommandBuffer* _commandBuffer;
    HgiGraphicsPipelineHandle _pipeline;
    bool _renderPassStarted;
    bool _viewportSet;
    bool _scissorSet;
    HgiVulkanGfxFunctionVector _pendingUpdates;

    // GraphicsCmds is used only one frame so storing multi-frame state on
    // GraphicsCmds will not survive.
};

FORGE_NAMESPACE_END

#endif
