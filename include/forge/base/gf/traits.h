#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/traits.h"
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
#ifndef FORGE_BASE_GF_TRAITS_H
#define FORGE_BASE_GF_TRAITS_H

#include "forge/forge.h"

#include <type_traits>

FORGE_NAMESPACE_BEGIN

/// A metafunction with a static const bool member 'value' that is true for
/// GfVec types, like GfVec2i, GfVec4d, etc and false for all other types.
template <class T>
struct GfIsGfVec { static const bool value = false; };

/// A metafunction with a static const bool member 'value' that is true for
/// GfMatrix types, like GfMatrix3d, GfMatrix4f, etc and false for all other
/// types.
template <class T>
struct GfIsGfMatrix { static const bool value = false; };

/// A metafunction with a static const bool member 'value' that is true for
/// GfQuat types and false for all other types.
template <class T>
struct GfIsGfQuat { static const bool value = false; };

/// A metafunction with a static const bool member 'value' that is true for
/// GfRange types and false for all other types.
template <class T>
struct GfIsGfRange { static const bool value = false; };

/// A metafunction which is equivalent to std::is_floating_point but
/// allows for additional specialization for types like GfHalf
template <class T>
struct GfIsFloatingPoint : public std::is_floating_point<T>{};

/// A metafunction which is equivalent to std::arithmetic but
/// also includes any specializations from GfIsFloatingPoint (like GfHalf)
template <class T>
struct GfIsArithmetic : public std::integral_constant<
    bool, GfIsFloatingPoint<T>::value || std::is_arithmetic<T>::value>{};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_TRAITS_H
