#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/shaderFunction.h"
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
#ifndef FORGE_IMAGING_HGIGL_SHADERFUNCTION_H
#define FORGE_IMAGING_HGIGL_SHADERFUNCTION_H

#include "forge/imaging/hgi/shaderFunction.h"
#include "forge/imaging/hgiGL/api.h"

FORGE_NAMESPACE_BEGIN


///
/// \class HgiGLShaderFunction
///
/// OpenGL implementation of HgiShaderFunction
///
class HgiGLShaderFunction final : public HgiShaderFunction
{
public:
    HGIGL_API
    ~HgiGLShaderFunction() override;

    HGIGL_API
    bool IsValid() const override;

    HGIGL_API
    std::string const& GetCompileErrors() override;

    HGIGL_API
    size_t GetByteSizeOfResource() const override;

    HGIGL_API
    uint64_t GetRawResource() const override;

    /// Returns the gl resource id of the shader.
    HGIGL_API
    uint32_t GetShaderId() const;

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLShaderFunction(HgiShaderFunctionDesc const& desc);

private:
    HgiGLShaderFunction() = delete;
    HgiGLShaderFunction & operator=(const HgiGLShaderFunction&) = delete;
    HgiGLShaderFunction(const HgiGLShaderFunction&) = delete;

private:
    std::string _errors;
    uint32_t _shaderId;
};


FORGE_NAMESPACE_END

#endif
