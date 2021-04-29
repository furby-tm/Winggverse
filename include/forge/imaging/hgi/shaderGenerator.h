#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/shaderGenerator.h"
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

#ifndef FORGE_IMAGING_HGI_SHADERGENERATOR_H
#define FORGE_IMAGING_HGI_SHADERGENERATOR_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"

#include <iosfwd>
#include <string>

FORGE_NAMESPACE_BEGIN

struct HgiShaderFunctionDesc;

/// \class HgiShaderGenerator
///
/// Base class for shader function generation
/// Given a descriptor, converts glslfx domain language to concrete shader
/// languages. Can be extended with new types of code sections and specialized
/// for different APIs. It's main role is to make GLSLFX a write once language,
/// no matter the API
///
class HgiShaderGenerator
{
public:
    //Write the generated code to the stringstream given once set up
    HGI_API
    void Execute(std::ostream &ss);

    HGI_API
    virtual ~HgiShaderGenerator();

protected:
    HGI_API
    explicit HgiShaderGenerator(const HgiShaderFunctionDesc &descriptor);

    HGI_API
    virtual void _Execute(
        std::ostream &ss,
        const std::string &originalShaderCode) = 0;

    HGI_API
    const std::string& _GetOriginalShader() const;

    HGI_API
    HgiShaderStage _GetShaderStage() const;

    HGI_API
    const std::string& _GetVersion() const;

private:
    HgiShaderGenerator() = delete;
    HgiShaderGenerator & operator=(const HgiShaderGenerator&) = delete;
    HgiShaderGenerator(const HgiShaderGenerator&) = delete;

    const std::string _version;
    const std::string _originalShader;
    const HgiShaderStage _stage;
};

FORGE_NAMESPACE_END

#endif
