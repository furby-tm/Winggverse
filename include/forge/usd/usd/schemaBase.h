#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/schemaBase.h"
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
#ifndef FORGE_USD_USD_SCHEMA_BASE_H
#define FORGE_USD_USD_SCHEMA_BASE_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/attribute.h"
#include "forge/usd/usd/relationship.h"
#include "forge/usd/usd/references.h"

FORGE_NAMESPACE_BEGIN


/// \class UsdSchemaBase
///
/// The base class for all schema types in Usd.
///
/// Schema objects hold a ::UsdPrim internally and provide a layer of specific
/// named API atop the underlying scene graph.
///
/// Schema objects are polymorphic but they are intended to be created as
/// automatic local variables, so they may be passed and returned by-value.
/// This leaves them subject to <a
/// href="http://en.wikipedia.org/wiki/Object_slicing">slicing</a>.  This means
/// that if one passes a <tt>SpecificSchema</tt> instance to a function that
/// takes a UsdSchemaBase \e by-value, all the polymorphic behavior specific to
/// <tt>SpecificSchema</tt> is lost.
///
/// To avoid slicing, it is encouraged that functions taking schema object
/// arguments take them by <tt>const &</tt> if const access is sufficient,
/// otherwise by non-const pointer.
///
class UsdSchemaBase {
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind in usd/common.h
    static const UsdSchemaKind schemaKind = UsdSchemaType::AbstractBase;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::AbstractBase;

    /// Returns whether or not this class corresponds to a concrete instantiable
    /// prim type in scene description.  If this is true,
    /// GetStaticPrimDefinition() will return a valid prim definition with
    /// a non-empty typeName.
    bool IsConcrete() const {
        return GetSchemaKind() == UsdSchemaKind::ConcreteTyped;
    }

    /// Returns whether or not this class inherits from UsdTyped. Types which
    /// inherit from UsdTyped can impart a typename on a UsdPrim.
    bool IsTyped() const {
        return GetSchemaKind() == UsdSchemaKind::ConcreteTyped
            || GetSchemaKind() == UsdSchemaKind::AbstractTyped;
    }

    /// Returns whether this is an API schema or not.
    bool IsAPISchema() const {
        return GetSchemaKind() == UsdSchemaKind::NonAppliedAPI
            || GetSchemaKind() == UsdSchemaKind::SingleApplyAPI
            || GetSchemaKind() == UsdSchemaKind::MultipleApplyAPI;
    }

    /// Returns whether this is an applied API schema or not. If this returns
    /// true this class will have an Apply() method
    bool IsAppliedAPISchema() const {
        return GetSchemaKind() == UsdSchemaKind::SingleApplyAPI
            || GetSchemaKind() == UsdSchemaKind::MultipleApplyAPI;
    }

    /// Returns whether this is an applied API schema or not. If this returns
    /// true the constructor, Get and Apply methods of this class will take
    /// in the name of the API schema instance.
    bool IsMultipleApplyAPISchema() const {
        return GetSchemaKind() == UsdSchemaKind::MultipleApplyAPI;
    }

    /// Returns the kind of schema this class is.
    UsdSchemaKind GetSchemaKind() const {
        // To retain backward compatibility with schemas that have not been
        // updated yet we return the value from _GetSchemaType. Once we're
        // ready to retire schemaType completely, this will be updated to
        // return _GetSchemaKind instead.
        return _GetSchemaType();
    }

    /// \deprecated
    /// Use GetSchemaKind instead.
    UsdSchemaKind GetSchemaType() const {
        return _GetSchemaType();
    }

    /// Construct and store \p prim as the held prim.
    USD_API
    explicit UsdSchemaBase(const UsdPrim& prim = UsdPrim());

    /// Construct and store for the same prim held by \p otherSchema
    USD_API
    explicit UsdSchemaBase(const UsdSchemaBase& otherSchema);

    /// Destructor.
    USD_API
    virtual ~UsdSchemaBase();

    /// \name Held prim access.
    //@{

    /// Return this schema object's held prim.
    UsdPrim GetPrim() const { return UsdPrim(_primData, _proxyPrimPath); }

    /// Shorthand for GetPrim()->GetPath().
    SdfPath GetPath() const {
        if (!_proxyPrimPath.IsEmpty()) {
            return _proxyPrimPath;
        }
        else if (Usd_PrimDataConstPtr p = get_pointer(_primData)) {
            return p->GetPath();
        }
        return SdfPath::EmptyPath();
    }

    //@}

    /// \name PrimDefinition access.
    //@{

    /// Return the prim definition associated with this schema instance if one
    /// exists, otherwise return null.  This does not use the held prim's type.
    /// To get the held prim instance's definition, use
    /// UsdPrim::GetPrimDefinition().  \sa UsdPrim::GetPrimDefinition()
    USD_API
    const UsdPrimDefinition *GetSchemaClassPrimDefinition() const;

    //@}

    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true)
    {
        /* This only exists for consistency */
        static TfTokenVector names;
        return names;
    }

    /// Return true if this schema object is compatible with its held prim,
    /// false otherwise.  For untyped schemas return true if the held prim is
    /// not expired, otherwise return false.  For typed schemas return true if
    /// the held prim is not expired and its type is the schema's type or a
    /// subtype of the schema's type.  Otherwise return false.  This method
    /// invokes polymorphic behavior.
    ///
    /// \sa UsdSchemaBase::_IsCompatible()
    USD_API
    explicit operator bool() const {
        return _primData && _IsCompatible();
    }

protected:
    /// Returns the kind of schema this class is.
    ///
    /// \sa UsdSchemaBase::schemaKind
    virtual UsdSchemaKind _GetSchemaKind() const {
        return schemaKind;
    }

    /// \deprecated
    /// This has been replace with _GetSchemaKind but is around for now for
    /// backwards compatibility while schemas are being updated.
    virtual UsdSchemaKind _GetSchemaType() const {
        return schemaType;
    }

    // Helper for subclasses to get the TfType for this schema object's dynamic
    // C++ type.
    const TfType &_GetType() const {
        return _GetTfType();
    }

    USD_API
    UsdAttribute _CreateAttr(TfToken const &attrName,
                             SdfValueTypeName const & typeName,
                             bool custom, SdfVariability variability,
                             VtValue const &defaultValue,
                             bool writeSparsely) const;

    /// Subclasses may override _IsCompatible to do specific compatibility
    /// checking with the given prim, such as type compatibility or value
    /// compatibility.  This check is performed when clients invoke the
    /// explicit bool operator.
    USD_API
    virtual bool _IsCompatible() const;

private:
    // Subclasses should not override _GetTfType.  It is implemented by the
    // schema class code generator.
    USD_API
    virtual const TfType &_GetTfType() const;

    // The held prim and proxy prim path.
    Usd_PrimDataHandle _primData;
    SdfPath _proxyPrimPath;
};


FORGE_NAMESPACE_END

#endif //FORGE_USD_USD_SCHEMA_BASE_H
