#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/tokens.h"
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
#ifndef USD_TOKENS_H
#define USD_TOKENS_H

/// \file usd/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdTokensType
///
/// \link UsdTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdTokens->apiSchemas);
/// \endcode
struct UsdTokensType {
    USD_API UsdTokensType();
    /// \brief "apiSchemas"
    ///
    ///  A listop metadata containing the API schemas which have been applied to this prim, using the Apply() method on the particular schema class.
    const TfToken apiSchemas;
    /// \brief "clips"
    ///
    ///  Dictionary that contains the definition of the clip sets on this prim. See \ref UsdClipsAPI::GetClips.
    const TfToken clips;
    /// \brief "clipSets"
    ///
    ///  ListOp that may be used to affect how opinions from clip sets are applied during value resolution.  See \ref UsdClipsAPI::GetClipSets.
    const TfToken clipSets;
    /// \brief "collection"
    ///
    /// Property namespace prefix for the UsdCollectionAPI schema.
    const TfToken collection;
    /// \brief "exclude"
    ///
    ///  This is the token used to exclude a path from a collection.  Although it is not a possible value for the "expansionRule" attribute, it is used as the expansionRule for excluded paths  in UsdCollectionAPI::MembershipQuery::IsPathIncluded.
    const TfToken exclude;
    /// \brief "excludes"
    ///
    /// UsdCollectionAPI
    const TfToken excludes;
    /// \brief "expandPrims"
    ///
    /// Possible value for UsdCollectionAPI::GetExpansionRuleAttr(), Default value for UsdCollectionAPI::GetExpansionRuleAttr()
    const TfToken expandPrims;
    /// \brief "expandPrimsAndProperties"
    ///
    /// Possible value for UsdCollectionAPI::GetExpansionRuleAttr()
    const TfToken expandPrimsAndProperties;
    /// \brief "expansionRule"
    ///
    /// UsdCollectionAPI
    const TfToken expansionRule;
    /// \brief "explicitOnly"
    ///
    /// Possible value for UsdCollectionAPI::GetExpansionRuleAttr()
    const TfToken explicitOnly;
    /// \brief "fallbackPrimTypes"
    ///
    ///  A dictionary metadata that maps the name of a concrete schema prim type to an ordered list of schema prim types to use instead if the schema prim type doesn't exist in version of USD being used.
    const TfToken fallbackPrimTypes;
    /// \brief "includeRoot"
    ///
    /// UsdCollectionAPI
    const TfToken includeRoot;
    /// \brief "includes"
    ///
    /// UsdCollectionAPI
    const TfToken includes;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdTokensType
extern USD_API TfStaticData<UsdTokensType> UsdTokens;

FORGE_NAMESPACE_END

#endif
