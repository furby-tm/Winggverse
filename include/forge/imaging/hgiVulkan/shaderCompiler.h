#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/shaderCompiler.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_SHADERCOMPILER_H
#define FORGE_IMAGING_HGIVULKAN_SHADERCOMPILER_H

#include "forge/forge.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>


FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;

struct HgiVulkanDescriptorSetInfo
{
  uint32_t setNumber;
  VkDescriptorSetLayoutCreateInfo createInfo;
  std::vector<VkDescriptorSetLayoutBinding> bindings;
};

using HgiVulkanDescriptorSetInfoVector =
    std::vector<HgiVulkanDescriptorSetInfo>;

using VkDescriptorSetLayoutVector = std::vector<VkDescriptorSetLayout>;


/// Compiles ascii shader code (glsl) into spirv binary code (spirvOut).
/// Returns true if successful. Errors can optionally be captured.
/// numShaderCodes determines how many strings are provided via shaderCodes.
/// 'name' is purely for debugging compile errors. It can be anything.
HGIVULKAN_API
bool HgiVulkanCompileGLSL(
    const char* name,
    const char* shaderCodes[],
    uint8_t numShaderCodes,
    HgiShaderStage stage,
    std::vector<unsigned int>* spirvOUT,
    std::string* errors = nullptr);

/// Uses spirv-reflection to create new descriptor set layout information for
/// the provided spirv.
/// This information can be merged with the info of the other shader stage
/// modules to create the pipeline layout.
/// During Hgi pipeline layout creation we know the shader modules
/// (HgiShaderProgram), but not the HgiResourceBindings so we must use
/// spirv reflection to discover the descriptorSet info for the module.
HGIVULKAN_API
HgiVulkanDescriptorSetInfoVector HgiVulkanGatherDescriptorSetInfo(
    std::vector<unsigned int> const& spirv);

/// Given all of the DescriptorSetInfos of all of the shader modules in a
/// shader program, this function merges them and creates the descriptorSet
/// layouts needed during pipeline layout creation.
/// The caller takes ownership of the returned layouts and must destroy them.
HGIVULKAN_API
VkDescriptorSetLayoutVector HgiVulkanMakeDescriptorSetLayouts(
    HgiVulkanDevice* device,
    std::vector<HgiVulkanDescriptorSetInfoVector> const& infos,
    std::string const& debugName);

FORGE_NAMESPACE_END

#endif
