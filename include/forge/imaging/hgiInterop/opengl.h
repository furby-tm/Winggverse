#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiInterop/opengl.h"
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
#ifndef FORGE_IMAGING_HGIINTEROP_HGIINTEROPOPENGL_H
#define FORGE_IMAGING_HGIINTEROP_HGIINTEROPOPENGL_H

#include "forge/forge.h"
#include "forge/base/gf/vec4i.h"
#include "forge/imaging/hgi/texture.h"
#include "forge/imaging/hgiInterop/api.h"


FORGE_NAMESPACE_BEGIN

class VtValue;

/// \class HgiInteropOpenGL
///
/// Provides GL/GL interop.
///
class HgiInteropOpenGL final
{
public:
    HGIINTEROP_API
    HgiInteropOpenGL();

    HGIINTEROP_API
    ~HgiInteropOpenGL();

    /// Composite provided color (and optional depth) textures over app's
    /// framebuffer contents.
    HGIINTEROP_API
    void CompositeToInterop(
        HgiTextureHandle const &color,
        HgiTextureHandle const &depth,
        VtValue const &framebuffer,
        GfVec4i const& viewport);

private:
    uint32_t _vs;
    uint32_t _fsNoDepth;
    uint32_t _fsDepth;
    uint32_t _prgNoDepth;
    uint32_t _prgDepth;
    uint32_t _vertexBuffer;
};

FORGE_NAMESPACE_END

#endif
