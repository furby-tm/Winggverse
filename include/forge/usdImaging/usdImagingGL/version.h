#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImagingGL/version.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_GL_VERSION_H
#define FORGE_USD_IMAGING_USD_IMAGING_GL_VERSION_H

// 0 -> 1: added IDRenderColor decode and direct Rprim path fetching.
// 1 -> 2: added RenderParams::enableUsdDrawModes
// 2 -> 3: refactor picking API.
// 3 -> 4: Add "instancerContext" to new picking API.
// 4 -> 5: Use UsdImagingGLEngine::_GetSceneDelegate() instead of _delegate.
// 5 -> 6: Use UsdImagingGLEngine::_GetHdEngine() instead of _engine.
// 6 -> 7: Added UsdImagingGLEngine::_GetTaskController() and _IsUsingLegacyImpl()
// 7 -> 8: Added outHitNormal parameter to UsdImagingGLEngine::TestIntersection()
#define USDIMAGINGGL_API_VERSION 8

#endif // FORGE_USD_IMAGING_USD_IMAGING_GL_VERSION_H
