#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/cxxCast.h"
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
#ifndef FORGE_BASE_TF_CXX_CAST_H
#define FORGE_BASE_TF_CXX_CAST_H

/// \file tf/cxxCast.h
/// C++ Cast Utilities.

#ifndef __cplusplus
#error This include file can only be included in C++ programs.
#endif

#include "forge/forge.h"
#include <type_traits>

FORGE_NAMESPACE_BEGIN

template <class Src, class Dst>
using Tf_CopyConst =
    typename std::conditional<std::is_const<Src>::value,
                              typename std::add_const<Dst>::type, Dst>::type;

template <class Src, class Dst>
using Tf_CopyVolatile =
    typename std::conditional<std::is_volatile<Src>::value,
                              typename std::add_volatile<Dst>::type, Dst>::type;

template <class Src, class Dst>
using Tf_CopyCV = Tf_CopyConst<Src, Tf_CopyVolatile<Src, Dst>>;

/// Return a pointer to the most-derived object.
///
/// A \c dynamic_cast to \c void* is legal only for pointers to polymorphic
/// objects. This function returns the original pointer for non-polymorphic
/// types, and a pointer to the most-derived type of the object.
/// Said differently, given a pointer of static type \c B*, and given that
/// the object really points to an object of type \c D*, this function
/// returns the address of the object considered as a \c D*; however, for
/// non-polymorphic objects, the actual type of an object is taken to be \c B,
/// since one cannot prove that that the type is actually different.
///
/// \warning This function is public, but should be used sparingly (or not all).
template <typename T>
inline typename std::enable_if<
    std::is_polymorphic<T>::value, Tf_CopyCV<T, void>*>::type
TfCastToMostDerivedType(T* ptr)
{
    return dynamic_cast<Tf_CopyCV<T, void>*>(ptr);
}

template <typename T>
inline typename std::enable_if<
    !std::is_polymorphic<T>::value, Tf_CopyCV<T, void>*>::type
TfCastToMostDerivedType(T* ptr)
{
    return static_cast<Tf_CopyCV<T, void>*>(ptr);
}

FORGE_NAMESPACE_END

#endif
