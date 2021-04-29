#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdAppUtils/camera.h"
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
#ifndef FORGE_USD_IMAGING_USD_APP_UTILS_CAMERA_H
#define FORGE_USD_IMAGING_USD_APP_UTILS_CAMERA_H

/// \file usdAppUtils/camera.h
///
/// Collection of module-scoped utilities for applications that operate using
/// USD cameras.

#include "forge/forge.h"
#include "forge/usdImaging/usdAppUtils/api.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdGeom/camera.h"


FORGE_NAMESPACE_BEGIN


/// Gets the UsdGeomCamera matching \p cameraPath from the USD stage \p stage.
///
/// If \p cameraPath is an absolute path, this is equivalent to
/// UsdGeomCamera::Get(). Otherwise, if \p cameraPath is a single-element path
/// representing just the name of a camera prim, then \p stage will be searched
/// looking for a UsdGeomCamera matching that name. The UsdGeomCamera schema
/// for that prim will be returned if found, or an invalid UsdGeomCamera will
/// be returned if not.
///
/// Note that if \p cameraPath is a multi-element path, a warning is issued and
/// it is just made absolute using the absolute root path before searching. In
/// the future, this could potentially be changed to use a suffix-based match.
USDAPPUTILS_API
UsdGeomCamera UsdAppUtilsGetCameraAtPath(
        const UsdStagePtr& stage,
        const SdfPath& cameraPath);


FORGE_NAMESPACE_END


#endif
