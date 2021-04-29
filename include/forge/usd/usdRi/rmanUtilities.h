#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRi/rmanUtilities.h"
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
#ifndef FORGE_USD_USD_RI_RMAN_UTILITIES_H
#define FORGE_USD_USD_RI_RMAN_UTILITIES_H

/// \file usdRi/rmanUtilities.h
/// Utilities for converting between USD encodings and Renderman encodings in
/// cases where there is a difference.

#include "forge/forge.h"
#include "forge/usd/usdRi/api.h"

FORGE_NAMESPACE_BEGIN

class TfToken;

/// Given a \p token representing a UsdGeom interpolate boundary value, returns
/// corresponding rman enum (converted to int).
USDRI_API
int UsdRiConvertToRManInterpolateBoundary(const TfToken &token);

/// Given the integer \p i that corresponds to an rman enum for interpolate
/// boundary condition, returns the equivalent UsdGeom token.
USDRI_API
const TfToken &UsdRiConvertFromRManInterpolateBoundary(int i);

/// Given a \p token representing a UsdGeom face-varying interpolate boundary
/// value, returns corresponding rman enum (converted to int).
USDRI_API
int UsdRiConvertToRManFaceVaryingLinearInterpolation(const TfToken &token);

/// Given the integer \p i that corresponds to an rman enum for face-varying
/// interpolate boundary condition, returns the equivalent UsdGeom token.
USDRI_API
const TfToken &UsdRiConvertFromRManFaceVaryingLinearInterpolation(int i);

/// Given a \p token representing a UsdGeom Catmull-Clark triangle subdivision
/// rule value, returns corresponding rman enum (converted to int).
USDRI_API
int UsdRiConvertToRManTriangleSubdivisionRule(const TfToken &token);

/// Given the integer \p i that corresponds to an rman enum for a Catmull-
/// Clark triangle subdivision rule, returns the equivalent UsdGeom token.
USDRI_API
const TfToken &UsdRiConvertFromRManTriangleSubdivisionRule(int i);

FORGE_NAMESPACE_END

#endif //FORGE_USD_USD_RI_RMAN_UTILITIES_H
