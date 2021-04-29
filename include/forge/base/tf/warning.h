#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/warning.h"
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
#ifndef FORGE_BASE_TF_WARNING_H
#define FORGE_BASE_TF_WARNING_H

#include "forge/forge.h"

#include "forge/base/tf/diagnosticBase.h"

FORGE_NAMESPACE_BEGIN

/// \class TfWarning
/// \ingroup group_tf_Diagnostic
///
/// Represents an object that contains information about a warning.
///
/// See \ref page_tf_Diagnostic in the C++ API reference for a detailed
/// description of the warning issuing API.  For a example of how to post a
/// warning, see \c TF_WARN(), also in the C++ API reference.
///
/// In the Python API, you can issue a warning with Tf.Warn().
///
class TfWarning: public TfDiagnosticBase
{
private:
    TfWarning(TfEnum warningCode, char const *warningCodeString,
            TfCallContext const &context, const std::string& commentary,
            TfDiagnosticInfo info, bool quiet)
        : TfDiagnosticBase(warningCode, warningCodeString, context,
                            commentary, info, quiet)
    { }

    friend class TfDiagnosticMgr;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_WARNING_H
