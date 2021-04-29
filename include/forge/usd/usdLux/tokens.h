#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/tokens.h"
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
#ifndef USDLUX_TOKENS_H
#define USDLUX_TOKENS_H

/// \file usdLux/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdLuxTokensType
///
/// \link UsdLuxTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdLuxTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdLuxTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdLuxTokens->angular);
/// \endcode
struct UsdLuxTokensType {
    USDLUX_API UsdLuxTokensType();
    /// \brief "angular"
    ///
    /// Possible value for UsdLuxDomeLight::GetTextureFormatAttr()
    const TfToken angular;
    /// \brief "automatic"
    ///
    /// Possible value for UsdLuxDomeLight::GetTextureFormatAttr(), Default value for UsdLuxDomeLight::GetTextureFormatAttr()
    const TfToken automatic;
    /// \brief "collection:filterLink:includeRoot"
    ///
    /// UsdLuxLightFilter
    const TfToken collectionFilterLinkIncludeRoot;
    /// \brief "collection:lightLink:includeRoot"
    ///
    /// UsdLuxLight
    const TfToken collectionLightLinkIncludeRoot;
    /// \brief "collection:shadowLink:includeRoot"
    ///
    /// UsdLuxLight
    const TfToken collectionShadowLinkIncludeRoot;
    /// \brief "consumeAndContinue"
    ///
    /// Possible value for UsdLuxListAPI::GetLightListCacheBehaviorAttr()
    const TfToken consumeAndContinue;
    /// \brief "consumeAndHalt"
    ///
    /// Possible value for UsdLuxListAPI::GetLightListCacheBehaviorAttr()
    const TfToken consumeAndHalt;
    /// \brief "cubeMapVerticalCross"
    ///
    /// Possible value for UsdLuxDomeLight::GetTextureFormatAttr()
    const TfToken cubeMapVerticalCross;
    /// \brief "filterLink"
    ///
    ///  This token represents the collection name to use with UsdCollectionAPI to represent filter-linking of a UsdLuxLightFilter prim.
    const TfToken filterLink;
    /// \brief "filters"
    ///
    /// UsdLuxLight
    const TfToken filters;
    /// \brief "geometry"
    ///
    /// UsdLuxGeometryLight
    const TfToken geometry;
    /// \brief "ignore"
    ///
    /// Possible value for UsdLuxListAPI::GetLightListCacheBehaviorAttr()
    const TfToken ignore;
    /// \brief "inputs:angle"
    ///
    /// UsdLuxDistantLight
    const TfToken inputsAngle;
    /// \brief "inputs:color"
    ///
    /// UsdLuxLight
    const TfToken inputsColor;
    /// \brief "inputs:colorTemperature"
    ///
    /// UsdLuxLight
    const TfToken inputsColorTemperature;
    /// \brief "inputs:diffuse"
    ///
    /// UsdLuxLight
    const TfToken inputsDiffuse;
    /// \brief "inputs:enableColorTemperature"
    ///
    /// UsdLuxLight
    const TfToken inputsEnableColorTemperature;
    /// \brief "inputs:exposure"
    ///
    /// UsdLuxLight
    const TfToken inputsExposure;
    /// \brief "inputs:height"
    ///
    /// UsdLuxRectLight
    const TfToken inputsHeight;
    /// \brief "inputs:intensity"
    ///
    /// UsdLuxDistantLight, UsdLuxLight
    const TfToken inputsIntensity;
    /// \brief "inputs:length"
    ///
    /// UsdLuxCylinderLight
    const TfToken inputsLength;
    /// \brief "inputs:normalize"
    ///
    /// UsdLuxLight
    const TfToken inputsNormalize;
    /// \brief "inputs:radius"
    ///
    /// UsdLuxCylinderLight, UsdLuxSphereLight, UsdLuxDiskLight
    const TfToken inputsRadius;
    /// \brief "inputs:shadow:color"
    ///
    /// UsdLuxShadowAPI
    const TfToken inputsShadowColor;
    /// \brief "inputs:shadow:distance"
    ///
    /// UsdLuxShadowAPI
    const TfToken inputsShadowDistance;
    /// \brief "inputs:shadow:enable"
    ///
    /// UsdLuxShadowAPI
    const TfToken inputsShadowEnable;
    /// \brief "inputs:shadow:falloff"
    ///
    /// UsdLuxShadowAPI
    const TfToken inputsShadowFalloff;
    /// \brief "inputs:shadow:falloffGamma"
    ///
    /// UsdLuxShadowAPI
    const TfToken inputsShadowFalloffGamma;
    /// \brief "inputs:shaping:cone:angle"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingConeAngle;
    /// \brief "inputs:shaping:cone:softness"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingConeSoftness;
    /// \brief "inputs:shaping:focus"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingFocus;
    /// \brief "inputs:shaping:focusTint"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingFocusTint;
    /// \brief "inputs:shaping:ies:angleScale"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingIesAngleScale;
    /// \brief "inputs:shaping:ies:file"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingIesFile;
    /// \brief "inputs:shaping:ies:normalize"
    ///
    /// UsdLuxShapingAPI
    const TfToken inputsShapingIesNormalize;
    /// \brief "inputs:specular"
    ///
    /// UsdLuxLight
    const TfToken inputsSpecular;
    /// \brief "inputs:texture:file"
    ///
    /// UsdLuxDomeLight, UsdLuxRectLight
    const TfToken inputsTextureFile;
    /// \brief "inputs:texture:format"
    ///
    /// UsdLuxDomeLight
    const TfToken inputsTextureFormat;
    /// \brief "inputs:width"
    ///
    /// UsdLuxRectLight
    const TfToken inputsWidth;
    /// \brief "latlong"
    ///
    /// Possible value for UsdLuxDomeLight::GetTextureFormatAttr()
    const TfToken latlong;
    /// \brief "lightLink"
    ///
    ///  This token represents the collection name to use with UsdCollectionAPI to represent light-linking of a UsdLuxLight prim.
    const TfToken lightLink;
    /// \brief "lightList"
    ///
    /// UsdLuxListAPI
    const TfToken lightList;
    /// \brief "lightList:cacheBehavior"
    ///
    /// UsdLuxListAPI
    const TfToken lightListCacheBehavior;
    /// \brief "mirroredBall"
    ///
    /// Possible value for UsdLuxDomeLight::GetTextureFormatAttr()
    const TfToken mirroredBall;
    /// \brief "orientToStageUpAxis"
    ///
    ///  This token represents the suffix for a UsdGeomXformOp used to orient a light with the stage's up axis.
    const TfToken orientToStageUpAxis;
    /// \brief "portals"
    ///
    /// UsdLuxDomeLight
    const TfToken portals;
    /// \brief "shadowLink"
    ///
    ///  This token represents the collection name to use with UsdCollectionAPI to represent shadow-linking of a UsdLuxLight prim.
    const TfToken shadowLink;
    /// \brief "treatAsLine"
    ///
    /// UsdLuxCylinderLight
    const TfToken treatAsLine;
    /// \brief "treatAsPoint"
    ///
    /// UsdLuxSphereLight
    const TfToken treatAsPoint;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdLuxTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdLuxTokensType
extern USDLUX_API TfStaticData<UsdLuxTokensType> UsdLuxTokens;

FORGE_NAMESPACE_END

#endif
