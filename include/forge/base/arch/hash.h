#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/hash.h"
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
#ifndef FORGE_BASE_ARCH_HASH_H
#define FORGE_BASE_ARCH_HASH_H

/// \file arch/hash.h
/// Hash functions.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/inttypes.h"

FORGE_NAMESPACE_BEGIN

/// Hash \a len bytes of \a data.
///
/// To compute a hash value for data that is not contiguous in memory, iterate
/// over all the contiguous blocks of memory and accumulate the hash value by
/// passing it on as \p seed.  Note that this is *not* equivalent to hashing the
/// contiguous pieces as a whole.  Support for that may be added in future.
///
ARCH_API uint32_t ArchHash(const char *data, size_t len);
/// \overload
ARCH_API uint32_t ArchHash(const char *data, size_t len, uint32_t seed);

/// Hash \a len bytes of \a data.
///
/// To compute a hash value for data that is not contiguous in memory, iterate
/// over all the contiguous blocks of memory and accumulate the hash value by
/// passing it on as \p seed.  Note that this is *not* equivalent to hashing the
/// contiguous pieces as a whole.  Support for that may be added in future.
///
ARCH_API uint64_t ArchHash64(const char *data, size_t len);
/// \overload
ARCH_API uint64_t ArchHash64(const char *data, size_t len, uint64_t seed);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_HASH_H
