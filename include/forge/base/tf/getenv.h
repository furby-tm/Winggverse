#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/getenv.h"
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
#ifndef FORGE_BASE_TF_GETENV_H
#define FORGE_BASE_TF_GETENV_H

/// \file tf/getenv.h
/// \ingroup group_tf_SystemsExt
/// Functions for accessing environment variables.

#include "forge/forge.h"
#include "forge/base/tf/api.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_tf_SystemsExt
///@{

/// Return an environment variable as a string.
///
/// Return the value of the environment variable \c envName
/// as a string.  If the variable is unset, or is the empty string,
/// then \c defaultValue is returned.
TF_API
std::string TfGetenv(const std::string& envName,
                     const std::string& defaultValue = "");

/// Return an environment variable as an integer.
///
/// Return the value of the environment variable \c envName as an integer.  If
/// the variable is unset, or is the empty string, then \c defaultValue is
/// returned.  Otherwise, the function uses atoi() to convert the string to an
/// integer: the implication being that if the string is not a valid integer,
/// you get back whatever value atoi() comes up with.
TF_API
int TfGetenvInt(const std::string& envName, int defaultValue);

/// Return an environment variable as a boolean.
///
/// Return the value of the environment variable \c envName as a boolean.  If
/// the variable is unset, or is the empty string, then \c defaultValue is
/// returned. A value of \c true is returned if the environment variable is
/// any of "true", "yes", "on" or "1"; the match is not case sensitive. All
/// other values yield a return value of \c false.
TF_API
bool TfGetenvBool(const std::string&, bool defaultValue);

/// Return an environment variable as a double.
///
/// Return the value of the environment variable \c envName as a double.  If
/// the variable is unset, or is the empty string, then \c defaultValue is
/// returned. Otherwise, the function uses TfStringToDouble() to convert the
/// string to a double: the implication being that if the string is not a
/// valid double, you get back whatever value TfStringToDouble() comes up
/// with.
TF_API
double TfGetenvDouble(const std::string& envName, double defaultValue);

///@}

FORGE_NAMESPACE_END

#endif
