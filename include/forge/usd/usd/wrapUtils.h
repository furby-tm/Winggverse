#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/wrapUtils.h"
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
#ifndef FORGE_USD_USD_WRAP_UTILS_H
#define FORGE_USD_USD_WRAP_UTILS_H

#include "forge/forge.h"
#include "forge/usd/usd/object.h"

#include <boost/python/def_visitor.hpp>
#include <boost/python/type_id.hpp>
#include <boost/python/converter/to_python_function_type.hpp>

FORGE_NAMESPACE_BEGIN


// This boost.python def_visitor is used to wrap UsdObject and its subclasses.
// It replaces boost.python's to_python converter with one that downcasts to the
// most derived UsdObject subclass.  This way, a wrapped C++ function that
// returns a UsdObject, for instance, will produce a UsdPrim or a UsdAttribute
// or a UsdRelationship in python, instead of a UsdObject.
struct Usd_ObjectSubclass : boost::python::def_visitor<Usd_ObjectSubclass>
{
    friend class boost::python::def_visitor_access;

    // Function pointer type for downcasting UsdObject * to a more-derived type.
    typedef const void *(*DowncastFn)(const UsdObject *);

    // We replace boost.python's to_python converter with one that downcasts
    // UsdObject types to their most derived type.  For example, when converting
    // a UsdProperty to python, we downcast it to either UsdAttribute or
    // UsdRelationship, as appropriate.
    template <typename CLS>
    void visit(CLS &c) const {
        typedef typename CLS::wrapped_type Type;
        _ReplaceConverter(boost::python::type_id<Type>(),
                          _Detail::GetObjType<Type>::Value,
                          _Convert<Type>, _Downcast<Type>);
    }

private:
    // Converter implementation for UsdObject subclass T.
    template <class T>
    static PyObject *_Convert(const void *in) {
        return _ConvertHelper(static_cast<const T *>(in));
    }

    // Downcast UsdObject to T.
    template <class T>
    static const void *_Downcast(const UsdObject *in) {
        return static_cast<const T *>(in);
    }

    // Internal method that replaces the boost.python to_python converter for
    // the type \p pti.
    static void _ReplaceConverter(
        boost::python::type_info pti,
        UsdObjType objType,
        boost::python::converter::to_python_function_t convert,
        DowncastFn downcast);

    // Non-template helper function for _Convert.
    static PyObject *_ConvertHelper(const UsdObject *obj);
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_WRAP_UTILS_H
