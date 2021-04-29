#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/glContextRegistry.h"
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
#ifndef FORGE_IMAGING_GLF_GL_CONTEXT_REGISTRY_H
#define FORGE_IMAGING_GLF_GL_CONTEXT_REGISTRY_H

/// \file glf/glContextRegistry.h

#include "forge/forge.h"
#include "forge/imaging/glf/glContext.h"
#include "forge/base/tf/singleton.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN


struct GlfGLContextRegistry_Data;

typedef std::shared_ptr<class GlfGLContext> GlfGLContextSharedPtr;

/// \class GlfGLContextRegistry
///
/// Registry of GlfGLContexts.
///
class GlfGLContextRegistry
{
public:
    static GlfGLContextRegistry& GetInstance()
    {
        return TfSingleton<GlfGLContextRegistry>::GetInstance();
    }

    /// Returns whether the registry has any registered interfaces.
    bool IsInitialized() const;

    /// Add a registration object to the registry.  This takes ownership
    /// of the object.
    void Add(GlfGLContextRegistrationInterface*);

    /// Returns the shared context, if any.
    GlfGLContextSharedPtr GetShared();

    /// Returns the context that matches the raw context, if any.
    GlfGLContextSharedPtr GetCurrent();

    /// Registers this context.  It must be current.
    void DidMakeCurrent(const GlfGLContextSharedPtr& context);

    /// Removes the context.
    void Remove(const GlfGLContext* context);

private:
    GlfGLContextRegistry();
    ~GlfGLContextRegistry();

    // Non-copyable
    GlfGLContextRegistry(const GlfGLContextRegistry &) = delete;
    GlfGLContextRegistry &operator=(const GlfGLContextRegistry &) = delete;

    friend class TfSingleton<GlfGLContextRegistry>;

private:
    std::vector<std::unique_ptr<GlfGLContextRegistrationInterface>> _interfaces;
    bool _sharedContextInitialized;
    GlfGLContextSharedPtr _shared;
    std::unique_ptr<GlfGLContextRegistry_Data> _data;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GLF_GL_CONTEXT_REGISTRY_H
