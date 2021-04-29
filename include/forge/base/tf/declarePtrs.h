#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/declarePtrs.h"
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
#ifndef FORGE_BASE_TF_DECLARE_PTRS_H
#define FORGE_BASE_TF_DECLARE_PTRS_H

/// \file tf/declarePtrs.h
/// Standard pointer typedefs.
///
/// This file provides typedefs for standard pointer types.

#include "forge/forge.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/base/tf/refPtr.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

/// \struct TfDeclarePtrs
/// Templated struct used for type definition macros.
template<typename T> struct TfDeclarePtrs {
    typedef TfWeakPtr< T >              Ptr;
    typedef TfWeakPtr< const T >        ConstPtr;
    typedef std::vector< Ptr >          PtrVector;
    typedef std::vector< ConstPtr >     ConstPtrVector;

    typedef TfRefPtr< T >               RefPtr;
    typedef TfRefPtr< const T >         ConstRefPtr;
    typedef std::vector< RefPtr >       RefPtrVector;
    typedef std::vector< ConstRefPtr >  ConstRefPtrVector;
};

/// Define standard weak pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_WEAK_PTRS(Class) declares ClassPtr, ClassConstPtr,
/// ClassPtrVector and ClassConstPtrVector.
///
/// \hideinitializer
#define TF_DECLARE_WEAK_PTRS(type)                                      \
    typedef TfDeclarePtrs< class type >::Ptr type##Ptr;                 \
    typedef TfDeclarePtrs< class type >::ConstPtr type##ConstPtr;       \
    typedef TfDeclarePtrs< class type >::PtrVector type##PtrVector;     \
    typedef TfDeclarePtrs< class type >::ConstPtrVector type##ConstPtrVector

/// Define standard ref pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_REF_PTRS(Class) declares ClassRefPtr and ClassConstRefPtr.
///
/// \hideinitializer
#define TF_DECLARE_REF_PTRS(type)                                       \
    typedef TfDeclarePtrs< class type >::RefPtr type##RefPtr;           \
    typedef TfDeclarePtrs< class type >::ConstRefPtr type##ConstRefPtr; \
    typedef TfDeclarePtrs< class type >::RefPtrVector type##RefPtrVector; \
    typedef TfDeclarePtrs< class type >::ConstRefPtrVector type##ConstRefPtrVector

/// Define standard weak, ref, and vector pointer types.
///
/// \param type is a class name.
///
/// \c TF_DECLARE_WEAK_AND_REF_PTRS(Class) declares ClassPtr, ClassConstPtr,
/// ClassPtrVector, ClassConstPtrVector, ClassRefPtr and ClassConstRefPtr.
///
/// \hideinitializer
#define TF_DECLARE_WEAK_AND_REF_PTRS(type)                              \
    TF_DECLARE_WEAK_PTRS(type);                                         \
    TF_DECLARE_REF_PTRS(type)

FORGE_NAMESPACE_END

#endif
