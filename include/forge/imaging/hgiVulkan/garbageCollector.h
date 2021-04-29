#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiVulkan/garbageCollector.h"
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
#ifndef FORGE_IMAGING_HGIVULKAN_GARBAGE_COLLECTOR_H
#define FORGE_IMAGING_HGIVULKAN_GARBAGE_COLLECTOR_H

#include "forge/forge.h"
#include "forge/base/tf/diagnostic.h"

#include "forge/imaging/hgi/hgi.h"
#include "forge/imaging/hgiVulkan/api.h"

#include <mutex>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HgiVulkan;
class HgiVulkanDevice;

using HgiVulkanBufferVector =
    std::vector<class HgiVulkanBuffer*>;
using HgiVulkanTextureVector =
    std::vector<class HgiVulkanTexture*>;
using HgiVulkanSamplerVector =
    std::vector<class HgiVulkanSampler*>;
using HgiVulkanShaderFunctionVector =
    std::vector<class HgiVulkanShaderFunction*>;
using HgiVulkanShaderProgramVector =
    std::vector<class HgiVulkanShaderProgram*>;
using HgiVulkanResourceBindingsVector =
    std::vector<class HgiVulkanResourceBindings*>;
using HgiVulkanGraphicsPipelineVector =
    std::vector<class HgiVulkanGraphicsPipeline*>;
using HgiVulkanComputePipelineVector =
    std::vector<class HgiVulkanComputePipeline*>;


/// \class HgiVulkanGarbageCollector
///
/// Handles garbage collection of vulkan objects by delaying their destruction
/// until those objects are no longer used.
///
class HgiVulkanGarbageCollector final
{
public:
    HGIVULKAN_API
    HgiVulkanGarbageCollector(HgiVulkan* hgi);

    HGIVULKAN_API
    ~HgiVulkanGarbageCollector();

    /// Destroys the objects inside the garbage collector.
    /// Thread safety: This call is not thread safe and should only be called
    /// while no other threads are destroying objects (e.g. during EndFrame).
    HGIVULKAN_API
    void PerformGarbageCollection(HgiVulkanDevice* device);

    /// Returns a garbage collection vector for a type of handle.
    /// Thread safety: The returned vector is a thread_local vector so this call
    /// is thread safe as long as the vector is only used by the calling thread.
    HgiVulkanBufferVector* GetBufferList();
    HgiVulkanTextureVector* GetTextureList();
    HgiVulkanSamplerVector* GetSamplerList();
    HgiVulkanShaderFunctionVector* GetShaderFunctionList();
    HgiVulkanShaderProgramVector* GetShaderProgramList();
    HgiVulkanResourceBindingsVector* GetResourceBindingsList();
    HgiVulkanGraphicsPipelineVector* GetGraphicsPipelineList();
    HgiVulkanComputePipelineVector* GetComputePipelineList();

private:
    HgiVulkanGarbageCollector & operator =
        (const HgiVulkanGarbageCollector&) = delete;
    HgiVulkanGarbageCollector(const HgiVulkanGarbageCollector&) = delete;

    /// Returns a thread_local vector in which to store a object handle.
    /// Thread safety: The returned vector is a thread_local vector so this call
    /// is thread safe as long as the vector is only used by the calling thread.
    template<class T>
    T* _GetThreadLocalStorageList(std::vector<T*>* collector);

    HgiVulkan* _hgi;

    // List of all the per-thread-vectors of objects that need to be destroyed.
    // The vectors are static (shared across HGIs), because we use thread_local
    // in _GetThreadLocalStorageList which makes us share the garbage collector
    // vectors across Hgi instances.
    static std::vector<HgiVulkanBufferVector*> _bufferList;
    static std::vector<HgiVulkanTextureVector*> _textureList;
    static std::vector<HgiVulkanSamplerVector*> _samplerList;
    static std::vector<HgiVulkanShaderFunctionVector*> _shaderFunctionList;
    static std::vector<HgiVulkanShaderProgramVector*> _shaderProgramList;
    static std::vector<HgiVulkanResourceBindingsVector*> _resourceBindingsList;
    static std::vector<HgiVulkanGraphicsPipelineVector*> _graphicsPipelineList;
    static std::vector<HgiVulkanComputePipelineVector*> _computePipelineList;

    bool _isDestroying;
};


FORGE_NAMESPACE_END

#endif
