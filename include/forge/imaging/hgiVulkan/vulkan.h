#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/vulkan.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_VULKAN_H
#define FORGE_IMAGING_HGIVULKAN_VULKAN_H

#include "forge/base/arch/defines.h"

// Define the platform for Vulkan so vulkan.h below picks the correct includes.
#if defined(ARCH_OS_WINDOWS)
    #define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ARCH_OS_LINUX)
    #define VK_USE_PLATFORM_XLIB_KHR
#elif defined(ARCH_OS_OSX)
    #define VK_USE_PLATFORM_MACOS_MVK
#else
    #error Unsupported Platform
#endif

#include <vulkan/vulkan.h>

#include "forge/imaging/hgiVulkan/vk_mem_alloc.h"

// Use the default allocator (nullptr)
inline VkAllocationCallbacks*
HgiVulkanAllocator() {
    return nullptr;
}

#endif
