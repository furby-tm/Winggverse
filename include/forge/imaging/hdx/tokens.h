#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/tokens.h"
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
#ifndef FORGE_IMAGING_HDX_TOKENS_H
#define FORGE_IMAGING_HDX_TOKENS_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN


#define HDX_TOKENS              \
    (hdxOitCounterBuffer)       \
    (hdxOitDataBuffer)          \
    (hdxOitDepthBuffer)         \
    (hdxOitIndexBuffer)         \
    (hdxSelectionBuffer)        \
    (imagerVersion)             \
    (lightingContext)           \
    (lightingShader)            \
    (occludedSelectionOpacity)  \
    (oitCounter)                \
    (oitData)                   \
    (oitDepth)                  \
    (oitIndices)                \
    (oitUniforms)               \
    (oitCounterBufferBar)       \
    (oitDataBufferBar)          \
    (oitDepthBufferBar)         \
    (oitIndexBufferBar)         \
    (oitUniformBar)             \
    (oitRenderPassState)        \
    (oitScreenSize)             \
    (oitRequestFlag)            \
    (oitClearedFlag)            \
    (renderPassState)           \
    (renderIndexVersion)        \
    (selection)                 \
    (selectionState)            \
    (selectionOffsets)          \
    (selectionUniforms)         \
    (selColor)                  \
    (selLocateColor)            \
    (selectionPointColors)      \
    (drawTargetRenderPasses)    \
    (aovBindings)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxTokens, HDX_API, HDX_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#define HDX_PRIMITIVE_TOKENS    \
    (lightTypePositional)       \
    (lightTypeDirectional)      \
    (lightTypeSpot)             \
                                \
    (aovInputTask)              \
    (drawTargetTask)            \
    (drawTargetResolveTask)     \
    (colorizeSelectionTask)     \
    (oitRenderTask)             \
    (oitResolveTask)            \
    (oitVolumeRenderTask)       \
    (pickTask)                  \
    (pickFromRenderBufferTask)  \
    (presentTask)               \
    (renderTask)                \
    (renderSetupTask)           \
    (simpleLightTask)           \
    (shadowTask)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxPrimitiveTokens, HDX_API, HDX_PRIMITIVE_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

// inCameraGuide is for guides for a camera that only show up when looking
// through that camera.

#define HDX_RENDERTAG_TOKENS   \
    (renderingGuide)            \
    (label)                     \
    (cameraGuide)               \
    (inCameraGuide)             \
    (streamline)                \
    (interactiveOnlyGeom)       \
    (path)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxRenderTagTokens, HDX_API, HDX_RENDERTAG_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

// XXX Deprecated Use: HdPhMaterialTagTokens
#define HDX_MATERIALTAG_TOKENS   \
    (additive)                   \
    (translucent)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxMaterialTagTokens, HDX_API, HDX_MATERIALTAG_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

#define HDX_COLOR_CORRECTION_TOKENS             \
    (disabled)                                  \
    (sRGB)                                      \
    (openColorIO)                               \
    (channelsOnly)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxColorCorrectionTokens, HDX_API, HDX_COLOR_CORRECTION_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

// Color channels
#define HDX_COLOR_CHANNEL_TOKENS  \
    (color)                         \
    (red)                           \
    (green)                         \
    (blue)                          \
    (alpha)                         \
    (luminance)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxColorChannelTokens, HDX_API, HDX_COLOR_CHANNEL_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * Color channels
 * colorIntermediate->colorIntermediate is used to ping-pong
 * between two color targets when a task wishes to
 * read from the color target and also write into it.
 */ 
#define HDX_AOV_TOKENS \
    (colorIntermediate)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxAovTokens, HDX_API, HDX_AOV_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_TOKENS_H
