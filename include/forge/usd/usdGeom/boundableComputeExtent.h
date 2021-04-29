#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdGeom/boundableComputeExtent.h"
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
#ifndef FORGE_USD_USD_GEOM_BOUNDABLE_COMPUTE_EXTENT_H
#define FORGE_USD_USD_GEOM_BOUNDABLE_COMPUTE_EXTENT_H

/// \file usdGeom/boundableComputeExtent.h

#include "forge/forge.h"
#include "forge/usd/usdGeom/api.h"

#include "forge/base/gf/vec3f.h"
#include "forge/base/vt/array.h"

#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class UsdGeomBoundable;
class UsdTimeCode;

/// Function registered with #UsdGeomRegisterComputeExtentFunction for
/// computing extents for a Boundable prim at the given time and filling
/// the given VtVec3fArray with the result.  If an optional transform matrix is
/// supplied, the extent is computed as if the object was first transformed by
/// the matrix. If the transform matrix is nullptr, the extent is computed as if
/// the identity matrix was passed.
///
/// The Boundable is guaranteed to be convertible to the prim type this
/// function was registered with.  The function must be thread-safe.
/// It should return true on success, false on failure.
using UsdGeomComputeExtentFunction = bool(*)(const UsdGeomBoundable&,
                                             const UsdTimeCode&,
                                             const GfMatrix4d*,
                                             VtVec3fArray*);

/// Registers \p fn as the function to use for computing extents for Boundable
/// prims of type \p PrimType by UsdGeomBoundable::ComputeExtentFromPlugins.
/// \p PrimType must derive from UsdGeomBoundable.
///
/// Plugins should generally call this function in a TF_REGISTRY_FUNCTION.
/// For example:
///
/// \code
/// TF_REGISTRY_FUNCTION(UsdGeomBoundable)
/// {
///     UsdGeomRegisterComputeExtentFunction<MyPrim>(MyComputeExtentFunction);
/// }
/// \endcode
///
/// Plugins must also note that this function is implemented for a prim type
/// in that type's schema definition.  For example:
///
/// \code
/// class "MyPrim" (
///     ...
///     customData = {
///         dictionary extraPlugInfo = {
///             bool implementsComputeExtent = true
///         }
///     }
///     ...
/// )
/// { ... }
/// \endcode
///
/// This allows the plugin system to discover this function dynamically
/// and load the plugin if needed.
template <class PrimType>
inline void
UsdGeomRegisterComputeExtentFunction(
    const UsdGeomComputeExtentFunction& fn)
{
    static_assert(
        std::is_base_of<UsdGeomBoundable, PrimType>::value,
        "Prim type must derive from UsdGeomBoundable");

    UsdGeomRegisterComputeExtentFunction(TfType::Find<PrimType>(), fn);
}

/// \overload
USDGEOM_API
void
UsdGeomRegisterComputeExtentFunction(
    const TfType& boundableType,
    const UsdGeomComputeExtentFunction& fn);

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_GEOM_BOUNDABLE_COMPUTE_EXTENT_H
