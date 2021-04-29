#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/error.h"
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
#ifndef FORGE_BASE_TF_ERROR_H
#define FORGE_BASE_TF_ERROR_H

/// \file tf/error.h

#include "forge/forge.h"
#include "forge/base/tf/diagnosticBase.h"

FORGE_NAMESPACE_BEGIN

class TfDiagnosticMgr;

/// \class TfError
/// \ingroup group_tf_Diagnostic
///
/// Represents an object that contains error information.
///
/// See \ref page_tf_Diagnostic in the C++ API reference for a detailed
/// description of the error issuing API.  For a example of how to post an
/// error, see \c TF_ERROR(), also in the C++ API reference.
///
/// In the Python API, you can raise several different types of errors,
/// including coding errors (Tf.RaiseCodingError), run time errors
/// (Tf.RaiseRuntimeError), fatal errors (Tf.Fatal).
///
class TfError: public TfDiagnosticBase {

public:
    /// Return the error code posted.
    TfEnum GetErrorCode() const {
        return GetDiagnosticCode();
    }

    /// Return the diagnostic code posted as a string.
    const std::string& GetErrorCodeAsString() const {
        return GetDiagnosticCodeAsString();
    }

private:
    TfError(TfEnum errorCode, char const *errCodeString,
            TfCallContext const &context, const std::string& commentary,
            TfDiagnosticInfo info, bool quiet);

    friend class TfDiagnosticMgr;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_ERROR_H
