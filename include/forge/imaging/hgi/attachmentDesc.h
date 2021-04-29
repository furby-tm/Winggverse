#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/attachmentDesc.h"
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
#ifndef FORGE_IMAGING_HGI_ATTACHMENT_DESC_H
#define FORGE_IMAGING_HGI_ATTACHMENT_DESC_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/types.h"
#include "forge/base/gf/vec4f.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiAttachmentDesc
///
/// Describes the properties of a framebuffer attachment.
///
/// <ul>
/// <li>format:
///   The format of the attachment.
///   Must match what is set in HgiTextureDesc.</li>
/// <li>usage:
///   Describes how the texture is intended to be used.
///   Must match what is set in HgiTextureDesc.</li>
/// <li>loadOp:
///   The operation to perform on the attachment pixel data prior to rendering.</li>
/// <li>storeOp:
///   The operation to perform on the attachment pixel data after rendering.</li>
/// <li>clearValue:
///   The value to clear the attachment with (r,g,b,a) or (depth,stencil,x,x)</li>
/// <li>blendEnabled:
///   Determines if a blend operation should be applied to the attachment.</li>
/// <li> ***BlendFactor:
///   The blend factors for source and destination.</li>
/// <li> ***BlendOp:
///   The blending operation.</li>
///
struct HgiAttachmentDesc
{
    HgiAttachmentDesc()
    : format(HgiFormatInvalid)
    , usage(0)
    , loadOp(HgiAttachmentLoadOpLoad)
    , storeOp(HgiAttachmentStoreOpStore)
    , clearValue(0)
    , blendEnabled(false)
    , srcColorBlendFactor(HgiBlendFactorZero)
    , dstColorBlendFactor(HgiBlendFactorZero)
    , colorBlendOp(HgiBlendOpAdd)
    , srcAlphaBlendFactor(HgiBlendFactorZero)
    , dstAlphaBlendFactor(HgiBlendFactorZero)
    , alphaBlendOp(HgiBlendOpAdd)
    {}

    HgiFormat format;
    HgiTextureUsage usage;
    HgiAttachmentLoadOp loadOp;
    HgiAttachmentStoreOp storeOp;
    GfVec4f clearValue;
    bool blendEnabled;
    HgiBlendFactor srcColorBlendFactor;
    HgiBlendFactor dstColorBlendFactor;
    HgiBlendOp colorBlendOp;
    HgiBlendFactor srcAlphaBlendFactor;
    HgiBlendFactor dstAlphaBlendFactor;
    HgiBlendOp alphaBlendOp;
};

using HgiAttachmentDescVector = std::vector<HgiAttachmentDesc>;

HGI_API
bool operator==(
    const HgiAttachmentDesc& lhs,
    const HgiAttachmentDesc& rhs);

HGI_API
bool operator!=(
    const HgiAttachmentDesc& lhs,
    const HgiAttachmentDesc& rhs);

HGI_API
std::ostream& operator<<(
    std::ostream& out,
    const HgiAttachmentDesc& attachment);


FORGE_NAMESPACE_END

#endif
