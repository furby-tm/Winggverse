#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/testArchUtil.h"
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
#ifndef FORGE_BASE_ARCH_TEST_ARCH_UTIL_H
#define FORGE_BASE_ARCH_TEST_ARCH_UTIL_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

// Crash types.
enum class ArchTestCrashMode {
    Error,
    ReadInvalidAddresses,
    ReadInvalidAddressesWithThread
};

// Cause the test to crash deliberately.
void ArchTestCrash(ArchTestCrashMode mode);

// On Windows we can't easily fork() so we just run the test again with
// command line arguments to request a crash.
void ArchTestCrashArgParse(int argc, char** argv);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_TEST_ARCH_UTIL_H
