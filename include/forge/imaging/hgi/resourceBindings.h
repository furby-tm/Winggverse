#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/resourceBindings.h"
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
#ifndef FORGE_IMAGING_HGI_RESOURCEBINDINGS_H
#define FORGE_IMAGING_HGI_RESOURCEBINDINGS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/buffer.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/handle.h"
#include "forge/imaging/hgi/sampler.h"
#include "forge/imaging/hgi/texture.h"
#include "forge/imaging/hgi/types.h"

#include <string>
#include <vector>


FORGE_NAMESPACE_BEGIN





/// \struct HgiBufferBindDesc
///
/// Describes the binding information of a buffer (or array of buffers).
///
/// <ul>
/// <li>buffers:
///   The buffer(s) to be bound.
///   If there are more than one buffer, the buffers will be put in an
///   array-of-buffers. Please note that different platforms have varying
///   limits to max buffers in an array.</li>
/// <li>offsets:
///    Offset (in bytes) where data begins from the start of the buffer.
///    This if an offset for each buffer in 'buffers'.</li>
/// <li>resourceType:
///    The type of buffer(s) that is to be bound.
///    All buffers in the array must have the same type.
///    Vertex, index and indirect buffers are not bound to a resourceSet.
///    They are instead passed to the draw command.</li>
/// <li>bindingIndex:
///    Binding location for the buffer(s).</li>
/// <li>stageUsage:
///    What shader stage(s) the buffer will be used in.</li>
/// </ul>
///
struct HgiBufferBindDesc
{
    HGI_API
    HgiBufferBindDesc();

    HgiBufferHandleVector buffers;
    std::vector<uint32_t> offsets;
    HgiBindResourceType resourceType;
    uint32_t bindingIndex;
    HgiShaderStage stageUsage;
};
using HgiBufferBindDescVector = std::vector<HgiBufferBindDesc>;

HGI_API
bool operator==(
    const HgiBufferBindDesc& lhs,
    const HgiBufferBindDesc& rhs);

HGI_API
inline bool operator!=(
    const HgiBufferBindDesc& lhs,
    const HgiBufferBindDesc& rhs);

/// \struct HgiTextureBindDesc
///
/// Describes the binding information of a texture (or array of textures).
///
/// <ul>
/// <li>textures:
///   The texture(s) to be bound.
///   If there are more than one texture, the textures will be put in an
///   array-of-textures (not texture-array). Please note that different
///   platforms have varying limits to max textures in an array.</li>
/// <li>samplers:
///   (optional) The sampler(s) to be bound for each texture in `textures`.
///   If empty a default sampler (clamp_to_edge, linear) should be used. </li>
/// <li>resourceType:
///    The type of the texture(s) that is to be bound.
///    All textures in the array must have the same type.</li>
/// <li>bindingIndex:
///    Binding location for the texture</li>
/// <li>stageUsage:
///    What shader stage(s) the texture will be used in.</li>
/// </ul>
///
struct HgiTextureBindDesc
{
    HGI_API
    HgiTextureBindDesc();

    HgiTextureHandleVector textures;
    HgiSamplerHandleVector samplers;
    HgiBindResourceType resourceType;
    uint32_t bindingIndex;
    HgiShaderStage stageUsage;
};
using HgiTextureBindDescVector = std::vector<HgiTextureBindDesc>;

HGI_API
bool operator==(
    const HgiTextureBindDesc& lhs,
    const HgiTextureBindDesc& rhs);

HGI_API
bool operator!=(
    const HgiTextureBindDesc& lhs,
    const HgiTextureBindDesc& rhs);

/// \struct HgiResourceBindingsDesc
///
/// Describes a set of resources that are bound to the GPU during encoding.
///
/// <ul>
/// <li>buffers:
///   The buffers to be bound (E.g. uniform or shader storage).</li>
/// <li>textures:
///   The textures to be bound.</li>
/// </ul>
///
struct HgiResourceBindingsDesc
{
    HGI_API
    HgiResourceBindingsDesc();

    std::string debugName;
    HgiBufferBindDescVector buffers;
    HgiTextureBindDescVector textures;
};

HGI_API
bool operator==(
    const HgiResourceBindingsDesc& lhs,
    const HgiResourceBindingsDesc& rhs);

HGI_API
bool operator!=(
    const HgiResourceBindingsDesc& lhs,
    const HgiResourceBindingsDesc& rhs);


///
/// \class HgiResourceBindings
///
/// Represents a collection of buffers, texture and vertex attributes that will
/// be used by an cmds object (and pipeline).
///
class HgiResourceBindings
{
public:
    HGI_API
    virtual ~HgiResourceBindings();

    /// The descriptor describes the object.
    HGI_API
    HgiResourceBindingsDesc const& GetDescriptor() const;

protected:
    HGI_API
    HgiResourceBindings(HgiResourceBindingsDesc const& desc);

    HgiResourceBindingsDesc _descriptor;

private:
    HgiResourceBindings() = delete;
    HgiResourceBindings & operator=(const HgiResourceBindings&) = delete;
    HgiResourceBindings(const HgiResourceBindings&) = delete;
};

using HgiResourceBindingsHandle = HgiHandle<HgiResourceBindings>;
using HgiResourceBindingsHandleVector = std::vector<HgiResourceBindingsHandle>;


FORGE_NAMESPACE_END

#endif
