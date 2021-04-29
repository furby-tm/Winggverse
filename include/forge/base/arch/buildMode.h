#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/buildMode.h"
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
#ifndef FORGE_BASE_ARCH_BUILD_MODE_H
#define FORGE_BASE_ARCH_BUILD_MODE_H

#include "forge/forge.h"
#include "forge/base/arch/defines.h"

FORGE_NAMESPACE_BEGIN

struct ArchBuildMode {
// Check if the build system has specified a build mode, falling
// back to commonly-used macros if it has not. (Typically, _DEBUG
// is defined by Visual Studio and DEBUG by Xcode for debug-mode builds)
#if defined(BUILD_OPTLEVEL_DEV) || defined(_DEBUG) || defined(DEBUG)
    enum { DEV_BUILD = 1 };
#else
    enum { DEV_BUILD = 0 };
#endif
};

#define ARCH_DEV_BUILD ArchBuildMode::DEV_BUILD

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_BUILD_MODE_H
