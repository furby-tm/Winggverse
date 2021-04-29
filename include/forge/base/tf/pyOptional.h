#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyOptional.h"
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
#ifndef FORGE_BASE_TF_PY_OPTIONAL_H
#define FORGE_BASE_TF_PY_OPTIONAL_H

/// \file tf/pyOptional.h

#include "forge/forge.h"

#include "forge/base/tf/pyUtils.h"
#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/python/converter/from_python.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/to_python_value.hpp>

FORGE_NAMESPACE_BEGIN

// Adapted from original at:
// http://mail.python.org/pipermail/cplusplus-sig/2007-May/012003.html

namespace TfPyOptional {

template <typename T, typename TfromPy>
struct object_from_python
{
    object_from_python() {
        boost::python::converter::registry::push_back
        (&TfromPy::convertible, &TfromPy::construct,
         boost::python::type_id<T>());
    }
};

template <typename T, typename TtoPy, typename TfromPy>
struct register_python_conversion
{
    register_python_conversion() {
        boost::python::to_python_converter<T, TtoPy>();
        object_from_python<T, TfromPy>();
    }
};

template <typename T>
struct python_optional : public boost::noncopyable
{
    struct optional_to_python
    {
        static PyObject * convert(const boost::optional<T>& value)
        {
            if (value) {
                boost::python::object obj = TfPyObject(*value);
                Py_INCREF(obj.ptr());
                return obj.ptr();
            }
            return boost::python::detail::none();
        }
    };

    struct optional_from_python
    {
        static void * convertible(PyObject * source)
        {
            using namespace boost::python::converter;

            if ((source == Py_None) || boost::python::extract<T>(source).check())
                return source;

            return NULL;
        }

        static void construct(PyObject * source,
                              boost::python::converter::rvalue_from_python_stage1_data * data)
        {
            using namespace boost::python::converter;

            void * const storage =
                ((rvalue_from_python_storage<T> *)data)->storage.bytes;

            if (data->convertible == Py_None) {
                new (storage) boost::optional<T>(); // An uninitialized optional
            } else {
                new (storage) boost::optional<T>(boost::python::extract<T>(source));
            }

            data->convertible = storage;
        }
    };

    explicit python_optional() {
        register_python_conversion<boost::optional<T>,
                                   optional_to_python, optional_from_python>();
    }
};

} // namespace TfPyOptional

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_OPTIONAL_H
