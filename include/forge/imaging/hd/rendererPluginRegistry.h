#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/rendererPluginRegistry.h"
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
#ifndef FORGE_IMAGING_HD_RENDERER_PLUGIN_REGISTRY_H
#define FORGE_IMAGING_HD_RENDERER_PLUGIN_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/renderDelegate.h"
#include "forge/base/tf/singleton.h"
#include "forge/imaging/hf/pluginRegistry.h"

FORGE_NAMESPACE_BEGIN


class HdRendererPlugin;
class HdRendererPluginHandle;
class HdPluginRenderDelegateUniqueHandle;

class HdRendererPluginRegistry final  : public HfPluginRegistry
{
public:
    ///
    /// Returns the singleton registry for \c HdRendererPlugin
    ///
    HD_API
    static HdRendererPluginRegistry &GetInstance();

    ///
    /// Entry point for defining an HdRendererPlugin plugin.
    ///
    template<typename T, typename... Bases>
    static void Define();

    ///
    /// Returns the id of plugin to use as the default
    ///
    HD_API
    TfToken GetDefaultPluginId();

    ///
    /// \deprecated Use GetOrCreateRendererPlugin instead.
    ///
    /// Returns the renderer plugin for the given id or null
    /// if not found.  The reference count on the returned
    /// delegate is incremented.
    ///
    HD_API
    HdRendererPlugin *GetRendererPlugin(const TfToken &pluginId);

    ///
    /// Returns the renderer plugin for the given id or a null handle
    /// if not found. The plugin is wrapped in a handle that automatically
    /// increments and decrements the reference count and also stores the
    /// plugin id.
    ///
    HD_API
    HdRendererPluginHandle GetOrCreateRendererPlugin(const TfToken &pluginId);

    ///
    /// Returns a render delegate created by the plugin with the given name
    /// if the plugin is supported using given initial settings.
    /// The render delegate is wrapped in a movable handle that
    /// keeps the plugin alive until the render delegate is destroyed by
    /// dropping the handle.
    ///
    HD_API
    HdPluginRenderDelegateUniqueHandle CreateRenderDelegate(
        const TfToken &pluginId,
        const HdRenderSettingsMap &settingsMap = {});

private:
    // Friend required by TfSingleton to access constructor (as it is private).
    friend class TfSingleton<HdRendererPluginRegistry>;

    // Singleton gets private constructed
    HdRendererPluginRegistry();
    ~HdRendererPluginRegistry() override;

    //
    /// This class is not intended to be copied.
    ///
    HdRendererPluginRegistry(const HdRendererPluginRegistry &)            = delete;
    HdRendererPluginRegistry &operator=(const HdRendererPluginRegistry &) = delete;
};


template<typename T, typename... Bases>
void HdRendererPluginRegistry::Define()
{
    HfPluginRegistry::Define<T, HdRendererPlugin, Bases...>();
}


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_RENDERER_PLUGIN_REGISTRY_H
