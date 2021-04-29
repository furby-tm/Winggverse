#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiInterop/hgiInterop.h"
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
#ifndef FORGE_IMAGING_HGIINTEROP_HGIINTEROP_H
#define FORGE_IMAGING_HGIINTEROP_HGIINTEROP_H

#include "forge/forge.h"
#include "forge/base/tf/token.h"
#include "forge/base/gf/vec4i.h"
#include "forge/imaging/hgiInterop/api.h"
#include "forge/imaging/hgi/texture.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class Hgi;
class HgiInteropMetal;
class HgiInteropOpenGL;
class HgiInteropVulkan;
class VtValue;

/// \class HgiInterop
///
/// Hydra Graphics Interface Interop.
///
/// HgiInterop provides functionality to transfer render targets between
/// supported APIs as efficiently as possible.
///
class HgiInterop final
{
public:
    HGIINTEROP_API
    HgiInterop();

    HGIINTEROP_API
    ~HgiInterop();

    /// Composite the provided textures over the application / viewer's
    /// framebuffer contents.
    /// `srcHgi`:
    ///     Determines the source format/platform of the textures.
    ///     Eg. if hgi is of type HgiMetal, the textures are HgiMetalTexture.
    /// `srcColor`: is the source color aov texture to composite to screen.
    /// `srcDepth`: (optional) is the depth aov texture to composite to screen.
    /// `dstApi`:
    ///     Determines what target format/platform the application is using.
    ///     E.g. If hgi==HgiMetal and dstApi==OpenGL then TransferToApp
    ///     will present the metal textures to the gl application.
    /// `dstFramebuffer`:
    ///     The framebuffer that the source textures are presented into. This
    ///     is a VtValue that encoding a framebuffer in a dstApi specific way.
    ///     E.g., a uint32_t (aka GLuint) for framebuffer object for
    ///     dstApi==OpenGL. For backwards compatibility, the currently bound
    ///     framebuffer is used when the VtValue is empty.
    ///
    /// `dstRegion`:
    ///     Subrect region of the framebuffer over which to composite.
    ///     Coordinates are (left, BOTTOM, width, height) which is the same
    ///     convention as OpenGL viewport coordinates.
    ///
    /// Note:
    /// To composite correctly, blending is enabled.
    /// If `srcDepth` is provided, depth testing is enabled.
    /// As a result, the contents of the application framebuffer matter.
    /// In order to use the contents of `srcColor` and `srcDepth` as-is
    /// (i.e., blit), the color attachment should be cleared to (0,0,0,0) and
    /// the depth attachment needs to be cleared to 1.
    ///
    HGIINTEROP_API
    void TransferToApp(
        Hgi *srcHgi,
        HgiTextureHandle const &srcColor,
        HgiTextureHandle const &srcDepth,
        TfToken const &dstApi,
        VtValue const &dstFramebuffer,
        GfVec4i const &dstRegion);

private:
    HgiInterop & operator=(const HgiInterop&) = delete;
    HgiInterop(const HgiInterop&) = delete;

#if defined(FORGE_METAL_SUPPORT_ENABLED)
    std::unique_ptr<HgiInteropMetal> _metalToOpenGL;
#elif defined(FORGE_VULKAN_SUPPORT_ENABLED)
    std::unique_ptr<HgiInteropVulkan> _vulkanToOpenGL;
#else
    std::unique_ptr<HgiInteropOpenGL> _openGLToOpenGL;
#endif
};


FORGE_NAMESPACE_END

#endif
