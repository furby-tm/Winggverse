#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/blackbody.h"
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
#ifndef FORGE_USD_USD_LUX_BLACKBODY_H
#define FORGE_USD_USD_LUX_BLACKBODY_H

/// \file usdLux/blackbody.h

#include "forge/usd/usdLux/api.h"
#include "forge/base/gf/vec3f.h"

FORGE_NAMESPACE_BEGIN

/// Compute the RGB equivalent of the spectrum emitted by a blackbody
/// with the given temperature in degrees Kelvin, with normalized
/// luminance.
USDLUX_API
GfVec3f UsdLuxBlackbodyTemperatureAsRgb(float colorTemp);

FORGE_NAMESPACE_END

#endif
