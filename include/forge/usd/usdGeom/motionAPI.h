#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdGeom/motionAPI.h"
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
#ifndef USDGEOM_GENERATED_MOTIONAPI_H
#define USDGEOM_GENERATED_MOTIONAPI_H

/// \file usdGeom/motionAPI.h

#include "forge/forge.h"
#include "forge/usd/usdGeom/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
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
// MOTIONAPI                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdGeomMotionAPI
///
/// UsdGeomMotionAPI encodes data that can live on any prim that
/// may affect computations involving:
/// - computed motion for motion blur
/// - sampling for motion blur
///
/// For example, UsdGeomMotionAPI provides *velocityScale*
/// (GetVelocityScaleAttr()) for controlling how motion-blur samples should
/// be computed by velocity-consuming schemas.
///
class UsdGeomMotionAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::SingleApplyAPI;

    /// Construct a UsdGeomMotionAPI on UsdPrim \p prim .
    /// Equivalent to UsdGeomMotionAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdGeomMotionAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdGeomMotionAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdGeomMotionAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdGeomMotionAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDGEOM_API
    virtual ~UsdGeomMotionAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDGEOM_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdGeomMotionAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdGeomMotionAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDGEOM_API
    static UsdGeomMotionAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "MotionAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdGeomMotionAPI object is returned upon success.
    /// An invalid (or empty) UsdGeomMotionAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDGEOM_API
    static UsdGeomMotionAPI
    Apply(const UsdPrim &prim);

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
    // VELOCITYSCALE
    // --------------------------------------------------------------------- //
    /// VelocityScale is an **inherited** float attribute that
    /// velocity-based schemas (e.g. PointBased, PointInstancer) can consume
    /// to compute interpolated positions and orientations by applying
    /// velocity and angularVelocity, which is required for interpolating
    /// between samples when topology is varying over time.  Although these
    /// quantities are generally physically computed by a simulator, sometimes
    /// we require more or less motion-blur to achieve the desired look.
    /// VelocityScale allows artists to dial-in, as a post-sim correction,
    /// a scale factor to be applied to the velocity prior to computing
    /// interpolated positions from it.
    ///
    /// See also ComputeVelocityScale()
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float motion:velocityScale = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetVelocityScaleAttr() const;

    /// See GetVelocityScaleAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateVelocityScaleAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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

    /// Compute the inherited value of *velocityScale* at \p time, i.e. the
    /// authored value on the prim closest to this prim in namespace, resolved
    /// upwards through its ancestors in namespace.
    ///
    /// \return the inherited value, or 1.0 if neither the prim nor any
    /// of its ancestors possesses an authored value.
    ///
    /// \note this is a reference implementation that is not particularly
    /// efficient if evaluating over many prims, because it does not share
    /// inherited results.
    USDGEOM_API
    float ComputeVelocityScale(UsdTimeCode time = UsdTimeCode::Default()) const;

};

FORGE_NAMESPACE_END

#endif
