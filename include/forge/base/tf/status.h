#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/status.h"
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
#ifndef FORGE_BASE_TF_STATUS_H
#define FORGE_BASE_TF_STATUS_H

#include "forge/forge.h"

#include "forge/base/tf/diagnosticBase.h"

FORGE_NAMESPACE_BEGIN

/// \class TfStatus
/// \ingroup group_tf_Diagnostic
///
/// Represents an object that contains information about a status message.
///
/// See \ref page_tf_Diagnostic in the C++ API reference for a detailed
/// description of the status message issuing API.  For a example of how to
/// post a status message, see \c TF_STATUS(), also in the C++ API reference.
///
/// In the Python API, you can issue a status message with Tf.Status().
///
class TfStatus: public TfDiagnosticBase
{
private:
    TfStatus(TfEnum statusCode, char const *statusCodeString,
            TfCallContext const &context, const std::string& commentary,
            TfDiagnosticInfo info, bool quiet)
        : TfDiagnosticBase(statusCode, statusCodeString, context,
                            commentary, info, quiet)
    { }

    friend class TfDiagnosticMgr;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_STATUS_H
