#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/version.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_VERSION_H
#define FORGE_USD_IMAGING_USD_IMAGING_VERSION_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN



// Version 3 -- add support for nested instancers in InsertInstancer.
// Version 4 -- Populate returns SdfPath, HdxSelectionInstanceMap.
// Version 5 -- GetPathForInstanceIndex returns absoluteInstanceIndex.
// Version 6 -- PrimAdater::GetDependPaths.
// Version 7 -- GetPathForInstanceIndex returns instanceContext.
// Version 8 -- GetPathForInstanceIndex returns instanceContext (as
//              SdfPathVector) and rprimPath  separately.
// Version 9 -- Rework UsdImagingEngineGL::RenderParams API to conform to
//              updated purpose tokens and make proxy imaging optional.
// Version 10 - Add "UsdPrim" parameter to adapter PopulateSelection.
// Version 11 - PopulateSelection takes "usdPath" (relative to USD stage),
//              rather than a path with the delegate root.
// Version 12 - Adapter PopulateSelection signature change to adapt to
//              flat instance indices in hydra selection.
// Version 13 - Deleted GetPathForInstanceIndex; added GetScenePrimPath.
// Version 14 - Added HdInstancerContext to GetScenePrimPath.
// Version 15 - CanPopulateMaster renamed to CanPopulateUsdInstance.
// Version 16 - InsertRprim/InsertInstancer no longer take an instancer path.

#define USD_IMAGING_API_VERSION 16


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_VERSION_H
