#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/garch/glPlatformContext.h"
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
#ifndef FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H
#define FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H

/// \file garch/glPlatformContext.h

#include "forge/forge.h"
#include "forge/imaging/garch/api.h"
#include "forge/base/arch/defines.h"
#include <cstddef>
#include <functional>

#if defined(ARCH_OS_LINUX)

#include "forge/imaging/garch/glPlatformContextGLX.h"

#elif defined(ARCH_OS_DARWIN)

#include "forge/imaging/garch/glPlatformContextDarwin.h"

#elif defined(ARCH_OS_WINDOWS)

#include "forge/imaging/garch/glPlatformContextWindows.h"

#else

#error "Unknown platform"

#endif

FORGE_NAMESPACE_BEGIN

GARCH_API GarchGLPlatformContextState GarchGetNullGLPlatformContextState();

FORGE_NAMESPACE_END

namespace std
{
template<>
struct hash<FORGE_NS::GarchGLPlatformContextState>
{
    inline size_t operator()(const FORGE_NS::GarchGLPlatformContextState& x) const
    {
        return x.GetHash();
    }
};
}


#endif  // FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_H
