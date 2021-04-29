#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/type_Impl.h"
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
#ifndef FORGE_BASE_TF_TYPE_IMPL_H
#define FORGE_BASE_TF_TYPE_IMPL_H

#include "forge/base/tf/mallocTag.h"

#include <initializer_list>

FORGE_NAMESPACE_BEGIN

template <class DERIVED, class BASE>
inline void*
Tf_CastToParent(void* addr, bool derivedToBase);

// Declare and register casts for all the C++ bases in the given TypeVector.
template <typename TypeVector>
struct Tf_AddBases;

template <typename... Bases>
struct Tf_AddBases<TfType::Bases<Bases...>>
{
    // Declare types in Bases as TfTypes and accumulate them into a runtime
    // vector.
    static std::vector<TfType>
    Declare()
    {
        return std::vector<TfType> {
            TfType::Declare(
                TfType::GetCanonicalTypeName( typeid(Bases) ))...
        };
    }

    // Register casts to and from Derived and each base type in Bases.
    template <typename Derived>
    static void
    RegisterCasts(TfType const* type)
    {
        struct Cast
        {
            const std::type_info *typeInfo;
            TfType::_CastFunction func;
        };

        const std::initializer_list<Cast> baseCasts = {
            { &typeid(Bases), &Tf_CastToParent<Derived, Bases> }...
        };

        for (const Cast &cast : baseCasts) {
            type->_AddCppCastFunc(*cast.typeInfo, cast.func);
        }
    }
};

template <class T, class BaseTypes>
TfType const &
TfType::Declare()
{
    // Declare each of the base types.
    std::vector<TfType> baseTfTypes = Tf_AddBases<BaseTypes>::Declare();
    // Declare our type T.
    const std::type_info &typeInfo = typeid(T);
    const std::string typeName = TfType::GetCanonicalTypeName(typeInfo);
    return TfType::Declare(typeName, baseTfTypes);
}

template <typename T, typename BaseTypes>
TfType const&
TfType::Define()
{
    TfAutoMallocTag2 tag2("Tf", "TfType::Define");

    // Declare each of the base types.
    std::vector<TfType> baseTfTypes = Tf_AddBases<BaseTypes>::Declare();

    // Declare our type T.
    const std::type_info &typeInfo = typeid(T);
    const std::string typeName = TfType::GetCanonicalTypeName(typeInfo);
    TfType const& newType = TfType::Declare(typeName, baseTfTypes);

    // Record traits information about T.
    const bool isPodType = std::is_pod<T>::value;
    const bool isEnumType = std::is_enum<T>::value;
    const size_t sizeofType = TfSizeofType<T>::value;

    newType._DefineCppType(typeInfo, sizeofType, isPodType, isEnumType);
    Tf_AddBases<BaseTypes>::template RegisterCasts<T>(&newType);

    return newType;
}

template <typename T>
TfType const&
TfType::Define()
{
    return Define<T, Bases<> >();
}

// Helper function to implement up/down casts between TfType types.
// This was taken from the previous TfType implementation.
template <class DERIVED, class BASE>
inline void*
Tf_CastToParent(void* addr, bool derivedToBase)
{
    if (derivedToBase) {
        // Upcast -- can be done implicitly.
        DERIVED* derived = reinterpret_cast<DERIVED*>(addr);
        BASE* base = derived;
        return base;
    } else {
        // Downcast -- use static_cast.
        BASE* base = reinterpret_cast<BASE*>(addr);
        DERIVED* derived = static_cast<DERIVED*>(base);
        return derived;
    }
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_TYPE_IMPL_H
