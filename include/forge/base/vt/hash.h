#line 1 "C:/Users/tyler/dev/WINGG/forge/base/vt/hash.h"
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
#ifndef FORGE_BASE_VT_HASH_H
#define FORGE_BASE_VT_HASH_H

#include "forge/forge.h"
#include "forge/base/vt/api.h"
#include "forge/base/tf/hash.h"
#include <boost/functional/hash.hpp>
#include <typeinfo>
#include <utility>

FORGE_NAMESPACE_BEGIN

namespace Vt_HashDetail {

// Issue a coding error when we attempt to hash a t.
VT_API void _IssueUnimplementedHashError(std::type_info const &t);

// We make unqualified calls, intending to pick up boost::hash_value if an
// overload isn't found by ADL.
using boost::hash_value;

// A constexpr function that determines hashability.
template <class T, class = decltype(hash_value(std::declval<T>()))>
constexpr bool _IsHashable(int) { return true; }
template <class T, class = decltype(TfHash()(std::declval<T>()))>
constexpr bool _IsHashable(long) { return true; }
template <class T>
constexpr bool _IsHashable(...) { return false; }

// Hash implementations -- We're using an overload resolution ordering trick
// here (int vs long vs ...) so that we pick hash_value first, if possible,
// otherwise we do TfHash() if possible, otherwise we issue a runtime error.
template <class T, class = decltype(hash_value(std::declval<T>()))>
inline size_t
_HashValueImpl(T const &val, int)
{
    return hash_value(val);
}

template <class T, class = decltype(TfHash()(std::declval<T>()))>
inline size_t
_HashValueImpl(T const &val, long)
{
    return TfHash()(val);
}

template <class T>
inline size_t
_HashValueImpl(T const &val, ...)
{
    Vt_HashDetail::_IssueUnimplementedHashError(typeid(T));
    return 0;
}

} // Vt_HashDetail


/// A constexpr function that returns true if T is hashable via VtHashValue,
/// false otherwise.  This is true if we can either invoke
/// (boost::)hash_value() or TfHash()() on a T instance.
template <class T>
constexpr bool
VtIsHashable() {
    return Vt_HashDetail::_IsHashable<T>(0);
}

/// Compute a hash code for \p val by invoking (boost::)hash_value(val) if
/// possible, otherwise by invoking TfHash()(val), or if neither are possible
/// issue a coding error and return 0.
template <class T>
size_t VtHashValue(T const &val)
{
    return Vt_HashDetail::_HashValueImpl(val, 0);
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_VT_HASH_H
