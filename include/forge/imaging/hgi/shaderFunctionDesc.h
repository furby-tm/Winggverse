#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/shaderFunctionDesc.h"
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

#ifndef FORGE_IMAGING_HGI_SHADERFUNCTIONDESC_H
#define FORGE_IMAGING_HGI_SHADERFUNCTIONDESC_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/types.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiShaderFunctionTextureDesc
///
/// Describes a texture to be passed into a shader
///
/// <ul>
/// <li>nameInShader:
///   The name written from the codegen into shader file for the texture.</li>
/// <li>dimensions:
///   1d, 2d or 3d texture declaration.</li>
/// <li>format
///   Format of the texture. This is required in APIs where sampler types depend
///   on the texture (e.g., GL) </li>
/// </ul>
///
struct HgiShaderFunctionTextureDesc
{
    HGI_API
    HgiShaderFunctionTextureDesc();

    std::string nameInShader;
    uint32_t dimensions;
    HgiFormat format;
};

using HgiShaderFunctionTextureDescVector =
    std::vector<HgiShaderFunctionTextureDesc>;

HGI_API
bool operator==(
    const HgiShaderFunctionTextureDesc& lhs,
    const HgiShaderFunctionTextureDesc& rhs);

HGI_API
bool operator!=(
    const HgiShaderFunctionTextureDesc& lhs,
    const HgiShaderFunctionTextureDesc& rhs);

/// \struct HgiShaderFunctionParamDesc
///
/// Describes a constant param passed into a shader
///
/// <ul>
/// <li>nameInShader:
///   The name written from the codegen into the shader file for the param.</li>
/// <li>type:
///   Type of the param within the shader file.</li>
/// <li>role:
///   Optionally a role can be specified, like position, uv, color.</li>
/// <li>attribute:
///   Optionally an attribute can be specified, like versions or addresses.</li>
/// <li>attributeIndex:
///   Used in metal, to specify indicies of attributes.</li>
/// </ul>
///
struct HgiShaderFunctionParamDesc
{
    HGI_API
    HgiShaderFunctionParamDesc();

    std::string nameInShader;
    std::string type;
    std::string role;
    std::string attribute;
    std::string attributeIndex;
};

using HgiShaderFunctionParamDescVector =
    std::vector<HgiShaderFunctionParamDesc>;

HGI_API
bool operator==(
    const HgiShaderFunctionParamDesc& lhs,
    const HgiShaderFunctionParamDesc& rhs);

HGI_API
bool operator!=(
    const HgiShaderFunctionParamDesc& lhs,
    const HgiShaderFunctionParamDesc& rhs);

/// \struct HgiShaderFunctionDesc
///
/// Describes the properties needed to create a GPU shader function.
///
/// <ul>
/// <li>debugName:
///   This label can be applied as debug label for gpu debugging.</li>
/// <li>shaderStage:
///   The shader stage this function represents.</li>
/// <li>shaderCode:
///   The ascii shader code used to compile the shader.</li>
/// <li>textures:
///   List of texture descriptions to be passed into a shader.</li>
/// <li>constantParams:
///   List of descriptions of constant params passed into a shader.</li>
/// <li>stageInputs:
///   List of descriptions of the inputs of the shader.</li>
/// <li>stageOutputs:
///   List of descriptions of the outputs of the shader.</li>
/// </ul>
///
struct HgiShaderFunctionDesc
{
    HGI_API
    HgiShaderFunctionDesc();
    std::string debugName;
    HgiShaderStage shaderStage;
    const char*  shaderCode;
    std::vector<HgiShaderFunctionTextureDesc> textures;
    std::vector<HgiShaderFunctionParamDesc> constantParams;
    std::vector<HgiShaderFunctionParamDesc> stageInputs;
    std::vector<HgiShaderFunctionParamDesc> stageOutputs;
};

using HgiShaderFunctionDescVector =
    std::vector<HgiShaderFunctionDesc>;

HGI_API
bool operator==(
    const HgiShaderFunctionDesc& lhs,
    const HgiShaderFunctionDesc& rhs);

HGI_API
bool operator!=(
    const HgiShaderFunctionDesc& lhs,
    const HgiShaderFunctionDesc& rhs);

/// Adds texture descriptor to given shader function descriptor.
HGI_API
void
HgiShaderFunctionAddTexture(
    HgiShaderFunctionDesc *desc,
    const std::string &nameInShader,
    uint32_t dimensions = 2,
    const HgiFormat &format = HgiFormatFloat32Vec4);

/// Adds constant function param descriptor to given shader function
/// descriptor.
HGI_API
void
HgiShaderFunctionAddConstantParam(
    HgiShaderFunctionDesc *desc,
    const std::string &nameInShader,
    const std::string &type,
    const std::string &role = std::string(),
    const std::string &attribute = std::string(),
    const std::string &attributeIndex = std::string());

/// Adds stage input function param descriptor to given shader function
/// descriptor.
HGI_API
void
HgiShaderFunctionAddStageInput(
    HgiShaderFunctionDesc *desc,
    const std::string &nameInShader,
    const std::string &type,
    const std::string &role = std::string(),
    const std::string &attribute = std::string(),
    const std::string &attributeIndex = std::string());

/// Adds stage output function param descriptor to given shader function
/// descriptor.
HGI_API
void
HgiShaderFunctionAddStageOutput(
    HgiShaderFunctionDesc *desc,
    const std::string &nameInShader,
    const std::string &type,
    const std::string &role = std::string(),
    const std::string &attribute = std::string(),
    const std::string &attributeIndex = std::string());

FORGE_NAMESPACE_END

#endif
