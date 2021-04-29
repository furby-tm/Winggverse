#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/shaderFunction.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_SHADERFUNCTION_H
#define FORGE_IMAGING_HGIVULKAN_SHADERFUNCTION_H

#include "forge/imaging/hgi/shaderFunction.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/shaderCompiler.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanDevice;


///
/// \class HgiVulkanShaderFunction
///
/// Vulkan implementation of HgiShaderFunction
///
class HgiVulkanShaderFunction final : public HgiShaderFunction
{
public:
    HGIVULKAN_API
    ~HgiVulkanShaderFunction() override;

    HGIVULKAN_API
    bool IsValid() const override;

    HGIVULKAN_API
    std::string const& GetCompileErrors() override;

    HGIVULKAN_API
    size_t GetByteSizeOfResource() const override;

    HGIVULKAN_API
    uint64_t GetRawResource() const override;

    /// Returns the shader stage this function operates in.
    HGIVULKAN_API
    VkShaderStageFlagBits GetShaderStage() const;

    /// Returns the binary shader module of the shader function.
    HGIVULKAN_API
    VkShaderModule GetShaderModule() const;

    /// Returns the shader entry function name (usually "main").
    HGIVULKAN_API
    const char* GetShaderFunctionName() const;

    /// Returns the descriptor set layout information that describe the
    /// resource bindings for this module. The returned info would usually be
    /// merged with info of other shader modules to create a VkPipelineLayout.
    HGIVULKAN_API
    HgiVulkanDescriptorSetInfoVector const& GetDescriptorSetInfo() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanShaderFunction(
        HgiVulkanDevice* device,
        HgiShaderFunctionDesc const& desc);

private:
    HgiVulkanShaderFunction() = delete;
    HgiVulkanShaderFunction& operator=(const HgiVulkanShaderFunction&) = delete;
    HgiVulkanShaderFunction(const HgiVulkanShaderFunction&) = delete;

    HgiVulkanDevice* _device;
    std::string _errors;
    size_t _spirvByteSize;
    VkShaderModule _vkShaderModule;
    HgiVulkanDescriptorSetInfoVector _descriptorSetInfo;
    uint64_t _inflightBits;
};


FORGE_NAMESPACE_END

#endif
