#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/hints.h"
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
#ifndef FORGE_BASE_ARCH_HINTS_H
#define FORGE_BASE_ARCH_HINTS_H

#include "forge/base/arch/defines.h"

/// \file arch/hints.h
/// Compiler hints.
///
/// \c ARCH_LIKELY(bool-expr) and \c ARCH_UNLIKELY(bool-expr) will evaluate to
/// the value of bool-expr but will also emit compiler intrinsics providing
/// hints for branch prediction if the compiler has such intrinsics.  It is
/// advised that you only use these in cases where you empirically know the
/// outcome of bool-expr to a very high degree of certainty.  For example,
/// fatal-error cases, invariants, first-time initializations, etc.

#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_CLANG)

#define ARCH_LIKELY(x) (__builtin_expect((bool)(x), true))
#define ARCH_UNLIKELY(x) (__builtin_expect((bool)(x), false))

#else

#define ARCH_LIKELY(x) (x)
#define ARCH_UNLIKELY(x) (x)

#endif

#endif // FORGE_BASE_ARCH_HINTS_H
