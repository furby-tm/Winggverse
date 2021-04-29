#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/graphicsCmdsDesc.h"
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
#ifndef FORGE_IMAGING_HGI_GRAPHICS_CMDS_DESC_H
#define FORGE_IMAGING_HGI_GRAPHICS_CMDS_DESC_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/attachmentDesc.h"
#include "forge/imaging/hgi/texture.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiGraphicsCmdsDesc
///
/// Describes the properties to begin a HgiGraphicsCmds.
///
/// <ul>
/// <li>colorAttachmentDescs:
///   Describes each of the color attachments.</li>
/// <li>depthAttachmentDesc:
///   Describes the depth attachment (optional)</li>
/// <li>colorTextures:
///   The color attachment render targets.</li>
/// <li>colorResolveTextures:
///   The (optional) textures that the color textures will be resolved into
///   at the end of the render pass.</li>
/// <li>depthTexture:
///   The depth attachment render target (optional)</li>
/// <li>depthResolveTexture:
///   The (optional) texture that the depth texture will be resolved into
///   at the end of the render pass.</li>
/// <li>width:
///   Render target width (in pixels)</li>
/// <li>height:
///   Render target height (in pixels)</li>
/// </ul>
///
struct HgiGraphicsCmdsDesc
{
    HgiGraphicsCmdsDesc()
    : colorAttachmentDescs()
    , depthAttachmentDesc()
    , colorTextures()
    , colorResolveTextures()
    , depthTexture()
    , depthResolveTexture()
    {}

    inline bool HasAttachments() const {
        return !colorAttachmentDescs.empty() || depthTexture;
    }

    HgiAttachmentDescVector colorAttachmentDescs;
    HgiAttachmentDesc depthAttachmentDesc;

    HgiTextureHandleVector colorTextures;
    HgiTextureHandleVector colorResolveTextures;

    HgiTextureHandle depthTexture;
    HgiTextureHandle depthResolveTexture;
};

HGI_API
bool operator==(
    const HgiGraphicsCmdsDesc& lhs,
    const HgiGraphicsCmdsDesc& rhs);

HGI_API
bool operator!=(
    const HgiGraphicsCmdsDesc& lhs,
    const HgiGraphicsCmdsDesc& rhs);

HGI_API
std::ostream& operator<<(
    std::ostream& out,
    const HgiGraphicsCmdsDesc& desc);


FORGE_NAMESPACE_END

#endif
