#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/systemInfo.h"
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
#ifndef FORGE_BASE_ARCH_SYSTEM_INFO_H
#define FORGE_BASE_ARCH_SYSTEM_INFO_H

/// \file arch/systemInfo.h
/// \ingroup group_arch_SystemFunctions
/// Provide architecture-specific system information.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_arch_SystemFunctions
///@{

/// Return current working directory as a string.
ARCH_API
std::string ArchGetCwd();

/// Return the path to the program's executable.
ARCH_API
std::string ArchGetExecutablePath();

/// Return the system's memory page size.  Safe to assume power-of-two.
ARCH_API
int ArchGetPageSize();

///@}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_SYSTEM_INFO_H
