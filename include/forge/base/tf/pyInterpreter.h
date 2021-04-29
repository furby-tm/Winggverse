#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyInterpreter.h"
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
#ifndef FORGE_BASE_TF_PY_INTERPRETER_H
#define FORGE_BASE_TF_PY_INTERPRETER_H

/// \file tf/pyInterpreter.h
/// Python runtime utilities.

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>
#include <string>

FORGE_NAMESPACE_BEGIN

/// Starts up the python runtime.
/// IMPORTANT: The GIL will NOT be held when this returns.
/// (If Python is already initialized, the GIL will be unchanged)
///
/// The program name and arguments are set automatically. sys.argv has no
/// arguments other than an argv[0] matching the program name.
TF_API
extern void TfPyInitialize(void);

/// Runs the given string using PyRun_SimpleString().
///
/// Starts the interpreter if necessary. Deals with necessary thread state
/// setup.
TF_API
extern int TfPyRunSimpleString(const std::string & cmd);

/// Runs the given string using PyRun_String().
///
/// \a start is Py_eval_input, Py_single_input or Py_file_input.
/// \a globals and locals can be dictionaries to use when evaluating the
///    string in python. Defaults to reusing globals from main module. If
///    only the globals are provided, they will also be used as locals.
///
/// Starts the interpreter if necessary. Deals with necessary thread state
/// setup.
TF_API
extern boost::python::handle<>
TfPyRunString(const std::string & cmd, int start,
              boost::python::object const &globals = boost::python::object(),
              boost::python::object const &locals = boost::python::object()
              );

/// Runs the given file using PyRun_File().
///
/// \a start is Py_eval_input, Py_single_input or Py_file_input.
/// \a globals and locals can be dictionaries to use when evaluating the
///    string in python. Defaults to reusing globals from main module. If
///    only the globals are provided, they will also be used as locals.
///
/// Starts the interpreter if necessary. Deals with necessary thread state
/// setup.
TF_API
extern boost::python::handle<>
TfPyRunFile(const std::string &filename, int start,
            boost::python::object const &globals = boost::python::object(),
            boost::python::object const &locals = boost::python::object()
            );

/// Returns the disk path to the given module as an NSString.
///
/// Starts the interpreter if necessary. Deals with necessary thread state
/// setup.
TF_API
extern std::string TfPyGetModulePath(const std::string & moduleName);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_INTERPRETER_H
