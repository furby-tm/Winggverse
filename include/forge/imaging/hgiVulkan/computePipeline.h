#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/computePipeline.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_COMPUTE_PIPELINE_H
#define FORGE_IMAGING_HGI_VULKAN_COMPUTE_PIPELINE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/computePipeline.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"
#include <vector>


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;

using VkDescriptorSetLayoutVector = std::vector<VkDescriptorSetLayout>;


/// \class HgiVulkanComputePipeline
///
/// Vulkan implementation of HgiComputePipeline.
///
class HgiVulkanComputePipeline final : public HgiComputePipeline
{
public:
    HGIVULKAN_API
    ~HgiVulkanComputePipeline() override;

    /// Apply pipeline state
    HGIVULKAN_API
    void BindPipeline(VkCommandBuffer cb);

    /// Returns the vulkan pipeline layout
    HGIVULKAN_API
    VkPipelineLayout GetVulkanPipelineLayout() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanComputePipeline(
        HgiVulkanDevice* device,
        HgiComputePipelineDesc const& desc);

private:
    HgiVulkanComputePipeline() = delete;
    HgiVulkanComputePipeline & operator=(const HgiVulkanComputePipeline&) = delete;
    HgiVulkanComputePipeline(const HgiVulkanComputePipeline&) = delete;

    HgiVulkanDevice* _device;
    uint64_t _inflightBits;
    VkPipeline _vkPipeline;
    VkPipelineLayout _vkPipelineLayout;
    VkDescriptorSetLayoutVector _vkDescriptorSetLayouts;
};


FORGE_NAMESPACE_END

#endif
