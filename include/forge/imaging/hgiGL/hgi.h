#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/hgi.h"
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
#ifndef FORGE_IMAGING_HGI_GL_HGI_H
#define FORGE_IMAGING_HGI_GL_HGI_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/garbageCollector.h"
#include "forge/imaging/hgi/hgi.h"
#include "forge/imaging/hgi/tokens.h"

#include <functional>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HgiGLDevice;

using HgiGLOpsFn = std::function<void(void)>;
using HgiGLOpsVector = std::vector<HgiGLOpsFn>;


/// \class HgiGL
///
/// OpenGL implementation of the Hydra Graphics Interface.
///
/// HgiGL expects the GL context to be externally managed.
/// When HgiGL is constructed and during any of its resource create / destroy
/// calls and during command recording operations it expects that the OpenGL
/// context is valid and current.
///
class HgiGL final : public Hgi
{
public:
    HGIGL_API
    HgiGL();

    HGIGL_API
    ~HgiGL() override;

    HGIGL_API
    HgiGraphicsCmdsUniquePtr CreateGraphicsCmds(
        HgiGraphicsCmdsDesc const& desc) override;

    HGIGL_API
    HgiBlitCmdsUniquePtr CreateBlitCmds() override;

    HGIGL_API
    HgiComputeCmdsUniquePtr CreateComputeCmds() override;

    HGIGL_API
    HgiTextureHandle CreateTexture(HgiTextureDesc const & desc) override;

    HGIGL_API
    void DestroyTexture(HgiTextureHandle* texHandle) override;

    HGIGL_API
    HgiTextureViewHandle CreateTextureView(
        HgiTextureViewDesc const& desc) override;

    HGIGL_API
    void DestroyTextureView(HgiTextureViewHandle* viewHandle) override;

    HGIGL_API
    HgiSamplerHandle CreateSampler(HgiSamplerDesc const & desc) override;

    HGIGL_API
    void DestroySampler(HgiSamplerHandle* smpHandle) override;

    HGIGL_API
    HgiBufferHandle CreateBuffer(HgiBufferDesc const & desc) override;

    HGIGL_API
    void DestroyBuffer(HgiBufferHandle* bufHandle) override;

    HGIGL_API
    HgiShaderFunctionHandle CreateShaderFunction(
        HgiShaderFunctionDesc const& desc) override;

    HGIGL_API
    void DestroyShaderFunction(
        HgiShaderFunctionHandle* shaderFunctionHandle) override;

    HGIGL_API
    HgiShaderProgramHandle CreateShaderProgram(
        HgiShaderProgramDesc const& desc) override;

    HGIGL_API
    void DestroyShaderProgram(
        HgiShaderProgramHandle* shaderProgramHandle) override;

    HGIGL_API
    HgiResourceBindingsHandle CreateResourceBindings(
        HgiResourceBindingsDesc const& desc) override;

    HGIGL_API
    void DestroyResourceBindings(HgiResourceBindingsHandle* resHandle) override;

    HGIGL_API
    HgiGraphicsPipelineHandle CreateGraphicsPipeline(
        HgiGraphicsPipelineDesc const& pipeDesc) override;

    HGIGL_API
    void DestroyGraphicsPipeline(
        HgiGraphicsPipelineHandle* pipeHandle) override;

    HGIGL_API
    HgiComputePipelineHandle CreateComputePipeline(
        HgiComputePipelineDesc const& pipeDesc) override;

    HGIGL_API
    void DestroyComputePipeline(HgiComputePipelineHandle* pipeHandle) override;

    HGIGL_API
    TfToken const& GetAPIName() const override;

    HGIGL_API
    void StartFrame() override;

    HGIGL_API
    void EndFrame() override;

    //
    // HgiGL specific
    //

    /// Returns the opengl device.
    HGIGL_API
    HgiGLDevice* GetPrimaryDevice() const;

protected:
    HGIGL_API
    bool _SubmitCmds(HgiCmds* cmds, HgiSubmitWaitType wait) override;

private:
    HgiGL & operator=(const HgiGL&) = delete;
    HgiGL(const HgiGL&) = delete;

    // Invalidates the resource handle and places the object in the garbage
    // collector vector for future destruction.
    // This is helpful to avoid destroying GPU resources still in-flight.
    template<class T>
    void _TrashObject(
        HgiHandle<T>* handle, std::vector<HgiHandle<T>>* collector) {
        collector->push_back(HgiHandle<T>(handle->Get(), /*id*/0));
        *handle = HgiHandle<T>();
    }

    HgiGLDevice* _device;
    HgiGLGarbageCollector _garbageCollector;
    int _frameDepth;
};

FORGE_NAMESPACE_END

#endif
