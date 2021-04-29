#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRender/settingsAPI.h"
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
#ifndef USDRENDER_GENERATED_SETTINGSAPI_H
#define USDRENDER_GENERATED_SETTINGSAPI_H

/// \file usdRender/settingsAPI.h

#include "forge/forge.h"
#include "forge/usd/usdRender/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// RENDERSETTINGSAPI                                                          //
// -------------------------------------------------------------------------- //

/// \class UsdRenderSettingsAPI
///
/// UsdRenderSettingsAPI is a base class for API schemas
/// to encode renderer-specific settings.
///
class UsdRenderSettingsAPI : public UsdAPISchemaBase
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

    /// Construct a UsdRenderSettingsAPI on UsdPrim \p prim .
    /// Equivalent to UsdRenderSettingsAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRenderSettingsAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdRenderSettingsAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdRenderSettingsAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRenderSettingsAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDRENDER_API
    virtual ~UsdRenderSettingsAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRENDER_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRenderSettingsAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRenderSettingsAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRENDER_API
    static UsdRenderSettingsAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "RenderSettingsAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdRenderSettingsAPI object is returned upon success.
    /// An invalid (or empty) UsdRenderSettingsAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDRENDER_API
    static UsdRenderSettingsAPI
    Apply(const UsdPrim &prim);

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
