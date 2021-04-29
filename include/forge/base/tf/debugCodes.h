#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/debugCodes.h"
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
#ifndef FORGE_BASE_TF_DEBUG_CODES_H
#define FORGE_BASE_TF_DEBUG_CODES_H

#include "forge/forge.h"
#include "forge/base/tf/debug.h"

FORGE_NAMESPACE_BEGIN

//
// Note that this is a private header file to lib/tf.
// If you add a new entry here, please be sure to update DebugCodes.cpp as well.
//

TF_DEBUG_CODES(

    TF_DISCOVERY_TERSE,     // these are special in that they don't have a
    TF_DISCOVERY_DETAILED,  // corresponding entry in debugCodes.cpp; see
    TF_DEBUG_REGISTRY,      // registryManager.cpp and debug.cpp for the reason.
    TF_DLOPEN,
    TF_DLCLOSE,

    TF_SCRIPT_MODULE_LOADER,

    TF_TYPE_REGISTRY,

    TF_ATTACH_DEBUGGER_ON_ERROR,
    TF_ATTACH_DEBUGGER_ON_FATAL_ERROR,
    TF_ATTACH_DEBUGGER_ON_WARNING

);

FORGE_NAMESPACE_END

#endif
