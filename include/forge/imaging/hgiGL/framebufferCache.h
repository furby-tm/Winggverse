#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/framebufferCache.h"
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
#ifndef FORGE_IMAGING_HGI_GL_FRAMEBUFFER_CACHE_H
#define FORGE_IMAGING_HGI_GL_FRAMEBUFFER_CACHE_H

#include <ostream>
#include <fstream>
#include <vector>

#include "forge/forge.h"
#include "forge/imaging/hgi/graphicsCmdsDesc.h"
#include "forge/imaging/hgiGL/api.h"

FORGE_NAMESPACE_BEGIN

using HgiGLDescriptorCacheVec = std::vector<struct HgiGLDescriptorCacheItem*>;


/// \class HgiGLFramebufferCache
///
/// Manages a cache of framebuffers based on graphics cmds descriptors.
///
class HgiGLFramebufferCache final
{
public:
    HGIGL_API
    HgiGLFramebufferCache();

    HGIGL_API
    ~HgiGLFramebufferCache();

    /// Get a framebuffer that matches the descriptor.
    /// If the framebuffer exists in the cache, it will be returned.
    /// If none exist that match the descriptor, it will be created.
    /// Do not hold onto the returned id. Re-acquire it every frame.
    ///
    /// When the cmds descriptor has resolved textures, two framebuffers are
    /// created for the MSAA and for the resolved textures. The bool flag can
    /// be used to access the respective ones.
    HGIGL_API
    uint32_t AcquireFramebuffer(HgiGraphicsCmdsDesc const& desc,
                                bool resolved = false);

    /// Clears all framebuffersfrom cache.
    /// This should generally only be called when the device is being destroyed.
    HGIGL_API
    void Clear();

private:
    friend std::ostream& operator<<(
        std::ostream& out,
        const HgiGLFramebufferCache& fbc);

    HgiGLDescriptorCacheVec _descriptorCache;
};


FORGE_NAMESPACE_END

#endif
