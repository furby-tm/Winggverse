#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/device.h"
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
#ifndef FORGE_IMAGING_HGIGL_DEVICE_H
#define FORGE_IMAGING_HGIGL_DEVICE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/graphicsCmdsDesc.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgiGL/framebufferCache.h"
#include "forge/imaging/hgiGL/hgi.h"

#include <fstream>
#include <ostream>

FORGE_NAMESPACE_BEGIN


/// \class HgiGlDevice
///
/// OpenGL implementation of GPU device.
/// Note that there is only one global opengl context / device.
///
class HgiGLDevice final {
public:
    HGIGL_API
    HgiGLDevice();

    HGIGL_API
    ~HgiGLDevice();

    /// Get a framebuffer that matches the descriptor.
    /// Do not hold onto the framebuffer Id. Instead re-acquire it every frame.
    /// Framebuffer are internally managed in a framebuffer cache.
    ///
    /// When the cmds descriptor has resolved textures, two framebuffers are
    /// created for the MSAA and for the resolved textures. The bool flag can
    /// be used to access the respective ones.
    HGIGL_API
    uint32_t AcquireFramebuffer(
        HgiGraphicsCmdsDesc const& desc,
        bool resolved = false);

    /// Execute the provided functions / ops. This will emit the GL calls.
    HGIGL_API
    void SubmitOps(HgiGLOpsVector const& ops);

private:
    HgiGLDevice & operator=(const HgiGLDevice&) = delete;
    HgiGLDevice(const HgiGLDevice&) = delete;

    friend std::ofstream& operator<<(
        std::ofstream& out,
        const HgiGLDevice& dev);

    HgiGLFramebufferCache _framebufferCache;
};


FORGE_NAMESPACE_END

#endif
