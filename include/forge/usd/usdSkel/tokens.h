#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/tokens.h"
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
#ifndef USDSKEL_TOKENS_H
#define USDSKEL_TOKENS_H

/// \file usdSkel/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdSkelTokensType
///
/// \link UsdSkelTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdSkelTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdSkelTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdSkelTokens->bindTransforms);
/// \endcode
struct UsdSkelTokensType {
    USDSKEL_API UsdSkelTokensType();
    /// \brief "bindTransforms"
    ///
    /// UsdSkelSkeleton
    const TfToken bindTransforms;
    /// \brief "blendShapes"
    ///
    /// UsdSkelAnimation
    const TfToken blendShapes;
    /// \brief "blendShapeWeights"
    ///
    /// UsdSkelAnimation
    const TfToken blendShapeWeights;
    /// \brief "jointNames"
    ///
    /// UsdSkelSkeleton
    const TfToken jointNames;
    /// \brief "joints"
    ///
    /// UsdSkelAnimation, UsdSkelSkeleton
    const TfToken joints;
    /// \brief "normalOffsets"
    ///
    /// UsdSkelBlendShape
    const TfToken normalOffsets;
    /// \brief "offsets"
    ///
    /// UsdSkelBlendShape
    const TfToken offsets;
    /// \brief "pointIndices"
    ///
    /// UsdSkelBlendShape
    const TfToken pointIndices;
    /// \brief "primvars:skel:geomBindTransform"
    ///
    /// UsdSkelBindingAPI
    const TfToken primvarsSkelGeomBindTransform;
    /// \brief "primvars:skel:jointIndices"
    ///
    /// UsdSkelBindingAPI
    const TfToken primvarsSkelJointIndices;
    /// \brief "primvars:skel:jointWeights"
    ///
    /// UsdSkelBindingAPI
    const TfToken primvarsSkelJointWeights;
    /// \brief "restTransforms"
    ///
    /// UsdSkelSkeleton
    const TfToken restTransforms;
    /// \brief "rotations"
    ///
    /// UsdSkelAnimation
    const TfToken rotations;
    /// \brief "scales"
    ///
    /// UsdSkelAnimation
    const TfToken scales;
    /// \brief "skel:animationSource"
    ///
    /// UsdSkelBindingAPI
    const TfToken skelAnimationSource;
    /// \brief "skel:blendShapes"
    ///
    /// UsdSkelBindingAPI
    const TfToken skelBlendShapes;
    /// \brief "skel:blendShapeTargets"
    ///
    /// UsdSkelBindingAPI
    const TfToken skelBlendShapeTargets;
    /// \brief "skel:joints"
    ///
    /// UsdSkelBindingAPI
    const TfToken skelJoints;
    /// \brief "skel:skeleton"
    ///
    /// UsdSkelBindingAPI
    const TfToken skelSkeleton;
    /// \brief "translations"
    ///
    /// UsdSkelAnimation
    const TfToken translations;
    /// \brief "weight"
    ///
    /// UsdSkelInbetweenShape - The weight location at which the inbetween shape applies.
    const TfToken weight;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdSkelTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdSkelTokensType
extern USDSKEL_API TfStaticData<UsdSkelTokensType> UsdSkelTokens;

FORGE_NAMESPACE_END

#endif
