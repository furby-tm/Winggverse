#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/shaderGenerator.h"
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

#ifndef FORGE_IMAGING_HGIGL_SHADERGENERATOR_H
#define FORGE_IMAGING_HGIGL_SHADERGENERATOR_H

#include "forge/imaging/hgi/shaderGenerator.h"
#include "forge/imaging/hgiGL/shaderSection.h"
#include "forge/imaging/hgiGL/api.h"

FORGE_NAMESPACE_BEGIN

using HgiGLShaderSectionUniquePtrVector =
    std::vector<std::unique_ptr<HgiGLShaderSection>>;

/// \class HgiGLShaderGenerator
///
/// Takes in a descriptor and spits out GLSL code through it's execute function.
///
class HgiGLShaderGenerator final: public HgiShaderGenerator
{
public:
    HGIGL_API
    explicit HgiGLShaderGenerator(const HgiShaderFunctionDesc &descriptor);

    //This is not commonly consumed by the end user, but is available.
    HGIGL_API
    HgiGLShaderSectionUniquePtrVector* GetShaderSections();

protected:
    HGIGL_API
    void _Execute(
        std::ostream &ss,
        const std::string &originalShaderShader) override;

private:
    HgiGLShaderGenerator() = delete;
    HgiGLShaderGenerator & operator=(const HgiGLShaderGenerator&) = delete;
    HgiGLShaderGenerator(const HgiGLShaderGenerator&) = delete;

    void _WriteTextures(const HgiShaderFunctionTextureDescVector &textures);

    void _WriteConstantParams(
        const HgiShaderFunctionParamDescVector &parameters);

    //For writing shader inputs and outputs who are very similarly written
    void _WriteInOuts(
        const HgiShaderFunctionParamDescVector &parameters,
        const std::string &qualifier);

    HgiGLShaderSectionUniquePtrVector _shaderSections;
};

FORGE_NAMESPACE_END

#endif
