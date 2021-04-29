#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/rendererPluginHandle.h"
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
#ifndef FORGE_IMAGING_HD_RENDERER_PLUGIN_HANDLE_H
#define FORGE_IMAGING_HD_RENDERER_PLUGIN_HANDLE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/renderDelegate.h"

#include "forge/base/tf/token.h"

#include <cstddef>

FORGE_NAMESPACE_BEGIN

class HdRendererPlugin;
class HdPluginRenderDelegateUniqueHandle;

///
/// A handle for HdRendererPlugin also storing the plugin id.
///
/// Alleviates the need to ever call, e.g., ReleasePlugin since it
/// automatically decreases and increases the plugin's reference
/// counts with the plugin registry.
///
class HdRendererPluginHandle final
{
public:
    HdRendererPluginHandle() : _plugin(nullptr) { }
    HdRendererPluginHandle(const std::nullptr_t &) : _plugin(nullptr) { }

    HD_API
    HdRendererPluginHandle(const HdRendererPluginHandle &);

    HD_API
    ~HdRendererPluginHandle();

    HD_API
    HdRendererPluginHandle &operator=(const HdRendererPluginHandle &);

    HD_API
    HdRendererPluginHandle &operator=(const std::nullptr_t &);

    /// Get the wrapped HdRendererPlugin
    HdRendererPlugin *Get() const { return _plugin; }

    HdRendererPlugin *operator->() const { return _plugin; }
    HdRendererPlugin &operator*() const { return *_plugin; }

    /// Is the wrapped HdRendererPlugin valid?
    explicit operator bool() const { return _plugin; }

private:
    friend class HdRendererPluginRegistry;
    friend class HdRendererPlugin;

    HdRendererPluginHandle(HdRendererPlugin * const plugin)
      : _plugin(plugin) { }

    HdRendererPlugin *_plugin;
};

FORGE_NAMESPACE_END

#endif
