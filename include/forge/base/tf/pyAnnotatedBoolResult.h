#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyAnnotatedBoolResult.h"
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
#ifndef FORGE_BASE_TF_PY_ANNOTATED_BOOL_RESULT_H
#define FORGE_BASE_TF_PY_ANNOTATED_BOOL_RESULT_H

#include "forge/forge.h"

#include "forge/base/tf/py3Compat.h"
#include "forge/base/tf/pyLock.h"
#include "forge/base/tf/pyUtils.h"

#include <boost/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>
#include <boost/python/return_by_value.hpp>

#include <string>

FORGE_NAMESPACE_BEGIN

template <class Annotation>
struct TfPyAnnotatedBoolResult :
    boost::equality_comparable<TfPyAnnotatedBoolResult<Annotation>, bool>
{
    TfPyAnnotatedBoolResult() {}

    TfPyAnnotatedBoolResult(bool val, Annotation const &annotation) :
        _val(val), _annotation(annotation) {}

    bool GetValue() const {
        return _val;
    }

    Annotation const &GetAnnotation() const {
        return _annotation;
    }

    std::string GetRepr() const {
        return GetValue() ? "True" :
            "(False, " + TfPyRepr(GetAnnotation()) + ")";
    }

    /// Returns \c true if the result is the same as \p rhs.
    bool operator==(bool rhs) const {
        return _val == rhs;
    }

    template <class Derived>
    static boost::python::class_<Derived>
    Wrap(char const *name, char const *annotationName) {
        typedef TfPyAnnotatedBoolResult<Annotation> This;
        using namespace boost::python;
        TfPyLock lock;
        return class_<Derived>(name, no_init)
            .def(TfPyBoolBuiltinFuncName, &Derived::GetValue)
            .def("__repr__", &Derived::GetRepr)
            .def(self == bool())
            .def(self != bool())
            .def(bool() == self)
            .def(bool() != self)
            // Use a helper function.  We'd like to def_readonly the
            // _annotation member but there are two problems with that.
            // First, we can't control the return_value_policy and if the
            // Annotation type has a custom to-Python converter then the
            // def_readonly return_value_policy of return_internal_reference
            // won't work since the object needs conversion.  Second, if we
            // try to use GetAnnotation() with add_property then we'll get
            // a failure at runtime because Python has a Derived but
            // GetAnnotation takes a TfPyAnnotatedBoolResult<Annotation>
            // and boost python doesn't know the former is-a latter because
            // TfPyAnnotatedBoolResult<Annotation> is not wrapped.
            //
            // So we provide a templated static method that takes a Derived
            // and returns Annotation by value.  We can add_property that
            // with no problem.
            .add_property(annotationName, &This::_GetAnnotation<Derived>)
            .def("__getitem__", &This::_GetItem<Derived>)
            ;
    }

    using AnnotationType = Annotation;

private:
    // Helper function for wrapper.
    template <class Derived>
    static Annotation _GetAnnotation(const Derived& x)
    {
        return x.GetAnnotation();
    }

    template <class Derived>
    static boost::python::object _GetItem(const Derived& x, int i)
    {
        if (i == 0) {
            return boost::python::object(x._val);
        }
        if (i == 1) {
            return boost::python::object(x._annotation);
        }

        PyErr_SetString(PyExc_IndexError, "Index must be 0 or 1.");
        boost::python::throw_error_already_set();

        return boost::python::object();
    }

private:
    bool _val;
    Annotation _annotation;

};

/// Returns \c true if the result of \p lhs is the same as \p rhs.
template <class Annotation>
bool operator==(bool lhs, TfPyAnnotatedBoolResult<Annotation>& rhs)
{
    return rhs == lhs;
}

/// Returns \c false if the result of \p lhs is the same as \p rhs.
template <class Annotation>
bool operator!=(bool lhs, TfPyAnnotatedBoolResult<Annotation>& rhs)
{
    return rhs != lhs;
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_ANNOTATED_BOOL_RESULT_H
