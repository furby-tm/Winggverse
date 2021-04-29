#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUI/tokens.h"
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
#ifndef USDUI_TOKENS_H
#define USDUI_TOKENS_H

/// \file usdUI/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdUI/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdUITokensType
///
/// \link UsdUITokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdUITokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdUITokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdUITokens->closed);
/// \endcode
struct UsdUITokensType {
    USDUI_API UsdUITokensType();
    /// \brief "closed"
    ///
    /// Possible value for UsdUINodeGraphNodeAPI::GetExpansionStateAttr()
    const TfToken closed;
    /// \brief "minimized"
    ///
    /// Possible value for UsdUINodeGraphNodeAPI::GetExpansionStateAttr()
    const TfToken minimized;
    /// \brief "open"
    ///
    /// Possible value for UsdUINodeGraphNodeAPI::GetExpansionStateAttr()
    const TfToken open;
    /// \brief "ui:title"
    ///
    /// UsdUIWindow
    const TfToken uiTitle;
    /// \brief "ui:description"
    ///
    /// UsdUIBackdrop
    const TfToken uiDescription;
    /// \brief "ui:displayGroup"
    ///
    /// UsdUISceneGraphPrimAPI
    const TfToken uiDisplayGroup;
    /// \brief "ui:displayName"
    ///
    /// UsdUISceneGraphPrimAPI
    const TfToken uiDisplayName;
    /// \brief "ui:nodegraph:node:displayColor"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodeDisplayColor;
    /// \brief "ui:nodegraph:node:expansionState"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodeExpansionState;
    /// \brief "ui:nodegraph:node:icon"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodeIcon;
    /// \brief "ui:nodegraph:node:pos"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodePos;
    /// \brief "ui:nodegraph:node:size"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodeSize;
    /// \brief "ui:nodegraph:node:stackingOrder"
    ///
    /// UsdUINodeGraphNodeAPI
    const TfToken uiNodegraphNodeStackingOrder;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdUITokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdUITokensType
extern USDUI_API TfStaticData<UsdUITokensType> UsdUITokens;

FORGE_NAMESPACE_END

#endif
