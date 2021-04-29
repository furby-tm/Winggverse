#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/pyConversions.h"
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
#ifndef FORGE_USD_USD_PY_CONVERSIONS_H
#define FORGE_USD_USD_PY_CONVERSIONS_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/base/tf/pyObjWrapper.h"

FORGE_NAMESPACE_BEGIN

class VtValue;
class TfToken;
class SdfValueTypeName;

// XXX: DEPRECATED.  This function does nothing except convert \p value to
// python.  Do not call, it will be removed.
USD_API
TfPyObjWrapper UsdVtValueToPython(const VtValue &value);

/// Helper for converting a python value to the target Usd/Sdf type, if
/// possible.  Invokes VtValue::CastToTypeOf() to do the conversion, if
/// required.  This internally handles python buffers (e.g. numpy) -> VtArray
/// and some python tuple/list -> VtArray conversions.  If conversion fails,
/// returns a VtValue extracted from the pyVal, which may produce a VtValue
/// holding a python object.
USD_API
VtValue UsdPythonToSdfType(TfPyObjWrapper pyVal,
                           SdfValueTypeName const &targetType);

/// Helper for converting a python value to a metadata value for metadata
/// known to the SdfSchema.  Generates a coding error if \p key is unknown
/// to the SdfSchema.
///
/// For dictionary-valued metadata, \p keyPath may be specified as the path
/// in the dictionary we are targeting, so that if the dictionary was registered
/// with a fallback for that dictionary subcomponent, we will convert
/// appropriately to its type.
///
/// \return \c true on successful conversion, which can happen even if
/// the converted \p result is an empty VtValue
USD_API
bool UsdPythonToMetadataValue(const TfToken &key, const TfToken &keyPath,
                              TfPyObjWrapper pyVal, VtValue *result);


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_PY_CONVERSIONS_H
