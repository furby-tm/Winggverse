#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/renderPass.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PASS_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PASS_H

#include "forge/forge.h"

#include "forge/imaging/hd/aov.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hd/renderThread.h"
#include "forge/imaging/plugin/hdEmbree/renderer.h"
#include "forge/imaging/plugin/hdEmbree/renderBuffer.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/rect2i.h"

#include <atomic>

FORGE_NAMESPACE_BEGIN

/// \class HdEmbreeRenderPass
///
/// HdRenderPass represents a single render iteration, rendering a view of the
/// scene (the HdRprimCollection) for a specific viewer (the camera/viewport
/// parameters in HdRenderPassState) to the current draw target.
///
/// This class does so by raycasting into the embree scene via HdEmbreeRenderer.
///
class HdEmbreeRenderPass final : public HdRenderPass
{
public:
    /// Renderpass constructor.
    ///   \param index The render index containing scene data to render.
    ///   \param collection The initial rprim collection for this renderpass.
    ///   \param renderThread A handle to the global render thread.
    ///   \param renderer A handle to the global renderer.
    HdEmbreeRenderPass(HdRenderIndex *index,
                       HdRprimCollection const &collection,
                       HdRenderThread *renderThread,
                       HdEmbreeRenderer *renderer,
                       std::atomic<int> *sceneVersion);

    /// Renderpass destructor.
    ~HdEmbreeRenderPass() override;

    // -----------------------------------------------------------------------
    // HdRenderPass API

    /// Determine whether the sample buffer has enough samples.
    ///   \return True if the image has enough samples to be considered final.
    bool IsConverged() const override;

protected:

    // -----------------------------------------------------------------------
    // HdRenderPass API

    /// Draw the scene with the bound renderpass state.
    ///   \param renderPassState Input parameters (including viewer parameters)
    ///                          for this renderpass.
    ///   \param renderTags Which rendertags should be drawn this pass.
    void _Execute(HdRenderPassStateSharedPtr const& renderPassState,
                  TfTokenVector const &renderTags) override;

    /// Update internal tracking to reflect a dirty collection.
    void _MarkCollectionDirty() override {}

private:
    // A handle to the render thread.
    HdRenderThread *_renderThread;

    // A handle to the global renderer.
    HdEmbreeRenderer *_renderer;

    // A reference to the global scene version.
    std::atomic<int> *_sceneVersion;

    // The last scene version we rendered with.
    int _lastSceneVersion;

    // The last settings version we rendered with.
    int _lastSettingsVersion;

    // The pixels written to. Like viewport in OpenGL,
    // but coordinates are y-Down.
    GfRect2i _dataWindow;

    // The view matrix: world space to camera space
    GfMatrix4d _viewMatrix;
    // The projection matrix: camera space to NDC space (with
    // respect to the data window).
    GfMatrix4d _projMatrix;

    // The list of aov buffers this renderpass should write to.
    HdRenderPassAovBindingVector _aovBindings;

    // If no attachments are provided, provide an anonymous renderbuffer for
    // color and depth output.
    HdEmbreeRenderBuffer _colorBuffer;
    HdEmbreeRenderBuffer _depthBuffer;

    // Were the color/depth buffer converged the last time we blitted them?
    bool _converged;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDER_PASS_H
