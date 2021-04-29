#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/valueTypeRegistry.h"
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
#ifndef FORGE_USD_SDF_VALUE_TYPE_REGISTRY_H
#define FORGE_USD_SDF_VALUE_TYPE_REGISTRY_H

#include "forge/forge.h"
#include "forge/usd/sdf/valueTypeName.h"
#include "forge/base/tf/enum.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/array.h"
#include "forge/base/vt/value.h"
#include <boost/noncopyable.hpp>
#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class TfType;

/// \class Sdf_ValueTypeRegistry
///
/// A registry of value type names used by a schema.
///
class Sdf_ValueTypeRegistry : boost::noncopyable {
public:
    Sdf_ValueTypeRegistry();
    ~Sdf_ValueTypeRegistry();

    /// Returns all registered value type names.
    std::vector<SdfValueTypeName> GetAllTypes() const;

    /// Returns a value type name by name.
    SdfValueTypeName FindType(const TfToken& name) const;
    SdfValueTypeName FindType(const char *name) const;
    SdfValueTypeName FindType(const std::string &name) const;

    /// Returns the value type name for the type and role if any, otherwise
    /// returns the invalid value type name.  This returns the first
    /// registered value type name for a given type/role pair if there are
    /// aliases
    SdfValueTypeName FindType(const TfType& type,
                              const TfToken& role = TfToken()) const;

    /// Returns the value type name for the held value and given role if
    /// any, otherwise returns the invalid value type.  This returns the
    /// first registered name for a given type/role pair if there are
    /// aliases.
    SdfValueTypeName FindType(const VtValue& value,
                              const TfToken& role = TfToken()) const;

    /// Returns a value type name by name.  If a type with that name is
    /// registered it returns the object for that name.  Otherwise a
    /// temporary type name is created and returned.  This name will match
    /// other temporary value type names that use the exact same name.  Use
    /// this function when you need to ensure that the name isn't lost even
    /// if the type isn't registered, typically when writing the name to a
    /// file or log.
    SdfValueTypeName FindOrCreateTypeName(const TfToken& name) const;

    /// \class Type
    /// Named parameter object for specifying an SdfValueTypeName to
    /// be added to the registry.
    class Type
    {
    public:
        // Specify a type with the given name, default value, and default
        // array value.
        Type(const TfToken& name,
             const VtValue& defaultValue,
             const VtValue& defaultArrayValue)
            : _name(name)
            , _defaultValue(defaultValue)
            , _defaultArrayValue(defaultArrayValue)
        { }

        // Specify a type with the given name, default value, and default
        // array value of VtArray<T>.
        template <class T>
        Type(char const *name, const T& defaultValue)
            : Type(TfToken(name), VtValue(defaultValue), VtValue(VtArray<T>()))
        { }

        // Specify a type with the given name and underlying C++ type.
        // No default value or array value will be registered.
        Type(const TfToken& name, const TfType& type)
            : _name(name)
            , _type(type)
        { }

        // Set C++ type name string for this type. Defaults to type name
        // from TfType.
        Type& CPPTypeName(const std::string& cppTypeName)
        {
            _cppTypeName = cppTypeName;
            if (!_defaultArrayValue.IsEmpty()) {
                _arrayCppTypeName = "VtArray<" + cppTypeName + ">";
            }
            return *this;
        }

        // Set shape for this type. Defaults to shapeless.
        Type& Dimensions(const SdfTupleDimensions& dims)
        { _dimensions = dims; return *this; }

        // Set default unit for this type. Defaults to dimensionless unit.
        Type& DefaultUnit(TfEnum unit) { _unit = unit; return *this; }

        // Set role for this type. Defaults to no role.
        Type& Role(const TfToken& role) { _role = role; return *this; }

        // Indicate that arrays of this type are not supported.
        Type& NoArrays()
        {
            _defaultArrayValue = VtValue();
            _arrayCppTypeName = std::string();
            return *this;
        }

    private:
        friend class Sdf_ValueTypeRegistry;

        TfToken _name;
        TfType _type;
        VtValue _defaultValue, _defaultArrayValue;
        std::string _cppTypeName, _arrayCppTypeName;
        TfEnum _unit;
        TfToken _role;
        SdfTupleDimensions _dimensions;
    };

    /// Register the value type specified by \p type.
    /// \see Type
    void AddType(const Type& type);

    /// Register a value type and it's corresponding array value type.
    void AddType(const TfToken& name,
                 const VtValue& defaultValue,
                 const VtValue& defaultArrayValue,
                 const std::string& cppName, const std::string& cppArrayName,
                 TfEnum defaultUnit, const TfToken& role,
                 const SdfTupleDimensions& dimensions);

    /// Register a value type and it's corresponding array value type.
    /// In this case the default values are empty.  This is useful for types
    /// provided by plugins;  you don't need to load the plugin just to
    /// register the type.  However, there is no default value.
    void AddType(const TfToken& name,
                 const TfType& type, const TfType& arrayType,
                 const std::string& cppName, const std::string& cppArrayName,
                 TfEnum defaultUnit, const TfToken& role,
                 const SdfTupleDimensions& dimensions);

    /// Empties out the registry.  Any existing types, roles or their names
    /// become invalid and must not be used.
    void Clear();

private:
    class _Impl;
    std::unique_ptr<_Impl> _impl;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_VALUE_TYPE_REGISTRY_H
