#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdGeom/samplingUtils.h"
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
#ifndef FORGE_USD_USD_GEOM_SAMPLING_UTILS_H
#define FORGE_USD_USD_GEOM_SAMPLING_UTILS_H

#include "forge/forge.h"
#include "forge/base/vt/types.h"

FORGE_NAMESPACE_BEGIN

class UsdAttribute;
class UsdPrim;
class UsdTimeCode;


/// Get the authored positions (or points), velocities, and accelerations.
/// Also fetches the velocity scale. This method fails if the positions can't
/// be fetched. If velocities can't be fetched or positions are not time-varying,
/// then \p velocities is cleared and \p velocitiesSampleTime is not changed.
/// If accelerations can't be fetched then \p accelerations is cleared.
bool
UsdGeom_GetPositionsVelocitiesAndAccelerations(
    const UsdAttribute& positionsAttr,
    const UsdAttribute& velocitiesAttr,
    const UsdAttribute& accelerationsAttr,
    UsdTimeCode baseTime,
    size_t expectedNumPositions,
    VtVec3fArray* positions,
    VtVec3fArray* velocities,
    UsdTimeCode* velocitiesSampleTime,
    VtVec3fArray* accelerations,
    float* velocityScale,
    UsdPrim const &prim);

/// Get the authored scales. This method fails if the scales can't be fetched.
bool
UsdGeom_GetScales(
    const UsdAttribute& scalesAttr,
    const UsdTimeCode baseTime,
    size_t expectedNumScales,
    VtVec3fArray* scales,
    UsdPrim const &prim);


/// Get the authored orientations and angular velocities for instance
/// transform computation. This method fails if the orientations can't be
/// fetched. If angular velocities can't be fetched or orientations are not
/// time-varying, then \p angularVelocities is cleared and
/// \p angularVelocitiesSampleTime is not changed.
bool
UsdGeom_GetOrientationsAndAngularVelocities(
    const UsdAttribute& orientationsAttr,
    const UsdAttribute& angularVelocitiesAttr,
    UsdTimeCode baseTime,
    size_t expectedNumOrientations,
    VtQuathArray* orientations,
    VtVec3fArray* angularVelocities,
    UsdTimeCode* angularVelocitiesSampleTime,
    UsdPrim const &prim);

/// Compute the scaled time difference based on velocity scale and
/// timeCodesPerSecond
float
UsdGeom_CalculateTimeDelta(
    const float velocityScale,
    const UsdTimeCode time,
    const UsdTimeCode sampleTime,
    const double timeCodesPerSecond);


FORGE_NAMESPACE_END

#endif
