#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/ostreamMethods.h"
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
#ifndef FORGE_BASE_TF_OSTREAM_METHODS_H
#define FORGE_BASE_TF_OSTREAM_METHODS_H

/// \file tf/ostreamMethods.h
/// \ingroup group_tf_DebuggingOutput
///
/// Handy ostream output for various lib/tf and STL containers.
///
/// These functions are useful when you need to quickly output various STL
/// containers.  The stream operators are only available if the contained
/// types have stream operators.
///
/// This facility should \e not be used to output data for later input: this
/// is essentially a "write-only" facility meant for diagnostics or
/// human-readable display; the formats described herein are subject to change
/// without notice.

#include "forge/forge.h"
#include "forge/base/tf/hashmap.h"

#include <ostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <type_traits>

#include <boost/type_traits/has_left_shift.hpp>

FORGE_NAMESPACE_BEGIN

template <class T>
constexpr bool Tf_IsOstreamable() {
    return boost::has_left_shift<
        std::ostream &, /* << */ T, /* -> */ std::ostream &>::value;
}

FORGE_NAMESPACE_END

// These operator<< overloads need to go in the std namespace for
// Koenig lookup to work.
namespace std {

/// Output an STL vector using [ ] as delimiters.
/// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<FORGE_NS::Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << "[ ";
    for (auto const &obj: v)
        out << obj << " ";
    out << "]";

    return out;
}

/// Output an STL set using ( ) as delimiters.
/// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<FORGE_NS::Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::set<T> &v)
{
    out << "( ";
    for (auto const &obj: v)
        out << obj << " ";
    out << ")";

    return out;
}

/// Output an STL list using { } as delimiters.
/// \ingroup group_tf_DebuggingOutput
template <class T>
typename std::enable_if<FORGE_NS::Tf_IsOstreamable<T>(), std::ostream &>::type
operator<<(std::ostream &out, const std::list<T> &l)
{
    out << "{ ";
    for (auto const &obj: l)
        out << obj << " ";
    out << "}";

    return out;
}

/// Output an TfHashMap using < > as delimiters.
/// \ingroup group_tf_DebuggingOutput
template <class K, class M, class H, class C, class A>
typename std::enable_if<
    FORGE_NS::Tf_IsOstreamable<K>() && FORGE_NS::Tf_IsOstreamable<M>(), std::ostream &>::type
operator<<(std::ostream &out, const FORGE_NS::TfHashMap<K, M, H, C, A> &h)
{
    out << "< ";
    for (auto const &p: h)
        out << "<" << p.first << ": " << p.second << "> ";
    out << ">";
    return out;
}

/// Output an STL map using < > as delimiters.
/// \ingroup group_tf_DebuggingOutput
template <class K, class M>
typename std::enable_if<
    FORGE_NS::Tf_IsOstreamable<K>() && FORGE_NS::Tf_IsOstreamable<M>(), std::ostream &>::type
operator<<(std::ostream &out, const std::map<K, M> &h)
{
    out << "< ";
    for (auto const &p: h)
        out << "<" << p.first << ": " << p.second << "> ";
    out << ">";
    return out;
}

} // namespace std

#endif // FORGE_BASE_TF_OSTREAM_METHODS_H
