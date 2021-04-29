#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/glRawContext.h"
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
#ifndef FORGE_IMAGING_GLF_GL_RAW_CONTEXT_H
#define FORGE_IMAGING_GLF_GL_RAW_CONTEXT_H

/// \file glf/glRawContext.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/imaging/glf/glContext.h"
#include "forge/imaging/garch/glPlatformContext.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


typedef std::shared_ptr<class GlfGLRawContext> GlfGLRawContextSharedPtr;

class GlfGLRawContext : public GlfGLContext {
public:
    /// Returns a new object with the current context.
    GLF_API
    static GlfGLRawContextSharedPtr New();

    /// Returns a new object with the given state.
    GLF_API
    static GlfGLRawContextSharedPtr New(const GarchGLPlatformContextState&);

    GLF_API
    virtual ~GlfGLRawContext();

    /// Returns the held state.
    const GarchGLPlatformContextState& GetState() const { return _state; }

    // GlfGLContext overrides
    GLF_API
    virtual bool IsValid() const;

protected:
    // GlfGLContext overrides
    GLF_API
    virtual void _MakeCurrent();
    GLF_API
    virtual bool _IsSharing(const GlfGLContextSharedPtr& rhs) const;
    GLF_API
    virtual bool _IsEqual(const GlfGLContextSharedPtr& rhs) const;

private:
    GlfGLRawContext(const GarchGLPlatformContextState&);

private:
    GarchGLPlatformContextState _state;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GLF_GL_RAW_CONTEXT_H
