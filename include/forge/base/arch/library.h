#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/library.h"
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
#ifndef FORGE_BASE_ARCH_LIBRARY_H
#define FORGE_BASE_ARCH_LIBRARY_H

#include "forge/forge.h"
#include "forge/base/arch/api.h"

#include <string>

#if defined(ARCH_OS_WINDOWS)
#   define ARCH_LIBRARY_LAZY    0
#   define ARCH_LIBRARY_NOW     0
#   define ARCH_LIBRARY_LOCAL   0
#   define ARCH_LIBRARY_GLOBAL  0
#   define ARCH_LIBRARY_SUFFIX  ".dll"
#   define ARCH_STATIC_LIBRARY_SUFFIX ".lib"
#else
#   include <dlfcn.h>
#   define ARCH_LIBRARY_LAZY    RTLD_LAZY
#   define ARCH_LIBRARY_NOW     RTLD_NOW
#   define ARCH_LIBRARY_LOCAL   RTLD_LOCAL
#   define ARCH_LIBRARY_GLOBAL  RTLD_GLOBAL
#   if defined(ARCH_OS_DARWIN)
#       define ARCH_LIBRARY_SUFFIX  ".dylib"
#   else
#       define ARCH_LIBRARY_SUFFIX  ".so"
#   endif
#   define ARCH_STATIC_LIBRARY_SUFFIX ".a"
#endif

// On MacOS shared libraries and loadable modules (aka loadable bundles aka
// plugins) are different entities. Most cross-platform software packages
// that create  loadable modules use .so as the extension on MacOS for
// compatibility, so we use that here.
#if defined(ARCH_OS_DARWIN)
#   define ARCH_PLUGIN_SUFFIX ".so"
#else
#   define ARCH_PLUGIN_SUFFIX ARCH_LIBRARY_SUFFIX
#endif

FORGE_NAMESPACE_BEGIN

/// library.h
/// Architecture dependent loading and unloading of dynamic libraries.
/// \ingroup group_arch_SystemFunctions

/// Load an executable object file.
/// \ingroup group_arch_SystemFunctions
///
/// Opens the dynamic library that is specified by filename.
/// Returning the handle to the module if successful; false otherwise.
ARCH_API
void* ArchLibraryOpen(const std::string &filename, int flag);

/// Obtain a description of the most recent error that occurred from
/// \c ArchLibraryOpen.
///\ingroup group_arch_SystemFunctions
ARCH_API
std::string ArchLibraryError();

/// Closes an object opened with \c ArchLibraryOpen.
/// \ingroup group_arch_SystemFunctions
ARCH_API
int ArchLibraryClose(void* handle);

/// Obtain the address of a symbol defined within an object opened with
/// \c ArchLibraryOpen.
/// \ingroup group_arch_SystemFunctions
///
/// Obtain the address of a symbol that is specified by name.
/// Returning the address of the symbol if successful; nullptr otherwise.
ARCH_API
void* ArchLibraryGetSymbolAddress(void* handle, const char* name);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_LIBRARY_H
