#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdVol/tokens.h"
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
#ifndef USDVOL_TOKENS_H
#define USDVOL_TOKENS_H

/// \file usdVol/tokens.h

// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//
// This is an automatically generated file (by usdGenSchema.py).
// Do not hand-edit!
//
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "forge/forge.h"
#include "forge/usd/usdVol/api.h"
#include "forge/base/tf/staticData.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdVolTokensType
///
/// \link UsdVolTokens \endlink provides static, efficient
/// \link TfToken TfTokens\endlink for use in all public USD API.
///
/// These tokens are auto-generated from the module's schema, representing
/// property names, for when you need to fetch an attribute or relationship
/// directly by name, e.g. UsdPrim::GetAttribute(), in the most efficient
/// manner, and allow the compiler to verify that you spelled the name
/// correctly.
///
/// UsdVolTokens also contains all of the \em allowedTokens values
/// declared for schema builtin attributes of 'token' scene description type.
/// Use UsdVolTokens like so:
///
/// \code
///     gprim.GetMyTokenValuedAttr().Set(UsdVolTokens->bool_);
/// \endcode
struct UsdVolTokensType {
    USDVOL_API UsdVolTokensType();
    /// \brief "bool"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken bool_;
    /// \brief "Color"
    ///
    /// Possible value for UsdVolFieldAsset::GetVectorDataRoleHintAttr()
    const TfToken color;
    /// \brief "double2"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken double2;
    /// \brief "double3"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken double3;
    /// \brief "double"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken double_;
    /// \brief "field"
    ///
    /// This is the namespace prefix used to  specify the fields that make up a volume primitive.
    const TfToken field;
    /// \brief "fieldClass"
    ///
    /// UsdVolOpenVDBAsset
    const TfToken fieldClass;
    /// \brief "fieldDataType"
    ///
    /// UsdVolOpenVDBAsset, UsdVolField3DAsset, UsdVolFieldAsset
    const TfToken fieldDataType;
    /// \brief "fieldIndex"
    ///
    /// UsdVolFieldAsset
    const TfToken fieldIndex;
    /// \brief "fieldName"
    ///
    /// UsdVolFieldAsset
    const TfToken fieldName;
    /// \brief "fieldPurpose"
    ///
    /// UsdVolField3DAsset
    const TfToken fieldPurpose;
    /// \brief "filePath"
    ///
    /// UsdVolFieldAsset
    const TfToken filePath;
    /// \brief "float2"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken float2;
    /// \brief "float3"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken float3;
    /// \brief "float"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken float_;
    /// \brief "fogVolume"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldClassAttr()
    const TfToken fogVolume;
    /// \brief "half"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken half;
    /// \brief "half2"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken half2;
    /// \brief "half3"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr(), Possible value for UsdVolField3DAsset::GetFieldDataTypeAttr()
    const TfToken half3;
    /// \brief "int2"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken int2;
    /// \brief "int3"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken int3;
    /// \brief "int64"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken int64;
    /// \brief "int"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken int_;
    /// \brief "levelSet"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldClassAttr()
    const TfToken levelSet;
    /// \brief "mask"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken mask;
    /// \brief "matrix3d"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken matrix3d;
    /// \brief "matrix4d"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken matrix4d;
    /// \brief "None"
    ///
    /// Possible value for UsdVolFieldAsset::GetVectorDataRoleHintAttr(), Default value for UsdVolFieldAsset::GetVectorDataRoleHintAttr()
    const TfToken none;
    /// \brief "Normal"
    ///
    /// Possible value for UsdVolFieldAsset::GetVectorDataRoleHintAttr()
    const TfToken normal;
    /// \brief "Point"
    ///
    /// Possible value for UsdVolFieldAsset::GetVectorDataRoleHintAttr()
    const TfToken point;
    /// \brief "quatd"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken quatd;
    /// \brief "staggered"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldClassAttr()
    const TfToken staggered;
    /// \brief "string"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken string;
    /// \brief "uint"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldDataTypeAttr()
    const TfToken uint;
    /// \brief "unknown"
    ///
    /// Possible value for UsdVolOpenVDBAsset::GetFieldClassAttr()
    const TfToken unknown;
    /// \brief "Vector"
    ///
    /// Possible value for UsdVolFieldAsset::GetVectorDataRoleHintAttr()
    const TfToken vector;
    /// \brief "vectorDataRoleHint"
    ///
    /// UsdVolFieldAsset
    const TfToken vectorDataRoleHint;
    /// A vector of all of the tokens listed above.
    const std::vector<TfToken> allTokens;
};

/// \var UsdVolTokens
///
/// A global variable with static, efficient \link TfToken TfTokens\endlink
/// for use in all public USD API.  \sa UsdVolTokensType
extern USDVOL_API TfStaticData<UsdVolTokensType> UsdVolTokens;

FORGE_NAMESPACE_END

#endif
