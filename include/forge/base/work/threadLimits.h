#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/threadLimits.h"
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
#ifndef FORGE_BASE_WORK_THREAD_LIMITS_H
#define FORGE_BASE_WORK_THREAD_LIMITS_H

#include "forge/forge.h"
#include "forge/base/work/api.h"

FORGE_NAMESPACE_BEGIN

/// \file work/threadLimits.h

/// Return the current concurrency limit, always >= 1.
///
/// The initial value is determined by the FORGE_WORK_THREAD_LIMIT env setting,
/// which defaults to WorkGetPhysicalConcurrencyLimit(). If the env setting
/// has been explicitly set to a non-zero value, it will always override any
/// concurrency limit set via the API calls below.
///
/// Note that this can return a value larger than
/// WorkGetPhysicalConcurrencyLimit() if WorkSetConcurrencyLimit() was called
/// with such a value, or if FORGE_WORK_THREAD_LIMIT was set with such a value.
///
WORK_API unsigned WorkGetConcurrencyLimit();

/// Return the number of physical execution cores available to the program.
/// This is either the number of physical cores on the machine or the number of
/// cores specified by the process's affinity mask, whichever is smaller.
///
WORK_API unsigned WorkGetPhysicalConcurrencyLimit();

/// Set the concurrency limit to \p n, if \p n is a non-zero value.
///
/// If \p n is zero, then do not change the current concurrency limit.
///
/// Note, calling this function with n > WorkGetPhysicalConcurrencyLimit() may
/// overtax the machine.
///
/// In general, very few places should call this function.  Call it in places
/// where the number of allowed threads is dictated, for example, by a hosting
/// environment.  Lower-level library code should never call this function.
///
WORK_API void WorkSetConcurrencyLimit(unsigned n);

/// Sanitize \p n as described below and set the concurrency limit accordingly.
/// This function is useful for interpreting command line arguments.
///
/// If \p n is zero, then do not change the current concurrency limit.
///
/// If \p n is a positive, non-zero value then call WorkSetConcurrencyLimit(n).
/// Note that calling this method with \p n greater than the value returned by
/// WorkGetPhysicalConcurrencyLimit() may overtax the machine.
///
/// If \p n is negative, then set the concurrency limit to all but abs(\p n)
/// cores. The number of cores is determined by the value returned by
/// WorkGetPhysicalConcurrencyLimit().
/// For example, if \p n is -2, then use all but two cores.  If abs(\p n) is
/// greater than the number of physical cores, then call
/// WorkSetConcurrencyLimit(1), effectively disabling concurrency.
///
WORK_API void WorkSetConcurrencyLimitArgument(int n);

/// Set the concurrency limit to be the maximum recommended for the hardware
/// on which it's running.  Equivalent to:
/// \code
/// WorkSetConcurrencyLimit(WorkGetPhysicalConcurrencyLimit()).
/// \endcode
///
WORK_API void WorkSetMaximumConcurrencyLimit();

FORGE_NAMESPACE_END

#endif
