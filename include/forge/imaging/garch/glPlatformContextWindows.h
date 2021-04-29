#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/garch/glPlatformContextWindows.h"
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
#ifndef FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_WINDOWS_H
#define FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_WINDOWS_H

#include "forge/forge.h"
#include "forge/imaging/garch/api.h"
#include <memory>

FORGE_NAMESPACE_BEGIN


class GarchWGLContextState {
public:
    /// Construct with the current state.
    GARCH_API
    GarchWGLContextState();

    enum class NullState { nullstate };

    /// Construct with the null state.
    GARCH_API
    GarchWGLContextState(NullState);

    /// Compare for equality.
    GARCH_API
    bool operator==(const GarchWGLContextState& rhs) const;

    /// Returns a hash value for the state.
    GARCH_API
    size_t GetHash() const;

    /// Returns \c true if the context state is valid.
    GARCH_API
    bool IsValid() const;

    /// Make the context current.
    GARCH_API
    void MakeCurrent();

    /// Make no context current.
    GARCH_API
    static void DoneCurrent();

private:
    class _Detail;
    std::shared_ptr<_Detail> _detail;
};

// Hide the platform specific type name behind a common name.
typedef GarchWGLContextState GarchGLPlatformContextState;


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GARCH_GL_PLATFORM_CONTEXT_WINDOWS_H
