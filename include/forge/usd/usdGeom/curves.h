#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdGeom/curves.h"
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
#ifndef USDGEOM_GENERATED_CURVES_H
#define USDGEOM_GENERATED_CURVES_H

/// \file usdGeom/curves.h

#include "forge/forge.h"
#include "forge/usd/usdGeom/api.h"
#include "forge/usd/usdGeom/pointBased.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdGeom/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// CURVES                                                                     //
// -------------------------------------------------------------------------- //

/// \class UsdGeomCurves
///
/// Base class for UsdGeomBasisCurves, UsdGeomNurbsCurves, and
/// UsdGeomHermiteCurves.  The BasisCurves schema is designed to be
/// analagous to offline renderers' notion of batched curves (such as
/// the classical RIB definition via Basis and Curves statements),
/// while the NurbsCurve schema is designed to be analgous to the
/// NURBS curves found in packages like Maya and Houdini while
/// retaining their consistency with the RenderMan specification for
/// NURBS Patches. HermiteCurves are useful for the
/// interchange of animation guides and paths.
///
/// It is safe to use the length of the curve vertex count to derive
/// the number of curves and the number and layout of curve vertices,
/// but this schema should NOT be used to derive the number of curve
/// points. While vertex indices are implicit in all shipped
/// descendent types of this schema, one should not assume that all
/// internal or future shipped schemas will follow this pattern. Be
/// sure to key any indexing behavior off the concrete type, not this
/// abstract type.
///
///
class UsdGeomCurves : public UsdGeomPointBased
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractTyped;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::AbstractTyped;

    /// Construct a UsdGeomCurves on UsdPrim \p prim .
    /// Equivalent to UsdGeomCurves::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdGeomCurves(const UsdPrim& prim=UsdPrim())
        : UsdGeomPointBased(prim)
    {
    }

    /// Construct a UsdGeomCurves on the prim held by \p schemaObj .
    /// Should be preferred over UsdGeomCurves(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdGeomCurves(const UsdSchemaBase& schemaObj)
        : UsdGeomPointBased(schemaObj)
    {
    }

    /// Destructor.
    USDGEOM_API
    virtual ~UsdGeomCurves();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDGEOM_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdGeomCurves holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdGeomCurves(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDGEOM_API
    static UsdGeomCurves
    Get(const UsdStagePtr &stage, const SdfPath &path);


protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDGEOM_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDGEOM_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDGEOM_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDGEOM_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // CURVEVERTEXCOUNTS
    // --------------------------------------------------------------------- //
    /// Curves-derived primitives can represent multiple distinct,
    /// potentially disconnected curves.  The length of 'curveVertexCounts'
    /// gives the number of such curves, and each element describes the
    /// number of vertices in the corresponding curve
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int[] curveVertexCounts` |
    /// | C++ Type | VtArray<int> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->IntArray |
    USDGEOM_API
    UsdAttribute GetCurveVertexCountsAttr() const;

    /// See GetCurveVertexCountsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateCurveVertexCountsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // WIDTHS
    // --------------------------------------------------------------------- //
    /// Provides width specification for the curves, whose application
    /// will depend on whether the curve is oriented (normals are defined for
    /// it), in which case widths are "ribbon width", or unoriented, in which
    /// case widths are cylinder width.  'widths' is not a generic Primvar,
    /// but the number of elements in this attribute will be determined by
    /// its 'interpolation'.  See \ref SetWidthsInterpolation() .  If 'widths'
    /// and 'primvars:widths' are both specified, the latter has precedence.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float[] widths` |
    /// | C++ Type | VtArray<float> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->FloatArray |
    USDGEOM_API
    UsdAttribute GetWidthsAttr() const;

    /// See GetWidthsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateWidthsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by
    // the code generator.
    //
    // Just remember to:
    //  - Close the class declaration with };
    //  - Close the namespace with FORGE_NAMESPACE_END
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--

    /// Get the \ref Usd_InterpolationVals "interpolation" for the \em widths
    /// attribute.
    ///
    /// Although 'widths' is not classified as a generic UsdGeomPrimvar (and
    /// will not be included in the results of UsdGeomImageable::GetPrimvars() )
    /// it does require an interpolation specification.  The fallback
    /// interpolation, if left unspecified, is UsdGeomTokens->vertex ,
    /// which means a width value is specified at the end of each curve segment.
    USDGEOM_API
    TfToken GetWidthsInterpolation() const;

    /// Set the \ref Usd_InterpolationVals "interpolation" for the \em widths
    /// attribute.
    ///
    /// \return true upon success, false if \p interpolation is not a legal
    /// value as defined by UsdPrimvar::IsValidInterpolation(), or if there
    /// was a problem setting the value.  No attempt is made to validate
    /// that the widths attr's value contains the right number of elements
    /// to match its interpolation to its prim's topology.
    ///
    /// \sa GetWidthsInterpolation()
    USDGEOM_API
    bool SetWidthsInterpolation(TfToken const &interpolation);

    /// Compute the extent for the curves defined by points and widths.
    ///
    /// \return true upon success, false if unable to calculate extent.
    ///
    /// On success, extent will contain an approximate axis-aligned bounding
    /// box of the curve defined by points with the given widths.
    ///
    /// This function is to provide easy authoring of extent for usd authoring
    /// tools, hence it is static and acts outside a specific prim (as in
    /// attribute based methods).
    USDGEOM_API
    static bool ComputeExtent(const VtVec3fArray& points,
        const VtFloatArray& widths, VtVec3fArray* extent);

    /// \overload
    /// Computes the extent as if the matrix \p transform was first applied.
    USDGEOM_API
    static bool ComputeExtent(const VtVec3fArray& points,
        const VtFloatArray& widths, const GfMatrix4d& transform,
        VtVec3fArray* extent);

    /// Returns the number of curves as defined by the size of the
    /// _curveVertexCounts_ array at _timeCode_.
    ///
    /// \snippetdoc snippets.dox GetCount
    /// \sa GetCurveVertexCountsAttr()
    USDGEOM_API
    size_t GetCurveCount(UsdTimeCode timeCode = UsdTimeCode::Default()) const;
};

FORGE_NAMESPACE_END

#endif
