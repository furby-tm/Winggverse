#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/computeCmds.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_COMPUTE_CMDS_H
#define FORGE_IMAGING_HGIVULKAN_COMPUTE_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/computeCmds.h"
#include "forge/imaging/hgi/computePipeline.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanCommandBuffer;


/// \class HgiVulkanComputeCmds
///
/// OpenGL implementation of HgiComputeCmds.
///
class HgiVulkanComputeCmds final : public HgiComputeCmds
{
public:
    HGIVULKAN_API
    ~HgiVulkanComputeCmds() override;

    HGIVULKAN_API
    void PushDebugGroup(const char* label) override;

    HGIVULKAN_API
    void PopDebugGroup() override;

    HGIVULKAN_API
    void BindPipeline(HgiComputePipelineHandle pipeline) override;

    HGIVULKAN_API
    void BindResources(HgiResourceBindingsHandle resources) override;

    HGIVULKAN_API
    void SetConstantValues(
        HgiComputePipelineHandle pipeline,
        uint32_t bindIndex,
        uint32_t byteSize,
        const void* data) override;

    HGIVULKAN_API
    void Dispatch(int dimX, int dimY) override;

    HGIVULKAN_API
    void MemoryBarrier(HgiMemoryBarrier barrier) override;

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanComputeCmds(HgiVulkan* hgi);

    HGIVULKAN_API
    bool _Submit(Hgi* hgi, HgiSubmitWaitType wait) override;

private:
    HgiVulkanComputeCmds() = delete;
    HgiVulkanComputeCmds & operator=(const HgiVulkanComputeCmds&) = delete;
    HgiVulkanComputeCmds(const HgiVulkanComputeCmds&) = delete;

    void _BindResources();
    void _CreateCommandBuffer();

    HgiVulkan* _hgi;
    HgiVulkanCommandBuffer* _commandBuffer;
    VkPipelineLayout _pipelineLayout;
    HgiResourceBindingsHandle _resourceBindings;
    bool _pushConstantsDirty;
    uint8_t* _pushConstants;
    uint32_t _pushConstantsByteSize;

    // Cmds is used only one frame so storing multi-frame state on will not
    // survive.
};

FORGE_NAMESPACE_END

#endif
