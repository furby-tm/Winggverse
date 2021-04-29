#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/pyResolverContext_v1.h"
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
#ifndef INCLUDE_AR_PY_RESOLVER_CONTEXT
#error This file should not be included directly. Include pyResolverContext.h instead
#endif

#ifndef FORGE_USD_AR_PY_RESOLVER_CONTEXT_V1_H
#define FORGE_USD_AR_PY_RESOLVER_CONTEXT_V1_H

/// \file ar/pyResolverContext_v1.h
/// Macros for creating Python bindings for objects used with
/// ArResolverContext.

#include "forge/base/tf/pySafePython.h"

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/usd/ar/resolverContext.h"

#include "forge/base/tf/pyLock.h"
#include "forge/base/tf/pyObjWrapper.h"

#include <functional>

FORGE_NAMESPACE_BEGIN

/// Register the specified type as a context object that may be
/// converted from a Python into a ArResolverContext object
/// in C++ and vice versa. This typically would be called in the
/// source file where the Python wrapping for the context object
/// is defined.
template <class Context>
void
ArWrapResolverContextForPython();

#ifndef doxygen
// Private helper functions for converting ArResolverContext
// objects to and from Python.

template <class Context>
bool
Ar_ConvertResolverContextFromPython(
    PyObject* obj,
    ArResolverContext* context)
{
    boost::python::extract<const Context&> x(obj);
    if (x.check()) {
        if (context) {
            *context = ArResolverContext(x());
        }
        return true;
    }
    return false;
}

template <class Context>
bool
Ar_ConvertResolverContextToPython(
    const ArResolverContext& context,
    TfPyObjWrapper* obj)
{
    if (const Context* contextObj = context.Get<Context>()) {
        if (obj) {
            TfPyLock lock;
            *obj = boost::python::object(*contextObj);
        }
        return true;
    }
    return false;
}

typedef std::function<bool(PyObject*, ArResolverContext*)>
    Ar_MakeResolverContextFromPythonFn;
typedef std::function<bool(const ArResolverContext&, TfPyObjWrapper*)>
    Ar_ResolverContextToPythonFn;

AR_API
void
Ar_RegisterResolverContextPythonConversion(
    const Ar_MakeResolverContextFromPythonFn& convertFunc,
    const Ar_ResolverContextToPythonFn& getObjectFunc);

AR_API
bool
Ar_CanConvertResolverContextFromPython(PyObject* pyObj);

AR_API
ArResolverContext
Ar_ConvertResolverContextFromPython(PyObject* pyObj);

AR_API
TfPyObjWrapper
Ar_ConvertResolverContextToPython(const ArResolverContext& context);

template <class Context>
void
ArWrapResolverContextForPython()
{
    Ar_RegisterResolverContextPythonConversion(
        Ar_ConvertResolverContextFromPython<Context>,
        Ar_ConvertResolverContextToPython<Context>);
};

#endif //doxygen

FORGE_NAMESPACE_END

#endif
