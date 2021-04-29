#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/py3Compat.h"
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
#ifndef FORGE_BASE_TF_PY_3_COMPAT_H
#define FORGE_BASE_TF_PY_3_COMPAT_H

/// \file tf/py3Compat.h
/// Compatibility code for supporting python 2 and 3

#include "forge/forge.h"

#include "forge/base/tf/pySafePython.h"

FORGE_NAMESPACE_BEGIN

// Python 3 migrating helpers:
#if PY_MAJOR_VERSION >= 3

// These flags are needed in python 2 only, stub them out in python 3.
// In python 3 this behavior is the default. See PEP-3118
#define TfPy_TPFLAGS_HAVE_NEWBUFFER 0
#define TfPy_TPFLAGS_HAVE_GETCHARBUFFER 0

#define TfPyString_Check(a) (PyBytes_Check(a) || PyUnicode_Check(a))
#define TfPyString_AsString PyUnicode_AsUTF8

// PyInt -> PyLong remapping
#define TfPyInt_Check PyLong_Check
// Note: Slightly different semantics, the macro does not do any error checking
#define TfPyInt_AS_LONG PyLong_AsLong

// Method and module names that are changed in python 3
#define TfPyIteratorNextMethodName "__next__"
#define TfPyClassMethodFuncName "__func__"
#define TfPyBoolBuiltinFuncName "__bool__"
#define TfPyBuiltinModuleName "builtins"

#else // Python 2

#define TfPy_TPFLAGS_HAVE_NEWBUFFER Py_TPFLAGS_HAVE_NEWBUFFER
#define TfPy_TPFLAGS_HAVE_GETCHARBUFFER Py_TPFLAGS_HAVE_GETCHARBUFFER

#define TfPyInt_Check PyInt_Check
#define TfPyInt_AS_LONG PyInt_AS_LONG

#define TfPyIteratorNextMethodName "next"
#define TfPyClassMethodFuncName "im_func"
#define TfPyBoolBuiltinFuncName "__nonzero__"
#define TfPyBuiltinModuleName "__builtin__"

#define TfPyString_AsString PyString_AsString
#define TfPyString_Check PyString_Check

#endif

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_3_COMPAT_H
