#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImagingGL/engine.h"
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

/// \file usdImagingGL/engine.h

#ifndef FORGE_USD_IMAGING_USD_IMAGING_GL_ENGINE_H
#define FORGE_USD_IMAGING_USD_IMAGING_GL_ENGINE_H

#include "forge/forge.h"
#include "forge/usdImaging/usdImagingGL/api.h"
#include "forge/usdImaging/usdImagingGL/version.h"
#include "forge/usdImaging/usdImaging/version.h"

#include "forge/usdImaging/usdImagingGL/renderParams.h"
#include "forge/usdImaging/usdImagingGL/rendererSettings.h"

#include "forge/imaging/cameraUtil/conformWindow.h"

#include "forge/imaging/hd/driver.h"
#include "forge/imaging/hd/engine.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hd/pluginRenderDelegateUniqueHandle.h"

#include "forge/imaging/hdx/selectionTracker.h"
#include "forge/imaging/hdx/renderSetupTask.h"

#include "forge/imaging/hgi/hgi.h"

#include "forge/imaging/glf/simpleLight.h"
#include "forge/imaging/glf/simpleMaterial.h"

#include "forge/imaging/hgi/hgi.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/usd/timeCode.h"

#include "forge/base/gf/frustum.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/gf/vec4i.h"

#include "forge/base/vt/dictionary.h"

#include "forge/base/tf/declarePtrs.h"

FORGE_NAMESPACE_BEGIN

class UsdPrim;
class HdRenderIndex;
class HdxTaskController;
class UsdImagingDelegate;
class UsdImagingGLLegacyEngine;

TF_DECLARE_WEAK_AND_REF_PTRS(GlfSimpleLightingContext);

/// \class UsdImagingGLEngine
///
/// The UsdImagingGLEngine is the main entry point API for rendering USD scenes.
///
class UsdImagingGLEngine
{
public:

    // ---------------------------------------------------------------------
    /// \name Global State
    /// @{
    // ---------------------------------------------------------------------

    /// Returns true if Hydra is enabled for GL drawing.
    USDIMAGINGGL_API
    static bool IsHydraEnabled();

    /// @}

    // ---------------------------------------------------------------------
    /// \name Construction
    /// @{
    // ---------------------------------------------------------------------

    /// A HdDriver, containing the Hgi of your choice, can be optionally passed
    /// in during construction. This can be helpful if you application creates
    /// multiple UsdImagingGLEngine that wish to use the same HdDriver / Hgi.
    USDIMAGINGGL_API
    UsdImagingGLEngine(const HdDriver& driver = HdDriver());

    USDIMAGINGGL_API
    UsdImagingGLEngine(const SdfPath& rootPath,
                       const SdfPathVector& excludedPaths,
                       const SdfPathVector& invisedPaths=SdfPathVector(),
                       const SdfPath& sceneDelegateID =
                                        SdfPath::AbsoluteRootPath(),
                       const HdDriver& driver = HdDriver());

    // Disallow copies
    UsdImagingGLEngine(const UsdImagingGLEngine&) = delete;
    UsdImagingGLEngine& operator=(const UsdImagingGLEngine&) = delete;

    USDIMAGINGGL_API
    ~UsdImagingGLEngine();

    /// @}

    // ---------------------------------------------------------------------
    /// \name Rendering
    /// @{
    // ---------------------------------------------------------------------

    /// Support for batched drawing
    USDIMAGINGGL_API
    void PrepareBatch(const UsdPrim& root,
                      const UsdImagingGLRenderParams& params);
    USDIMAGINGGL_API
    void RenderBatch(const SdfPathVector& paths,
                     const UsdImagingGLRenderParams& params);

    /// Entry point for kicking off a render
    USDIMAGINGGL_API
    void Render(const UsdPrim& root,
                const UsdImagingGLRenderParams &params);

    /// Returns true if the resulting image is fully converged.
    /// (otherwise, caller may need to call Render() again to refine the result)
    USDIMAGINGGL_API
    bool IsConverged() const;

    /// @}

    // ---------------------------------------------------------------------
    /// \name Root Transform and Visibility
    /// @{
    // ---------------------------------------------------------------------

    /// Sets the root transform.
    USDIMAGINGGL_API
    void SetRootTransform(GfMatrix4d const& xf);

    /// Sets the root visibility.
    USDIMAGINGGL_API
    void SetRootVisibility(bool isVisible);

    /// @}

    // ---------------------------------------------------------------------
    /// \name Camera State
    /// @{
    // ---------------------------------------------------------------------

    /// Scene camera API
    /// Set the scene camera path to use for rendering.
    USDIMAGINGGL_API
    void SetCameraPath(SdfPath const& id);

    /// Determines how the filmback of the camera is mapped into
    /// the pixels of the render buffer and what pixels of the render
    /// buffer will be rendered into.
    USDIMAGINGGL_API
    void SetFraming(CameraUtilFraming const& framing);

    /// Specifies whether to force a window policy when conforming
    /// the frustum of the camera to match the display window of
    /// the camera framing.
    ///
    /// If set to {false, ...}, the window policy of the specified camera
    /// will be used.
    ///
    /// Note: std::pair<bool, ...> is used instead of std::optional<...>
    /// because the latter is only available in C++17 or later.
    USDIMAGINGGL_API
    void SetOverrideWindowPolicy(
        const std::pair<bool, CameraUtilConformWindowPolicy> &policy);

    /// Set the size of the render buffers baking the AOVs.
    /// GUI applications should set this to the size of the window.
    ///
    USDIMAGINGGL_API
    void SetRenderBufferSize(GfVec2i const& size);

    /// Set the viewport to use for rendering as (x,y,w,h), where (x,y)
    /// represents the lower left corner of the viewport rectangle, and (w,h)
    /// is the width and height of the viewport in pixels.
    ///
    /// \deprecated Use SetFraming and SetRenderBufferSize instead.
    USDIMAGINGGL_API
    void SetRenderViewport(GfVec4d const& viewport);

    /// Set the window policy to use.
    /// XXX: This is currently used for scene cameras set via SetCameraPath.
    /// See comment in SetCameraState for the free cam.
    USDIMAGINGGL_API
    void SetWindowPolicy(CameraUtilConformWindowPolicy policy);

    /// Free camera API
    /// Set camera framing state directly (without pointing to a camera on the
    /// USD stage). The projection matrix is expected to be pre-adjusted for the
    /// window policy.
    USDIMAGINGGL_API
    void SetCameraState(const GfMatrix4d& viewMatrix,
                        const GfMatrix4d& projectionMatrix);

    /// Helper function to extract camera and viewport state from opengl and
    /// then call SetCameraState and SetRenderViewport
    USDIMAGINGGL_API
    void SetCameraStateFromOpenGL();

    /// @}

    // ---------------------------------------------------------------------
    /// \name Light State
    /// @{
    // ---------------------------------------------------------------------

    /// Helper function to extract lighting state from opengl and then
    /// call SetLights.
    USDIMAGINGGL_API
    void SetLightingStateFromOpenGL();

    /// Copy lighting state from another lighting context.
    USDIMAGINGGL_API
    void SetLightingState(GlfSimpleLightingContextPtr const &src);

    /// Set lighting state
    /// Derived classes should ensure that passing an empty lights
    /// vector disables lighting.
    /// \param lights is the set of lights to use, or empty to disable lighting.
    USDIMAGINGGL_API
    void SetLightingState(GlfSimpleLightVector const &lights,
                          GlfSimpleMaterial const &material,
                          GfVec4f const &sceneAmbient);

    /// @}

    // ---------------------------------------------------------------------
    /// \name Selection Highlighting
    /// @{
    // ---------------------------------------------------------------------

    /// Sets (replaces) the list of prim paths that should be included in
    /// selection highlighting. These paths may include root paths which will
    /// be expanded internally.
    USDIMAGINGGL_API
    void SetSelected(SdfPathVector const& paths);

    /// Clear the list of prim paths that should be included in selection
    /// highlighting.
    USDIMAGINGGL_API
    void ClearSelected();

    /// Add a path with instanceIndex to the list of prim paths that should be
    /// included in selection highlighting. UsdImagingDelegate::ALL_INSTANCES
    /// can be used for highlighting all instances if path is an instancer.
    USDIMAGINGGL_API
    void AddSelected(SdfPath const &path, int instanceIndex);

    /// Sets the selection highlighting color.
    USDIMAGINGGL_API
    void SetSelectionColor(GfVec4f const& color);

    /// @}

    // ---------------------------------------------------------------------
    /// \name Picking
    /// @{
    // ---------------------------------------------------------------------

    /// Finds closest point of intersection with a frustum by rendering.
    ///
    /// This method uses a PickRender and a customized depth buffer to find an
    /// approximate point of intersection by rendering. This is less accurate
    /// than implicit methods or rendering with GL_SELECT, but leverages any
    /// data already cached in the renderer.
    ///
    /// Returns whether a hit occurred and if so, \p outHitPoint will contain
    /// the intersection point in world space (i.e. \p projectionMatrix and
    /// \p viewMatrix factored back out of the result), and \p outHitNormal
    /// will contain the world space normal at that point.
    ///
    /// \p outHitPrimPath will point to the gprim selected by the pick.
    /// \p outHitInstancerPath will point to the point instancer (if applicable)
    /// of that gprim. For nested instancing, outHitInstancerPath points to
    /// the closest instancer.
    ///
    USDIMAGINGGL_API
    bool TestIntersection(
        const GfMatrix4d &viewMatrix,
        const GfMatrix4d &projectionMatrix,
        const UsdPrim& root,
        const UsdImagingGLRenderParams &params,
        GfVec3d *outHitPoint,
        GfVec3d *outHitNormal,
        SdfPath *outHitPrimPath = NULL,
        SdfPath *outHitInstancerPath = NULL,
        int *outHitInstanceIndex = NULL,
        HdInstancerContext *outInstancerContext = NULL);

    /// Decodes a pick result given hydra prim ID/instance ID (like you'd get
    /// from an ID render).
    USDIMAGINGGL_API
    bool DecodeIntersection(
        unsigned char const primIdColor[4],
        unsigned char const instanceIdColor[4],
        SdfPath *outHitPrimPath = NULL,
        SdfPath *outHitInstancerPath = NULL,
        int *outHitInstanceIndex = NULL,
        HdInstancerContext *outInstancerContext = NULL);

    /// @}

    // ---------------------------------------------------------------------
    /// \name Renderer Plugin Management
    /// @{
    // ---------------------------------------------------------------------

    /// Return the vector of available render-graph delegate plugins.
    USDIMAGINGGL_API
    static TfTokenVector GetRendererPlugins();

    /// Return the user-friendly description of a renderer plugin.
    USDIMAGINGGL_API
    static std::string GetRendererDisplayName(TfToken const &id);

    /// Return the id of the currently used renderer plugin.
    USDIMAGINGGL_API
    TfToken GetCurrentRendererId() const;

    /// Set the current render-graph delegate to \p id.
    /// the plugin will be loaded if it's not yet.
    USDIMAGINGGL_API
    bool SetRendererPlugin(TfToken const &id);

    /// @}

    // ---------------------------------------------------------------------
    /// \name AOVs and Renderer Settings
    /// @{
    // ---------------------------------------------------------------------

    /// Return the vector of available renderer AOV settings.
    USDIMAGINGGL_API
    TfTokenVector GetRendererAovs() const;

    /// Set the current renderer AOV to \p id.
    USDIMAGINGGL_API
    bool SetRendererAov(TfToken const& id);

    /// Returns an AOV texture handle for the given token.
    USDIMAGINGGL_API
    HgiTextureHandle GetAovTexture(TfToken const& name) const;

    /// Returns the list of renderer settings.
    USDIMAGINGGL_API
    UsdImagingGLRendererSettingsList GetRendererSettingsList() const;

    /// Gets a renderer setting's current value.
    USDIMAGINGGL_API
    VtValue GetRendererSetting(TfToken const& id) const;

    /// Sets a renderer setting's value.
    USDIMAGINGGL_API
    void SetRendererSetting(TfToken const& id,
                            VtValue const& value);

    /// Enable / disable presenting the render to bound framebuffer.
    /// An application may choose to manage the AOVs that are rendered into
    /// itself and skip the engine's presentation.
    USDIMAGINGGL_API
    void SetEnablePresentation(bool enabled);

    /// The destination API (e.g., OpenGL, see hgiInterop for details) and
    /// framebuffer that the AOVs are presented into. The framebuffer
    /// is a VtValue that encoding a framebuffer in a destination API
    /// specific way.
    /// E.g., a uint32_t (aka GLuint) for framebuffer object for OpenGL.
    USDIMAGINGGL_API
    void SetPresentationOutput(TfToken const &api, VtValue const &framebuffer);

    /// @}

    // ---------------------------------------------------------------------
    /// \name Control of background rendering threads.
    /// @{
    // ---------------------------------------------------------------------

    /// Query the renderer as to whether it supports pausing and resuming.
    USDIMAGINGGL_API
    bool IsPauseRendererSupported() const;

    /// Pause the renderer.
    ///
    /// Returns \c true if successful.
    USDIMAGINGGL_API
    bool PauseRenderer();

    /// Resume the renderer.
    ///
    /// Returns \c true if successful.
    USDIMAGINGGL_API
    bool ResumeRenderer();

    /// Query the renderer as to whether it supports stopping and restarting.
    USDIMAGINGGL_API
    bool IsStopRendererSupported() const;

    /// Stop the renderer.
    ///
    /// Returns \c true if successful.
    USDIMAGINGGL_API
    bool StopRenderer();

    /// Restart the renderer.
    ///
    /// Returns \c true if successful.
    USDIMAGINGGL_API
    bool RestartRenderer();

    /// @}

    // ---------------------------------------------------------------------
    /// \name Color Correction
    /// @{
    // ---------------------------------------------------------------------

    /// Set \p id to one of the HdxColorCorrectionTokens.
    USDIMAGINGGL_API
    void SetColorCorrectionSettings(
        TfToken const& id);

    /// @}

    /// Returns true if the platform is color correction capable.
    USDIMAGINGGL_API
    static bool IsColorCorrectionCapable();

    // ---------------------------------------------------------------------
    /// \name Render Statistics
    /// @{
    // ---------------------------------------------------------------------

    /// Returns render statistics.
    ///
    /// The contents of the dictionary will depend on the current render
    /// delegate.
    ///
    USDIMAGINGGL_API
    VtDictionary GetRenderStats() const;

    /// @}

    // ---------------------------------------------------------------------
    /// \name HGI
    /// @{
    // ---------------------------------------------------------------------

    /// Returns the HGI interface.
    ///
    USDIMAGINGGL_API
    Hgi* GetHgi();

    /// @}

protected:

    /// Open some protected methods for whitebox testing.
    friend class UsdImagingGL_UnitTestGLDrawing;

    /// Returns the render index of the engine, if any.  This is only used for
    /// whitebox testing.
    USDIMAGINGGL_API
    HdRenderIndex *_GetRenderIndex() const;

    USDIMAGINGGL_API
    void _Execute(const UsdImagingGLRenderParams &params,
                  HdTaskSharedPtrVector tasks);

    USDIMAGINGGL_API
    bool _CanPrepare(const UsdPrim& root);
    USDIMAGINGGL_API
    void _PreSetTime(const UsdImagingGLRenderParams& params);
    USDIMAGINGGL_API
    void _PostSetTime(const UsdImagingGLRenderParams& params);

    USDIMAGINGGL_API
    void _PrepareRender(const UsdImagingGLRenderParams& params);

    // Create a hydra collection given root paths and render params.
    // Returns true if the collection was updated.
    USDIMAGINGGL_API
    static bool _UpdateHydraCollection(HdRprimCollection *collection,
                          SdfPathVector const& roots,
                          UsdImagingGLRenderParams const& params);
    USDIMAGINGGL_API
    static HdxRenderTaskParams _MakeHydraUsdImagingGLRenderParams(
                          UsdImagingGLRenderParams const& params);
    USDIMAGINGGL_API
    static void _ComputeRenderTags(UsdImagingGLRenderParams const& params,
                          TfTokenVector *renderTags);

    USDIMAGINGGL_API
    void _InitializeHgiIfNecessary();

    USDIMAGINGGL_API
    void _SetRenderDelegateAndRestoreState(
        HdPluginRenderDelegateUniqueHandle &&);

    USDIMAGINGGL_API
    void _SetRenderDelegate(HdPluginRenderDelegateUniqueHandle &&);

    USDIMAGINGGL_API
    SdfPath _ComputeControllerPath(const HdPluginRenderDelegateUniqueHandle &);

    USDIMAGINGGL_API
    static TfToken _GetDefaultRendererPluginId();

    USDIMAGINGGL_API
    UsdImagingDelegate *_GetSceneDelegate() const;

    USDIMAGINGGL_API
    HdEngine *_GetHdEngine();

    USDIMAGINGGL_API
    HdxTaskController *_GetTaskController() const;

    USDIMAGINGGL_API
    bool _IsUsingLegacyImpl() const;

    USDIMAGINGGL_API
    HdSelectionSharedPtr _GetSelection() const;

protected:

// private:
    // Note that any of the fields below might become private
    // in the future and subclasses should use the above getters
    // to access them instead.

    HgiUniquePtr _hgi;
    // Similar for HdDriver.
    HdDriver _hgiDriver;

    VtValue _userFramebuffer;

protected:
    HdPluginRenderDelegateUniqueHandle _renderDelegate;
    std::unique_ptr<HdRenderIndex> _renderIndex;

    SdfPath const _sceneDelegateId;

    std::unique_ptr<HdxTaskController> _taskController;

    HdxSelectionTrackerSharedPtr _selTracker;
    HdRprimCollection _renderCollection;
    HdRprimCollection _intersectCollection;

    GlfSimpleLightingContextRefPtr _lightingContextForOpenGLState;

    // Data we want to live across render plugin switches:
    GfVec4f _selectionColor;

    SdfPath _rootPath;
    SdfPathVector _excludedPrimPaths;
    SdfPathVector _invisedPrimPaths;
    bool _isPopulated;

    // An implementation of much of the engine functionality that doesn't
    // invoke any of the advanced Hydra features.  It is kept around for
    // backwards compatibility and may one day be deprecated.  Most of the
    // time we expect this to be null.  When it is not null, none of the other
    // member variables of this class are used.
    std::unique_ptr<UsdImagingGLLegacyEngine> _legacyImpl;

private:
    void _DestroyHydraObjects();

    std::unique_ptr<UsdImagingDelegate> _sceneDelegate;
    std::unique_ptr<HdEngine> _engine;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_GL_ENGINE_H
