#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/shadowAPI.h"
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
#ifndef USDLUX_GENERATED_SHADOWAPI_H
#define USDLUX_GENERATED_SHADOWAPI_H

/// \file usdLux/shadowAPI.h

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdLux/tokens.h"

#include "forge/usd/usdShade/input.h"
#include "forge/usd/usdShade/output.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// SHADOWAPI                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdLuxShadowAPI
///
/// Controls to refine a light's shadow behavior.  These are
/// non-physical controls that are valuable for visual lighting work.
///
class UsdLuxShadowAPI : public UsdAPISchemaBase
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

    /// Construct a UsdLuxShadowAPI on UsdPrim \p prim .
    /// Equivalent to UsdLuxShadowAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdLuxShadowAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdLuxShadowAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdLuxShadowAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdLuxShadowAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDLUX_API
    virtual ~UsdLuxShadowAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDLUX_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdLuxShadowAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdLuxShadowAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDLUX_API
    static UsdLuxShadowAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "ShadowAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdLuxShadowAPI object is returned upon success.
    /// An invalid (or empty) UsdLuxShadowAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDLUX_API
    static UsdLuxShadowAPI
    Apply(const UsdPrim &prim);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDLUX_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDLUX_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDLUX_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDLUX_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // SHADOW:ENABLE
    // --------------------------------------------------------------------- //
    /// Enables shadows to be cast by this light.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool inputs:shadow:enable = 1` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDLUX_API
    UsdAttribute GetShadowEnableAttr() const;

    /// See GetShadowEnableAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateShadowEnableAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHADOW:COLOR
    // --------------------------------------------------------------------- //
    /// The color of shadows cast by the light.  This is a
    /// non-physical control.  The default is to cast black shadows.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `color3f inputs:shadow:color = (0, 0, 0)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Color3f |
    USDLUX_API
    UsdAttribute GetShadowColorAttr() const;

    /// See GetShadowColorAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateShadowColorAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHADOW:DISTANCE
    // --------------------------------------------------------------------- //
    /// The maximum distance shadows are cast.
    /// The default value (-1) indicates no limit.
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float inputs:shadow:distance = -1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDLUX_API
    UsdAttribute GetShadowDistanceAttr() const;

    /// See GetShadowDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateShadowDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHADOW:FALLOFF
    // --------------------------------------------------------------------- //
    /// The near distance at which shadow falloff begins.
    /// The default value (-1) indicates no falloff.
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float inputs:shadow:falloff = -1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDLUX_API
    UsdAttribute GetShadowFalloffAttr() const;

    /// See GetShadowFalloffAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateShadowFalloffAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHADOW:FALLOFFGAMMA
    // --------------------------------------------------------------------- //
    /// A gamma (i.e., exponential) control over shadow strength
    /// with linear distance within the falloff zone.
    /// This requires the use of shadowDistance and shadowFalloff.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float inputs:shadow:falloffGamma = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDLUX_API
    UsdAttribute GetShadowFalloffGammaAttr() const;

    /// See GetShadowFalloffGammaAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateShadowFalloffGammaAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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

    // -------------------------------------------------------------------------
    /// \name Conversion to and from UsdShadeConnectableAPI
    ///
    /// @{

    /// Constructor that takes a ConnectableAPI object.
    /// Allow implicit conversion of UsdShadeConnectableAPI to
    /// UsdLuxShadowAPI.
    USDLUX_API
    UsdLuxShadowAPI(const UsdShadeConnectableAPI &connectable);

    /// Contructs and returns a UsdShadeConnectableAPI object with this shadow
    /// API prim. Note that a valid UsdLuxShadowAPI will only return a valid
    /// UsdShadeConnectableAPI if the its prim's Typed schema type is actually
    /// connectable.
    USDLUX_API
    UsdShadeConnectableAPI ConnectableAPI() const;

    /// @}

    // -------------------------------------------------------------------------
    /// \name Outputs API
    ///
    /// Outputs represent a typed attribute on a shadow API whose value is
    /// computed externally.
    ///
    /// @{

    /// Create an output which can either have a value or can be connected.
    /// The attribute representing the output is created in the "outputs:"
    /// namespace. Outputs on a shadow API cannot be connected, as their
    /// value is assumed to be computed externally.
    ///
    USDLUX_API
    UsdShadeOutput CreateOutput(const TfToken& name,
                                const SdfValueTypeName& typeName);

    /// Return the requested output if it exists.
    ///
    USDLUX_API
    UsdShadeOutput GetOutput(const TfToken &name) const;

    /// Outputs are represented by attributes in the "outputs:" namespace.
    /// If \p onlyAuthored is true (the default), then only return authored
    /// attributes; otherwise, this also returns un-authored builtins.
    ///
    USDLUX_API
    std::vector<UsdShadeOutput> GetOutputs(bool onlyAuthored=true) const;

    /// @}

    // -------------------------------------------------------------------------

    /// \name Inputs API
    ///
    /// Inputs are connectable attribute with a typed value.
    ///
    /// Shadow API parameters are encoded as inputs.
    ///
    /// @{

    /// Create an input which can either have a value or can be connected.
    /// The attribute representing the input is created in the "inputs:"
    /// namespace. Inputs on shadow API are connectable.
    ///
    USDLUX_API
    UsdShadeInput CreateInput(const TfToken& name,
                              const SdfValueTypeName& typeName);

    /// Return the requested input if it exists.
    ///
    USDLUX_API
    UsdShadeInput GetInput(const TfToken &name) const;

    /// Inputs are represented by attributes in the "inputs:" namespace.
    /// If \p onlyAuthored is true (the default), then only return authored
    /// attributes; otherwise, this also returns un-authored builtins.
    ///
    USDLUX_API
    std::vector<UsdShadeInput> GetInputs(bool onlyAuthored=true) const;

    /// @}
};

FORGE_NAMESPACE_END

#endif
