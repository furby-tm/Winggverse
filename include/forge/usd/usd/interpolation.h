#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/interpolation.h"
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
#ifndef FORGE_USD_USD_INTERPOLATION_H
#define FORGE_USD_USD_INTERPOLATION_H

/// \file usd/interpolation.h

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/sdf/timeCode.h"
#include "forge/base/vt/array.h"
#include "forge/base/gf/declare.h"

#include <boost/preprocessor/seq/for_each.hpp>

FORGE_NAMESPACE_BEGIN


/// \enum UsdInterpolationType
///
/// Attribute value interpolation options.
///
/// See \ref Usd_AttributeInterpolation for more details.
///
enum UsdInterpolationType
{
    UsdInterpolationTypeHeld,  ///< Held interpolation
    UsdInterpolationTypeLinear ///< Linear interpolation
};

/// \anchor USD_LINEAR_INTERPOLATION_TYPES
/// Sequence of value types that support linear interpolation.
/// These types and VtArrays of these types are supported:
/// \li <b>GfHalf</b>
/// \li <b>float</b>
/// \li <b>double</b>
/// \li <b>SdfTimeCode</b>
/// \li <b>GfMatrix2d</b>
/// \li <b>GfMatrix3d</b>
/// \li <b>GfMatrix4d</b>
/// \li <b>GfVec2d</b>
/// \li <b>GfVec2f</b>
/// \li <b>GfVec2h</b>
/// \li <b>GfVec3d</b>
/// \li <b>GfVec3f</b>
/// \li <b>GfVec3h</b>
/// \li <b>GfVec4d</b>
/// \li <b>GfVec4f</b>
/// \li <b>GfVec4h</b>
/// \li <b>GfQuatd</b> (via quaternion slerp)
/// \li <b>GfQuatf</b> (via quaternion slerp)
/// \li <b>GfQuath</b> (via quaternion slerp)
/// \hideinitializer
#define USD_LINEAR_INTERPOLATION_TYPES               \
    (GfHalf) (VtArray<GfHalf>)                       \
    (float) (VtArray<float>)                         \
    (double) (VtArray<double>)                       \
    (SdfTimeCode) (VtArray<SdfTimeCode>)             \
    (GfMatrix2d) (VtArray<GfMatrix2d>)               \
    (GfMatrix3d) (VtArray<GfMatrix3d>)               \
    (GfMatrix4d) (VtArray<GfMatrix4d>)               \
    (GfVec2d) (VtArray<GfVec2d>)                     \
    (GfVec2f) (VtArray<GfVec2f>)                     \
    (GfVec2h) (VtArray<GfVec2h>)                     \
    (GfVec3d) (VtArray<GfVec3d>)                     \
    (GfVec3f) (VtArray<GfVec3f>)                     \
    (GfVec3h) (VtArray<GfVec3h>)                     \
    (GfVec4d) (VtArray<GfVec4d>)                     \
    (GfVec4f) (VtArray<GfVec4f>)                     \
    (GfVec4h) (VtArray<GfVec4h>)                     \
    (GfQuatd) (VtArray<GfQuatd>)                     \
    (GfQuatf) (VtArray<GfQuatf>)                     \
    (GfQuath) (VtArray<GfQuath>)

/// \struct UsdLinearInterpolationTraits
///
/// Traits class describing whether a particular C++ value type
/// supports linear interpolation.
///
/// UsdLinearInterpolationTraits<T>::isSupported will be true for all
/// types listed in the USD_LINEAR_INTERPOLATION_TYPES sequence.
template <class T>
struct UsdLinearInterpolationTraits
{
    static const bool isSupported = false;
};

/// \cond INTERNAL
#define _USD_DECLARE_INTERPOLATION_TRAITS(r, unused, type)       \
template <>                                                     \
struct UsdLinearInterpolationTraits<type>                       \
{                                                               \
    static const bool isSupported = true;                       \
};

BOOST_PP_SEQ_FOR_EACH(_USD_DECLARE_INTERPOLATION_TRAITS, ~,
                      USD_LINEAR_INTERPOLATION_TYPES)

#undef _USD_DECLARE_INTERPOLATION_TRAITS
/// \endcond


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_INTERPOLATION_H
