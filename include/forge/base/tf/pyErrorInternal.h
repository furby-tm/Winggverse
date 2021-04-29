#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyErrorInternal.h"
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
#ifndef FORGE_BASE_TF_PY_ERROR_INTERNAL_H
#define FORGE_BASE_TF_PY_ERROR_INTERNAL_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyExceptionState.h"
#include <boost/python/handle.hpp>
#include <boost/python/object_fwd.hpp>

FORGE_NAMESPACE_BEGIN

enum Tf_PyExceptionErrorCode {
    TF_PYTHON_EXCEPTION
};

TF_API TfPyExceptionState Tf_PyFetchPythonExceptionState();
TF_API void Tf_PyRestorePythonExceptionState(TfPyExceptionState state);
TF_API boost::python::handle<> Tf_PyGetErrorExceptionClass();
TF_API void Tf_PySetErrorExceptionClass(boost::python::object const &cls);

/// RAII class to save and restore the Python exception state.  The client
/// must hold the GIL during all methods, including the c'tor and d'tor.
class TfPyExceptionStateScope {
public:
    // Save the current exception state but don't unset it.
    TfPyExceptionStateScope();
    TfPyExceptionStateScope(const TfPyExceptionStateScope&) = delete;
    TfPyExceptionStateScope& operator=(const TfPyExceptionStateScope&) = delete;

    // Restore the exception state as it was in the c'tor.
    ~TfPyExceptionStateScope();

    // Restore the exception state as it was in the c'tor.
    void Restore();

private:
    TfPyExceptionState _state;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_ERROR_INTERNAL_H
