#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/debugCodes.h"
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
#ifndef FORGE_USD_USD_DEBUG_CODES_H
#define FORGE_USD_USD_DEBUG_CODES_H

#include "forge/forge.h"
#include "forge/base/tf/debug.h"

FORGE_NAMESPACE_BEGIN


TF_DEBUG_CODES(
    USD_AUTO_APPLY_API_SCHEMAS,
    USD_CHANGES,
    USD_CLIPS,
    USD_COMPOSITION,
    USD_DATA_BD,
    USD_DATA_BD_TRY,
    USD_INSTANCING,
    USD_PATH_RESOLUTION,
    USD_PAYLOADS,
    USD_PRIM_LIFETIMES,
    USD_SCHEMA_REGISTRATION,
    USD_STAGE_CACHE,
    USD_STAGE_LIFETIMES,
    USD_STAGE_OPEN,
    USD_STAGE_INSTANTIATION_TIME,
    USD_VALUE_RESOLUTION,
    USD_VALIDATE_VARIABILITY

);


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_DEBUG_CODES_H
