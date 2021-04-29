#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/blitCmds.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_BLIT_CMDS_H
#define FORGE_IMAGING_HGIVULKAN_BLIT_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgi/blitCmds.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanCommandBuffer;


/// \class HgiVulkanBlitCmds
///
/// Vulkan implementation of HgiBlitCmds.
///
class HgiVulkanBlitCmds final : public HgiBlitCmds
{
public:
    HGIVULKAN_API
    ~HgiVulkanBlitCmds() override;

    HGIVULKAN_API
    void PushDebugGroup(const char* label) override;

    HGIVULKAN_API
    void PopDebugGroup() override;

    HGIVULKAN_API
    void CopyTextureGpuToCpu(HgiTextureGpuToCpuOp const& copyOp) override;

    HGIVULKAN_API
    void CopyTextureCpuToGpu(HgiTextureCpuToGpuOp const& copyOp) override;

    HGIVULKAN_API
    void CopyBufferGpuToGpu(HgiBufferGpuToGpuOp const& copyOp) override;

    HGIVULKAN_API
    void CopyBufferCpuToGpu(HgiBufferCpuToGpuOp const& copyOp) override;

    HGIVULKAN_API
    void CopyBufferGpuToCpu(HgiBufferGpuToCpuOp const& copyOp) override;

    HGIVULKAN_API
    void CopyTextureToBuffer(HgiTextureToBufferOp const& copyOp) override;

    HGIVULKAN_API
    void CopyBufferToTexture(HgiBufferToTextureOp const& copyOp) override;

    HGIVULKAN_API
    void GenerateMipMaps(HgiTextureHandle const& texture) override;

    HGIVULKAN_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

    /// Returns the command buffer used inside this cmds.
    HGIVULKAN_API
    HgiVulkanCommandBuffer* GetCommandBuffer();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanBlitCmds(HgiVulkan* hgi);

    HGIVULKAN_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiVulkanBlitCmds & operator=(const HgiVulkanBlitCmds&) = delete;
    HgiVulkanBlitCmds(const HgiVulkanBlitCmds&) = delete;

    void _CreateCommandBuffer();

    HgiVulkan* _hgi;
    HgiVulkanCommandBuffer* _commandBuffer;

    // BlitCmds is used only one frame so storing multi-frame state on BlitCmds
    // will not survive.
};

FORGE_NAMESPACE_END

#endif
