#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/shaderSection.h"
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

#ifndef FORGE_IMAGING_HGIVULKAN_SHADERSECTION_H
#define FORGE_IMAGING_HGIVULKAN_SHADERSECTION_H

#include "forge/imaging/hgi/shaderFunctionDesc.h"
#include "forge/imaging/hgi/shaderSection.h"
#include "forge/imaging/hgiVulkan/api.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class HgiVulkanShaderSection
///
/// Base class for Vulkan code sections. The generator holds these
///
class HgiVulkanShaderSection : public HgiShaderSection
{
public:
    HGIVULKAN_API
    explicit HgiVulkanShaderSection(
        const std::string &identifier,
        const HgiShaderSectionAttributeVector &attributes = {},
        const std::string &storageQualifier = std::string(),
        const std::string &defaultValue = std::string());

    HGIVULKAN_API
    ~HgiVulkanShaderSection() override;

    HGIVULKAN_API
    void WriteDeclaration(std::ostream &ss) const override;
    HGIVULKAN_API
    void WriteParameter(std::ostream &ss) const override;

    HGIVULKAN_API
    virtual bool VisitGlobalIncludes(std::ostream &ss);
    HGIVULKAN_API
    virtual bool VisitGlobalMacros(std::ostream &ss);
    HGIVULKAN_API
    virtual bool VisitGlobalStructs(std::ostream &ss);
    HGIVULKAN_API
    virtual bool VisitGlobalMemberDeclarations(std::ostream &ss);
    HGIVULKAN_API
    virtual bool VisitGlobalFunctionDefinitions(std::ostream &ss);

protected:
    const std::string _storageQualifier;

private:
    HgiVulkanShaderSection() = delete;
    HgiVulkanShaderSection & operator=(const HgiVulkanShaderSection&) = delete;
    HgiVulkanShaderSection(const HgiVulkanShaderSection&) = delete;
};

/// \class HgiVulkanMacroShaderSection
///
/// A ShaderSection for defining macros.
/// Accepts raw strings and dumps it to the global scope under includes
///
class HgiVulkanMacroShaderSection final: public HgiVulkanShaderSection
{
public:
    HGIVULKAN_API
    explicit HgiVulkanMacroShaderSection(
        const std::string &macroDeclaration,
        const std::string &macroComment);

    HGIVULKAN_API
    ~HgiVulkanMacroShaderSection() override;

    HGIVULKAN_API
    bool VisitGlobalMacros(std::ostream &ss) override;

private:
    HgiVulkanMacroShaderSection() = delete;
    HgiVulkanMacroShaderSection & operator=(
        const HgiVulkanMacroShaderSection&) = delete;
    HgiVulkanMacroShaderSection(const HgiVulkanMacroShaderSection&) = delete;

    const std::string _macroComment;
};

/// \class HgiVulkanMemberShaderSection
///
/// Declares a member in global scope, for declaring instances of structs, constant
/// params etc - it's quite flexible in it's writing capabilities
///
class HgiVulkanMemberShaderSection final: public HgiVulkanShaderSection
{
public:
    HGIVULKAN_API
    explicit HgiVulkanMemberShaderSection(
        const std::string &identifier,
        const std::string &typeName,
        const HgiShaderSectionAttributeVector &attributes,
        const std::string &storageQualifier,
        const std::string &defaultValue = std::string());

    HGIVULKAN_API
    ~HgiVulkanMemberShaderSection() override;

    HGIVULKAN_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

    HGIVULKAN_API
    void WriteType(std::ostream& ss) const override;

private:
    HgiVulkanMemberShaderSection() = delete;
    HgiVulkanMemberShaderSection & operator=(
        const HgiVulkanMemberShaderSection&) = delete;
    HgiVulkanMemberShaderSection(const HgiVulkanMemberShaderSection&) = delete;

    std::string _typeName;
};

/// \class HgiVulkanBlockShaderSection
///
/// For writing out uniform blocks, defines them in the global member declerations.
///
class HgiVulkanBlockShaderSection final: public HgiVulkanShaderSection
{
public:
    HGIVULKAN_API
    explicit HgiVulkanBlockShaderSection(
            const std::string &identifier,
            const HgiShaderFunctionParamDescVector &parameters);

    HGIVULKAN_API
    ~HgiVulkanBlockShaderSection() override;

    HGIVULKAN_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

private:
    const HgiShaderFunctionParamDescVector _parameters;
};

/// \class HgiVulkanMemberShaderSection
///
/// Declares OpenGL textures, and their cross language function
///
class HgiVulkanTextureShaderSection final: public HgiVulkanShaderSection
{
public:
    HGIVULKAN_API
    explicit HgiVulkanTextureShaderSection(
        const std::string &identifier,
        const uint32_t layoutIndex,
        const uint32_t dimensions,
        const HgiShaderSectionAttributeVector &attributes,
        const std::string &defaultValue = std::string());

    HGIVULKAN_API
    ~HgiVulkanTextureShaderSection() override;

    HGIVULKAN_API
    void WriteType(std::ostream &ss) const override;

    HGIVULKAN_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;
    HGIVULKAN_API
    bool VisitGlobalFunctionDefinitions(std::ostream &ss) override;

private:
    HgiVulkanTextureShaderSection() = delete;
    HgiVulkanTextureShaderSection & operator=(
        const HgiVulkanTextureShaderSection&) = delete;
    HgiVulkanTextureShaderSection(const HgiVulkanTextureShaderSection&) = delete;

    const uint32_t _dimensions;
};

FORGE_NAMESPACE_END

#endif
