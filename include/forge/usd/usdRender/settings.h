#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRender/settings.h"
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
#ifndef USDRENDER_GENERATED_SETTINGS_H
#define USDRENDER_GENERATED_SETTINGS_H

/// \file usdRender/settings.h

#include "forge/forge.h"
#include "forge/usd/usdRender/api.h"
#include "forge/usd/usdRender/settingsBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRender/tokens.h"

#include "forge/base/gf/frustum.h"


#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// RENDERSETTINGS                                                             //
// -------------------------------------------------------------------------- //

/// \class UsdRenderSettings
///
/// A UsdRenderSettings prim specifies global settings for
/// a render process, including an enumeration of the RenderProducts
/// that should result, and the UsdGeomImageable purposes that should
/// be rendered.  \ref UsdRenderHowSettingsAffectRendering
///
class UsdRenderSettings : public UsdRenderSettingsBase
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

    /// Construct a UsdRenderSettings on UsdPrim \p prim .
    /// Equivalent to UsdRenderSettings::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRenderSettings(const UsdPrim& prim=UsdPrim())
        : UsdRenderSettingsBase(prim)
    {
    }

    /// Construct a UsdRenderSettings on the prim held by \p schemaObj .
    /// Should be preferred over UsdRenderSettings(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRenderSettings(const UsdSchemaBase& schemaObj)
        : UsdRenderSettingsBase(schemaObj)
    {
    }

    /// Destructor.
    USDRENDER_API
    virtual ~UsdRenderSettings();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRENDER_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRenderSettings holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRenderSettings(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRENDER_API
    static UsdRenderSettings
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
    USDRENDER_API
    static UsdRenderSettings
    Define(const UsdStagePtr &stage, const SdfPath &path);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDRENDER_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDRENDER_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDRENDER_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDRENDER_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // INCLUDEDPURPOSES
    // --------------------------------------------------------------------- //
    /// The list of UsdGeomImageable _purpose_ values that
    /// should be included in the render.  Note this cannot be
    /// specified per-RenderProduct because it is a statement of
    /// which geometry is present.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform token[] includedPurposes = ["default", "render"]` |
    /// | C++ Type | VtArray<TfToken> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->TokenArray |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    USDRENDER_API
    UsdAttribute GetIncludedPurposesAttr() const;

    /// See GetIncludedPurposesAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRENDER_API
    UsdAttribute CreateIncludedPurposesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // MATERIALBINDINGPURPOSES
    // --------------------------------------------------------------------- //
    /// Ordered list of material purposes to consider when
    /// resolving material bindings in the scene.  The empty string
    /// indicates the "allPurpose" binding.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform token[] materialBindingPurposes = ["full", ""]` |
    /// | C++ Type | VtArray<TfToken> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->TokenArray |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    /// | \ref UsdRenderTokens "Allowed Values" | full, preview, "" |
    USDRENDER_API
    UsdAttribute GetMaterialBindingPurposesAttr() const;

    /// See GetMaterialBindingPurposesAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRENDER_API
    UsdAttribute CreateMaterialBindingPurposesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // PRODUCTS
    // --------------------------------------------------------------------- //
    /// The set of RenderProducts the render should produce.
    /// This relationship should target UsdRenderProduct prims.
    /// If no _products_ are specified, an application should produce
    /// an rgb image according to the RenderSettings configuration,
    /// to a default display or image name.
    ///
    USDRENDER_API
    UsdRelationship GetProductsRel() const;

    /// See GetProductsRel(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
    USDRENDER_API
    UsdRelationship CreateProductsRel() const;

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

    /// Fetch and return \p stage 's render settings, as indicated by root
    /// layer metadata.  If unauthored, or the metadata does not refer to
    /// a valid UsdRenderSettings prim, this will return an invalid
    /// UsdRenderSettings prim.
    USDRENDER_API
    static UsdRenderSettings
    GetStageRenderSettings(const UsdStageWeakPtr &stage);
};

FORGE_NAMESPACE_END

#endif
