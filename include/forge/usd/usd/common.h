#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/common.h"
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
#ifndef FORGE_USD_USD_COMMON_H
#define FORGE_USD_USD_COMMON_H

/// \file usd/common.h

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/stringUtils.h"
#include "forge/usd/sdf/layerOffset.h"

#include "forge/usd/usd/primDataHandle.h"
#include "forge/usd/usd/timeCode.h"

#include <string>
#include <map>

FORGE_NAMESPACE_BEGIN

// Forward declare Usd classes.
class UsdStage;
class UsdObject;
class UsdPrim;
class UsdProperty;
class UsdAttribute;
class UsdRelationship;
class UsdStageCache;

class VtValue;

TF_DECLARE_WEAK_AND_REF_PTRS(UsdStage);
typedef UsdStagePtr UsdStageWeakPtr;

/// Return a human-readable description.
USD_API
std::string UsdDescribe(const UsdObject &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageRefPtr &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageWeakPtr &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStage *);
/// \overload
USD_API
std::string UsdDescribe(const UsdStage &);
/// \overload
USD_API
std::string UsdDescribe(const UsdStageCache &);

// XXX:
// Currently used for querying composed values from ascii layers, so VtValue is
// the optimal value-store, but this may not always be the case.
typedef std::map<class TfToken, VtValue,
                 TfDictionaryLessThan
                 > UsdMetadataValueMap;

/// \enum UsdListPosition
///
/// Specifies a position to add items to lists.  Used by some Add()
/// methods in the USD API that manipulate lists, such as AddReference().
///
enum UsdListPosition {
    /// The position at the front of the prepend list.
    /// An item added at this position will, after composition is applied,
    /// be stronger than other items prepended in this layer, and stronger
    /// than items added by weaker layers.
    UsdListPositionFrontOfPrependList,
    /// The position at the back of the prepend list.
    /// An item added at this position will, after composition is applied,
    /// be weaker than other items prepended in this layer, but stronger
    /// than items added by weaker layers.
    UsdListPositionBackOfPrependList,
    /// The position at the front of the append list.
    /// An item added at this position will, after composition is applied,
    /// be stronger than other items appended in this layer, and stronger
    /// than items added by weaker layers.
    UsdListPositionFrontOfAppendList,
    /// The position at the back of the append list.
    /// An item added at this position will, after composition is applied,
    /// be weaker than other items appended in this layer, but stronger
    /// than items added by weaker layers.
    UsdListPositionBackOfAppendList,
};

/// \enum UsdLoadPolicy
///
/// Controls UsdStage::Load() and UsdPrim::Load() behavior regarding whether or
/// not descendant prims are loaded.
///
enum UsdLoadPolicy {
    /// Load a prim plus all its descendants.
    UsdLoadWithDescendants,
    /// Load a prim by itself with no descendants.
    UsdLoadWithoutDescendants
};

/// \enum UsdSchemaKind
///
/// An enum representing which kind of schema a given schema class belongs to
///
enum class UsdSchemaKind {
    /// Invalid or unknown schema kind.
    Invalid,
    /// Represents abstract or base schema types that are interface-only
    /// and cannot be instantiated. These are reserved for core base classes
    /// known to the usdGenSchema system, so this should never be assigned to
    /// generated schema classes.
    AbstractBase,
    /// Represents a non-concrete typed schema
    AbstractTyped,
    /// Represents a concrete typed schema
    ConcreteTyped,
    /// Non-applied API schema
    NonAppliedAPI,
    /// Single Apply API schema
    SingleApplyAPI,
    /// Multiple Apply API Schema
    MultipleApplyAPI
};

/// \deprecated Backwards compatible type name mapping.
using UsdSchemaType = UsdSchemaKind;

FORGE_NAMESPACE_END

#endif
