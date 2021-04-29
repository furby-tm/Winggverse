#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/timing.h"
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
#ifndef FORGE_BASE_ARCH_TIMING_H
#define FORGE_BASE_ARCH_TIMING_H

/// \file arch/timing.h
/// \ingroup group_arch_SystemFunctions
/// High-resolution, low-cost timing routines.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/defines.h"
#include "forge/base/arch/inttypes.h"

/// \addtogroup group_arch_SystemFunctions
///@{

#if defined(ARCH_OS_LINUX)
#include <x86intrin.h>
#elif defined(ARCH_OS_DARWIN)
#include <mach/mach_time.h>
#elif defined(ARCH_OS_WINDOWS)
#include <intrin.h>
#endif

FORGE_NAMESPACE_BEGIN

/// Macro that defines the clocks per second
///
/// Unfortunately, Red Hat 7.1 does not define CLK_TCK correctly, so
/// ARCH_CLK_TCK is the only guaranteed way to get the value of CLK_TCK. The
/// value is currently the same on all of our platforms.
#define ARCH_CLK_TCK 100

/// Return the current time in system-dependent units.
///
/// The current time is returned as a number of "ticks", where each tick
/// represents some system-dependent amount of time.  The resolution of the
/// timing routines varies, but on all systems, it is well under one
/// microsecond.  The cost of this routine is in the tens of nanoseconds
/// on GHz class machines.
inline uint64_t
ArchGetTickTime()
{
#if defined(ARCH_OS_DARWIN)
    // On Darwin we'll use mach_absolute_time().
    return mach_absolute_time();
#elif defined(ARCH_CPU_INTEL)
    // On Intel we'll use the rdtsc instruction.
    return __rdtsc();
#else
#error Unknown architecture.
#endif
}

/// Convert a duration measured in "ticks", as returned by
/// \c ArchGetTickTime(), to nanoseconds.
///
/// An example to test the timing routines would be:
/// \code
///     int64_t t1 = ArchGetTickTime();
///     sleep(10);
///     int64_t t2 = ArchGetTickTime();
///
///     // duration should be approximately 10/// 1e9 = 1e10 nanoseconds.
///     int64_t duration = ArchTicksToNanoseconds(t2 - t1);
/// \endcode
///
ARCH_API
int64_t ArchTicksToNanoseconds(uint64_t nTicks);

/// Convert a duration measured in "ticks", as returned by
/// \c ArchGetTickTime(), to seconds.
ARCH_API
double ArchTicksToSeconds(uint64_t nTicks);

/// Convert a duration in seconds to "ticks", as returned by
/// \c ArchGetTickTime().
ARCH_API
uint64_t ArchSecondsToTicks(double seconds);

/// Get nanoseconds per tick. Useful when converting ticks obtained from
/// \c ArchTickTime()
ARCH_API
double ArchGetNanosecondsPerTick();

///@}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_TIMING_H
