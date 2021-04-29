#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/typeFunctions.h"
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
#ifndef FORGE_BASE_TF_TYPE_FUNCTIONS_H
#define FORGE_BASE_TF_TYPE_FUNCTIONS_H

/// \file tf/typeFunctions.h
/// \ingroup group_tf_Internal

#include "forge/forge.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

/// \class TfTypeFunctions
/// \ingroup group_tf_Internal
///
/// Implements assorted functions based on compile-time type information.
///
/// TfTypeFunctions<T>::GetRawPtr(T* tPtr) returns tPtr.  A smart-pointer
/// class, such as \c TfRefPtr, may specialize this function to have different
/// behavior.  Note that for a non-pointer type, this returns the address of
/// the object, which allows one to uniformly apply the -> operator for member
/// function calls.
///
/// TfTypeFunctions<T>::ConstructFromRawPtr(T* tPtr) returns tPtr.
/// Pointer-like objects should specialize this function so that given a raw
/// pointer of type T*, they return a smart pointer pointing to that object
/// (see refPtr.h for an example). Essentially, this is the inverse of
/// TfTypeFunctions<T>::GetRawPtr.
///
template <class T, class ENABLE = void>
struct TfTypeFunctions {
#if 0
    static T* GetRawPtr(T& t) {
        return &t;
    }
#endif

    static const T* GetRawPtr(const T& t) {
        return &t;
    }

    static T& ConstructFromRawPtr(T* ptr) { return *ptr; }

    static bool IsNull(const T&) {
        return false;
    }

    static void Class_Object_MUST_Not_Be_Const() { }
    static void Object_CANNOT_Be_a_Pointer() { }
};

template <class T>
struct TfTypeFunctions<T*> {
    static T* GetRawPtr(T* t) {
        return t;
    }

    static T* ConstructFromRawPtr(T* ptr) { return ptr; }

    static bool IsNull(T* ptr) {
        return !ptr;
    }

    static void Class_Object_MUST_Be_Passed_By_Address() { }
    static void Class_Object_MUST_Not_Be_Const() { }
};

template <class T>
struct TfTypeFunctions<const T*> {
    static const T* GetRawPtr(const T* t) {
        return t;
    }

    static bool IsNull(const T* ptr) {
        return !ptr;
    }

    static const T* ConstructFromRawPtr(T* ptr) { return ptr; }
    static void Class_Object_MUST_Be_Passed_By_Address() { }
};

/// \class TfCopyIfNotReference
/// \ingroup group_tf_Internal
///
/// \c TfCopyIfNotReference<T>::Apply(v) is used to return a pointer to the
/// value \p v.  If \c T is a non-reference type, then the value returned
/// points to newly constructed dynamic space, which the caller must free.
/// Otherwise, the returned value is the address of \p v.
///
template <class T>
struct TfCopyIfNotReference
{
    static T* Apply(T value) {
        return new T(value);
    }
};

template <class T>
struct TfCopyIfNotReference<T&>
{
    static T* Apply(T& value) {
        return &value;
    }
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_TYPE_FUNCTIONS_H
