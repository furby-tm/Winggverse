#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/resourceBindings.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_RESOURCEBINDINGS_H
#define FORGE_IMAGING_HGI_VULKAN_RESOURCEBINDINGS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;


///
/// \class HgiVulkanResourceBindings
///
/// Vulkan implementation of HgiResourceBindings.
///
///
class HgiVulkanResourceBindings final : public HgiResourceBindings
{
public:
    HGIVULKAN_API
    ~HgiVulkanResourceBindings() override;

    /// Binds the resources to GPU.
    HGIVULKAN_API
    void BindResources(
        VkCommandBuffer cb,
        VkPipelineBindPoint bindPoint,
        VkPipelineLayout layout);

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanResourceBindings(
        HgiVulkanDevice* device,
        HgiResourceBindingsDesc const& desc);

private:
    HgiVulkanResourceBindings() = delete;
    HgiVulkanResourceBindings & operator=(const HgiVulkanResourceBindings&) = delete;
    HgiVulkanResourceBindings(const HgiVulkanResourceBindings&) = delete;

    HgiVulkanDevice* _device;
    uint64_t _inflightBits;

    VkDescriptorPool _vkDescriptorPool;
    VkDescriptorSetLayout _vkDescriptorSetLayout;
    VkDescriptorSet _vkDescriptorSet;
};


FORGE_NAMESPACE_END

#endif
