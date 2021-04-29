#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/bitUtils.h"
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
#ifndef FORGE_BASE_TF_BIT_UTILS_H
#define FORGE_BASE_TF_BIT_UTILS_H

/// \file tf/bitUtils.h
/// \ingroup group_tf_BasicMath

#include "forge/forge.h"

#include <cstddef>
#include <type_traits>

FORGE_NAMESPACE_BEGIN

/// Compute the number of bits required to store the given number of values.
///
/// Note that the computed result for a number smaller or equal to zero is
/// undefined.  The input number can be any compile-time constant.
///
/// \ingroup group_tf_BasicMath
/// \hideinitializer
#define TF_BITS_FOR_VALUES(n) \
    Tf_NumBits<n-1>::type::value

template <size_t N, size_t SUM=0, size_t BIT=sizeof(N)*8/2>
struct Tf_NumBits
{
    // The result is computed by divide and conquer; for a given word N the
    // bit at position BIT divides the word in an upper and a lower half.
    // If the upper half contain any ones, then the result is SUM plus BIT
    // plus the result for the upper half.  If not, the result is SUM plus
    // the result for the lower half.
    typedef typename std::conditional<N >= (1ULL<<BIT),
        Tf_NumBits<(N>>BIT), SUM+BIT, BIT/2>,
        Tf_NumBits<N, SUM, BIT/2> >::type _func;
    typedef typename _func::type type;
};

template <size_t N, size_t SUM>
struct Tf_NumBits<N, SUM, 0>
{
    typedef std::integral_constant<size_t, SUM+1> type;
};

/// Compute the number of bits required to store the given number of (signed)
/// enum values.
///
/// \note This is intended to be used when storing enum values in a bitfield
/// without casting the enum type to an unsigned integer.  (At least GCC
/// considers enums to be signed and hence wastes one bit when all enumerants
/// are non-negative).
///
/// \ingroup group_tf_BasicMath
/// \hideinitializer
#define TF_BITS_FOR_ENUM_VALUES(n) \
    (TF_BITS_FOR_VALUES(n) + 1)

FORGE_NAMESPACE_END

#endif /* FORGE_BASE_TF_BIT_UTILS_H */
