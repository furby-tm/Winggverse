#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/inttypes.h"
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
#ifndef FORGE_BASE_ARCH_INTTYPES_H
#define FORGE_BASE_ARCH_INTTYPES_H

/// \file arch/inttypes.h
/// \ingroup group_arch_Bits
/// Define integral types.
///
/// By including this file, the "standard" integer types \c int16_t,
/// \c int32_t, and \c int64_t are all defined, as are their unsigned
/// counterparts \c uint16_t, \c uint32_t, and \c uint64_t.  This also
/// includes the macros for limits, constants, and printf format specifiers.

// These defines should in theory not be needed to get the related sized-int
// macros, as this was not adopted by the C++ committee and was dropped by the C
// committee, but glibc erroneously "respects" them so we need to have them.
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#include <cinttypes>
#include <cstdint>

#include "forge/forge.h"
#include "forge/base/arch/defines.h"
#include <sys/types.h>

FORGE_NAMESPACE_BEGIN

typedef unsigned char uchar;

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_INTTYPES_H
