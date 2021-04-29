#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/shaderProgram.h"
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
#ifndef FORGE_IMAGING_HGI_SHADERPROGRAM_H
#define FORGE_IMAGING_HGI_SHADERPROGRAM_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/handle.h"
#include "forge/imaging/hgi/shaderFunction.h"
#include "forge/imaging/hgi/types.h"

#include <vector>


FORGE_NAMESPACE_BEGIN


/// \struct HgiShaderProgramDesc
///
/// Describes the properties needed to create a GPU shader program.
///
/// <ul>
/// <li>debugName:
///   This label can be applied as debug label for gpu debugging.</li>
/// <li>shaderFunctions:
///   Holds handles to shader functions for each shader stage.</li>
/// </ul>
///
struct HgiShaderProgramDesc
{
    HGI_API
    HgiShaderProgramDesc();

    std::string debugName;
    HgiShaderFunctionHandleVector shaderFunctions;
};

HGI_API
inline bool operator==(
    const HgiShaderProgramDesc& lhs,
    const HgiShaderProgramDesc& rhs);

HGI_API
inline bool operator!=(
    const HgiShaderProgramDesc& lhs,
    const HgiShaderProgramDesc& rhs);


///
/// \class HgiShaderProgram
///
/// Represents a collection of shader functions.
/// This object does not take ownership of the shader functions and does not
/// destroy them automatically. The client must destroy the shader functions
/// when the program is detroyed, because only the client knows if the shader
/// functions are used by other shader programs.
///
class HgiShaderProgram
{
public:
    HGI_API
    virtual ~HgiShaderProgram();

    /// The descriptor describes the object.
    HGI_API
    HgiShaderProgramDesc const& GetDescriptor() const;

    /// Returns false if any shader compile errors occured.
    HGI_API
    virtual bool IsValid() const = 0;

    /// Returns shader compile errors.
    HGI_API
    virtual std::string const& GetCompileErrors() = 0;

    /// Returns the shader functions that are part of this program.
    HGI_API
    virtual HgiShaderFunctionHandleVector const& GetShaderFunctions() const = 0;

    /// Returns the byte size of the GPU shader program.
    /// APIs that do not have programs can return the combined byte size of the
    /// shader functions used by the program.
    /// This can be helpful if the application wishes to tally up memory usage.
    HGI_API
    virtual size_t GetByteSizeOfResource() const = 0;

    /// This function returns the handle to the Hgi backend's gpu resource, cast
    /// to a uint64_t. Clients should avoid using this function and instead
    /// use Hgi base classes so that client code works with any Hgi platform.
    /// For transitioning code to Hgi, it can however we useful to directly
    /// access a platform's internal resource handles.
    /// There is no safety provided in using this. If you by accident pass a
    /// HgiMetal resource into an OpenGL call, bad things may happen.
    /// In OpenGL this returns the GLuint resource name.
    /// In Metal, Vulkan this returns 0.
    HGI_API
    virtual uint64_t GetRawResource() const = 0;

protected:
    HGI_API
    HgiShaderProgram(HgiShaderProgramDesc const& desc);

    HgiShaderProgramDesc _descriptor;

private:
    HgiShaderProgram() = delete;
    HgiShaderProgram & operator=(const HgiShaderProgram&) = delete;
    HgiShaderProgram(const HgiShaderProgram&) = delete;
};

using HgiShaderProgramHandle = HgiHandle<class HgiShaderProgram>;
using HgiShaderProgramHandleVector = std::vector<HgiShaderProgramHandle>;


FORGE_NAMESPACE_END

#endif
