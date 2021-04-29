#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/pipelineCache.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_PIPELINE_CACHE_H
#define FORGE_IMAGING_HGI_VULKAN_PIPELINE_CACHE_H

#include "forge/forge.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;

/// \class HgiVulkanPipelineCache
///
/// Wrapper for Vulkan pipeline cache.
///
class HgiVulkanPipelineCache final
{
public:
    HGIVULKAN_API
    HgiVulkanPipelineCache(HgiVulkanDevice* device);

    HGIVULKAN_API
    ~HgiVulkanPipelineCache();

    /// Returns the vulkan pipeline cache.
    HGIVULKAN_API
    VkPipelineCache GetVulkanPipelineCache() const;

private:
    HgiVulkanPipelineCache() = delete;
    HgiVulkanPipelineCache & operator=(const HgiVulkanPipelineCache&) = delete;
    HgiVulkanPipelineCache(const HgiVulkanPipelineCache&) = delete;

    HgiVulkanDevice* _device;
    VkPipelineCache _vkPipelineCache;
};


FORGE_NAMESPACE_END

#endif
