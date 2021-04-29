#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/sampler.h"
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
#ifndef FORGE_IMAGING_HGI_VULKAN_SAMPLER_H
#define FORGE_IMAGING_HGI_VULKAN_SAMPLER_H

#include "forge/imaging/hgi/sampler.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;


///
/// \class HgiVulkanSampler
///
/// Vulkan implementation of HgiSampler
///
class HgiVulkanSampler final : public HgiSampler
{
public:
    HGIVULKAN_API
    ~HgiVulkanSampler() override;

    HGIVULKAN_API
    uint64_t GetRawResource() const override;

    /// Returns the vulkan sampler object.
    HGIVULKAN_API
    VkSampler GetVulkanSampler() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanSampler(
        HgiVulkanDevice* device,
        HgiSamplerDesc const& desc);

private:
    HgiVulkanSampler() = delete;
    HgiVulkanSampler & operator=(const HgiVulkanSampler&) = delete;
    HgiVulkanSampler(const HgiVulkanSampler&) = delete;

    VkSampler _vkSampler;

    HgiVulkanDevice* _device;
    uint64_t _inflightBits;
};


FORGE_NAMESPACE_END

#endif