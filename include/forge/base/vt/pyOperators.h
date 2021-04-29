#line 1 "C:/Users/tyler/dev/WINGG/forge/base/vt/pyOperators.h"
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

#include "forge/forge.h"
#include "forge/base/vt/api.h"

// See the description in vt/operators.h for a better understanding regarding
// the purpose and usage of macros defined below.

FORGE_NAMESPACE_BEGIN

// -------------------------------------------------------------------------
// Python operator definitions
// -------------------------------------------------------------------------
// These will define the operator to work with tuples and lists from Python.

// base macro called by wrapping layers below for various operators, python
// types (lists and tuples), and special methods
#define VTOPERATOR_WRAP_PYTYPE_BASE(op,method,pytype,rettype,expr)           \
    template <typename T> static                                             \
    VtArray<rettype> method##pytype(VtArray<T> vec, pytype obj)              \
    {                                                                        \
        size_t length = len(obj);                                            \
        if (length != vec.size()) {                                          \
            TfPyThrowValueError("Non-conforming inputs for operator " #op);  \
            return VtArray<T>();                                             \
        }                                                                    \
        VtArray<rettype> ret(vec.size());                                    \
        for (size_t i = 0; i < length; ++i) {                                \
            if (!extract<T>(obj[i]).check())                                 \
                TfPyThrowValueError("Element is of incorrect type.");        \
            ret[i] = expr;                                                   \
        }                                                                    \
        return ret;                                                          \
    }

// wrap Array op pytype
#define VTOPERATOR_WRAP_PYTYPE(op,lmethod,tuple,T)                             \
    VTOPERATOR_WRAP_PYTYPE_BASE(op,lmethod,tuple,T,                            \
                                (vec[i] op (T)extract<T>(obj[i])) )

// wrap pytype op Array (for noncommutative ops like subtraction)
#define VTOPERATOR_WRAP_PYTYPE_R(op,lmethod,tuple,T)                           \
    VTOPERATOR_WRAP_PYTYPE_BASE(op,lmethod,tuple,T,                            \
                                ((T)extract<T>(obj[i]) op vec[i]) )


// operator that needs a special method plus a reflected special method,
// each defined on tuples and lists
#define VTOPERATOR_WRAP(op,lmethod,rmethod)                 \
    VTOPERATOR_WRAP_PYTYPE(op,lmethod,tuple,T)              \
    VTOPERATOR_WRAP_PYTYPE(op,lmethod,list,T)               \
    VTOPERATOR_WRAP_PYTYPE(op,rmethod,tuple,T)              \
    VTOPERATOR_WRAP_PYTYPE(op,rmethod,list,T)

// like above, but for non-commutative ops like subtraction
#define VTOPERATOR_WRAP_NONCOMM(op,lmethod,rmethod)         \
    VTOPERATOR_WRAP_PYTYPE(op,lmethod,tuple,T)              \
    VTOPERATOR_WRAP_PYTYPE(op,lmethod,list,T)               \
    VTOPERATOR_WRAP_PYTYPE_R(op,rmethod,tuple,T)            \
    VTOPERATOR_WRAP_PYTYPE_R(op,rmethod,list,T)

// to be used to actually declare the wrapping with def() on the class
#define VTOPERATOR_WRAPDECLARE_BASE(op,method,rettype)      \
    .def(self op self)                                      \
    .def(self op Type())                                    \
    .def(Type() op self)                                    \
    .def(#method,method##tuple<rettype>)                    \
    .def(#method,method##list<rettype>)

#define VTOPERATOR_WRAPDECLARE(op,lmethod,rmethod)          \
    VTOPERATOR_WRAPDECLARE_BASE(op,lmethod,Type)            \
    .def(#rmethod,rmethod##tuple<Type>)                     \
    .def(#rmethod,rmethod##list<Type>)

// to be used for wrapping conditional functions that return bool arrays
// (i.e. Equal, etc)
#define VTOPERATOR_WRAP_PYTYPE_BOOL_BASE(func,arg1,arg2,expr)         \
    template <typename T> static                                      \
    VtArray<bool> Vt##func(arg1, arg2)                                \
    {                                                                 \
        size_t length = len(obj);                                     \
        if (length != vec.size()) {                                   \
            TfPyThrowValueError("Non-conforming inputs for " #func);  \
            return VtArray<bool>();                                   \
        }                                                             \
        VtArray<bool> ret(vec.size());                                \
        for (size_t i = 0; i < length; ++i) {                         \
            if (!extract<T>(obj[i]).check())                          \
                TfPyThrowValueError("Element is of incorrect type."); \
            ret[i] = expr;                                            \
        }                                                             \
        return ret;                                                   \
    }

// array OP pytype
// pytype OP array
#define VTOPERATOR_WRAP_PYTYPE_BOOL(func,pytype,op)         \
        VTOPERATOR_WRAP_PYTYPE_BOOL_BASE(func,              \
            VtArray<T> const &vec, pytype const &obj,       \
            (vec[i] op (T)extract<T>(obj[i])) )             \
        VTOPERATOR_WRAP_PYTYPE_BOOL_BASE(func,              \
            pytype const &obj,VtArray<T> const &vec,        \
            ((T)extract<T>(obj[i]) op vec[i]) )

#define VTOPERATOR_WRAP_BOOL(func,op)                       \
        VTOPERATOR_WRAP_PYTYPE_BOOL(func,list,op)           \
        VTOPERATOR_WRAP_PYTYPE_BOOL(func,tuple,op)

// to be used to actually declare the wrapping with def() on the class
#define VTOPERATOR_WRAPDECLARE_BOOL(func)                   \
       def(#func,(VtArray<bool> (*)                         \
            (VtArray<Type> const &,VtArray<Type> const &))  \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (Type const &,VtArray<Type> const &))           \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (VtArray<Type> const &,Type const &))           \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (VtArray<Type> const &,tuple const &))          \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (tuple const &,VtArray<Type> const &))          \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (VtArray<Type> const &,list const &))           \
            Vt##func<Type>);                                \
        def(#func,(VtArray<bool> (*)                        \
            (list const &,VtArray<Type> const &))           \
            Vt##func<Type>);

FORGE_NAMESPACE_END
