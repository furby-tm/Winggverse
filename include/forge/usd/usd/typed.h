#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/typed.h"
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
#ifndef FORGE_USD_USD_TYPED_H
#define FORGE_USD_USD_TYPED_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/schemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN


/// \class UsdTyped
///
/// The base class for all \em typed schemas (those that can impart a
/// typeName to a UsdPrim), and therefore the base class for all
/// instantiable and "IsA" schemas.
///
/// UsdTyped implements a typeName-based query for its override of
/// UsdSchemaBase::_IsCompatible().  It provides no other behavior.
///
class UsdTyped : public UsdSchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractBase;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::AbstractBase;

    /// Construct a UsdTyped on UsdPrim \p prim .
    /// Equivalent to UsdTyped::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdTyped(const UsdPrim& prim=UsdPrim())
        : UsdSchemaBase(prim)
    {
    }

    /// Construct a UsdTyped on the prim wrapped by \p schemaObj .
    /// Should be preferred over UsdTyped(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdTyped(const UsdSchemaBase& schemaObj)
        : UsdSchemaBase(schemaObj)
    {
    }

    USD_API
    virtual ~UsdTyped();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true) {
        /* This only exists for consistency */
        static TfTokenVector names;
        return names;
    }

    /// Return a UsdTyped holding the prim adhering to this schema at \p path
    /// on \p stage.  If no prim exists at \p path on \p stage, or if the prim
    /// at that path does not adhere to this schema, return an invalid schema
    /// object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdTyped(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USD_API
    static UsdTyped
    Get(const UsdStagePtr &stage, const SdfPath &path);

protected:
    USD_API
    bool _IsCompatible() const override;

private:
    USD_API
    const TfType &_GetTfType() const override;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_TYPED_H
