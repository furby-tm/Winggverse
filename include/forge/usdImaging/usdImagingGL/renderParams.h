#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImagingGL/renderParams.h"
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

/// \file usdImagingGL/renderParams.h

#ifndef FORGE_USD_IMAGING_USD_IMAGING_GL_RENDER_PARAMS_H
#define FORGE_USD_IMAGING_USD_IMAGING_GL_RENDER_PARAMS_H

#include "forge/forge.h"
#include "forge/usdImaging/usdImagingGL/api.h"

#include "forge/usd/usd/timeCode.h"

#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

enum class UsdImagingGLDrawMode
{
    DRAW_POINTS,
    DRAW_WIREFRAME,
    DRAW_WIREFRAME_ON_SURFACE,
    DRAW_SHADED_FLAT,
    DRAW_SHADED_SMOOTH,
    DRAW_GEOM_ONLY,
    DRAW_GEOM_FLAT,
    DRAW_GEOM_SMOOTH
};

// Note: some assumptions are made about the order of these enums, so please
// be careful when updating them.
enum class UsdImagingGLCullStyle
{
    CULL_STYLE_NO_OPINION,
    CULL_STYLE_NOTHING,
    CULL_STYLE_BACK,
    CULL_STYLE_FRONT,
    CULL_STYLE_BACK_UNLESS_DOUBLE_SIDED,

    CULL_STYLE_COUNT
};


/// \class UsdImagingGLRenderParams
///
/// Used as an arguments class for various methods in UsdImagingGLEngine.
///
class UsdImagingGLRenderParams
{
public:

    typedef std::vector<GfVec4d> ClipPlanesVector;

    UsdTimeCode frame;
    float complexity;
    UsdImagingGLDrawMode drawMode;
    bool showGuides;
    bool showProxy;
    bool showRender;
    bool forceRefresh;
    bool flipFrontFacing;
    UsdImagingGLCullStyle cullStyle;
    bool enableIdRender;
    bool enableLighting;
    bool enableSampleAlphaToCoverage;
    bool applyRenderState;
    bool gammaCorrectColors;
    bool highlight;
    GfVec4f overrideColor;
    GfVec4f wireframeColor;
    float alphaThreshold; // threshold < 0 implies automatic
    ClipPlanesVector clipPlanes;
    bool enableSceneMaterials;
    bool enableSceneLights;
    // Respect USD's model:drawMode attribute...
    bool enableUsdDrawModes;
    GfVec4f clearColor;
    TfToken colorCorrectionMode;
    int lut3dSizeOCIO;

    inline UsdImagingGLRenderParams();

    inline bool operator==(const UsdImagingGLRenderParams &other) const;

    inline bool operator!=(const UsdImagingGLRenderParams &other) const {
        return !(*this == other);
    }
};


UsdImagingGLRenderParams::UsdImagingGLRenderParams() :
    frame(UsdTimeCode::EarliestTime()),
    complexity(1.0),
    drawMode(UsdImagingGLDrawMode::DRAW_SHADED_SMOOTH),
    showGuides(false),
    showProxy(true),
    showRender(false),
    forceRefresh(false),
    flipFrontFacing(false),
    cullStyle(UsdImagingGLCullStyle::CULL_STYLE_NOTHING),
    enableIdRender(false),
    enableLighting(true),
    enableSampleAlphaToCoverage(false),
    applyRenderState(true),
    gammaCorrectColors(true),
    highlight(false),
    overrideColor(.0f, .0f, .0f, .0f),
    wireframeColor(.0f, .0f, .0f, .0f),
    alphaThreshold(-1),
    clipPlanes(),
    enableSceneMaterials(true),
    enableSceneLights(true),
    enableUsdDrawModes(true),
    clearColor(0,0,0,1),
    lut3dSizeOCIO(65)
{
}

bool
UsdImagingGLRenderParams::operator==(const UsdImagingGLRenderParams &other)
    const
{
    return frame                       == other.frame
        && complexity                  == other.complexity
        && drawMode                    == other.drawMode
        && showGuides                  == other.showGuides
        && showProxy                   == other.showProxy
        && showRender                  == other.showRender
        && forceRefresh                == other.forceRefresh
        && flipFrontFacing             == other.flipFrontFacing
        && cullStyle                   == other.cullStyle
        && enableIdRender              == other.enableIdRender
        && enableLighting              == other.enableLighting
        && enableSampleAlphaToCoverage == other.enableSampleAlphaToCoverage
        && applyRenderState            == other.applyRenderState
        && gammaCorrectColors          == other.gammaCorrectColors
        && highlight                   == other.highlight
        && overrideColor               == other.overrideColor
        && wireframeColor              == other.wireframeColor
        && alphaThreshold              == other.alphaThreshold
        && clipPlanes                  == other.clipPlanes
        && enableSceneMaterials        == other.enableSceneMaterials
        && enableSceneLights           == other.enableSceneLights
        && enableUsdDrawModes          == other.enableUsdDrawModes
        && clearColor                  == other.clearColor
        && colorCorrectionMode         == other.colorCorrectionMode
        && lut3dSizeOCIO               == other.lut3dSizeOCIO;
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_GL_RENDER_PARAMS_H
