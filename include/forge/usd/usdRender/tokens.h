#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRender/tokens.h"
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
#ifndef USDRENDER_TOKENS_H
#define USDRENDER_TOKENS_H

/// \file usdRender/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdRender/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdRenderTokensType
///
/// \link UsdRenderTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdRenderTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdRenderTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdRenderTokens->adjustApertureHeight);
/// \endcode
struct UsdRenderTokensType {
    USDRENDER_API UsdRenderTokensType();
    /// \brief "adjustApertureHeight"
    ///
    /// Possible value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr()
    const TfToken adjustApertureHeight;
    /// \brief "adjustApertureWidth"
    ///
    /// Possible value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr()
    const TfToken adjustApertureWidth;
    /// \brief "adjustPixelAspectRatio"
    ///
    /// Possible value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr()
    const TfToken adjustPixelAspectRatio;
    /// \brief "aspectRatioConformPolicy"
    ///
    /// UsdRenderSettingsBase
    const TfToken aspectRatioConformPolicy;
    /// \brief "camera"
    ///
    /// UsdRenderSettingsBase
    const TfToken camera;
    /// \brief "color3f"
    ///
    /// Default value for UsdRenderVar::GetDataTypeAttr()
    const TfToken color3f;
    /// \brief "cropAperture"
    ///
    /// Possible value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr()
    const TfToken cropAperture;
    /// \brief "dataType"
    ///
    /// UsdRenderVar
    const TfToken dataType;
    /// \brief "dataWindowNDC"
    ///
    /// UsdRenderSettingsBase
    const TfToken dataWindowNDC;
    /// \brief "expandAperture"
    ///
    /// Possible value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr(), Default value for UsdRenderSettingsBase::GetAspectRatioConformPolicyAttr()
    const TfToken expandAperture;
    /// \brief "full"
    ///
    /// Possible value for UsdRenderSettings::GetMaterialBindingPurposesAttr()
    const TfToken full;
    /// \brief "includedPurposes"
    ///
    /// UsdRenderSettings
    const TfToken includedPurposes;
    /// \brief "instantaneousShutter"
    ///
    /// UsdRenderSettingsBase
    const TfToken instantaneousShutter;
    /// \brief "intrinsic"
    ///
    /// Possible value for UsdRenderVar::GetSourceTypeAttr()
    const TfToken intrinsic;
    /// \brief "lpe"
    ///
    /// Possible value for UsdRenderVar::GetSourceTypeAttr()
    const TfToken lpe;
    /// \brief "materialBindingPurposes"
    ///
    /// UsdRenderSettings
    const TfToken materialBindingPurposes;
    /// \brief "orderedVars"
    ///
    /// UsdRenderProduct
    const TfToken orderedVars;
    /// \brief "pixelAspectRatio"
    ///
    /// UsdRenderSettingsBase
    const TfToken pixelAspectRatio;
    /// \brief "preview"
    ///
    /// Possible value for UsdRenderSettings::GetMaterialBindingPurposesAttr()
    const TfToken preview;
    /// \brief "primvar"
    ///
    /// Possible value for UsdRenderVar::GetSourceTypeAttr()
    const TfToken primvar;
    /// \brief "productName"
    ///
    /// UsdRenderProduct
    const TfToken productName;
    /// \brief "products"
    ///
    /// UsdRenderSettings
    const TfToken products;
    /// \brief "productType"
    ///
    /// UsdRenderProduct
    const TfToken productType;
    /// \brief "raster"
    ///
    /// RenderProduct productType value that indicates a 2D raster image of pixels., Default value for UsdRenderProduct::GetProductTypeAttr()
    const TfToken raster;
    /// \brief "raw"
    ///
    /// Possible value for UsdRenderVar::GetSourceTypeAttr(), Default value for UsdRenderVar::GetSourceTypeAttr()
    const TfToken raw;
    /// \brief "renderSettingsPrimPath"
    ///
    /// Stage-level metadata that encodes the path to UsdRenderSettingsPrim to use for rendering.
    const TfToken renderSettingsPrimPath;
    /// \brief "resolution"
    ///
    /// UsdRenderSettingsBase
    const TfToken resolution;
    /// \brief "sourceName"
    ///
    /// UsdRenderVar
    const TfToken sourceName;
    /// \brief "sourceType"
    ///
    /// UsdRenderVar
    const TfToken sourceType;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdRenderTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdRenderTokensType
extern USDRENDER_API TfStaticData<UsdRenderTokensType> UsdRenderTokens;

FORGE_NAMESPACE_END

#endif
