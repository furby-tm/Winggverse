#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyClassMethod.h"
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
#ifndef FORGE_BASE_TF_PY_CLASS_METHOD_H
#define FORGE_BASE_TF_PY_CLASS_METHOD_H

#include "forge/forge.h"

#include <boost/python/class.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/object.hpp>
#include <boost/python/def_visitor.hpp>

FORGE_NAMESPACE_BEGIN

namespace Tf_PyClassMethod {

using namespace boost::python;

// Visitor for wrapping functions as Python class methods.
// See typedef below for docs.
// This is very similar to the staticmethod() method on boost::python::class,
// except it uses PyClassMethod_New() instead of PyStaticMethod_New().
struct _TfPyClassMethod : def_visitor<_TfPyClassMethod>
{
    friend class def_visitor_access;

    _TfPyClassMethod(const std::string &methodName) :
        _methodName(methodName) {}
    explicit _TfPyClassMethod(const char *methodName) :
        _methodName(methodName) {}

    template <typename CLS>
    void visit(CLS &c) const
    {
        PyTypeObject* self = downcast<PyTypeObject>( c.ptr() );
        dict d((handle<>(borrowed(self->tp_dict))));

        object method(d[_methodName]);

        c.attr(_methodName.c_str()) = object(
            handle<>( PyClassMethod_New((_CallableCheck)(method.ptr()) )));
    }

private:

    PyObject* _CallableCheck(PyObject* callable) const
    {
        if (PyCallable_Check(expect_non_null(callable)))
            return callable;

        PyErr_Format( PyExc_TypeError,
           "classmethod expects callable object; got an object of type %s, "
           "which is not callable",
           callable->ob_type->tp_name);

        throw_error_already_set();
        return 0;
    }

    const std::string _methodName;
};

}

/// A boost.python class visitor which replaces the named method with a
/// classmethod()-wrapped one.
///
/// \code
///    void Foo( boost::python::object & pyClassObject ) { /* ... */ }
///
///    class_<...>(...)
///         .def("Foo", &Foo)
///         .def(TfPyClassMethod("Foo"))
///         ;
/// \endcode
///
typedef Tf_PyClassMethod::_TfPyClassMethod TfPyClassMethod;

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_CLASS_METHOD_H
