#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/diagnostic.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_DIAGNOSTIC_H
#define FORGE_IMAGING_HGIVULKAN_DIAGNOSTIC_H

#include "forge/forge.h"
#include "forge/imaging/hgiVulkan/api.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkanCommandBuffer;
class HgiVulkanDevice;
class HgiVulkanInstance;


/// Returns true if debugging is enabled (HGIVULKAN_DEBUG=1)
HGIVULKAN_API
bool HgiVulkanIsDebugEnabled();

/// Setup vulkan debug callbacks
HGIVULKAN_API
void HgiVulkanCreateDebug(HgiVulkanInstance* instance);

/// Tear down vulkan debug callbacks
HGIVULKAN_API
void HgiVulkanDestroyDebug(HgiVulkanInstance* instance);

/// Setup vulkan device debug callbacks
HGIVULKAN_API
void HgiVulkanSetupDeviceDebug(
    HgiVulkanInstance* instance,
    HgiVulkanDevice* device);

/// Add a debug name to a vulkan object
HGIVULKAN_API
void HgiVulkanSetDebugName(
    HgiVulkanDevice* device,
    uint64_t vulkanObject, /*Handle to vulkan object cast to uint64_t*/
    VkObjectType objectType,
    const char* name);

/// Begin a label in a vulkan command buffer
HGIVULKAN_API
void HgiVulkanBeginLabel(
    HgiVulkanDevice* device,
    HgiVulkanCommandBuffer* cb,
    const char* label);

/// End the last pushed label in a vulkan command buffer
HGIVULKAN_API
void HgiVulkanEndLabel(
    HgiVulkanDevice* device,
    HgiVulkanCommandBuffer* cb);

/// Begin a label in the vulkan device gfx queue
HGIVULKAN_API
void HgiVulkanBeginQueueLabel(
    HgiVulkanDevice* device,
    const char* label);

/// End the last pushed label in the vulkan device gfx queue
HGIVULKAN_API
void HgiVulkanEndQueueLabel(HgiVulkanDevice* device);

FORGE_NAMESPACE_END

#endif
