#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/align.h"
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
#ifndef FORGE_BASE_ARCH_ALIGN_H
#define FORGE_BASE_ARCH_ALIGN_H

/// \file arch/align.h
/// \ingroup group_arch_Memory
/// Provide architecture-specific memory-alignment information.

#if !defined(__cplusplus)
#error This include file can only be included in C++ programs.
#endif

#include "forge/forge.h"
#include "forge/base/arch/defines.h"
#include <cstddef>
#include <cstdint>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_arch_Memory
///@{

/// Return suitably aligned memory size.
///
/// Requests to \c malloc() or \c ::new for a given size are often rounded
/// upward.  Given a request for \c nBytes bytes of storage, this function
/// returns the amount that would actually be consumed by the system to
/// satisfy it. This is needed for efficient user-defined memory management.
///
inline size_t
ArchAlignMemorySize(size_t nBytes) {
    return (nBytes + 7) & (~0x7);
}

/// Maximum extra space needed for alignment.
///
/// The \c ArchAlignMemorySize() can increase the required memory by no more
/// than \c ARCH_MAX_ALIGNMENT_INCREASE.
///
/// \hideinitializer
#define ARCH_MAX_ALIGNMENT_INCREASE	7

/// Align memory to the next "best" alignment value.
///
/// This will take a pointer and bump it to the next ideal alignment boundary
/// that will work for all data types.
///
inline void *
ArchAlignMemory(void *base)
{
    return reinterpret_cast<void *>
	((reinterpret_cast<uintptr_t>(base) + 7) & ~0x7);
}

/// The size of a CPU cache line on the current processor architecture in bytes.
///
/// \hideinitializer
#if defined(ARCH_OS_DARWIN) && defined(ARCH_CPU_ARM)
#define ARCH_CACHE_LINE_SIZE 128
#else
#define ARCH_CACHE_LINE_SIZE 64
#endif

///@}

FORGE_NAMESPACE_END

#endif	// FORGE_BASE_ARCH_ALIGN_H
