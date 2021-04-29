#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/version.h"
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
#ifndef FORGE_IMAGING_HD_VERSION_H
#define FORGE_IMAGING_HD_VERSION_H

// 18 -> 19: Add support for SceneDelegate surface shaders.
// 19 -> 20: RenderPass constructor takes RenderIndex. RasterState class.
// 20 -> 21: Add HdSceneDelegate::IsEnabled().
// 21 -> 22: split HdRasterState out of HdRenderPass and renamed to HdRenderPassState.
//           HdEngine::Draw API change.
// 22 -> 23: remove ID render API
// 23 -> 24: GetPathForInstanceIndex returns absolute instance index.
// 24 -> 25: move simpleLightingShader to Hdx.
// 25 -> 26: move camera and light to Hdx.
// 26 -> 27: move drawTarget to Hdx.
// 27 -> 28: switch render index Sprim to take a typeId.
// 28 -> 29: cameras only support matrices.
// 29 -> 30: added IDRenderColor decode and direct Rprim path fetching.
// 30 -> 31: added pre-chained buffer sources
// 31 -> 32: renamed HdShader{Param} to HdMaterial{Param}
// 32 -> 33: Deleted GetPathForInstanceIndex; added GetScenePrimPath.
// 32 -> 34: Added HdInstancerContext to GetScenePrimPath.
// 34 -> 35: HdRepr is using std::unique_ptr<HdDrawItem>
// 35 -> 36: InsertRprim/InsertInstancer no longer take instancerId,
//           HdSceneDelegate now has GetInstancerId
// 36 -> 37: Renamed HdRprim::_SetMaterialId to SetMaterialId. It no longer
//           takes changeTracker.
// 37 -> 38: Removed Bprim garbage collection API from HdChangeTracker and
//           HdResourceRegistry.
// 38 -> 39: Removed garbage collection API from HdChangeTracker and
//           HdResourceRegistry.
// 39 -> 40: Removed Bind and Unbind API from HdRenderPassState.
// 40 -> 41: Renamed HdDelegate::GetMaterialNeworkselector() to
//           GetMaterialRenderContexts(). It now returns a TfTokenVector.
#define HD_API_VERSION 41

// 1  ->  2: SimpleLighting -> FallbackLighting
#define HD_SHADER_API 2

#endif // FORGE_IMAGING_HD_VERSION_H
