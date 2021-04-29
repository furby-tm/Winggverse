#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pixarDoubleConversion/cached-powers.h"
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

#ifndef DOUBLE_CONVERSION_CACHED_POWERS_H_
#define DOUBLE_CONVERSION_CACHED_POWERS_H_

#include "diy-fp.h"

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

namespace forge_double_conversion {

class PowersOfTenCache {
 public:

  // Not all powers of ten are cached. The decimal exponent of two neighboring
  // cached numbers will differ by kDecimalExponentDistance.
  static const int kDecimalExponentDistance;

  static const int kMinDecimalExponent;
  static const int kMaxDecimalExponent;

  // Returns a cached power-of-ten with a binary exponent in the range
  // [min_exponent; max_exponent] (boundaries included).
  static void GetCachedPowerForBinaryExponentRange(int min_exponent,
                                                   int max_exponent,
                                                   DiyFp* power,
                                                   int* decimal_exponent);

  // Returns a cached power of ten x ~= 10^k such that
  //   k <= decimal_exponent < k + kCachedPowersDecimalDistance.
  // The given decimal_exponent must satisfy
  //   kMinDecimalExponent <= requested_exponent, and
  //   requested_exponent < kMaxDecimalExponent + kDecimalExponentDistance.
  static void GetCachedPowerForDecimalExponent(int requested_exponent,
                                               DiyFp* power,
                                               int* found_exponent);
};

}  // namespace forge_double_conversion

FORGE_NAMESPACE_END

#endif  // DOUBLE_CONVERSION_CACHED_POWERS_H_
