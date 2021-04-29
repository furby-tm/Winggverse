#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/debugCodes.h"
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
#ifndef FORGE_BASE_PLUG_DEBUG_CODES_H
#define FORGE_BASE_PLUG_DEBUG_CODES_H

#include "forge/forge.h"
#include "forge/base/tf/debug.h"

FORGE_NAMESPACE_BEGIN

TF_DEBUG_CODES(

    PLUG_LOAD,
    PLUG_REGISTRATION,
    PLUG_LOAD_IN_SECONDARY_THREAD,
    PLUG_INFO_SEARCH

);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_DEBUG_CODES_H
