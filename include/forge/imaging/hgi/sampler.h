#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/sampler.h"
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
#ifndef FORGE_IMAGING_HGI_SAMPLER_H
#define FORGE_IMAGING_HGI_SAMPLER_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/handle.h"
#include "forge/imaging/hgi/types.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiSamplerDesc
///
/// Describes the properties needed to create a GPU sampler.
///
/// <ul>
/// <li>debugName:
///   This label can be applied as debug label for GPU debugging.</li>
/// <li>magFilter:
///    The (magnification) filter used to combine pixels when the sample area is
///    smaller than a pixel.</li>
/// <li>minFilter:
///    The (minification) filter used to combine pixels when the sample area is
///    larger than a pixel.</li>
/// <li> mipFilter:
///    The filter used for combining pixels between two mipmap levels.</li>
/// <li>addressMode***:
///    Wrapping modes.</li>
/// </ul>
///
struct HgiSamplerDesc
{
    HgiSamplerDesc()
        : magFilter(HgiSamplerFilterNearest)
        , minFilter(HgiSamplerFilterNearest)
        , mipFilter(HgiMipFilterNotMipmapped)
        , addressModeU(HgiSamplerAddressModeClampToEdge)
        , addressModeV(HgiSamplerAddressModeClampToEdge)
        , addressModeW(HgiSamplerAddressModeClampToEdge)
    {}

    std::string debugName;
    HgiSamplerFilter magFilter;
    HgiSamplerFilter minFilter;
    HgiMipFilter mipFilter;
    HgiSamplerAddressMode addressModeU;
    HgiSamplerAddressMode addressModeV;
    HgiSamplerAddressMode addressModeW;
};

HGI_API
bool operator==(
    const HgiSamplerDesc& lhs,
    const HgiSamplerDesc& rhs);

HGI_API
bool operator!=(
    const HgiSamplerDesc& lhs,
    const HgiSamplerDesc& rhs);


///
/// \class HgiSampler
///
/// Represents a graphics platform independent GPU sampler resource that
/// perform texture sampling operations.
/// Samplers should be created via Hgi::CreateSampler.
///
class HgiSampler
{
public:
    HGI_API
    virtual ~HgiSampler();

    /// The descriptor describes the object.
    HGI_API
    HgiSamplerDesc const& GetDescriptor() const;

    /// This function returns the handle to the Hgi backend's gpu resource, cast
    /// to a uint64_t. Clients should avoid using this function and instead
    /// use Hgi base classes so that client code works with any Hgi platform.
    /// For transitioning code to Hgi, it can however we useful to directly
    /// access a platform's internal resource handles.
    /// There is no safety provided in using this. If you by accident pass a
    /// HgiMetal resource into an OpenGL call, bad things may happen.
    /// In OpenGL this returns the GLuint resource name.
    /// In Metal this returns the id<MTLSamplerState> as uint64_t.
    /// In Vulkan this returns the VkSampler as uint64_t.
    HGI_API
    virtual uint64_t GetRawResource() const = 0;

protected:
    HGI_API
    HgiSampler(HgiSamplerDesc const& desc);

    HgiSamplerDesc _descriptor;

private:
    HgiSampler() = delete;
    HgiSampler & operator=(const HgiSampler&) = delete;
    HgiSampler(const HgiSampler&) = delete;
};

using HgiSamplerHandle = HgiHandle<HgiSampler>;
using HgiSamplerHandleVector = std::vector<HgiSamplerHandle>;


FORGE_NAMESPACE_END

#endif
