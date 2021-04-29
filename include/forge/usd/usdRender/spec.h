#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRender/spec.h"
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
#ifndef FORGE_USD_USD_RENDER_SPEC_H
#define FORGE_USD_USD_RENDER_SPEC_H

/// \file usdRender/spec.h

#include "forge/forge.h"
#include "forge/usd/usdRender/api.h"
#include "forge/usd/usdRender/settingsBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRender/tokens.h"

#include "forge/base/gf/frustum.h"


#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class UsdRenderSettings;

/// A self-contained specification of render settings.
/// \note This is preliminary API and is likely to change.
struct UsdRenderSpec {
    /// Specification of a product.  See UsdRenderProduct.
    struct Product {
        /// The type of product, ex: "raster".
        TfToken type;
        /// The name of the product, which uniquely identifies it.
        TfToken name;
        /// Path to the primary UsdGeomCamera camera to use for this product.
        SdfPath cameraPath;
        /// If set to true, disables motion blur.
        bool instantaneousShutter;
        /// The pixel resolution of the product.
        GfVec2i resolution;
        /// The pixel aspect ratio as adjusted by aspectRatioConformPolicy.
        float pixelAspectRatio;
        /// The policy that was applied to conform aspect ratio
        /// mismatches between the aperture and image.
        TfToken aspectRatioConformPolicy;
        /// The camera aperture size as adjusted by aspectRatioConformPolicy.
        GfVec2f apertureSize;
        /// The data window, in NDC terms relative to the aperture.
        /// (0,0) corresponds to bottom-left and (1,1) corresponds to
        /// top-right.  Note that the data window can partially cover
        /// or extend beyond the unit range, for representing overscan
        /// or cropped renders.
        GfRange2f dataWindowNDC;
        /// The render vars used by this product, as indices into the
        /// top-level renderVars array.
        std::vector<size_t> renderVarIndices;
        /// Any extra settings values discovered in requested namespaces.
        VtDictionary extraSettings;
    };
    /// Specification of a render variable (aka AOV).  See UsdRenderVar.
    struct RenderVar {
        /// The path of this render var, which uniquely identifies it.
        SdfPath renderVarPath;
        /// The value data type of the variable, as a USD type name.
        TfToken dataType;
        std::string sourceName;
        TfToken sourceType;
        /// Any extra settings values discovered in requested namespaces.
        VtDictionary extraSettings;
    };
    /// The full list of products requested by this render.
    std::vector<Product> products;
    /// The full list of render vars requested by products in this render.
    std::vector<RenderVar> renderVars;
    /// List of purposes to use to filter scene contents.
    VtArray<TfToken> includedPurposes;
    /// List of material binding purposes.
    VtArray<TfToken> materialBindingPurposes;
    /// Any extra settings values discovered in requested namespaces.
    VtDictionary extraSettings;
};

/// Computes the specification of the render settings.
/// For each product, applies the aspectRatioConformPolicy
/// and computes a final screenWindow and pixelAspectRatio.
///
/// Any other attributes encountered are returned in extraSettings.
/// If a non-empty list of namespaces is provided, only attributes
/// within those namespaces are returned.
/// If an empty list of namespaces is provided, all custom
/// (non-schema) attributes are returned.
/// The same list of namespaces is used for finding extraSettings
/// in all UsdRender prim types.
USDRENDER_API
UsdRenderSpec
UsdRenderComputeSpec(UsdRenderSettings const& settings,
                     UsdTimeCode time,
                     std::vector<std::string> const& namespaces);

FORGE_NAMESPACE_END

#endif
