#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/vsnprintf.h"
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
#ifndef FORGE_BASE_ARCH_VSNPRINTF_H
#define FORGE_BASE_ARCH_VSNPRINTF_H

/// \file arch/vsnprintf.h
/// \ingroup group_arch_Strings
/// Architecture dependent memory-safe sprintf capability

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/attributes.h"

#include <stdio.h>
#include <stdarg.h>
#include <string>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_arch_Strings
///@{

/// Return the number of characters (not including the null character)
/// necessary for a particular sprintf into a string.
///
/// \c ArchVsnprintf guarantees the C99 behavior of vsnprintf on all systems:
/// it returns the number of bytes (not including the terminating null
/// character) needed to actually print the requested string.  If \c size
/// indicates that \c str has enough capacity to hold the result, then the
/// function actually prints into \c str.
///
/// You probably want to use the functionality of this call via
/// \c TfStringPrintf().
///
ARCH_API
int ArchVsnprintf(char *str, size_t size, const char *format, va_list ap)
#ifndef doxygen
    ARCH_PRINTF_FUNCTION(3, 0)
#endif /* doxygen */
    ;

/// Returns a string formed by a printf()-like specification.
///
/// \c ArchStringPrintf() is a memory-safe architecture-independent way of
/// forming a string using printf()-like formatting.  For example,
/// \code
///  string formatMsg(const string& caller, int i, double val[])
///  {
///     return ArchStringPrintf("%s: val[%d] = %g\n", caller.c_str(), i, val[i]);
///  }
/// \endcode
///
/// The function is safe only to the extent that the arguments match the
/// formatting string.  In particular, be careful to pass strings themselve
/// into \c ArchStringPrintf() as in the above example (i.e. \c caller.c_str()
/// as opposed to just passing \c caller).
///
ARCH_API
std::string ArchStringPrintf(const char *fmt, ...)
#ifndef doxygen
    ARCH_PRINTF_FUNCTION(1, 2)
#endif /* doxygen */
    ;

/// Returns a string formed by a printf()-like specification.
///
/// \c ArchVStringPrintf() is equivalent to \c ArchStringPrintf() except that
/// it is called with a \c va_list instead of a variable number of arguments.
/// \c ArchVStringPrintf() does not call the \c va_end macro. Consequently,
/// the value of \c ap is undefined after the call. A functions that calls \c
/// ArchVStringPrintf() should call \c va_end(ap) itself afterwards.
///
ARCH_API
std::string ArchVStringPrintf(const char *fmt, va_list ap)
#ifndef doxygen
    ARCH_PRINTF_FUNCTION(1, 0)
    ;
#endif

/// @}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_VSNPRINTF_H
