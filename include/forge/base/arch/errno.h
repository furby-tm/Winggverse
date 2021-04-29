#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/errno.h"
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
#ifndef FORGE_BASE_ARCH_ERRNO_H
#define FORGE_BASE_ARCH_ERRNO_H

/// \file arch/errno.h
/// \ingroup group_arch_SystemFunctions
/// Functions for dealing with system errors.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_arch_SystemFunctions
///@{

/// Return the error string for the current value of errno.
///
/// This function provides a thread-safe method of fetching the error string
/// from errno. POSIX.1c defines errno as a macro which provides access to a
/// thread-local integer. This function is thread-safe.
/// \overload
ARCH_API std::string ArchStrerror();

/// Return the error string for the specified value of errno.
///
/// This function is thread-safe.
ARCH_API std::string ArchStrerror(int errorCode);

#if defined(ARCH_OS_WINDOWS)
/// Return the error string for the specified error code.
///
/// This function is thread-safe.
ARCH_API std::string ArchStrSysError(unsigned long errorCode);
#endif

///@}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_ERRNO_H
