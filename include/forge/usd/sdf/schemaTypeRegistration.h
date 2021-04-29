#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/schemaTypeRegistration.h"
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
#ifndef FORGE_USD_SDF_SCHEMA_TYPE_REGISTRATION_H
#define FORGE_USD_SDF_SCHEMA_TYPE_REGISTRATION_H

#include "forge/forge.h"
#include "forge/usd/sdf/layerOffset.h"
#include "forge/usd/sdf/listOp.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/schema.h"
#include "forge/usd/sdf/types.h"
#include "forge/base/vt/dictionary.h"
#include "forge/base/vt/value.h"

#include "forge/base/tf/enum.h"
#include "forge/base/tf/token.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

// Defines the built-in scene description fields supplied by Sdf as
// well as their C++ value types. SdfSchema supplies additional information
// about these fields, such as their default value and validation functions.
//
// XXX: bug 123508
// StartFrame and EndFrame should be migrated to Sd.
//
#define _SDF_FIELDS                                                      \
((SdfFieldKeys->Active,                  bool))                          \
((SdfFieldKeys->AllowedTokens,           VtTokenArray))                  \
((SdfFieldKeys->AssetInfo,               VtDictionary))                  \
((SdfFieldKeys->ColorConfiguration,      SdfAssetPath))                  \
((SdfFieldKeys->ColorManagementSystem,   TfToken))                       \
((SdfFieldKeys->ColorSpace,              TfToken))                       \
((SdfFieldKeys->Comment,                 std::string))                   \
((SdfFieldKeys->ConnectionPaths,         SdfPathListOp))                 \
((SdfFieldKeys->Custom,                  bool))                          \
((SdfFieldKeys->CustomData,              VtDictionary))                  \
((SdfFieldKeys->CustomLayerData,         VtDictionary))                  \
((SdfFieldKeys->Default,                 VtValue))                       \
((SdfFieldKeys->DefaultPrim,             TfToken))                       \
((SdfFieldKeys->DisplayGroup,            std::string))                   \
((SdfFieldKeys->DisplayGroupOrder,       VtStringArray))                 \
((SdfFieldKeys->DisplayName,             std::string))                   \
((SdfFieldKeys->DisplayUnit,             TfEnum))                        \
((SdfFieldKeys->Documentation,           std::string))                   \
((SdfFieldKeys->EndFrame,                double))                        \
((SdfFieldKeys->EndTimeCode,             double))                        \
((SdfFieldKeys->FramePrecision,          int))                           \
((SdfFieldKeys->FramesPerSecond,         double))                        \
((SdfFieldKeys->Hidden,                  bool))                          \
((SdfFieldKeys->HasOwnedSubLayers,       bool))                          \
((SdfFieldKeys->InheritPaths,            SdfPathListOp))                 \
((SdfFieldKeys->Instanceable,            bool))                          \
((SdfFieldKeys->Kind,                    TfToken))                       \
((SdfFieldKeys->Owner,                   std::string))                   \
((SdfFieldKeys->PrimOrder,               std::vector<TfToken>))          \
((SdfFieldKeys->NoLoadHint,              bool))                          \
((SdfFieldKeys->Payload,                 SdfPayloadListOp))              \
((SdfFieldKeys->Permission,              SdfPermission))                 \
((SdfFieldKeys->Prefix,                  std::string))                   \
((SdfFieldKeys->PrefixSubstitutions,     VtDictionary))                  \
((SdfFieldKeys->PropertyOrder,           std::vector<TfToken>))          \
((SdfFieldKeys->References,              SdfReferenceListOp))            \
((SdfFieldKeys->SessionOwner,            std::string))                   \
((SdfFieldKeys->TargetPaths,             SdfPathListOp))                 \
((SdfFieldKeys->TimeSamples,             SdfTimeSampleMap))              \
((SdfFieldKeys->Relocates,               SdfRelocatesMap))               \
((SdfFieldKeys->Specializes,             SdfPathListOp))                 \
((SdfFieldKeys->Specifier,               SdfSpecifier))                  \
((SdfFieldKeys->StartFrame,              double))                        \
((SdfFieldKeys->StartTimeCode,           double))                        \
((SdfFieldKeys->SubLayers,               std::vector<std::string>))      \
((SdfFieldKeys->SubLayerOffsets,         std::vector<SdfLayerOffset>))   \
((SdfFieldKeys->Suffix,                  std::string))                   \
((SdfFieldKeys->SuffixSubstitutions,     VtDictionary))                  \
((SdfFieldKeys->SymmetricPeer,           std::string))                   \
((SdfFieldKeys->SymmetryArgs,            VtDictionary))                  \
((SdfFieldKeys->SymmetryArguments,       VtDictionary))                  \
((SdfFieldKeys->SymmetryFunction,        TfToken))                       \
((SdfFieldKeys->TimeCodesPerSecond,      double))                        \
((SdfFieldKeys->TypeName,                TfToken))                       \
((SdfFieldKeys->VariantSetNames,         SdfStringListOp))               \
((SdfFieldKeys->VariantSelection,        SdfVariantSelectionMap))        \
((SdfFieldKeys->Variability,             SdfVariability))                \
((SdfChildrenKeys->ConnectionChildren,         std::vector<SdfPath>))    \
((SdfChildrenKeys->ExpressionChildren,         std::vector<TfToken>))    \
((SdfChildrenKeys->MapperArgChildren,          std::vector<TfToken>))    \
((SdfChildrenKeys->MapperChildren,             std::vector<SdfPath>))    \
((SdfChildrenKeys->PrimChildren,               std::vector<TfToken>))    \
((SdfChildrenKeys->PropertyChildren,           std::vector<TfToken>))    \
((SdfChildrenKeys->RelationshipTargetChildren, std::vector<SdfPath>))    \
((SdfChildrenKeys->VariantChildren,            std::vector<TfToken>))    \
((SdfChildrenKeys->VariantSetChildren,         std::vector<TfToken>))

#define _SDF_FIELDS_NAME(tup) BOOST_PP_TUPLE_ELEM(2, 0, tup)
#define _SDF_FIELDS_TYPE(tup) BOOST_PP_TUPLE_ELEM(2, 1, tup)

/// Registers each built-in Sd field along with its C++ value type with
/// \p reg. \p reg can be any type that has a member function:
///     template <class T> void RegisterField(const TfToken&);
///
/// This function will be invoked for each (field, type) pair. The template
/// type T will be the C++ value type and the TfToken will be the field name.
template <class Registrar>
inline void
SdfRegisterFields(Registrar* reg)
{
#define _SDF_REGISTER_FIELDS(r, unused, elem)                        \
    reg->template RegisterField< _SDF_FIELDS_TYPE(elem) >(_SDF_FIELDS_NAME(elem));

    BOOST_PP_SEQ_FOR_EACH(_SDF_REGISTER_FIELDS, ~, _SDF_FIELDS)
#undef _SDF_REGISTER_FIELDS
}

/// Registers all possible C++ value types for built-in fields with \p reg.
/// This is the set of C++ types that are used by built-in fields and could
/// be returned from an SdfAbstractData container. \p reg can be any type that
/// has a member function:
///    template <class T> void RegisterType();
///
/// This function will be invoked for each C++ value type, which will be
/// given to the function as the template type T. Note that this function may
/// be called with the same T multiple times.
template <class Registrar>
inline void
SdfRegisterTypes(Registrar* reg)
{
    // Register all of the C++ value types from the field list above.
#define _SDF_REGISTER_TYPES(r, unused, elem)             \
    reg->template RegisterType< _SDF_FIELDS_TYPE(elem) >();

    BOOST_PP_SEQ_FOR_EACH(_SDF_REGISTER_TYPES, ~, _SDF_FIELDS)
#undef _SDF_REGISTER_TYPES

   // Also register all of the C++ value types for value types.
#define _SDF_REGISTER_VALUE_TYPES(r, unused, elem)                     \
    {                                                                  \
        reg->template RegisterType<SDF_VALUE_CPP_TYPE(elem)>();        \
        reg->template RegisterType<SDF_VALUE_CPP_ARRAY_TYPE(elem)>();  \
    }
    BOOST_PP_SEQ_FOR_EACH(_SDF_REGISTER_VALUE_TYPES, ~, SDF_VALUE_TYPES)
#undef _SDF_REGISTER_VALUE_TYPES

    // Also register all of the C++ list op types supported for
    // generic plugin metadata.
    reg->template RegisterType<SdfIntListOp>();
    reg->template RegisterType<SdfInt64ListOp>();
    reg->template RegisterType<SdfUIntListOp>();
    reg->template RegisterType<SdfUInt64ListOp>();
    reg->template RegisterType<SdfStringListOp>();
    reg->template RegisterType<SdfTokenListOp>();
    reg->template RegisterType<SdfValueBlock>();
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_SCHEMA_TYPE_REGISTRATION_H
