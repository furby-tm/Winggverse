#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/shaderSection.h"
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

#ifndef FORGE_IMAGING_HGIGL_SHADERSECTION_H
#define FORGE_IMAGING_HGIGL_SHADERSECTION_H

#include "forge/imaging/hgi/shaderFunctionDesc.h"
#include "forge/imaging/hgi/shaderSection.h"
#include "forge/imaging/hgiGL/api.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class HgiGLShaderSection
///
/// Base class for OpenGL code sections. The generator holds these
///
class HgiGLShaderSection : public HgiShaderSection
{
public:
    HGIGL_API
    explicit HgiGLShaderSection(
        const std::string &identifier,
        const HgiShaderSectionAttributeVector &attributes = {},
        const std::string &storageQualifier = std::string(),
        const std::string &defaultValue = std::string());

    HGIGL_API
    ~HgiGLShaderSection() override;

    HGIGL_API
    void WriteDeclaration(std::ostream &ss) const override;
    HGIGL_API
    void WriteParameter(std::ostream &ss) const override;

    HGIGL_API
    virtual bool VisitGlobalIncludes(std::ostream &ss);
    HGIGL_API
    virtual bool VisitGlobalMacros(std::ostream &ss);
    HGIGL_API
    virtual bool VisitGlobalStructs(std::ostream &ss);
    HGIGL_API
    virtual bool VisitGlobalMemberDeclarations(std::ostream &ss);
    HGIGL_API
    virtual bool VisitGlobalFunctionDefinitions(std::ostream &ss);

private:
    HgiGLShaderSection() = delete;
    HgiGLShaderSection & operator=(const HgiGLShaderSection&) = delete;
    HgiGLShaderSection(const HgiGLShaderSection&) = delete;

    const std::string _storageQualifier;
};

/// \class HgiGLMacroShaderSection
///
/// A ShaderSection for defining macros.
/// Accepts raw strings and dumps it to the global scope under includes
///
class HgiGLMacroShaderSection final: public HgiGLShaderSection
{
public:
    HGIGL_API
    explicit HgiGLMacroShaderSection(
        const std::string &macroDeclaration,
        const std::string &macroComment);

    HGIGL_API
    ~HgiGLMacroShaderSection() override;

    HGIGL_API
    bool VisitGlobalMacros(std::ostream &ss) override;

private:
    HgiGLMacroShaderSection() = delete;
    HgiGLMacroShaderSection & operator=(
        const HgiGLMacroShaderSection&) = delete;
    HgiGLMacroShaderSection(const HgiGLMacroShaderSection&) = delete;

    const std::string _macroComment;
};

/// \class HgiGLMemberShaderSection
///
/// Declares a member in global scope, for declaring instances of structs, constant
/// params etc - it's quite flexible in it's writing capabilities
///
class HgiGLMemberShaderSection final: public HgiGLShaderSection
{
public:
    HGIGL_API
    explicit HgiGLMemberShaderSection(
        const std::string &identifier,
        const std::string &typeName,
        const HgiShaderSectionAttributeVector &attributes,
        const std::string &storageQualifier = std::string(),
        const std::string &defaultValue = std::string());

    HGIGL_API
    ~HgiGLMemberShaderSection() override;

    HGIGL_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

    HGIGL_API
    void WriteType(std::ostream& ss) const override;

private:
    HgiGLMemberShaderSection() = delete;
    HgiGLMemberShaderSection & operator=(
        const HgiGLMemberShaderSection&) = delete;
    HgiGLMemberShaderSection(const HgiGLMemberShaderSection&) = delete;

    std::string _typeName;
};

/// \class HgiGLBlockShaderSection
///
/// For writing out uniform blocks, defines them in the global member declerations.
///
class HgiGLBlockShaderSection final: public HgiGLShaderSection
{
public:
    HGIGL_API
    explicit HgiGLBlockShaderSection(
            const std::string &identifier,
            const HgiShaderFunctionParamDescVector &parameters,
            const uint32_t bindingNo=0);

    HGIGL_API
    ~HgiGLBlockShaderSection() override;

    HGIGL_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

private:
    const HgiShaderFunctionParamDescVector _parameters;
    const uint32_t _bindingNo;
};

/// \class HgiGLMemberShaderSection
///
/// Declares OpenGL textures, and their cross language function
///
class HgiGLTextureShaderSection final: public HgiGLShaderSection
{
public:
    HGIGL_API
    explicit HgiGLTextureShaderSection(
        const std::string &identifier,
        const uint32_t layoutIndex,
        const uint32_t dimensions,
        const HgiFormat format,
        const HgiShaderSectionAttributeVector &attributes,
        const std::string &defaultValue = std::string());

    HGIGL_API
    ~HgiGLTextureShaderSection() override;

    HGIGL_API
    void WriteType(std::ostream &ss) const override;

    HGIGL_API
    bool VisitGlobalMemberDeclarations(std::ostream &ss) override;
    HGIGL_API
    bool VisitGlobalFunctionDefinitions(std::ostream &ss) override;

private:
    HgiGLTextureShaderSection() = delete;
    HgiGLTextureShaderSection & operator=(
        const HgiGLTextureShaderSection&) = delete;
    HgiGLTextureShaderSection(const HgiGLTextureShaderSection&) = delete;

    void _WriteSamplerType(std::ostream &ss) const;
    void _WriteSampledDataType(std::ostream &ss) const;

    const uint32_t _dimensions;
    const HgiFormat _format;
    static const std::string _storageQualifier;
};

FORGE_NAMESPACE_END

#endif
