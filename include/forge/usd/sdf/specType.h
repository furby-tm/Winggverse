#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/specType.h"
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
#ifndef FORGE_USD_SDF_SPEC_TYPE_H
#define FORGE_USD_SDF_SPEC_TYPE_H

/// \file sdf/specType.h

#include "forge/forge.h"
#include "forge/usd/sdf/types.h"

#include <typeinfo>
#include <vector>

FORGE_NAMESPACE_BEGIN

class SdfSpec;
class TfType;

/// \class SdfSpecTypeRegistration
///
/// Provides functions to register spec types with the runtime typing system
/// used to cast between C++ spec types. Implementations of C++ spec types
/// should use as follows:
///
/// For a concrete spec type that corresponds to a specific SdfSpecType:
/// TF_REGISTRY_FUNCTION(SdfSpecTypeRegistration) {
///    SdfSpecTypeRegistration::RegisterSpecType<MyPrimSpec>();
/// }
///
/// For an abstract spec type that has no corresponding SdfSpecType:
/// TF_REGISTRY_FUNCTION(SdfSpecTypeRegistration) {
///    SdfSpecTypeRegistration::RegisterAbstractSpecType<MyPropertySpec>();
/// }
///
class SdfSpecTypeRegistration
{
public:
    /// Registers the C++ type T as a concrete spec class.
    template <class SchemaType, class SpecType>
    static void RegisterSpecType(SdfSpecType specTypeEnum)
    {
        _RegisterSpecType(typeid(SpecType), specTypeEnum, typeid(SchemaType));
    }

    /// Registers the C++ type T as an abstract spec class.
    template <class SchemaType, class SpecType>
    static void RegisterAbstractSpecType()
    {
        _RegisterAbstractSpecType(typeid(SpecType), typeid(SchemaType));
    }

private:
    static void _RegisterSpecType(
        const std::type_info& specCPPType, SdfSpecType specEnumType,
        const std::type_info& schemaType);
    static void _RegisterAbstractSpecType(
        const std::type_info& specCPPType,
        const std::type_info& schemaType);
};

// This class holds type information for specs.  It associates a
// spec type with the corresponding TfType.
class Sdf_SpecType {
public:
    // If \p spec can be represented by the C++ spec class \p to, returns
    // the TfType for \p to. This includes verifying that \p spec's schema
    // matches the schema associated with \p to.
    static TfType Cast(const SdfSpec& spec, const std::type_info& to);

    // Returns whether the \p spec can be represented by the C++ spec
    // class \p to. This includes verifying that \p spec's schema matches
    // the schema associated with \p to.
    static bool CanCast(const SdfSpec& spec, const std::type_info& to);

    // Returns whether a spec with spec type \p from can be represented by
    // the C++ spec class \p to, regardless of schema.
    static bool CanCast(SdfSpecType from, const std::type_info& to);
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_SPEC_TYPE_H
