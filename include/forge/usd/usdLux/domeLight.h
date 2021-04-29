#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/domeLight.h"
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
#ifndef USDLUX_GENERATED_DOMELIGHT_H
#define USDLUX_GENERATED_DOMELIGHT_H

/// \file usdLux/domeLight.h

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"
#include "forge/usd/usdLux/light.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdLux/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// DOMELIGHT                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdLuxDomeLight
///
/// Light emitted inward from a distant external environment,
/// such as a sky or IBL light probe.  The orientation of a dome light with a
/// latlong texture is expected to match the OpenEXR specification for latlong
/// environment maps.  From the OpenEXR documentation:
///
/// -------------------------------------------------------------------------
/// Latitude-Longitude Map:
///
/// The environment is projected onto the image using polar coordinates
/// (latitude and longitude).  A pixel's x coordinate corresponds to
/// its longitude, and the y coordinate corresponds to its latitude.
/// Pixel (dataWindow.min.x, dataWindow.min.y) has latitude +pi/2 and
/// longitude +pi; pixel (dataWindow.max.x, dataWindow.max.y) has
/// latitude -pi/2 and longitude -pi.
///
/// In 3D space, latitudes -pi/2 and +pi/2 correspond to the negative and
/// positive y direction.  Latitude 0, longitude 0 points into positive
/// z direction; and latitude 0, longitude pi/2 points into positive x
/// direction.
///
/// The size of the data window should be 2*N by N pixels (width by height),
/// where N can be any integer greater than 0.
/// -------------------------------------------------------------------------
///
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdLuxTokens.
/// So to set an attribute to the value "rightHanded", use UsdLuxTokens->rightHanded
/// as the value.
///
class UsdLuxDomeLight : public UsdLuxLight
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

    /// Construct a UsdLuxDomeLight on UsdPrim \p prim .
    /// Equivalent to UsdLuxDomeLight::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdLuxDomeLight(const UsdPrim& prim=UsdPrim())
        : UsdLuxLight(prim)
    {
    }

    /// Construct a UsdLuxDomeLight on the prim held by \p schemaObj .
    /// Should be preferred over UsdLuxDomeLight(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdLuxDomeLight(const UsdSchemaBase& schemaObj)
        : UsdLuxLight(schemaObj)
    {
    }

    /// Destructor.
    USDLUX_API
    virtual ~UsdLuxDomeLight();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDLUX_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdLuxDomeLight holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdLuxDomeLight(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDLUX_API
    static UsdLuxDomeLight
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
    USDLUX_API
    static UsdLuxDomeLight
    Define(const UsdStagePtr &stage, const SdfPath &path);

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
    // TEXTUREFILE
    // --------------------------------------------------------------------- //
    /// A color texture to use on the dome, such as an HDR (high
    /// dynamic range) texture intended for IBL (image based lighting).
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `asset inputs:texture:file` |
    /// | C++ Type | SdfAssetPath |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Asset |
    USDLUX_API
    UsdAttribute GetTextureFileAttr() const;

    /// See GetTextureFileAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateTextureFileAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREFORMAT
    // --------------------------------------------------------------------- //
    /// Specifies the parameterization of the color map file.
    /// Valid values are:
    /// - automatic: Tries to determine the layout from the file itself.
    /// For example, Renderman texture files embed an explicit
    /// parameterization.
    /// - latlong: Latitude as X, longitude as Y.
    /// - mirroredBall: An image of the environment reflected in a
    /// sphere, using an implicitly orthogonal projection.
    /// - angular: Similar to mirroredBall but the radial dimension
    /// is mapped linearly to the angle, providing better sampling
    /// at the edges.
    /// - cubeMapVerticalCross: A cube map with faces laid out as a
    /// vertical cross.
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token inputs:texture:format = "automatic"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdLuxTokens "Allowed Values" | automatic, latlong, mirroredBall, angular, cubeMapVerticalCross |
    USDLUX_API
    UsdAttribute GetTextureFormatAttr() const;

    /// See GetTextureFormatAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDLUX_API
    UsdAttribute CreateTextureFormatAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // PORTALS
    // --------------------------------------------------------------------- //
    /// Optional portals to guide light sampling.
    ///
    USDLUX_API
    UsdRelationship GetPortalsRel() const;

    /// See GetPortalsRel(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    USDLUX_API
    UsdRelationship CreatePortalsRel() const;

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

    /// Adds a transformation op, if neeeded, to orient the dome to align with
    /// the stage's up axis.  Uses UsdLuxTokens->orientToStageUpAxis as the op
    /// suffix.  If an op with this suffix already exists, this method assumes
    /// it is already applying the proper correction and does nothing further.
    /// If no op is required to match the stage's up axis, no op will be
    /// created.
    ///
    /// \see UsdGeomXformOp
    /// \see UsdGeomGetStageUpAxis
    USDLUX_API
    void OrientToStageUpAxis() const;
};

FORGE_NAMESPACE_END

#endif
