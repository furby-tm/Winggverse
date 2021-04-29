#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/garbageCollector.h"
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
#ifndef FORGE_IMAGING_HGI_GL_GARBAGE_COLLECTOR_H
#define FORGE_IMAGING_HGI_GL_GARBAGE_COLLECTOR_H

#include "forge/forge.h"
#include "forge/base/tf/diagnostic.h"

#include "forge/imaging/hgi/hgi.h"
#include "forge/imaging/hgiGL/api.h"

#include <mutex>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HgiGL;

/// \class HgiGLGarbageCollector
///
/// Handles garbage collection of opengl objects by delaying their destruction
/// until those objects are no longer used.
///
class HgiGLGarbageCollector final
{
public:
    HGIGL_API
    HgiGLGarbageCollector(HgiGL* hgi);

    HGIGL_API
    ~HgiGLGarbageCollector();

    /// Destroys the objects inside the garbage collector.
    /// Thread safety: This call is not thread safe and must be called from
    /// the thread that has the opengl context bound while no other threads are
    /// destroying objects (e.g. during EndFrame).
    HGIGL_API
    void PerformGarbageCollection();

    /// Returns a garbage collection vector for a type of handle.
    /// Thread safety: The returned vector is a thread_local vector so this call
    /// is thread safe as long as the vector is only used by the calling thread.
    HgiBufferHandleVector* GetBufferList();
    HgiTextureHandleVector* GetTextureList();
    HgiSamplerHandleVector* GetSamplerList();
    HgiShaderFunctionHandleVector* GetShaderFunctionList();
    HgiShaderProgramHandleVector* GetShaderProgramList();
    HgiResourceBindingsHandleVector* GetResourceBindingsList();
    HgiGraphicsPipelineHandleVector* GetGraphicsPipelineList();
    HgiComputePipelineHandleVector* GetComputePipelineList();

private:
    HgiGLGarbageCollector & operator =
        (const HgiGLGarbageCollector&) = delete;
    HgiGLGarbageCollector(const HgiGLGarbageCollector&) = delete;

    /// Returns a thread_local vector in which to store a object handle.
    /// Thread safety: The returned vector is a thread_local vector so this call
    /// is thread safe as long as the vector is only used by the calling thread.
    template<class T>
    T* _GetThreadLocalStorageList(std::vector<T*>* collector);

    HgiGL* _hgi;

    // List of all the per-thread-vectors of objects that need to be destroyed.
    // The vectors are static (shared across HGIs), because we use thread_local
    // in _GetThreadLocalStorageList which makes us share the garbage collector
    // vectors across Hgi instances.
    static std::vector<HgiBufferHandleVector*> _bufferList;
    static std::vector<HgiTextureHandleVector*> _textureList;
    static std::vector<HgiSamplerHandleVector*> _samplerList;
    static std::vector<HgiShaderFunctionHandleVector*> _shaderFunctionList;
    static std::vector<HgiShaderProgramHandleVector*> _shaderProgramList;
    static std::vector<HgiResourceBindingsHandleVector*> _resourceBindingsList;
    static std::vector<HgiGraphicsPipelineHandleVector*> _graphicsPipelineList;
    static std::vector<HgiComputePipelineHandleVector*> _computePipelineList;

    bool _isDestroying;
};


FORGE_NAMESPACE_END

#endif
