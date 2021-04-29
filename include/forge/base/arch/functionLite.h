#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/functionLite.h"
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
#ifndef FORGE_BASE_ARCH_FUNCTION_LITE_H
#define FORGE_BASE_ARCH_FUNCTION_LITE_H

/// \file arch/functionLite.h
/// Define preprocessor function name macros.
///
/// This file defines preprocessor macros for getting the current function
/// name and related information so they can be used in a architecture
/// independent manner.  This file needs to be public but shouldn't be
/// included directly by anything outside of \c forge/base/tf.

#include "forge/base/arch/defines.h"
// Note: this file specifically does not include <string>.

#define __ARCH_FUNCTION__ __func__

#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_ICC) || \
    defined(ARCH_COMPILER_CLANG)
#    define __ARCH_PRETTY_FUNCTION__ __PRETTY_FUNCTION__
#elif defined(ARCH_COMPILER_MSVC)
#    define __ARCH_PRETTY_FUNCTION__ __FUNCSIG__
#else
#    define __ARCH_PRETTY_FUNCTION__ __ARCH_FUNCTION__
#endif /* defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_ICC) ||
          defined(ARCH_COMPILER_CLANG)*/

#if defined(BUILD_COMPONENT_SRC_PREFIX)
#    define __ARCH_FILE__ BUILD_COMPONENT_SRC_PREFIX __FILE__
#else
#    define __ARCH_FILE__ __FILE__
#endif /* defined(BUILD_COMPONENT_SRC_PREFIX) */

#endif // FORGE_BASE_ARCH_FUNCTION_LITE_H
