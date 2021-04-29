#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pixarDoubleConversion/fixed-dtoa.h"
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

#ifndef DOUBLE_CONVERSION_FIXED_DTOA_H_
#define DOUBLE_CONVERSION_FIXED_DTOA_H_

#include "utils.h"

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

namespace forge_double_conversion {

// Produces digits necessary to print a given number with
// 'fractional_count' digits after the decimal point.
// The buffer must be big enough to hold the result plus one terminating null
// character.
//
// The produced digits might be too short in which case the caller has to fill
// the gaps with '0's.
// Example: FastFixedDtoa(0.001, 5, ...) is allowed to return buffer = "1", and
// decimal_point = -2.
// Halfway cases are rounded towards +/-Infinity (away from 0). The call
// FastFixedDtoa(0.15, 2, ...) thus returns buffer = "2", decimal_point = 0.
// The returned buffer may contain digits that would be truncated from the
// shortest representation of the input.
//
// This method only works for some parameters. If it can't handle the input it
// returns false. The output is null-terminated when the function succeeds.
bool FastFixedDtoa(double v, int fractional_count,
                   Vector<char> buffer, int* length, int* decimal_point);

}  // namespace forge_double_conversion

FORGE_NAMESPACE_END

#endif  // DOUBLE_CONVERSION_FIXED_DTOA_H_
