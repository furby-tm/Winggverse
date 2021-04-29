#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/instantiateType.h"
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
/*
 * This header is not meant to be included in a .h file.
 * Complain if we see this header twice through.
 */

#ifdef FORGE_BASE_TF_INSTANTIATE_TYPE_H
#error This file should only be included once in any given source (.cpp) file.
#endif

#define FORGE_BASE_TF_INSTANTIATE_TYPE_H

#include "forge/forge.h"
#include "forge/base/arch/attributes.h"
#include "forge/base/tf/type.h"
#include "forge/base/tf/refPtr.h"

FORGE_NAMESPACE_BEGIN

template <typename T, bool AS_REF_PTR>
struct Tf_TypeFactoryType {
    struct FactoryType : public TfType::FactoryBase {
        TfRefPtr<T> New() { return T::New(); }
    };
};
template <class T>
struct TfTest_RefPtrFactory {
};

template <typename T>
struct Tf_TypeFactoryType<T, false> {
    struct FactoryType : public TfType::FactoryBase {
        T* New() { return new T; }
    };
};

// Make the type actually manufacturable.
template <typename T, bool MANUFACTURABLE>
struct Tf_MakeTypeManufacturable {
    static void Doit(TfType t) {
        typedef typename Tf_TypeFactoryType<T, TF_SUPPORTS_REFPTR(T)>::FactoryType FT;
        t.SetFactory<FT>();
    }
};

// Don't make it manufacturable.
template <typename T>
struct Tf_MakeTypeManufacturable<T, false> {
    static void Doit(TfType) {
    }
};

#define _TF_REMOVE_PARENS_HELPER(...) __VA_ARGS__
#define _TF_REMOVE_PARENS(parens) _TF_REMOVE_PARENS_HELPER parens

#define TF_NO_PARENT()            (TfType::Bases<>)
#define TF_1_PARENT(p1)            (TfType::Bases<p1 >)
#define TF_2_PARENT(p1,p2)  (TfType::Bases<p1, p2 >)
#define TF_INSTANTIATE_TYPE(Type, flags, Bases) \
    TF_REGISTRY_DEFINE_WITH_TYPE(TfType, Type) { \
        TfType t1 = TfType::Define<Type, _TF_REMOVE_PARENS(Bases) >(); \
        Tf_MakeTypeManufacturable<Type, (flags&TfType::MANUFACTURABLE)!=0 >::Doit(t1); \
    }

FORGE_NAMESPACE_END
