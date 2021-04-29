#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/computePipeline.h"
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
#ifndef FORGE_IMAGING_HGI_COMPUTE_PIPELINE_H
#define FORGE_IMAGING_HGI_COMPUTE_PIPELINE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/attachmentDesc.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/handle.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgi/shaderProgram.h"
#include "forge/imaging/hgi/types.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiComputeShaderConstantsDesc
///
/// A small, but fast buffer of uniform data for shaders.
///
/// <ul>
/// <li>byteSize:
///    Size of the constants in bytes. (max 256 bytes)</li>
/// </ul>
///
struct HgiComputeShaderConstantsDesc {
    HGI_API
    HgiComputeShaderConstantsDesc();

    uint32_t byteSize;
};

HGI_API
bool operator==(
    const HgiComputeShaderConstantsDesc& lhs,
    const HgiComputeShaderConstantsDesc& rhs);

HGI_API
bool operator!=(
    const HgiComputeShaderConstantsDesc& lhs,
    const HgiComputeShaderConstantsDesc& rhs);

/// \struct HgiComputePipelineDesc
///
/// Describes the properties needed to create a GPU compute pipeline.
///
/// <ul>
/// <li>shaderProgram:
///   Shader function used in this pipeline.</li>
/// <li>shaderConstantsDesc:
///   Describes the shader uniforms.</li>
/// </ul>
///
struct HgiComputePipelineDesc
{
    HGI_API
    HgiComputePipelineDesc();

    std::string debugName;
    HgiShaderProgramHandle shaderProgram;
    HgiComputeShaderConstantsDesc shaderConstantsDesc;
};

HGI_API
bool operator==(
    const HgiComputePipelineDesc& lhs,
    const HgiComputePipelineDesc& rhs);

HGI_API
bool operator!=(
    const HgiComputePipelineDesc& lhs,
    const HgiComputePipelineDesc& rhs);


///
/// \class HgiComputePipeline
///
/// Represents a graphics platform independent GPU compute pipeline resource.
///
/// Base class for Hgi compute pipelines.
/// To the client (HdPh) compute pipeline resources are referred to via
/// opaque, stateless handles (HgiComputePipelineHandle).
///
class HgiComputePipeline
{
public:
    HGI_API
    virtual ~HgiComputePipeline();

    /// The descriptor describes the object.
    HGI_API
    HgiComputePipelineDesc const& GetDescriptor() const;

protected:
    HGI_API
    HgiComputePipeline(HgiComputePipelineDesc const& desc);

    HgiComputePipelineDesc _descriptor;

private:
    HgiComputePipeline() = delete;
    HgiComputePipeline & operator=(const HgiComputePipeline&) = delete;
    HgiComputePipeline(const HgiComputePipeline&) = delete;
};

using HgiComputePipelineHandle = HgiHandle<class HgiComputePipeline>;
using HgiComputePipelineHandleVector = std::vector<HgiComputePipelineHandle>;


FORGE_NAMESPACE_END

#endif
