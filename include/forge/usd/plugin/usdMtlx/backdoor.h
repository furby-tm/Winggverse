#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdMtlx/backdoor.h"
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
#ifndef FORGE_USD_PLUGIN_USD_MTLX_BACKDOOR_H
#define FORGE_USD_PLUGIN_USD_MTLX_BACKDOOR_H

#include "forge/forge.h"

#include "forge/usd/plugin/usdMtlx/api.h"

#include "forge/base/tf/declarePtrs.h"
#include <string>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(UsdStage);

/// Return MaterialX XML in \p buffer converted to a USD stage.
/// This is to allow testing from Python.  If \p nodeGraphs is true
/// then only node graphs are read, otherwise everything else is read.
USDMTLX_API
UsdStageRefPtr UsdMtlx_TestString(const std::string& buffer,
                                  bool nodeGraphs = false);

/// Return MaterialX XML in file at \p pathname converted to a USD stage.
/// This is to allow testing from Python.  If \p nodeGraphs is true
/// then only node graphs are read, otherwise everything else is read.
USDMTLX_API
UsdStageRefPtr UsdMtlx_TestFile(const std::string& pathname,
                                bool nodeGraphs = false);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PLUGIN_USD_MTLX_BACKDOOR_H
