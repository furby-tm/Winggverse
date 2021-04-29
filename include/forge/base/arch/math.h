#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/math.h"
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
#ifndef FORGE_BASE_ARCH_MATH_H
#define FORGE_BASE_ARCH_MATH_H

/// \file arch/math.h
/// \ingroup group_arch_Math
/// Architecture-specific math function calls.

#include "forge/forge.h"
#include "forge/base/arch/defines.h"
#include "forge/base/arch/inttypes.h"

#include <cmath>
#if !defined(M_PI)
#define M_PI 3.14159265358979323846
#endif

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_arch_Math
///@{

#if defined (ARCH_CPU_INTEL) || defined (ARCH_CPU_ARM) || defined (doxygen)

/// This is the smallest value e such that 1+e^2 == 1, using floats.
/// True for all IEEE754 chipsets.
#define ARCH_MIN_FLOAT_EPS_SQR      0.000244141F

/// Three-valued sign.  Return 1 if val > 0, 0 if val == 0, or -1 if val < 0.
inline long ArchSign(long val) {
    return (val > 0) - (val < 0);
}

/// Returns The IEEE-754 bit pattern of the specified single precision value
/// as a 32-bit unsigned integer.
inline uint32_t ArchFloatToBitPattern(float v) {
    union {
        float _float;
        uint32_t _uint;
    } value;
    value._float = v;
    return value._uint;
}

/// Returns The single precision floating point value corresponding to the
/// given IEEE-754 bit pattern.
inline float ArchBitPatternToFloat(uint32_t v) {
    union {
        uint32_t _uint;
        float _float;
    } value;
    value._uint = v;
    return value._float;
}

/// Returns The IEEE-754 bit pattern of the specified double precision value
/// as a 64-bit unsigned integer.
inline uint64_t ArchDoubleToBitPattern(double v) {
    union {
        double _double;
        uint64_t _uint;
    } value;
    value._double = v;
    return value._uint;
}

/// Returns The double precision floating point value corresponding to the
/// given IEEE-754 bit pattern.
inline double ArchBitPatternToDouble(uint64_t v) {
    union {
        uint64_t _uint;
        double _double;
    } value;
    value._uint = v;
    return value._double;
}

#else
#error Unknown system architecture.
#endif

#if defined(ARCH_OS_LINUX) || defined(doxygen)

/// Computes the sine and cosine of the specified value as a float.
inline void ArchSinCosf(float v, float *s, float *c) { sincosf(v, s, c); }

/// Computes the sine and cosine of the specified value as a double.
inline void ArchSinCos(double v, double *s, double *c) { sincos(v, s, c); }

#elif defined(ARCH_OS_DARWIN) || defined(ARCH_OS_WINDOWS)

inline void ArchSinCosf(float v, float *s, float *c) {
    *s = std::sin(v);
    *c = std::cos(v);
}
inline void ArchSinCos(double v, double *s, double *c) {
    *s = std::sin(v);
    *c = std::cos(v);
}

#else
#error Unknown architecture.
#endif

///@}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_MATH_H
