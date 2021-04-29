#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/env.h"
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
#ifndef FORGE_BASE_ARCH_ENV_H
#define FORGE_BASE_ARCH_ENV_H

#include "forge/forge.h"
#include "forge/base/arch/api.h"

#include <string>

FORGE_NAMESPACE_BEGIN

///
/// Architecture dependent access to environment variables.
/// \ingroup group_arch_SystemFunctions
///

///
/// Returns \c true if and only if the current environment contains \c name.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
bool
ArchHasEnv(const std::string &name);

///
/// Gets a value from the current environment identified by \c name.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
std::string
ArchGetEnv(const std::string &name);

///
/// Creates or modifies an environment variable.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
bool
ArchSetEnv(const std::string &name, const std::string &value, bool overwrite);

///
/// Removes an environment variable.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
bool
ArchRemoveEnv(const std::string &name);

///
/// Expands environment variables in \c str.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
std::string
ArchExpandEnvironmentVariables(const std::string& str);

///
/// Return an array of the environment variables.
/// \ingroup group_arch_SystemFunctions
///
ARCH_API
char**
ArchEnviron();

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_ENV_H
