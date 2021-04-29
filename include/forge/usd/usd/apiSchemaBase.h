#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/apiSchemaBase.h"
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
#ifndef USD_GENERATED_APISCHEMABASE_H
#define USD_GENERATED_APISCHEMABASE_H

/// \file usd/apiSchemaBase.h

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/schemaBase.h"
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
// APISCHEMABASE                                                              //
// -------------------------------------------------------------------------- //

/// \class UsdAPISchemaBase
///
/// The base class for all \em API schemas.
///
/// An API schema provides an interface to a prim's qualities, but does not
/// specify a typeName for the underlying prim. The prim's qualities include
/// its inheritance structure, attributes, relationships etc. Since it cannot
/// provide a typeName, an API schema is considered to be non-concrete.
///
/// To auto-generate an API schema using usdGenSchema, simply leave the
/// typeName empty and make it inherit from "/APISchemaBase" or from another
/// API schema. See UsdModelAPI, UsdClipsAPI and UsdCollectionAPI for examples.
///
/// API schemas are classified into applied and non-applied API schemas.
/// The author of an API schema has to decide on the type of API schema
/// at the time of its creation by setting customData['apiSchemaType'] in the
/// schema definition (i.e. in  the associated primSpec inside the schema.usda
/// file).  UsdAPISchemaBase implements methods that are used to record the
/// application of an API schema on a USD prim.
///
/// If an API schema only provides an interface to set certain core bits of
/// metadata (like UsdModelAPI, which sets model kind and UsdClipsAPI, which
/// sets clips-related metadata) OR if the API schema can apply to any type of
/// prim or only to a known fixed set of prim types OR if there is no use of
/// recording the application of the API schema, in such cases, it would be
/// better to make it a non-applied API schema. Examples of non-applied API
/// schemas include UsdModelAPI, UsdClipsAPI, UsdShadeConnectableAPI and
/// UsdGeomPrimvarsAPI.
///
/// If there is a need to discover (or record) whether a prim contains or
/// subscribes to a given API schema, it would be advantageous to make the API
/// schema be "applied". In general, API schemas that add one or more properties
/// to a prim should be tagged as applied API schemas. A public Apply() method
/// is generated for applied API schemas by usdGenSchema. An applied API schema
/// must be applied to a prim via a call to the generated Apply() method, for
/// the schema object to evaluate to true when converted to a bool using the
/// explicit bool conversion operator. Examples of applied API schemas include
/// UsdCollectionAPI, UsdGeomModelAPI and UsdGeomMotionAPI
///
/// \anchor UsdAPISchemaBase_SingleVsMultipleApply
/// \name Single vs. Multiple Apply API Schemas
///
/// Applied API schemas can further be classified into single-apply and
/// multiple-apply API schemas. As the name suggests, a single-apply API schema
/// can only be applied once to a prim. A multiple-apply API schema can be
/// applied multiple times with different 'instanceName' values. An example of
/// a multiple-apply API schema is UsdCollectionAPI, where the API schema is
/// applied to a prim once for every collection owned by the prim.
///
/// \note An applied API schema can only inherit from another applied API
/// schema or directly from APISchemaBase. Similarly, a non-applied API schema
/// can only inherit from a non-applied API Schema or directly from
/// APISchemaBase. 'usdGenSchema' attempts to issue a warning if it detects
/// an incompability.
///
/// \note A multiple-apply API schema may not inherit from a single-apply API
/// schema and vice versa.
///
/// \note When the bool-conversion operator is invoked on an applied API
/// schema, it evaluates to true only if the application of the API schema has
/// been recorded on the prim via a call to the auto-generated Apply() method.
///
///
///
class UsdAPISchemaBase : public UsdSchemaBase
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

    /// Construct a UsdAPISchemaBase on UsdPrim \p prim .
    /// Equivalent to UsdAPISchemaBase::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdAPISchemaBase(const UsdPrim& prim=UsdPrim())
        : UsdSchemaBase(prim)
    {
    }

    /// Construct a UsdAPISchemaBase on the prim held by \p schemaObj .
    /// Should be preferred over UsdAPISchemaBase(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdAPISchemaBase(const UsdSchemaBase& schemaObj)
        : UsdSchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USD_API
    virtual ~UsdAPISchemaBase() = 0;

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USD_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);


protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USD_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USD_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USD_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USD_API
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

protected:
    /// Construct a multiple-apply UsdAPISchemaBase on UsdPrim \p prim with
    /// the specified \p instanceName.
    explicit UsdAPISchemaBase(const UsdPrim& prim,
                              const TfToken &instanceName)
        : UsdSchemaBase(prim)
        , _instanceName(instanceName)
    {
    }

    /// Construct a multiple-apply UsdAPISchemaBase on the prim held by
    /// \p schemaObj with the given \p instanceName.
    explicit UsdAPISchemaBase(const UsdSchemaBase& schemaObj,
                              const TfToken &instanceName)
        : UsdSchemaBase(schemaObj)
        , _instanceName(instanceName)
    {
    }

    /// Returns the instance name of the API schema object belonging to a
    /// multiple-apply API schema.
    ///
    /// The returned instance name will be empty for non-applied and
    /// single-apply API schemas.
    const TfToken &_GetInstanceName() const {
        return _instanceName;
    }

protected:
    /// Helper method to apply a <b>single-apply</b> API schema with the given
    /// schema name \p apiSchemaName' and C++ type 'APISchemaType'. The schema
    /// is applied on the given \p prim in the current edit target.
    ///
    /// This information is stored by adding \p apiSchemaName value to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// A valid schema object of type \em APISchemaType is returned upon
    /// success.
    ///
    /// A coding error is issued and an invalid schema object is returned if
    /// <li>if \p prim is invalid or is an instance proxy prim or is contained
    /// within an instance prototype OR</li>
    /// <li>\p apiSchemaName cannot be added to the apiSchemas listOp
    /// metadata.</li></ul>
    ///
    /// A run-time error is issued and an invalid schema object is returned
    /// if the given prim is valid, but cannot be reached or overridden in the
    /// current edit target.
    ///
    template <typename APISchemaType>
    static APISchemaType _ApplyAPISchema(
        const UsdPrim &prim,
        const TfToken &apiSchemaName)
    {
        if (prim.ApplyAPI<APISchemaType>()) {
            return APISchemaType(prim);
        }
        return APISchemaType();
    }

    /// Helper method to apply a </b>multiple-apply</b> API schema with the
    /// given schema name \p apiSchemaName', C++ type 'APISchemaType' and
    /// instance name \p instanceName. The schema is applied on the given
    /// \p prim in the current edit target.
    ///
    /// This information is stored in the token-valued, listOp metadata
    /// \em apiSchemas on the prim. For example, if \p apiSchemaName is
    /// 'CollectionAPI' and \p instanceName is 'plasticStuff', the name
    /// 'CollectionAPI:plasticStuff' is added to 'apiSchemas' listOp metadata.
    ///
    /// A valid schema object of type \em APISchemaType is returned upon
    /// success.
    ///
    /// A coding error is issued and an invalid schema object is returned if
    /// <li>the \p prim is invalid or is an instance proxy prim or is contained
    /// within an instance prototype OR</li>
    /// <li>\p instanceName is empty OR</li>
    /// <li><i>apiSchemaName:instanceName</i> cannot be added to the apiSchemas
    /// listOp metadata.</li></ul>
    ///
    /// A run-time error is issued and an invalid schema object is returned
    /// if the given prim is valid, but cannot be reached or overridden in the
    /// current edit target.
    ///
    template <typename APISchemaType>
    static APISchemaType _MultipleApplyAPISchema(
        const UsdPrim &prim,
        const TfToken &apiSchemaName,
        const TfToken &instanceName)
    {
        if (prim.ApplyAPI<APISchemaType>(instanceName)) {
            return APISchemaType(prim, instanceName);
        }
        return APISchemaType();
    }

    /// Check whether this APISchema object is valid for the currently held
    /// prim.
    ///
    /// If this is an applied API schema, this returns true if the held prim
    /// is valid and already has the API schema applied to it, along with the
    /// instanceName (in the case of multiple-apply). The instanceName should
    /// not be empty in the case of a multiple-apply API schema.
    ///
    /// This check is performed when clients invoke the explicit bool conversion
    /// operator, implemented in UsdSchemaBase.
    ///
    /// \sa UsdPrim::HasAPI()
    USD_API
    bool _IsCompatible() const override;

private:
    // The instance name associated with this schema object, if it is a
    // multiple-apply API schema. For example, in the case of UsdCollectionAPI,
    // this will hold the name of the collection.
    TfToken _instanceName;
};

FORGE_NAMESPACE_END

#endif
