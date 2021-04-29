#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/function.h"
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
#ifndef FORGE_BASE_ARCH_FUNCTION_H
#define FORGE_BASE_ARCH_FUNCTION_H

/// \file arch/function.h
/// Define preprocessor function name macros.
///
/// This file extents the functionality of forge/base/arch/functionLite.h.
/// This file needs to be public but shouldn't be included directly by
/// anything outside of \c lib/tf.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/functionLite.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// Return well formatted function name.
///
/// This function assumes \c function is __ARCH_FUNCTION__ and
/// \c prettyFunction is __ARCH_PRETTY_FUNCTION__, and attempts to
/// reconstruct a well formatted function name.
///
/// \ingroup group_arch_Diagnostic
ARCH_API
std::string ArchGetPrettierFunctionName(const std::string &function,
                                        const std::string &prettyFunction);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_FUNCTION_H
