#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/texture.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_TEXTURE_H
#define FORGE_IMAGING_HGI_VULKAN_TEXTURE_H

#include "forge/forge.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgi/texture.h"


FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanBuffer;
class HgiVulkanCommandBuffer;
class HgiVulkanDevice;


/// \class HgiVulkanTexture
///
/// Represents a Vulkan GPU texture resource.
///
class HgiVulkanTexture final : public HgiTexture
{
public:
    static const uint32_t NO_PENDING_WRITES = 0;

    HGIVULKAN_API
    ~HgiVulkanTexture() override;

    HGIVULKAN_API
    size_t GetByteSizeOfResource() const override;

    HGIVULKAN_API
    uint64_t GetRawResource() const override;

    /// Creates (on first use) and returns the CPU staging buffer that can be
    /// used to upload new texture data to the image.
    /// After memcpy-ing new data into the returned address the client
    /// must use BlitCmds CopyTextureCpuToGpu to schedule the transfer
    /// from this staging buffer to the GPU texture.
    HGIVULKAN_API
    void* GetCPUStagingAddress();

    /// Returns true if the provided ptr matches the address of staging buffer.
    HGIVULKAN_API
    bool IsCPUStagingAddress(const void* address) const;

    /// Returns the staging buffer.
    HGIVULKAN_API
    HgiVulkanBuffer* GetStagingBuffer() const;

    /// Returns the image of the texture
    HGIVULKAN_API
    VkImage GetImage() const;

    /// Returns the image view of the texture
    HGIVULKAN_API
    VkImageView GetImageView() const;

    /// Returns the image layout of the texture
    HGIVULKAN_API
    VkImageLayout GetImageLayout() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

    /// Schedule a copy of texels from the provided buffer into the texture.
    /// If mipLevel is less than one, all mip levels will be copied from buffer.
    HGIVULKAN_API
    void CopyBufferToTexture(
        HgiVulkanCommandBuffer* cb,
        HgiVulkanBuffer* srcBuffer,
        GfVec3i const& dstTexelOffset = GfVec3i(0),
        int mipLevel=-1);

    /// Transition image from its current layout to newLayout.
    /// `producerAccess` of 0 means:
    ///    Only invalidation barrier, no flush barrier. For read-only resources.
    ///    Meaning: There are no pending writes.
    ///    Multiple passes can go back to back which all read the resource.
    /// If mipLevel is > -1 only that mips level will be transitioned.
    HGIVULKAN_API
    static void TransitionImageBarrier(
        HgiVulkanCommandBuffer* cb,
        HgiVulkanTexture* tex,
        VkImageLayout newLayout,
        VkAccessFlags producerAccess,
        VkAccessFlags consumerAccess,
        VkPipelineStageFlags producerStage,
        VkPipelineStageFlags consumerStage,
        int32_t mipLevel=-1);

    /// Returns the layout for a texture based on its usage flags.
    HGIVULKAN_API
    static VkImageLayout GetDefaultImageLayout(HgiTextureUsage usage);

    /// Returns the access flags for a texture based on its usage flags.
    HGIVULKAN_API
    static VkAccessFlags GetDefaultAccessFlags(HgiTextureUsage usage);

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanTexture(
        HgiVulkan* hgi,
        HgiVulkanDevice* device,
        HgiTextureDesc const & desc);

    // Texture view constructor to alias another texture's data.
    HGIVULKAN_API
    HgiVulkanTexture(
        HgiVulkan* hgi,
        HgiVulkanDevice* device,
        HgiTextureViewDesc const & desc);

private:
    HgiVulkanTexture() = delete;
    HgiVulkanTexture & operator=(const HgiVulkanTexture&) = delete;
    HgiVulkanTexture(const HgiVulkanTexture&) = delete;

    bool _isTextureView;
    VkImage _vkImage;
    VkImageView _vkImageView;
    VkImageLayout _vkImageLayout;
    VmaAllocation _vmaImageAllocation;
    HgiVulkanDevice* _device;
    uint64_t _inflightBits;
    HgiVulkanBuffer* _stagingBuffer;
    void* _cpuStagingAddress;
};


FORGE_NAMESPACE_END

#endif
