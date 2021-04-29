#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/shaderProgram.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_SHADERPROGRAM_H
#define FORGE_IMAGING_HGIVULKAN_SHADERPROGRAM_H

#include <vector>

#include "forge/imaging/hgi/shaderProgram.h"

#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/shaderFunction.h"

FORGE_NAMESPACE_BEGIN

class HgiVulkanDevice;


///
/// \class HgiVulkanShaderProgram
///
/// Vulkan implementation of HgiShaderProgram
///
class HgiVulkanShaderProgram final : public HgiShaderProgram
{
public:
    HGIVULKAN_API
    ~HgiVulkanShaderProgram() override = default;

    HGIVULKAN_API
    bool IsValid() const override;

    HGIVULKAN_API
    std::string const& GetCompileErrors() override;

    HGIVULKAN_API
    size_t GetByteSizeOfResource() const override;

    HGIVULKAN_API
    uint64_t GetRawResource() const override;

    /// Returns the shader functions that are part of this program.
    HGIVULKAN_API
    HgiShaderFunctionHandleVector const& GetShaderFunctions() const;

    /// Returns the device used to create this object.
    HGIVULKAN_API
    HgiVulkanDevice* GetDevice() const;

    /// Returns the (writable) inflight bits of when this object was trashed.
    HGIVULKAN_API
    uint64_t & GetInflightBits();

protected:
    friend class HgiVulkan;

    HGIVULKAN_API
    HgiVulkanShaderProgram(
        HgiVulkanDevice* device,
        HgiShaderProgramDesc const& desc);

private:
    HgiVulkanShaderProgram() = delete;
    HgiVulkanShaderProgram & operator=(const HgiVulkanShaderProgram&) = delete;
    HgiVulkanShaderProgram(const HgiVulkanShaderProgram&) = delete;

    HgiVulkanDevice* _device;
    uint64_t _inflightBits;
};


FORGE_NAMESPACE_END

#endif