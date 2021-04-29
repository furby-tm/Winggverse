#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/shaderProgram.h"
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
#ifndef FORGE_IMAGING_HGIGL_SHADERPROGRAM_H
#define FORGE_IMAGING_HGIGL_SHADERPROGRAM_H

#include "forge/imaging/hgi/shaderProgram.h"

#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/shaderFunction.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


///
/// \class HgiGLShaderProgram
///
/// OpenGL implementation of HgiShaderProgram
///
class HgiGLShaderProgram final : public HgiShaderProgram
{
public:
    HGIGL_API
    ~HgiGLShaderProgram() override;

    HGIGL_API
    bool IsValid() const override;

    HGIGL_API
    std::string const& GetCompileErrors() override;

    HGIGL_API
    HgiShaderFunctionHandleVector const& GetShaderFunctions() const override;

    HGIGL_API
    size_t GetByteSizeOfResource() const override;

    HGIGL_API
    uint64_t GetRawResource() const override;

    /// Returns the gl resource id of the program.
    HGIGL_API
    uint32_t GetProgramId() const;

    /// Returns the gl resource for the uniform block of this shader program.
    /// This uniform block is used to store some per-shader values, such as
    /// indices or offsets into other buffers.
    /// See also Hgi::SetConstantValues.
    /// 'sizeHint' is used to store the byte size of the uniform buffer, but
    /// this fn does not actually allocate the data storage for the buffer.
    HGIGL_API
    uint32_t GetUniformBuffer(size_t sizeHint);

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLShaderProgram(HgiShaderProgramDesc const& desc);

private:
    HgiGLShaderProgram() = delete;
    HgiGLShaderProgram & operator=(const HgiGLShaderProgram&) = delete;
    HgiGLShaderProgram(const HgiGLShaderProgram&) = delete;

private:
    std::string _errors;
    uint32_t _programId;
    size_t _programByteSize;
    uint32_t _uniformBuffer;
    size_t _uboByteSize;
};


FORGE_NAMESPACE_END

#endif
