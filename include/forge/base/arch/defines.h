#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/defines.h"
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
#ifndef FORGE_BASE_ARCH_DEFINES_H
#define FORGE_BASE_ARCH_DEFINES_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

//
// OS
//

#if defined(__linux__)
#define ARCH_OS_LINUX
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#define ARCH_OS_DARWIN
#if TARGET_OS_IPHONE
#define ARCH_OS_IOS
#else
#define ARCH_OS_OSX
#endif
#elif defined(_WIN32) || defined(_WIN64)
#define ARCH_OS_WINDOWS
#endif

//
// Processor
//

#if defined(i386) || defined(__i386__) || defined(__x86_64__) || \
    defined(_M_IX86) || defined(_M_X64)
#define ARCH_CPU_INTEL
#elif defined(__arm__) || defined(__aarch64__) || defined(_M_ARM)
#define ARCH_CPU_ARM
#endif

//
// Bits
//

#if defined(__x86_64__) || defined(__aarch64__) || defined(_M_X64)
#define ARCH_BITS_64
#else
#error "Unsupported architecture.  x86_64 or ARM64 required."
#endif

//
// Compiler
//

#if defined(__clang__)
#define ARCH_COMPILER_CLANG
#define ARCH_COMPILER_CLANG_MAJOR __clang_major__
#define ARCH_COMPILER_CLANG_MINOR __clang_minor__
#define ARCH_COMPILER_CLANG_PATCHLEVEL __clang_patchlevel__
#elif defined(__GNUC__)
#define ARCH_COMPILER_GCC
#define ARCH_COMPILER_GCC_MAJOR __GNUC__
#define ARCH_COMPILER_GCC_MINOR __GNUC_MINOR__
#define ARCH_COMPILER_GCC_PATCHLEVEL __GNUC_PATCHLEVEL__
#elif defined(__ICC)
#define ARCH_COMPILER_ICC
#elif defined(_MSC_VER)
#define ARCH_COMPILER_MSVC
#define ARCH_COMPILER_MSVC_VERSION _MSC_VER
#endif

//
// Features
//

// Only use the GNU STL extensions on Linux when using gcc.
#if defined(ARCH_OS_LINUX) && defined(ARCH_COMPILER_GCC)
#define ARCH_HAS_GNU_STL_EXTENSIONS
#endif

// The current version of Apple clang does not support the thread_local
// keyword.
#if !(defined(ARCH_OS_DARWIN) && defined(ARCH_COMPILER_CLANG))
#define ARCH_HAS_THREAD_LOCAL
#endif

// The MAP_POPULATE flag for mmap calls only exists on Linux platforms.
#if defined(ARCH_OS_LINUX)
#define ARCH_HAS_MMAP_MAP_POPULATE
#endif

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_DEFINES_H
