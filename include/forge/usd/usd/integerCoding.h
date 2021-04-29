#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/integerCoding.h"
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
#ifndef FORGE_USD_USD_INTEGER_CODING_H
#define FORGE_USD_USD_INTEGER_CODING_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"

#include <cstdint>
#include <memory>

FORGE_NAMESPACE_BEGIN

class Usd_IntegerCompression
{
public:
    // Return the max compression buffer size required for \p numInts 32-bit
    // integers.
    USD_API
    static size_t GetCompressedBufferSize(size_t numInts);

    // Return the max decompression working space size required for \p numInts
    // 32-bit integers.
    USD_API
    static size_t GetDecompressionWorkingSpaceSize(size_t numInts);

    // Compress \p numInts ints from \p ints to \p compressed.  The
    // \p compressed space must point to at least
    // GetCompressedBufferSize(numInts) bytes.  Return the actual number
    // of bytes written to \p compressed.
    USD_API
    static size_t CompressToBuffer(
        int32_t const *ints, size_t numInts, char *compressed);

    // Compress \p numInts ints from \p ints to \p compressed.  The
    // \p compressed space must point to at least
    // GetCompressedBufferSize(numInts) bytes.  Return the actual number
    // of bytes written to \p compressed.
    USD_API
    static size_t CompressToBuffer(
        uint32_t const *ints, size_t numInts, char *compressed);

    // Decompress \p compressedSize bytes from \p compressed to produce
    // \p numInts 32-bit integers into \p ints.  Clients may supply
    // \p workingSpace to save allocations if several decompressions will be
    // done but it isn't required.  If supplied it must point to at least
    // GetDecompressionWorkingSpaceSize(numInts) bytes.
    USD_API
    static size_t DecompressFromBuffer(
        char const *compressed, size_t compressedSize,
        int32_t *ints, size_t numInts,
        char *workingSpace=nullptr);

    // Decompress \p compressedSize bytes from \p compressed to produce
    // \p numInts 32-bit integers into \p ints.  Clients may supply
    // \p workingSpace to save allocations if several decompressions will be
    // done but it isn't required.  If supplied it must point to at least
    // GetDecompressionWorkingSpaceSize(numInts) bytes.
    USD_API
    static size_t DecompressFromBuffer(
        char const *compressed, size_t compressedSize,
        uint32_t *ints, size_t numInts,
        char *workingSpace=nullptr);
};

class Usd_IntegerCompression64
{
public:
    // Return the max compression buffer size required for \p numInts 64-bit
    // integers.
    USD_API
    static size_t GetCompressedBufferSize(size_t numInts);

    // Return the max decompression working space size required for \p numInts
    // 64-bit integers.
    USD_API
    static size_t GetDecompressionWorkingSpaceSize(size_t numInts);

    // Compress \p numInts ints from \p ints to \p compressed.  The
    // \p compressed space must point to at least
    // GetCompressedBufferSize(numInts) bytes.  Return the actual number
    // of bytes written to \p compressed.
    USD_API
    static size_t CompressToBuffer(
        int64_t const *ints, size_t numInts, char *compressed);

    // Compress \p numInts ints from \p ints to \p compressed.  The
    // \p compressed space must point to at least
    // GetCompressedBufferSize(numInts) bytes.  Return the actual number
    // of bytes written to \p compressed.
    USD_API
    static size_t CompressToBuffer(
        uint64_t const *ints, size_t numInts, char *compressed);

    // Decompress \p compressedSize bytes from \p compressed to produce
    // \p numInts 64-bit integers into \p ints.  Clients may supply
    // \p workingSpace to save allocations if several decompressions will be
    // done but it isn't required.  If supplied it must point to at least
    // GetDecompressionWorkingSpaceSize(numInts) bytes.
    USD_API
    static size_t DecompressFromBuffer(
        char const *compressed, size_t compressedSize,
        int64_t *ints, size_t numInts,
        char *workingSpace=nullptr);

    // Decompress \p compressedSize bytes from \p compressed to produce
    // \p numInts 64-bit integers into \p ints.  Clients may supply
    // \p workingSpace to save allocations if several decompressions will be
    // done but it isn't required.  If supplied it must point to at least
    // GetDecompressionWorkingSpaceSize(numInts) bytes.
    USD_API
    static size_t DecompressFromBuffer(
        char const *compressed, size_t compressedSize,
        uint64_t *ints, size_t numInts,
        char *workingSpace=nullptr);
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_INTEGER_CODING_H
