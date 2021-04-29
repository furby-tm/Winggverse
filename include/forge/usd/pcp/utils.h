#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/utils.h"
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
#ifndef FORGE_USD_PCP_UTILS_H
#define FORGE_USD_PCP_UTILS_H

/// \file pcp/utils.h

#include "forge/forge.h"
#include "forge/usd/sdf/layer.h"

#include <string>

FORGE_NAMESPACE_BEGIN

// Returns an SdfLayer::FileFormatArguments object with the "target" argument
// set to \p target if \p target is not empty.
SdfLayer::FileFormatArguments
Pcp_GetArgumentsForFileFormatTarget(
    const std::string& target);

// Returns an SdfLayer::FileFormatArguments object with the "target" argument
// set to \p target if \p target is not empty and a target is
// not embedded within the given \p identifier.
SdfLayer::FileFormatArguments
Pcp_GetArgumentsForFileFormatTarget(
    const std::string& identifier,
    const std::string& target);

// \overload
// Same as above, but modifies \p args instead of returning by value.
void
Pcp_GetArgumentsForFileFormatTarget(
    const std::string& identifier,
    const std::string& target,
    SdfLayer::FileFormatArguments* args);

// If a target argument is embedded in \p identifier, copies contents of
// \p defaultArgs to \p localArgs, removes the "target" argument, and returns
// a const reference to \p localArgs. Otherwise, returns a const reference to
// \p defaultArgs. This lets us avoid making a copy of \p defaultArgs unless
// needed.
const SdfLayer::FileFormatArguments&
Pcp_GetArgumentsForFileFormatTarget(
    const std::string& identifier,
    const SdfLayer::FileFormatArguments* defaultArgs,
    SdfLayer::FileFormatArguments* localArgs);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_UTILS_H
