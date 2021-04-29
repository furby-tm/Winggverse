#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/conversions.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_CONVERSIONS_H
#define FORGE_IMAGING_HGIVULKAN_CONVERSIONS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/types.h"

#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

FORGE_NAMESPACE_BEGIN

///
/// \class HgiVulkanConversions
///
/// Converts from Hgi types to Vulkan types.
///
class HgiVulkanConversions final
{
public:
    HGIVULKAN_API
    static VkFormat GetFormat(HgiFormat inFormat);

    HGIVULKAN_API
    static HgiFormat GetFormat(VkFormat inFormat);

    HGIVULKAN_API
    static VkImageAspectFlags GetImageAspectFlag(HgiTextureUsage usage);

    HGIVULKAN_API
    static VkImageUsageFlags GetTextureUsage(HgiTextureUsage tu);

    HGIVULKAN_API
    static VkFormatFeatureFlags GetFormatFeature(HgiTextureUsage tu);

    HGIVULKAN_API
    static VkAttachmentLoadOp GetLoadOp(HgiAttachmentLoadOp op);

    HGIVULKAN_API
    static VkAttachmentStoreOp GetStoreOp(HgiAttachmentStoreOp op);

    HGIVULKAN_API
    static VkSampleCountFlagBits GetSampleCount(HgiSampleCount sc);

    HGIVULKAN_API
    static VkShaderStageFlags GetShaderStages(HgiShaderStage ss);

    HGIVULKAN_API
    static VkBufferUsageFlags GetBufferUsage(HgiBufferUsage bu);

    HGIVULKAN_API
    static VkCullModeFlags GetCullMode(HgiCullMode cm);

    HGIVULKAN_API
    static VkPolygonMode GetPolygonMode(HgiPolygonMode pm);

    HGIVULKAN_API
    static VkFrontFace GetWinding(HgiWinding wd);

    HGIVULKAN_API
    static VkDescriptorType GetDescriptorType(HgiBindResourceType rt);

    HGIVULKAN_API
    static VkBlendFactor GetBlendFactor(HgiBlendFactor bf);

    HGIVULKAN_API
    static VkBlendOp GetBlendEquation(HgiBlendOp bo);

    HGIVULKAN_API
    static VkCompareOp GetDepthCompareFunction(HgiCompareFunction cf);

    HGIVULKAN_API
    static VkImageType GetTextureType(HgiTextureType tt);

    HGIVULKAN_API
    static VkImageViewType GetTextureViewType(HgiTextureType tt);

    HGIVULKAN_API
    static VkSamplerAddressMode GetSamplerAddressMode(HgiSamplerAddressMode a);

    HGIVULKAN_API
    static VkFilter GetMinMagFilter(HgiSamplerFilter mf);

    HGIVULKAN_API
    static VkSamplerMipmapMode GetMipFilter(HgiMipFilter mf);

    HGIVULKAN_API
    static VkComponentSwizzle GetComponentSwizzle(HgiComponentSwizzle cs);

    HGIVULKAN_API
    static VkPrimitiveTopology GetPrimitiveType(HgiPrimitiveType pt);
};


FORGE_NAMESPACE_END

#endif
