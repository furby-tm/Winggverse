#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/hgi.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_HGI_H
#define FORGE_IMAGING_HGIVULKAN_HGI_H

#include "forge/forge.h"
#include "forge/imaging/hgi/hgi.h"
#include "forge/imaging/hgi/tokens.h"

#include "forge/imaging/hgiVulkan/api.h"
#include "forge/imaging/hgiVulkan/commandQueue.h"
#include "forge/imaging/hgiVulkan/device.h"
#include "forge/imaging/hgiVulkan/vulkan.h"

#include <thread>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HgiVulkanGarbageCollector;
class HgiVulkanInstance;


/// \class HgiVulkan
///
/// Vulkan implementation of the Hydra Graphics Interface.
///
class HgiVulkan final : public Hgi
{
public:
    HGIVULKAN_API
    HgiVulkan();

    HGIVULKAN_API
    ~HgiVulkan() override;

    HGIVULKAN_API
    HgiGraphicsCmdsUniquePtr CreateGraphicsCmds(
        HgiGraphicsCmdsDesc const& desc) override;

    HGIVULKAN_API
    HgiBlitCmdsUniquePtr CreateBlitCmds() override;

    HGIVULKAN_API
    HgiComputeCmdsUniquePtr CreateComputeCmds() override;

    HGIVULKAN_API
    HgiTextureHandle CreateTexture(HgiTextureDesc const & desc) override;

    HGIVULKAN_API
    void DestroyTexture(HgiTextureHandle* texHandle) override;

    HGIVULKAN_API
    HgiTextureViewHandle CreateTextureView(
        HgiTextureViewDesc const& desc) override;

    HGIVULKAN_API
    void DestroyTextureView(HgiTextureViewHandle* viewHandle) override;

    HGIVULKAN_API
    HgiSamplerHandle CreateSampler(HgiSamplerDesc const & desc) override;

    HGIVULKAN_API
    void DestroySampler(HgiSamplerHandle* smpHandle) override;

    HGIVULKAN_API
    HgiBufferHandle CreateBuffer(HgiBufferDesc const & desc) override;

    HGIVULKAN_API
    void DestroyBuffer(HgiBufferHandle* bufHandle) override;

    HGIVULKAN_API
    HgiShaderFunctionHandle CreateShaderFunction(
        HgiShaderFunctionDesc const& desc) override;

    HGIVULKAN_API
    void DestroyShaderFunction(
        HgiShaderFunctionHandle* shaderFunctionHandle) override;

    HGIVULKAN_API
    HgiShaderProgramHandle CreateShaderProgram(
        HgiShaderProgramDesc const& desc) override;

    HGIVULKAN_API
    void DestroyShaderProgram(
        HgiShaderProgramHandle* shaderProgramHandle) override;

    HGIVULKAN_API
    HgiResourceBindingsHandle CreateResourceBindings(
        HgiResourceBindingsDesc const& desc) override;

    HGIVULKAN_API
    void DestroyResourceBindings(HgiResourceBindingsHandle* resHandle) override;

    HGIVULKAN_API
    HgiGraphicsPipelineHandle CreateGraphicsPipeline(
        HgiGraphicsPipelineDesc const& pipeDesc) override;

    HGIVULKAN_API
    void DestroyGraphicsPipeline(
        HgiGraphicsPipelineHandle* pipeHandle) override;

    HGIVULKAN_API
    HgiComputePipelineHandle CreateComputePipeline(
        HgiComputePipelineDesc const& pipeDesc) override;

    HGIVULKAN_API
    void DestroyComputePipeline(HgiComputePipelineHandle* pipeHandle) override;

    HGIVULKAN_API
    TfToken const& GetAPIName() const override;

    HGIVULKAN_API
    void StartFrame() override;

    HGIVULKAN_API
    void EndFrame() override;

    //
    // HgiVulkan specific
    //

    /// Returns the Hgi vulkan instance.
    /// Thread safety: Yes.
    HGIVULKAN_API
    HgiVulkanInstance* GetVulkanInstance() const;

    /// Returns the primary (presentation) vulkan device.
    /// Thread safety: Yes.
    HGIVULKAN_API
    HgiVulkanDevice* GetPrimaryDevice() const;

    /// Returns the garbage collector.
    /// Thread safety: Yes.
    HGIVULKAN_API
    HgiVulkanGarbageCollector* GetGarbageCollector() const;

    /// Invalidates the resource handle and places the object in the garbage
    /// collector vector for future destruction.
    /// This is helpful to avoid destroying GPU resources still in-flight.
    template<class T, class H>
    void TrashObject(H* handle, std::vector<T*>* collector)
    {
        T* object = static_cast<T*>(handle->Get());
        HgiVulkanDevice* device = object->GetDevice();
        HgiVulkanCommandQueue* queue = device->GetCommandQueue();
        object->GetInflightBits() = queue->GetInflightCommandBuffersBits();
        collector->push_back(object);
        *handle = H();
    }

protected:
    HGIVULKAN_API
    bool _SubmitCmds(HgiCmds* cmds, HgiSubmitWaitType wait) override;

private:
    HgiVulkan & operator=(const HgiVulkan&) = delete;
    HgiVulkan(const HgiVulkan&) = delete;

    // Perform low frequency actions, such as garbage collection.
    // Thread safety: No. Must be called from main thread.
    void _EndFrameSync();

    HgiVulkanInstance* _instance;
    HgiVulkanDevice* _device;
    HgiVulkanGarbageCollector* _garbageCollector;
    std::thread::id _threadId;
    int _frameDepth;
};

FORGE_NAMESPACE_END

#endif
