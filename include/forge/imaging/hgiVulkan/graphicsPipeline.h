#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/graphicsPipeline.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_PIPELINE_H
#define FORGE_IMAGING_HGI_VULKAN_PIPELINE_H

#include "forge/forge.h"
#include "forge/base/gf/vec2i.h"
#include "forge/imaging/hgi/graphicsCmdsDesc.h"
#include "forge/imaging/hgi/graphicsPipeline.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"
#include <vector>


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;

using VkDescriptorSetLayoutVector = std::vector<VkDescriptorSetLayout>;
using VkClearValueVector = std::vector<VkClearValue>;

/// \class HgiVulkanPipeline
///
/// Vulkan implementation of HgiGraphicsPipeline.
///
class HgiVulkanGraphicsPipeline final : public HgiGraphicsPipeline
{
public:
    HGIVULKAN_API
    ~HgiVulkanGraphicsPipeline() override;

    /// Apply pipeline state
    HGIVULKAN_API
    void BindPipeline(VkCommandBuffer cb);

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the vulkan pipeline layout
    HGIVULKAN_API
    VkPipelineLayout GetVulkanPipelineLayout() const;

    /// Returns the vulkan render pass
    HGIVULKAN_API
    VkRenderPass GetVulkanRenderPass() const;

    /// Returns the vulkan frame buffer, creating it if needed.
    HGIVULKAN_API
    VkFramebuffer AcquireVulkanFramebuffer(
        HgiGraphicsCmdsDesc const& gfxDesc,
        GfVec2i* dimensions);

    /// Returns the clear values for each color and depth attachment.
    HGIVULKAN_API
    VkClearValueVector const& GetClearValues() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanGraphicsPipeline(
        HgiVulkanDevice* device,
        HgiGraphicsPipelineDesc const& desc);

private:
    HgiVulkanGraphicsPipeline() = delete;
    HgiVulkanGraphicsPipeline & operator=(const HgiVulkanGraphicsPipeline&) = delete;
    HgiVulkanGraphicsPipeline(const HgiVulkanGraphicsPipeline&) = delete;

    void _CreateRenderPass();

    struct HgiVulkan_Framebuffer {
        GfVec2i dimensions;
        HgiGraphicsCmdsDesc desc;
        VkFramebuffer vkFramebuffer;
    };

    HgiVulkanDevice* _device;
    uint64_t _inflightBits;
    VkPipeline _vkPipeline;
    VkRenderPass _vkRenderPass;
    VkPipelineLayout _vkPipelineLayout;
    VkDescriptorSetLayoutVector _vkDescriptorSetLayouts;
    VkClearValueVector _vkClearValues;

    std::vector<HgiVulkan_Framebuffer> _framebuffers;
};


FORGE_NAMESPACE_END

#endif
