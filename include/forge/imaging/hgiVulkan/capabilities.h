#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/capabilities.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_CAPABILITIES_H
#define FORGE_IMAGING_HGIVULKAN_CAPABILITIES_H

#include "forge/forge.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;

/// \class HgiVulkanCapabilities
///
/// Reports the capabilities of the Vulkan device.
///
class HgiVulkanCapabilities final
{
public:
    HGIVULKAN_API
    HgiVulkanCapabilities(HgiVulkanDevice* device);

    HGIVULKAN_API
    ~HgiVulkanCapabilities();

    bool supportsTimeStamps;
    VkPhysicalDeviceProperties vkDeviceProperties;
    VkPhysicalDeviceFeatures vkDeviceFeatures;
    VkPhysicalDeviceFeatures2 vkDeviceFeatures2;
    VkPhysicalDeviceDescriptorIndexingFeaturesEXT vkIndexingFeatures;
    VkPhysicalDeviceMemoryProperties vkMemoryProperties;
};

FORGE_NAMESPACE_END

#endif
