#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/tokens.h"
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
#ifndef FORGE_IMAGING_HD_PH_TOKENS_H
#define FORGE_IMAGING_HD_PH_TOKENS_H

#include "forge/base/tf/staticTokens.h"
#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

#define HDPH_GLSL_PROGRAM_TOKENS \
  (smoothNormalsFloatToFloat)(smoothNormalsFloatToPacked)(smoothNormalsDoubleToDouble)( \
      smoothNormalsDoubleToPacked)(flatNormalsTriFloatToFloat)(flatNormalsTriFloatToPacked)( \
      flatNormalsTriDoubleToDouble)(flatNormalsTriDoubleToPacked)(flatNormalsQuadFloatToFloat)( \
      flatNormalsQuadFloatToPacked)(flatNormalsQuadDoubleToDouble)( \
      flatNormalsQuadDoubleToPacked)(quadrangulateFloat)(quadrangulateDouble)

#define HDPH_TOKENS \
  (packedSmoothNormals)(smoothNormals)(packedFlatNormals)(flatNormals)(scale)(bias)(rotation)( \
      translation)(sRGB)(raw)((colorSpaceAuto, "auto"))

#define HDPH_LIGHT_TOKENS (color)

#define HDPH_TEXTURE_TOKENS \
  (wrapS)(wrapT)(wrapR)(black)(clamp)(mirror)(repeat)(useMetadata)(minFilter)(magFilter)(linear)( \
      nearest)(linearMipmapLinear)(linearMipmapNearest)(nearestMipmapLinear)( \
      nearestMipmapNearest)

#define HDPH_RENDER_BUFFER_TOKENS ((phoenixMsaaSampleCount, "phoenix:msaaSampleCount"))

#define HDPH_RENDER_SETTINGS_TOKENS \
  (enableTinyPrimCulling)(volumeRaymarchingStepSize)(volumeRaymarchingStepSizeLighting)( \
      volumeMaxTextureMemoryPerField)

// Material tags help bucket prims into different queues for draw submission.
// The tags supported by Phoenix are:
//    defaultMaterialTag : opaque geometry
//    masked : opaque geometry that uses cutout masks (e.g., foliage)
//    translucentToSelection: opaque geometry that allows occluded selection
//                            to show through
//    additive : transparent geometry (cheap OIT solution w/o sorting)
//    translucent: transparent geometry (OIT solution w/ sorted fragment lists)
//    volume : transparent geoometry (raymarched)
#define HDPH_MATERIAL_TAG_TOKENS \
  (defaultMaterialTag)(masked)(translucentToSelection)(additive)(translucent)(volume)

#define HDPH_SDR_METADATA_TOKENS (swizzle)

#define HDPH_PERF_TOKENS (copyBufferGpuToGpu)(copyBufferCpuToGpu)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdPhGLSLProgramTokens, HDPH_API, HDPH_GLSL_PROGRAM_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhTokens, HDPH_API, HDPH_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhLightTokens, HDPH_API, HDPH_LIGHT_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhTextureTokens, HDPH_API, HDPH_TEXTURE_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhRenderBufferTokens, HDPH_API, HDPH_RENDER_BUFFER_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhRenderSettingsTokens, HDPH_API, HDPH_RENDER_SETTINGS_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhMaterialTagTokens, HDPH_API, HDPH_MATERIAL_TAG_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhSdrMetadataTokens, HDPH_API, HDPH_SDR_METADATA_TOKENS);

TF_DECLARE_PUBLIC_TOKENS(HdPhPerfTokens, HDPH_API, HDPH_PERF_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_TOKENS_H
