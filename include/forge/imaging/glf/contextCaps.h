#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/contextCaps.h"
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
#ifndef FORGE_IMAGING_GLF_CONTEXT_CAPS_H
#define FORGE_IMAGING_GLF_CONTEXT_CAPS_H

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/base/tf/singleton.h"


FORGE_NAMESPACE_BEGIN


/// \class GlfContextCaps
///
/// This class is intended to be a cache of the capabilites
/// (resource limits and features) of the underlying
/// GL context.
///
/// It serves two purposes.  Firstly to reduce driver
/// transition overhead of querying these values.
/// Secondly to provide access to these values from other
/// threads that don't have the context bound.
///
/// In the event of failure (InitInstance() wasn't called
/// or an issue accessing the GL context), a reasonable
/// set of defaults, based on GL minimums, is provided.
///
///
/// TO DO (bug #124971):
///   - LoadCaps() should be called whenever the context
///     changes.
///   - Provide a mechanism where other Hd systems can
///     subscribe to when the caps changes, so they can
///     update and invalidate.
///
class GlfContextCaps
{
public:

    /// InitInstance queries the GL context for its capabilities.
    /// It should be called by the application before using systems
    /// that depend on the caps, such as Hydra.  A good example would be
    /// to pair the call to initialize after a call to initialize GL
    GLF_API
    static void InitInstance();

    /// GetInstance() returns the filled capabilities structure.
    /// This function will not populate the caps and will issue a
    /// coding error if it hasn't been filled.
    GLF_API
    static const GlfContextCaps &GetInstance();



    // GL version
    int glVersion;                    // 400 (4.0), 410 (4.1), ...

    // Whether or not we are running with core profile
    bool coreProfile;

    // Max constants
    int maxArrayTextureLayers;
    int maxUniformBlockSize;
    int maxShaderStorageBlockSize;
    int maxTextureBufferSize;
    int uniformBufferOffsetAlignment;

    // GL extensions (ordered by version)
    bool arrayTexturesEnabled;        // EXT_texture_array                (3.0)
    bool shaderStorageBufferEnabled;  // ARB_shader_storage_buffer_object (4.3)
    bool bufferStorageEnabled;        // ARB_buffer_storage               (4.4)
    bool directStateAccessEnabled;    // ARB_direct_state_access          (4.5)
    bool multiDrawIndirectEnabled;    // ARB_multi_draw_indirect          (4.5)

    bool bindlessTextureEnabled;      // ARB_bindless_texture
    bool bindlessBufferEnabled;       // NV_shader_buffer_load

    // GLSL version and extensions
    int glslVersion;                  // 400, 410, ...
    bool explicitUniformLocation;     // ARB_explicit_uniform_location    (4.3)
    bool shadingLanguage420pack;      // ARB_shading_language_420pack     (4.2)
    bool shaderDrawParametersEnabled; // ARB_shader_draw_parameters       (4.5)

    // workarounds for driver issues
    bool copyBufferEnabled;

    bool floatingPointBuffersEnabled;

private:
    void _LoadCaps();
    GlfContextCaps();
    ~GlfContextCaps() = default;

    // Disallow copies
    GlfContextCaps(const GlfContextCaps&) = delete;
    GlfContextCaps& operator=(const GlfContextCaps&) = delete;

    friend class TfSingleton<GlfContextCaps>;
};

GLF_API_TEMPLATE_CLASS(TfSingleton<GlfContextCaps>);

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_GLF_CONTEXT_CAPS_H
