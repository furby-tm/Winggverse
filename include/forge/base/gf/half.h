#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/half.h"
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
#ifndef FORGE_BASE_GF_HALF_H
#define FORGE_BASE_GF_HALF_H

/// \file gf/half.h
///
/// This header serves to simply bring in the half float datatype and
/// provide a hash_value function.  For documentation, of the half type,
/// please see the half header in ilmbase_half.h.

#include "forge/forge.h"
#include "forge/base/gf/ilmbase_half.h"
#include "forge/base/gf/ilmbase_halfLimits.h"
#include "forge/base/gf/traits.h"

#include <type_traits>

FORGE_NAMESPACE_BEGIN

/// A 16-bit floating point data type.
using GfHalf = forge_half::half;

namespace forge_half {
    /// Overload hash_value for half.
    template<typename Half>
    inline
    typename std::enable_if<std::is_same<Half, half>::value, size_t>::type
    hash_value(const Half& h) { return h.bits(); }
}

template <>
struct GfIsFloatingPoint<GfHalf> :
    public std::integral_constant<bool, true>{};

FORGE_NAMESPACE_END


#endif // FORGE_BASE_GF_HALF_H
