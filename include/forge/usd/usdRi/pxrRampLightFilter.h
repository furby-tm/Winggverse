#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRi/pxrRampLightFilter.h"
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
#ifndef USDRI_GENERATED_PXRRAMPLIGHTFILTER_H
#define USDRI_GENERATED_PXRRAMPLIGHTFILTER_H

/// \file usdRi/pxrRampLightFilter.h

#include "forge/forge.h"
#include "forge/usd/usdRi/api.h"
#include "forge/usd/usdLux/lightFilter.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRi/tokens.h"

#include "forge/usd/usdRi/splineAPI.h"


#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// PXRRAMPLIGHTFILTER                                                         //
// -------------------------------------------------------------------------- //

/// \class UsdRiPxrRampLightFilter
///
///
/// \deprecated This schema will be replaced in a future release.
/// A ramp to modulate how a light falls off with distance.
///
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdRiTokens.
/// So to set an attribute to the value "rightHanded", use UsdRiTokens->rightHanded
/// as the value.
///
class UsdRiPxrRampLightFilter : public UsdLuxLightFilter
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::ConcreteTyped;

    /// Construct a UsdRiPxrRampLightFilter on UsdPrim \p prim .
    /// Equivalent to UsdRiPxrRampLightFilter::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRiPxrRampLightFilter(const UsdPrim& prim=UsdPrim())
        : UsdLuxLightFilter(prim)
    {
    }

    /// Construct a UsdRiPxrRampLightFilter on the prim held by \p schemaObj .
    /// Should be preferred over UsdRiPxrRampLightFilter(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRiPxrRampLightFilter(const UsdSchemaBase& schemaObj)
        : UsdLuxLightFilter(schemaObj)
    {
    }

    /// Destructor.
    USDRI_API
    virtual ~UsdRiPxrRampLightFilter();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRI_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRiPxrRampLightFilter holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRiPxrRampLightFilter(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRI_API
    static UsdRiPxrRampLightFilter
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Attempt to ensure a \a UsdPrim adhering to this schema at \p path
    /// is defined (according to UsdPrim::IsDefined()) on this stage.
    ///
    /// If a prim adhering to this schema at \p path is already defined on this
    /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
    /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
    /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
    /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
    /// current EditTarget for any nonexistent, or existing but not \a Defined
    /// ancestors.
    ///
    /// The given \a path must be an absolute prim path that does not contain
    /// any variant selections.
    ///
    /// If it is impossible to author any of the necessary PrimSpecs, (for
    /// example, in case \a path cannot map to the current UsdEditTarget's
    /// namespace) issue an error and return an invalid \a UsdPrim.
    ///
    /// Note that this method may return a defined prim whose typeName does not
    /// specify this schema class, in case a stronger typeName opinion overrides
    /// the opinion at the current EditTarget.
    ///
    USDRI_API
    static UsdRiPxrRampLightFilter
    Define(const UsdStagePtr &stage, const SdfPath &path);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDRI_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDRI_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDRI_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDRI_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // RAMPMODE
    // --------------------------------------------------------------------- //
    /// Specifies the direction in which the ramp is applied
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token rampMode = "distanceToLight"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdRiTokens "Allowed Values" | distanceToLight, linear, spherical, radial |
    USDRI_API
    UsdAttribute GetRampModeAttr() const;

    /// See GetRampModeAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRampModeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // BEGINDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance where the ramp starts.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float beginDistance = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetBeginDistanceAttr() const;

    /// See GetBeginDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateBeginDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ENDDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance where the ramp ends.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float endDistance = 10` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetEndDistanceAttr() const;

    /// See GetEndDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateEndDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FALLOFF
    // --------------------------------------------------------------------- //
    /// Controls the transition from the core to the edge.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int falloff = 4` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    USDRI_API
    UsdAttribute GetFalloffAttr() const;

    /// See GetFalloffAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateFalloffAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FALLOFFKNOTS
    // --------------------------------------------------------------------- //
    /// Knots of the falloff spline.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float[] falloff:knots = [0, 0, 1, 1]` |
    /// | C++ Type | VtArray<float> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->FloatArray |
    USDRI_API
    UsdAttribute GetFalloffKnotsAttr() const;

    /// See GetFalloffKnotsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateFalloffKnotsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FALLOFFFLOATS
    // --------------------------------------------------------------------- //
    /// Float values of the falloff spline.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float[] falloff:floats = [0, 0, 1, 1]` |
    /// | C++ Type | VtArray<float> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->FloatArray |
    USDRI_API
    UsdAttribute GetFalloffFloatsAttr() const;

    /// See GetFalloffFloatsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateFalloffFloatsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FALLOFFINTERPOLATION
    // --------------------------------------------------------------------- //
    /// Falloff spline type.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token falloff:interpolation = "linear"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdRiTokens "Allowed Values" | linear, catmull-rom, bspline, constant |
    USDRI_API
    UsdAttribute GetFalloffInterpolationAttr() const;

    /// See GetFalloffInterpolationAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateFalloffInterpolationAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORRAMP
    // --------------------------------------------------------------------- //
    /// Controls the color gradient for the transition.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int colorRamp = 4` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    USDRI_API
    UsdAttribute GetColorRampAttr() const;

    /// See GetColorRampAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorRampAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORRAMPKNOTS
    // --------------------------------------------------------------------- //
    /// Knots of the colorRamp spline.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float[] colorRamp:knots = [0, 0, 1, 1]` |
    /// | C++ Type | VtArray<float> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->FloatArray |
    USDRI_API
    UsdAttribute GetColorRampKnotsAttr() const;

    /// See GetColorRampKnotsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorRampKnotsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORRAMPCOLORS
    // --------------------------------------------------------------------- //
    /// Color values of the colorRamp spline.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `color3f[] colorRamp:colors = [(1, 1, 1), (1, 1, 1), (1, 1, 1), (1, 1, 1)]` |
    /// | C++ Type | VtArray<GfVec3f> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Color3fArray |
    USDRI_API
    UsdAttribute GetColorRampColorsAttr() const;

    /// See GetColorRampColorsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorRampColorsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORRAMPINTERPOLATION
    // --------------------------------------------------------------------- //
    /// ColorRamp spline type.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token colorRamp:interpolation = "linear"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdRiTokens "Allowed Values" | linear, catmull-rom, bspline, constant |
    USDRI_API
    UsdAttribute GetColorRampInterpolationAttr() const;

    /// See GetColorRampInterpolationAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorRampInterpolationAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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

    /// Return the UsdRiSplineAPI interface used for examining and modifying
    /// the falloff ramp.
    USDRI_API
    UsdRiSplineAPI GetFalloffRampAPI() const;

    /// Return the UsdRiSplineAPI interface used for examining and modifying
    /// the color ramp.
    USDRI_API
    UsdRiSplineAPI GetColorRampAPI() const;
};

FORGE_NAMESPACE_END

#endif
