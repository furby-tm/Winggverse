#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/buffer.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_BUFFER_H
#define FORGE_IMAGING_HGIVULKAN_BUFFER_H

#include "forge/imaging/hgi/buffer.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanCommandBuffer;
class HgiVulkanDevice;

///
/// \class HgiVulkanBuffer
///
/// Vulkan implementation of HgiBuffer
///
class HgiVulkanBuffer final : public HgiBuffer
{
public:
    HGIVULKAN_API
    ~HgiVulkanBuffer() override;

    HGIVULKAN_API
    size_t GetByteSizeOfResource() const override;

    HGIVULKAN_API
    uint64_t GetRawResource() const override;

    HGIVULKAN_API
    void* GetCPUStagingAddress() override;

    /// Returns true if the provided ptr matches the address of staging buffer.
    HGIVULKAN_API
    bool IsCPUStagingAddress(const void* address) const;

    /// Returns the vulkan buffer.
    HGIVULKAN_API
    VkBuffer GetVulkanBuffer() const;

    /// Returns the memory allocation
    HGIVULKAN_API
    VmaAllocation GetVulkanMemoryAllocation() const;

    /// Returns the staging buffer.
    HGIVULKAN_API
    HgiVulkanBuffer* GetStagingBuffer() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

    /// Creates a staging buffer.
    /// The caller is responsible for the lifetime (destruction) of the buffer.
    HGIVULKAN_API
    static HgiVulkanBuffer* CreateStagingBuffer(
        HgiVulkanDevice* device,
        HgiBufferDesc const& desc);

protected:
    friend class HgiVulkan;

    // Constructor for making buffers
    HGIVULKAN_API
    HgiVulkanBuffer(
        HgiVulkan* hgi,
        HgiVulkanDevice* device,
        HgiBufferDesc const& desc);

    // Constructor for making staging buffers
    HGIVULKAN_API
    HgiVulkanBuffer(
        HgiVulkanDevice* device,
        VkBuffer vkBuffer,
        VmaAllocation vmaAllocation,
        HgiBufferDesc const& desc);

private:
    HgiVulkanBuffer() = delete;
    HgiVulkanBuffer & operator=(const HgiVulkanBuffer&) = delete;
    HgiVulkanBuffer(const HgiVulkanBuffer&) = delete;

    HgiVulkanDevice* _device;
    VkBuffer _vkBuffer;
    VmaAllocation _vmaAllocation;
    uint64_t _inflightBits;
    HgiVulkanBuffer* _stagingBuffer;
    void* _cpuStagingAddress;
};


FORGE_NAMESPACE_END

#endif
