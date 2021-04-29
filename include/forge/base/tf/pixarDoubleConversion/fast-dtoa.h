#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pixarDoubleConversion/fast-dtoa.h"
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

#ifndef DOUBLE_CONVERSION_FAST_DTOA_H_
#define DOUBLE_CONVERSION_FAST_DTOA_H_

#include "utils.h"

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

namespace forge_double_conversion {

enum FastDtoaMode {
  // Computes the shortest representation of the given input. The returned
  // result will be the most accurate number of this length. Longer
  // representations might be more accurate.
  FAST_DTOA_SHORTEST,
  // Same as FAST_DTOA_SHORTEST but for single-precision floats.
  FAST_DTOA_SHORTEST_SINGLE,
  // Computes a representation where the precision (number of digits) is
  // given as input. The precision is independent of the decimal point.
  FAST_DTOA_PRECISION
};

// FastDtoa will produce at most kFastDtoaMaximalLength digits. This does not
// include the terminating '\0' character.
static const int kFastDtoaMaximalLength = 17;
// Same for single-precision numbers.
static const int kFastDtoaMaximalSingleLength = 9;

// Provides a decimal representation of v.
// The result should be interpreted as buffer * 10^(point - length).
//
// Precondition:
//   * v must be a strictly positive finite double.
//
// Returns true if it succeeds, otherwise the result can not be trusted.
// There will be *length digits inside the buffer followed by a null terminator.
// If the function returns true and mode equals
//   - FAST_DTOA_SHORTEST, then
//     the parameter requested_digits is ignored.
//     The result satisfies
//         v == (double) (buffer * 10^(point - length)).
//     The digits in the buffer are the shortest representation possible. E.g.
//     if 0.099999999999 and 0.1 represent the same double then "1" is returned
//     with point = 0.
//     The last digit will be closest to the actual v. That is, even if several
//     digits might correctly yield 'v' when read again, the buffer will contain
//     the one closest to v.
//   - FAST_DTOA_PRECISION, then
//     the buffer contains requested_digits digits.
//     the difference v - (buffer * 10^(point-length)) is closest to zero for
//     all possible representations of requested_digits digits.
//     If there are two values that are equally close, then FastDtoa returns
//     false.
// For both modes the buffer must be large enough to hold the result.
bool FastDtoa(double d,
              FastDtoaMode mode,
              int requested_digits,
              Vector<char> buffer,
              int* length,
              int* decimal_point);

}  // namespace forge_double_conversion

FORGE_NAMESPACE_END

#endif  // DOUBLE_CONVERSION_FAST_DTOA_H_
