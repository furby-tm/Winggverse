#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdShade/types.h"
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
#ifndef FORGE_USD_USD_SHADE_TYPES_H
#define FORGE_USD_USD_SHADE_TYPES_H

#include "forge/forge.h"
#include "forge/usd/usdShade/api.h"
#include "forge/usd/usd/attribute.h"

#include "forge/base/tf/smallVector.h"

FORGE_NAMESPACE_BEGIN

/// \enum UsdShadeAttributeType
///
/// Specifies the type of a shading attribute.
///
enum class UsdShadeAttributeType {
    Invalid,
    Input,
    Output,
};

/// \enum UsdShadeConnectionModification
///
/// Choice when creating a single connection with the \p ConnectToSource method
/// for a shading attribute. The new connection can replace any existing
/// connections or be added to the list of existing connections. In which case
/// there is a choice between prepending and appending to said list, which will
/// be represented by Usd's list editing operations.
///
enum class UsdShadeConnectionModification {
    Replace,
    Prepend,
    Append
};

/// \typedef UsdShadeAttributeVector
///
/// For performance reasons we want to be extra careful when reporting
/// attributes. It is possible to have multiple connections for a shading
/// attribute, but by far the more common cases are one or no connection. So we
/// use a small vector that can be stack allocated that holds space for a single
/// attributes, but that can "spill" to the heap in the case of multiple
/// upstream attributes.
using UsdShadeAttributeVector = TfSmallVector<UsdAttribute, 1>;

/// \typedef UsdShadeSourceInfoVector
///
/// For performance reasons we want to be extra careful when reporting
/// connections. It is possible to have multiple connections for a shading
/// attribute, but by far the more common cases are one or no connection.
/// So we use a small vector that can be stack allocated that holds space
/// for a single source, but that can "spill" to the heap in the case
/// of a multi-connection.
///
/// /sa UsdShadeConnectionSourceInfo in connectableAPI.h
struct UsdShadeConnectionSourceInfo;
using UsdShadeSourceInfoVector = TfSmallVector<UsdShadeConnectionSourceInfo, 1>;

FORGE_NAMESPACE_END

#endif
