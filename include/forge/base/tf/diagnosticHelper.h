#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/diagnosticHelper.h"
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
#ifndef FORGE_BASE_TF_DIAGNOSTIC_HELPER_H
#define FORGE_BASE_TF_DIAGNOSTIC_HELPER_H

#include "forge/forge.h"
#include "forge/base/tf/api.h"
#include "forge/base/arch/attributes.h"

// XXX: This include is a hack to avoid build errors due to
// incompatible macro definitions in pyport.h on macOS.
#include <locale>

#include <boost/any.hpp>
#include <string>

FORGE_NAMESPACE_BEGIN

typedef boost::any TfDiagnosticInfo;
class TfCallContext;
enum TfDiagnosticType : int;
class TfEnum;
class TfError;

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const std::string &msg);

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    TfDiagnosticType code,
    const std::string &msg);

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    TfDiagnosticType code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const std::string &msg);

TF_API bool
Tf_PostErrorHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(4, 5);

TF_API bool
Tf_PostQuietlyErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const TfDiagnosticInfo &info,
    const std::string &msg);

TF_API bool
Tf_PostQuietlyErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const TfDiagnosticInfo &info,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(4, 5);

TF_API bool
Tf_PostQuietlyErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const std::string &msg);

TF_API bool
Tf_PostQuietlyErrorHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);


// Helper functions for posting a warning with TF_WARN.
TF_API void
Tf_PostWarningHelper(const TfCallContext &context,
                     const std::string &msg);

TF_API void
Tf_PostWarningHelper(const TfCallContext &context,
                     const char *fmt, ...)  ARCH_PRINTF_FUNCTION(2, 3);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const std::string &msg);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    TfDiagnosticType code,
    const std::string &msg);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    TfDiagnosticType code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const std::string &msg);

TF_API void
Tf_PostWarningHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(4, 5);

TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(2, 3);

TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const std::string &msg);


TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const std::string &msg);

TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(3, 4);

TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const std::string &msg);

TF_API void
Tf_PostStatusHelper(
    const TfCallContext &context,
    const TfDiagnosticInfo &info,
    const TfEnum &code,
    const char *fmt, ...) ARCH_PRINTF_FUNCTION(4, 5);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_DIAGNOSTIC_HELPER_H
