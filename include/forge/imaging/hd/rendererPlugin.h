#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/rendererPlugin.h"
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
#ifndef FORGE_IMAGING_HD_RENDERER_PLUGIN_H
#define FORGE_IMAGING_HD_RENDERER_PLUGIN_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hf/pluginBase.h"
#include "forge/imaging/hd/renderDelegate.h"

FORGE_NAMESPACE_BEGIN

class SdfPath;
class HdRenderIndex;
class HdPluginRenderDelegateUniqueHandle;

///
/// This class defines a renderer plugin interface for Hydra.
/// A renderer plugin is a dynamically discovered and loaded at run-time using
/// the Plug system.
///
/// This object has singleton behavior, in that is instantiated once per
/// library (managed by the plugin registry).
///
/// The class is used to factory objects that provide delegate support
/// to other parts of the Hydra Ecosystem.
///
class HdRendererPlugin : public HfPluginBase {
public:

    ///
    /// Create a render delegate through the plugin and wrap it in a
    /// handle that keeps this plugin alive until render delegate is
    /// destroyed. Initial settings can be passed in.
    ///
    HD_API
    HdPluginRenderDelegateUniqueHandle CreateDelegate(
        HdRenderSettingsMap const &settingsMap = {});

    ///
    /// Look-up plugin id in plugin registry.
    ///
    HD_API
    TfToken GetPluginId() const;

    ///
    /// Clients should use CreateDelegate since this method
    /// will eventually become protected, use CreateRenderDelegateHandle
    /// instead.
    ///
    /// Factory a Render Delegate object, that Hydra can use to
    /// factory prims and communicate with a renderer.
    ///
    virtual HdRenderDelegate *CreateRenderDelegate() = 0;

    ///
    /// Clients should use CreateDelegate since this method
    /// will eventually become protected.
    ///
    /// Factory a Render Delegate object, that Hydra can use to
    /// factory prims and communicate with a renderer.  Pass in initial
    /// settings...
    ///
    HD_API
    virtual HdRenderDelegate *CreateRenderDelegate(
        HdRenderSettingsMap const& settingsMap);

    ///
    /// Clients should use CreateDelegate since this method
    /// will eventually become protected.
    ///
    /// Release the object factoried by CreateRenderDelegate().
    ///
    virtual void DeleteRenderDelegate(HdRenderDelegate *renderDelegate) = 0;

    ///
    /// Returns \c true if this renderer plugin is supported in the running
    /// process and \c false if not.
    ///
    /// This gives the plugin a chance to perform some runtime checks to make
    /// sure that the system meets minimum requirements.
    ///
    virtual bool IsSupported() const = 0;

protected:
    HdRendererPlugin() = default;
    HD_API
    ~HdRendererPlugin() override;

private:
    // This class doesn't require copy support.
    HdRendererPlugin(const HdRendererPlugin &)             = delete;
    HdRendererPlugin &operator =(const HdRendererPlugin &) = delete;

};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_RENDERER_PLUGIN_H
