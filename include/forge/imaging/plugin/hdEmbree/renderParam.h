#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/renderParam.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PARAM_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PARAM_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderDelegate.h"
#include "forge/imaging/hd/renderThread.h"

#include <embree3/rtcore.h>

FORGE_NAMESPACE_BEGIN

///
/// \class HdEmbreeRenderParam
///
/// The render delegate can create an object of type HdRenderParam, to pass
/// to each prim during Sync(). HdEmbree uses this class to pass top-level
/// embree state around.
///
class HdEmbreeRenderParam final : public HdRenderParam {
public:
    HdEmbreeRenderParam(RTCDevice device, RTCScene scene,
                        HdRenderThread *renderThread,
                        std::atomic<int> *sceneVersion)
        : _scene(scene), _device(device)
        , _renderThread(renderThread), _sceneVersion(sceneVersion)
        {}
    virtual ~HdEmbreeRenderParam() = default;

    /// Accessor for the top-level embree scene.
    RTCScene AcquireSceneForEdit() {
        _renderThread->StopRender();
        (*_sceneVersion)++;
        return _scene;
    }
    /// Accessor for the top-level embree device (library handle).
    RTCDevice GetEmbreeDevice() { return _device; }

private:
    /// A handle to the top-level embree scene.
    RTCScene _scene;
    /// A handle to the top-level embree device (library handle).
    RTCDevice _device;
    /// A handle to the global render thread.
    HdRenderThread *_renderThread;
    /// A version counter for edits to _scene.
    std::atomic<int> *_sceneVersion;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PARAM_H
