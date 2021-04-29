#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/types.h"
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
#ifndef FORGE_IMAGING_HGI_TYPES_H
#define FORGE_IMAGING_HGI_TYPES_H

#include "forge/forge.h"
#include "forge/base/gf/vec3i.h"
#include "forge/imaging/hgi/api.h"
#include <vector>
#include <limits>
#include <stdlib.h>


FORGE_NAMESPACE_BEGIN

/// \enum HgiFormat
///
/// HgiFormat describes the memory format of image buffers used in Hgi.
/// These formats are closely aligned with HdFormat and allow us to keep Hgi
/// independent of Hd.
///
/// For reference, see:
///   https://www.khronos.org/registry/vulkan/specs/1.1/html/vkspec.html#VkFormat
enum HgiFormat : int
{
    HgiFormatInvalid = -1,

    // UNorm8 - a 1-byte value representing a float between 0 and 1.
    // float value = (unorm / 255.0f);
    HgiFormatUNorm8 = 0,
    HgiFormatUNorm8Vec2,
    /* HgiFormatUNorm8Vec3 */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatUNorm8Vec4,

    // SNorm8 - a 1-byte value representing a float between -1 and 1.
    // float value = max(snorm / 127.0f, -1.0f);
    HgiFormatSNorm8,
    HgiFormatSNorm8Vec2,
    /* HgiFormatSNorm8Vec3 */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatSNorm8Vec4,

    // Float16 - a 2-byte IEEE half-precision float.
    HgiFormatFloat16,
    HgiFormatFloat16Vec2,
    HgiFormatFloat16Vec3,
    HgiFormatFloat16Vec4,

    // Float32 - a 4-byte IEEE float.
    HgiFormatFloat32,
    HgiFormatFloat32Vec2,
    HgiFormatFloat32Vec3,
    HgiFormatFloat32Vec4,

    // UInt16 - a 2-byte unsigned integer
    HgiFormatUInt16,
    HgiFormatUInt16Vec2,
    HgiFormatUInt16Vec3,
    HgiFormatUInt16Vec4,

    // Int32 - a 4-byte signed integer
    HgiFormatInt32,
    HgiFormatInt32Vec2,
    HgiFormatInt32Vec3,
    HgiFormatInt32Vec4,

    // UNorm8 SRGB - a 1-byte value representing a float between 0 and 1.
    // Gamma compression/decompression happens during read/write.
    // Alpha component is linear.
    /* HgiFormatUNorm8srgb */     // Unsupported by OpenGL
    /* HgiFormatUNorm8Vec2srgb */ // Unsupported by OpenGL
    /* HgiFormatUNorm8Vec3srgb */ // Unsupported Metal (MTLPixelFormat)
    HgiFormatUNorm8Vec4srgb,

    // BPTC compressed. 3-component, 4x4 blocks, signed floating-point
    HgiFormatBC6FloatVec3,

    // BPTC compressed. 3-component, 4x4 blocks, unsigned floating-point
    HgiFormatBC6UFloatVec3,

    // BPTC compressed. 4-component, 4x4 blocks, unsigned byte.
    // Representing a float between 0 and 1.
    HgiFormatBC7UNorm8Vec4,

    // BPTC compressed. 4-component, 4x4 blocks, unsigned byte, sRGB.
    // Representing a float between 0 and 1.
    HgiFormatBC7UNorm8Vec4srgb,

    // S3TC/DXT compressed. 4-component, 4x4 blocks, unsigned byte
    // Representing a float between 0 and 1.
    HgiFormatBC1UNorm8Vec4,

    // S3TC/DXT compressed. 4-component, 4x4 blocks, unsigned byte
    // Representing a float between 0 and 1.
    HgiFormatBC3UNorm8Vec4,

    // Depth stencil format (Float32 can be used for just depth)
    HgiFormatFloat32UInt8,

    HgiFormatCount
};

/// \class HgiMipInfo
///
/// HgiMipInfo describes size and other info for a mip level.
struct HgiMipInfo
{
    /// Offset in bytes from start of texture data to start of mip map.
    size_t byteOffset;
    /// Dimension of mip GfVec3i.
    GfVec3i dimensions;
    /// size of (one layer if array of) mip map in bytes.
    size_t byteSizePerLayer;
};

/// Return the count of components in the given format.
HGI_API
size_t HgiGetComponentCount(HgiFormat f);

/// Return the size of a single element of the given format.
///
/// For an uncompressed format, returns the number of bytes per pixel
/// and sets blockWidth and blockHeight to 1.
/// For a compressed format (e.g., BC6), returns the number of bytes per
/// block and sets blockWidth and blockHeight to the width and height of
/// a block.
///
HGI_API
size_t HgiGetDataSizeOfFormat(
    HgiFormat f,
    size_t *blockWidth = nullptr,
    size_t *blockHeight = nullptr);

/// Return whether the given format uses compression.
HGI_API
bool HgiIsCompressed(HgiFormat f);

/// Returns the size necessary to allocate a buffer of given dimensions
/// and format, rounding dimensions up to suitable multiple when
/// using a compressed format.
HGI_API
size_t HgiGetDataSize(
    HgiFormat f,
    const GfVec3i &dimensions);

/// Returns mip infos.
///
/// If dataByteSize is specified, the levels stops when the total memory
/// required by all levels up to that point reach the specified value.
/// Otherwise, the levels stop when all dimensions are 1.
/// Mip map sizes are calculated by dividing the previous mip level by two and
/// rounding down to the nearest integer (minimum integer is 1).
/// level 0: 37x53
/// level 1: 18x26
/// level 2: 9x13
/// level 3: 4x6
/// level 4: 2x3
/// level 5: 1x1
HGI_API
std::vector<HgiMipInfo>
HgiGetMipInfos(
    HgiFormat format,
    const GfVec3i& dimensions,
    size_t layerCount,
    size_t dataByteSize = std::numeric_limits<size_t>::max());

FORGE_NAMESPACE_END

#endif
