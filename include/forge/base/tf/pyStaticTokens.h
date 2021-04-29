#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyStaticTokens.h"
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

#ifndef FORGE_BASE_TF_PY_STATIC_TOKENS_H
#define FORGE_BASE_TF_PY_STATIC_TOKENS_H

/// \file tf/pyStaticTokens.h

#include "forge/forge.h"

#include <locale>

#include "forge/base/tf/staticTokens.h"
#include "forge/base/tf/preprocessorUtilsLite.h"

#include <boost/python/class.hpp>
#include <boost/python/scope.hpp>

FORGE_NAMESPACE_BEGIN

// TODO: Should wrap token arrays to Python.

/// Macro to wrap static tokens defined with \c TF_DEFINE_PUBLIC_TOKENS to
/// Python.  It creates a class of name \p name in the current scope
/// containing just the tokens in \p seq in the static tokens named by \p key.
/// Arrays are not wrapped but their components are.
///
/// \hideinitializer
#define TF_PY_WRAP_PUBLIC_TOKENS(name, key, seq)                            \
    boost::python::class_<_TF_TOKENS_STRUCT_NAME(key), boost::noncopyable>( \
            name, boost::python::no_init)                                   \
        _TF_PY_TOKENS_WRAP_SEQ(key, _TF_PY_TOKENS_EXPAND(seq))

/// Macro to wrap static tokens defined with \c TF_DEFINE_PUBLIC_TOKENS to
/// Python. This wraps tokens in \p seq in the static tokens named by \p key
/// as attributes on the current boost python scope. Arrays are not wrapped
/// but their components are.
///
/// \hideinitializer
#define TF_PY_WRAP_PUBLIC_TOKENS_IN_CURRENT_SCOPE(key, seq)                 \
    _TF_PY_TOKENS_WRAP_ATTR_SEQ(key, _TF_PY_TOKENS_EXPAND(seq))

// Helper to return a static token as a string.  We wrap tokens as Python
// strings and for some reason simply wrapping the token using def_readonly
// bypasses to-Python conversion, leading to the error that there's no
// Python type for the C++ TfToken type.  So we wrap this functor instead.
class _TfPyWrapStaticToken {
public:
    _TfPyWrapStaticToken(const TfToken* token) : _token(token) { }

    std::string operator()() const
    {
        return _token->GetString();
    }

private:
    const TfToken* _token;
};

// Private macros to add a single data member.
#define _TF_PY_TOKENS_WRAP_ATTR_MEMBER(r, key, name)                        \
    boost::python::scope().attr(                                            \
        TF_PP_STRINGIZE(name)) = key->name.GetString();

#define _TF_PY_TOKENS_WRAP_MEMBER(r, key, name)                             \
    .add_static_property(TF_PP_STRINGIZE(name),                             \
        boost::python::make_function(_TfPyWrapStaticToken((&key->name)),    \
            boost::python::return_value_policy<                             \
                boost::python::return_by_value>(),                          \
            boost::mpl::vector1<std::string>()))

#define _TF_PY_TOKENS_EXPAND(seq)                                           \
    BOOST_PP_SEQ_FILTER(_TF_TOKENS_IS_NOT_ARRAY, ~, seq)                    \
    _TF_TOKENS_EXPAND_ARRAY_ELEMENTS(seq)

// Private macros to wrap a single element in a sequence.
#define _TF_PY_TOKENS_WRAP_ELEMENT(r, key, elem)                            \
    _TF_PY_TOKENS_WRAP_MEMBER(r, key, _TF_PY_TOKEN_GET_ELEM(elem))

#define _TF_PY_TOKENS_WRAP_ATTR_ELEMENT(r, key, elem)                       \
    _TF_PY_TOKENS_WRAP_ATTR_MEMBER(r, key, _TF_PY_TOKEN_GET_ELEM(elem))

#define _TF_PY_TOKEN_GET_ELEM(elem)                                         \
    BOOST_PP_IIF(TF_PP_IS_TUPLE(elem),                                      \
        BOOST_PP_TUPLE_ELEM(2, 0, elem), elem)

// Private macros to wrap a sequence.
#define _TF_PY_TOKENS_WRAP_SEQ(key, seq)                                    \
    BOOST_PP_SEQ_FOR_EACH(_TF_PY_TOKENS_WRAP_ELEMENT, key, seq)

#define _TF_PY_TOKENS_WRAP_ATTR_SEQ(key, seq)                               \
    BOOST_PP_SEQ_FOR_EACH(_TF_PY_TOKENS_WRAP_ATTR_ELEMENT, key, seq)

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_STATIC_TOKENS_H
