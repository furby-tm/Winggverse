#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/rendererPlugin.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDERER_PLUGIN_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDERER_PLUGIN_H

#include "forge/forge.h"
#include "forge/imaging/hd/rendererPlugin.h"

FORGE_NAMESPACE_BEGIN

///
/// \class HdEmbreeRendererPlugin
///
/// A registered child of HdRendererPlugin, this is the class that gets
/// loaded when a hydra application asks to draw with a certain renderer.
/// It supports rendering via creation/destruction of renderer-specific
/// classes. The render delegate is the hydra-facing entrypoint into the
/// renderer; it's responsible for creating specialized implementations of hydra
/// prims (which translate scene data into drawable representations) and hydra
/// renderpasses (which draw the scene to the framebuffer).
///
class HdEmbreeRendererPlugin final : public HdRendererPlugin {
public:
    HdEmbreeRendererPlugin() = default;
    virtual ~HdEmbreeRendererPlugin() = default;

    /// Construct a new render delegate of type HdEmbreeRenderDelegate.
    /// Embree render delegates own the embree scene object, so a new render
    /// delegate should be created for each instance of HdRenderIndex.
    ///   \return A new HdEmbreeRenderDelegate object.
    virtual HdRenderDelegate *CreateRenderDelegate() override;

    /// Construct a new render delegate of type HdEmbreeRenderDelegate.
    /// Embree render delegates own the embree scene object, so a new render
    /// delegate should be created for each instance of HdRenderIndex.
    ///   \param settingsMap A list of initialization-time settings for embree.
    ///   \return A new HdEmbreeRenderDelegate object.
    virtual HdRenderDelegate *CreateRenderDelegate(
        HdRenderSettingsMap const& settingsMap) override;

    /// Destroy a render delegate created by this class's CreateRenderDelegate.
    ///   \param renderDelegate The render delegate to delete.
    virtual void DeleteRenderDelegate(
        HdRenderDelegate *renderDelegate) override;

    /// Checks to see if the embree plugin is supported on the running system
    ///
    virtual bool IsSupported() const override;

private:
    // This class does not support copying.
    HdEmbreeRendererPlugin(const HdEmbreeRendererPlugin&)             = delete;
    HdEmbreeRendererPlugin &operator =(const HdEmbreeRendererPlugin&) = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_EMBREE_RENDERER_PLUGIN_H
