#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/setenv.h"
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
#ifndef FORGE_BASE_TF_SETENV_H
#define FORGE_BASE_TF_SETENV_H

/// \file tf/setenv.h
/// \ingroup group_tf_SystemsExt
/// Functions for setting and unsetting environment variables

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// Set an environment variable.
///
/// Sets an environment variable and ensures that it appears in the Python
/// environment if Python is initialized. If Python has not yet been
/// initialized, the variable \p envName is set to \p value in the environment
/// using \c setenv. Otherwise, it is set both in the environment and in
/// Python using \c TfPySetenv. The new value overwrites any existing value.
///
/// If the value cannot be set, false is returned and a warning is posted.
/// Otherwise, the return value is true.
///
/// \ingroup group_tf_SystemsExt
TF_API
bool TfSetenv(const std::string& envName, const std::string& value);

/// Unset an environment variable.
///
/// Unsets an environment variable and ensures that it is also removed from
/// the Python environment if Python is initialized. If Python has not yet
/// been initialized, the variable \p envName is unset in the environment
/// using \c unsetenv. Otherwise, it is unset both in the environment and in
/// Python using \c TfPyUnsetenv.
///
/// If the value cannot be unset, false is returned and a warning is posted.
/// Otherwise, the return value is true.
///
/// \ingroup group_tf_SystemsExt
TF_API
bool TfUnsetenv(const std::string& envName);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_SETENV_H
