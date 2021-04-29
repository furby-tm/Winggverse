#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/pyUtils.h"
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
#ifndef FORGE_USD_SDF_PY_UTILS_H
#define FORGE_USD_SDF_PY_UTILS_H

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/layer.h"

#include <boost/python/dict.hpp>
#include <string>

FORGE_NAMESPACE_BEGIN

/// Convert the Python dictionary \p dict to an SdfLayer::FileFormatArguments
/// object and return it via \p args.
///
/// If a non-string key or value is encountered, \p errMsg will be filled in
/// (if given) and this function will return false. Otherwise, this function
/// will return true.
SDF_API bool
SdfFileFormatArgumentsFromPython(
    const boost::python::dict& dict,
    SdfLayer::FileFormatArguments* args,
    std::string* errMsg = NULL);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PY_UTILS_H
