#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/error.h"
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
#ifndef FORGE_BASE_ARCH_ERROR_H
#define FORGE_BASE_ARCH_ERROR_H

/// \file arch/error.h
/// \ingroup group_arch_Diagnostics
/// Low-level fatal error reporting.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/defines.h"
#include "forge/base/arch/functionLite.h"
#include <stddef.h>

FORGE_NAMESPACE_BEGIN

/// Print message to standard error and abort program.
///
/// \param msg The reason for the failure.
/// \param funcName The name of the function that \c Arch_Error was called from.
/// \param lineNo The line number of the file that \c Arch_Error was called from.
/// \param fileName The name of the file that \c Arch_Error was called from.
///
/// \private
[[noreturn]]
ARCH_API
void Arch_Error(const char* msg, const char* funcName,
                size_t lineNo, const char* fileName);

/// Print warning message to standard error, but continue execution.
///
/// \param msg The reason for the warning.
/// \param funcName The name of the function that \c Arch_Warning was called from.
/// \param lineNo The line number of the file that \c Arch_Warning was called from.
/// \param fileName The name of the file that \c Arch_Warning was called from.
///
/// \private
ARCH_API
void Arch_Warning(const char* msg, const char* funcName,
                  size_t lineNo, const char* fileName);

/// \addtogroup group_arch_Diagnostics
///@{

/// Unconditionally aborts the program.
///
/// \param msg is a literal string, a \c const \c char* (but not
///        an \c std::string) that describes why the program is aborting.
/// \hideinitializer
#define ARCH_ERROR(msg) \
    Arch_Error(msg, __ARCH_FUNCTION__, __LINE__, __ARCH_FILE__)

/// Prints a warning message to stderr.
///
/// \param msg is a literal string, a \c const \c char* (but not
///        an \c std::string).
/// \hideinitializer
#define ARCH_WARNING(msg) \
    Arch_Warning(msg, __ARCH_FUNCTION__, __LINE__, __ARCH_FILE__)

/// Aborts the program if \p cond evaluates to false.
/// \hideinitializer
#define ARCH_AXIOM(cond) \
    if (!(cond)) ARCH_ERROR("[" #cond "] axiom failed")

///@}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_ERROR_H
