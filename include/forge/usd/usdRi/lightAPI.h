#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRi/lightAPI.h"
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
#ifndef USDRI_GENERATED_LIGHTAPI_H
#define USDRI_GENERATED_LIGHTAPI_H

/// \file usdRi/lightAPI.h

#include "forge/forge.h"
#include "forge/usd/usdRi/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRi/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// RILIGHTAPI                                                                 //
// -------------------------------------------------------------------------- //

/// \class UsdRiLightAPI
///
///
/// \deprecated RenderMan-specific light settings will move to a
/// new schema in a future release.
///
/// RiLightAPI is an API schema that provides an interface
/// to add Renderman-specific attributes to lights.
///
class UsdRiLightAPI : public UsdAPISchemaBase
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

    /// Construct a UsdRiLightAPI on UsdPrim \p prim .
    /// Equivalent to UsdRiLightAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRiLightAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdRiLightAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdRiLightAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRiLightAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDRI_API
    virtual ~UsdRiLightAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRI_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRiLightAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRiLightAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRI_API
    static UsdRiLightAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "RiLightAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdRiLightAPI object is returned upon success.
    /// An invalid (or empty) UsdRiLightAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDRI_API
    static UsdRiLightAPI
    Apply(const UsdPrim &prim);

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
    // RISAMPLINGFIXEDSAMPLECOUNT
    // --------------------------------------------------------------------- //
    /// Specifies an override of the number of light samples to be
    /// taken for this light source. If set to something other than zero,
    /// it will override the sampling performed by the integrator and can
    /// result in a performance impact. For scenes that have lots of lights,
    /// resulting in some lights that are under-sampled, you may want to set
    /// it to non-zero.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int ri:sampling:fixedSampleCount` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    USDRI_API
    UsdAttribute GetRiSamplingFixedSampleCountAttr() const;

    /// See GetRiSamplingFixedSampleCountAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiSamplingFixedSampleCountAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RISAMPLINGIMPORTANCEMULTIPLIER
    // --------------------------------------------------------------------- //
    /// Importance of this light for noise control.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float ri:sampling:importanceMultiplier = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetRiSamplingImportanceMultiplierAttr() const;

    /// See GetRiSamplingImportanceMultiplierAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiSamplingImportanceMultiplierAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RIINTENSITYNEARDIST
    // --------------------------------------------------------------------- //
    /// Near distance between the point being illuminated and the
    /// light at which the sample doesn't get brighter. This may help you
    /// avoid hot spots and sampling issues where a light is near a
    /// surface.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float ri:intensityNearDist` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetRiIntensityNearDistAttr() const;

    /// See GetRiIntensityNearDistAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiIntensityNearDistAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RILIGHTGROUP
    // --------------------------------------------------------------------- //
    /// Specify the light group name used for light group LPEs.
    /// This is useful to generate per-light AOVs for later adjustment
    /// in compositing.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `string ri:lightGroup` |
    /// | C++ Type | std::string |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->String |
    USDRI_API
    UsdAttribute GetRiLightGroupAttr() const;

    /// See GetRiLightGroupAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiLightGroupAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RISHADOWTHINSHADOW
    // --------------------------------------------------------------------- //
    /// Enable thin shadow and disable refraction caustics for this
    /// light. This parameter will ignored if Trace Light Paths is
    /// enabled. This is a non-physical control that creates "fake"
    /// colored shadows for transmissive objects without needing to
    /// generate photons for caustics.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool ri:shadow:thinShadow` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetRiShadowThinShadowAttr() const;

    /// See GetRiShadowThinShadowAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiShadowThinShadowAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // RITRACELIGHTPATHS
    // --------------------------------------------------------------------- //
    /// Enable light and photon tracing from this light. This
    /// value enforces a physically-based light and as a side-effect
    /// disables the above Shadows controls. Users may use this feature
    /// to selectively decide which lights emit photons when using the
    /// PxrVCM or PxrUPBP Integrators.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool ri:trace:lightPaths` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetRiTraceLightPathsAttr() const;

    /// See GetRiTraceLightPathsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateRiTraceLightPathsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
};

FORGE_NAMESPACE_END

#endif
