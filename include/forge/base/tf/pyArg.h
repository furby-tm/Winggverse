#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyArg.h"
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
#ifndef FORGE_BASE_TF_PY_ARG_H
#define FORGE_BASE_TF_PY_ARG_H

#include "forge/forge.h"
#include "forge/base/tf/api.h"

#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class TfPyArg
///
/// Class representing a function argument.
///
/// This is similar to \c boost::python::arg, except it's not opaque and
/// provides more fields for documentation purposes.
class TfPyArg
{
public:
    /// Create a TfPyArg representing an argument with the given \p name.
    /// \p typeDoc and \p defaultValueDoc are optional documentation strings
    /// describing the expected type and default value of this argument.
    TfPyArg(const std::string& name,
            const std::string& typeDoc = std::string(),
            const std::string& defaultValueDoc = std::string())
        : _name(name), _typeDoc(typeDoc), _defaultValueDoc(defaultValueDoc)
    { }

    /// Returns argument name.
    const std::string& GetName() const
    { return _name; }

    /// Returns documentation for default value (if any) for this argument.
    const std::string& GetDefaultValueDoc() const
    { return _defaultValueDoc; }

    /// Returns documentation of type of value required by this argument.
    const std::string& GetTypeDoc() const
    { return _typeDoc; }

private:
    std::string _name;
    std::string _typeDoc;
    std::string _defaultValueDoc;
};

typedef std::vector<TfPyArg> TfPyArgs;

/// Helper function for processing optional arguments given as a tuple of
/// positional arguments and a dictionary of keyword arguments.
///
/// This function will match the given positional arguments in \p args with
/// the ordered list of allowed arguments in \p optionalArgs. Arguments that
/// are matched up in this way will be stored as (name, value) pairs and
/// merged with \p kwargs in the returned dictionary.
///
/// If \p allowExtraArgs is \c false, any unrecognized keyword or positional
/// arguments will cause a Python TypeError to be emitted. Otherwise,
/// unmatched arguments will be added to the returned tuple or dict.
TF_API
std::pair<boost::python::tuple, boost::python::dict>
TfPyProcessOptionalArgs(
    const boost::python::tuple& args,
    const boost::python::dict& kwargs,
    const TfPyArgs& expectedArgs,
    bool allowExtraArgs = false);

/// Create a doc string for a function with the given \p functionName,
/// \p requiredArguments and \p optionalArguments. An extra \p description
/// may also be supplied.
TF_API
std::string TfPyCreateFunctionDocString(
    const std::string& functionName,
    const TfPyArgs& requiredArguments = TfPyArgs(),
    const TfPyArgs& optionalArguments = TfPyArgs(),
    const std::string& description = std::string());

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_ARG_H
