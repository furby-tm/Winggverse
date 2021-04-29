#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/computeCmds.h"
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
#ifndef FORGE_IMAGING_HGI_COMPUTE_CMDS_H
#define FORGE_IMAGING_HGI_COMPUTE_CMDS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/computePipeline.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgi/cmds.h"
#include <memory>

FORGE_NAMESPACE_BEGIN

using HgiComputeCmdsUniquePtr = std::unique_ptr<class HgiComputeCmds>;


/// \class HgiComputeCmds
///
/// A graphics API independent abstraction of compute commands.
/// HgiComputeCmds is a lightweight object that cannot be re-used after it has
/// been submitted. A new cmds object should be acquired for each frame.
///
class HgiComputeCmds : public HgiCmds
{
public:
    HGI_API
    ~HgiComputeCmds() override;

    /// Push a debug marker.
    HGI_API
    virtual void PushDebugGroup(const char* label) = 0;

    /// Pop the last debug marker.
    HGI_API
    virtual void PopDebugGroup() = 0;

    /// Bind a pipeline state object. Usually you call this right after calling
    /// CreateGraphicsCmds to set the graphics pipeline state.
    /// The resource bindings used when creating the pipeline must be compatible
    /// with the resources bound via BindResources().
    HGI_API
    virtual void BindPipeline(HgiComputePipelineHandle pipeline) = 0;

    /// Bind resources such as textures and uniform buffers.
    /// Usually you call this right after BindPipeline() and the resources bound
    /// must be compatible with the bound pipeline.
    HGI_API
    virtual void BindResources(HgiResourceBindingsHandle resources) = 0;

    /// Set Push / Function constants.
    /// `pipeline` is the compute pipeline that you are binding before the
    /// draw call. It contains the program used for the uniform buffer
    /// constant values for.
    /// `bindIndex` is the binding point index in the pipeline's shader
    /// to bind the data to.
    /// `byteSize` is the size of the data you are updating.
    /// `data` is the data you are copying into the push constants block.
    HGI_API
    virtual void SetConstantValues(
        HgiComputePipelineHandle pipeline,
        uint32_t bindIndex,
        uint32_t byteSize,
        const void* data) = 0;

    /// Execute a compute shader with provided thread group count in each
    /// dimension.
    HGI_API
    virtual void Dispatch(int dimX, int dimY) = 0;

    /// Inserts a barrier so that data written to memory by commands before
    /// the barrier is available to commands after the barrier.
    HGI_API
    virtual void MemoryBarrier(HgiMemoryBarrier barrier) = 0;

protected:
    HGI_API
    HgiComputeCmds();

private:
    HgiComputeCmds & operator=(const HgiComputeCmds&) = delete;
    HgiComputeCmds(const HgiComputeCmds&) = delete;
};



FORGE_NAMESPACE_END

#endif
