#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/garch/glPlatformDebugContext.h"
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
#ifndef FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_CONTEXT_H
#define FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_CONTEXT_H

#include "forge/forge.h"
#include "forge/imaging/garch/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/weakBase.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


class GarchGLPlatformDebugContextPrivate;

TF_DECLARE_WEAK_AND_REF_PTRS(GarchGLPlatformDebugContext);

/// \class GarchGLPlatformDebugContext
///
/// Platform specific context (e.g. X11/GLX) which supports debug output.
///
class GarchGLPlatformDebugContext : public TfRefBase, public TfWeakBase {
public:

    static GarchGLPlatformDebugContextRefPtr
    New(int majorVersion, int minorVersion, bool coreProfile,
        bool directRenderering) {
        return TfCreateRefPtr(
            new GarchGLPlatformDebugContext(
                majorVersion, minorVersion, coreProfile, directRenderering));
    }

    virtual ~GarchGLPlatformDebugContext();

    GARCH_API
    static bool IsEnabledDebugOutput();

    GARCH_API
    static bool IsEnabledCoreProfile();

    GARCH_API
    void makeCurrent();

    GARCH_API
    void *chooseMacVisual();

public:
    std::unique_ptr<GarchGLPlatformDebugContextPrivate> _private;
    bool _coreProfile;

protected:
    GARCH_API
    GarchGLPlatformDebugContext(int majorVersion,
                               int minorVersion,
                               bool coreProfile,
                               bool directRenderering);

};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_CONTEXT_H
