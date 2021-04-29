#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/device.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_DEVICE_H
#define FORGE_IMAGING_HGIVULKAN_DEVICE_H

#include "forge/forge.h"

#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

class HgiVulkanCapabilities;
class HgiVulkanCommandQueue;
class HgiVulkanInstance;
class HgiVulkanPipelineCache;


/// \class HgiVulkanDevice
///
/// Vulkan implementation of GPU device.
///
class HgiVulkanDevice final
{
public:
    HGIVULKAN_API
    HgiVulkanDevice(HgiVulkanInstance* instance);

    HGIVULKAN_API
    ~HgiVulkanDevice();

    /// Returns the vulkan device
    HGIVULKAN_API
    VkDevice GetVulkanDevice() const;

    /// Returns the vulkan memory allocator.
    HGIVULKAN_API
    VmaAllocator GetVulkanMemoryAllocator() const;

    /// Returns the command queue which manages command buffers submission.
    HGIVULKAN_API
    HgiVulkanCommandQueue* GetCommandQueue() const;

    /// Returns the device capablities / features it supports.
    HGIVULKAN_API
    HgiVulkanCapabilities const& GetDeviceCapabilities() const;

    /// Returns the type (or family index) for the graphics queue.
    HGIVULKAN_API
    uint32_t GetGfxQueueFamilyIndex() const;

    /// Returns vulkan physical device
    HGIVULKAN_API
    VkPhysicalDevice GetVulkanPhysicalDevice() const;

    /// Returns the pipeline cache.
    HGIVULKAN_API
    HgiVulkanPipelineCache* GetPipelineCache() const;

    /// Wait for all queued up commands to have been processed on device.
    /// This should ideally never be used as it creates very big stalls, but
    /// is useful for unit testing.
    HGIVULKAN_API
    void WaitForIdle();

    /// Device extension function pointers
    PFN_vkCreateRenderPass2KHR vkCreateRenderPass2KHR = 0;
    PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT = 0;
    PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT = 0;
    PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT = 0;
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT = 0;
    PFN_vkQueueBeginDebugUtilsLabelEXT vkQueueBeginDebugUtilsLabelEXT = 0;
    PFN_vkQueueEndDebugUtilsLabelEXT vkQueueEndDebugUtilsLabelEXT = 0;

private:
    HgiVulkanDevice() = delete;
    HgiVulkanDevice & operator=(const HgiVulkanDevice&) = delete;
    HgiVulkanDevice(const HgiVulkanDevice&) = delete;

    // Returns true if the provided extension is supported by the device
    bool _IsSupportedExtension(const char* extensionName) const;

    // Vulkan device objects
    VkPhysicalDevice _vkPhysicalDevice;
    VkDevice _vkDevice;
    std::vector<VkExtensionProperties> _vkExtensions;
    VmaAllocator _vmaAllocator;
    uint32_t _vkGfxsQueueFamilyIndex;
    HgiVulkanCommandQueue* _commandQueue;
    HgiVulkanCapabilities* _capabilities;
    HgiVulkanPipelineCache* _pipelineCache;
};


FORGE_NAMESPACE_END

#endif
