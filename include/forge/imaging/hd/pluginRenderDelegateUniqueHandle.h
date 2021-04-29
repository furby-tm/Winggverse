#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/pluginRenderDelegateUniqueHandle.h"
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
#ifndef FORGE_IMAGING_HD_PLUGIN_RENDER_DELEGATE_UNIQUE_HANDLE_H
#define FORGE_IMAGING_HD_PLUGIN_RENDER_DELEGATE_UNIQUE_HANDLE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/rendererPluginHandle.h"

#include <cstddef>

FORGE_NAMESPACE_BEGIN

class HdRenderDelegate;

///
/// A (movable) handle for a render delegate that was created using a
/// a plugin.
///
/// The handle owns the render delegate (render delegate is destroyed
/// when handle is dropped). The handle also can be queried what
/// plugin was used to create the render delegate and ensures the
/// plugin is kept alive until the render delegate is destroyed.
/// In other words, the handle can be used just like a std::unique_ptr.
///
class HdPluginRenderDelegateUniqueHandle final
{
public:
    HdPluginRenderDelegateUniqueHandle() : _delegate(nullptr) { }
    HdPluginRenderDelegateUniqueHandle(const std::nullptr_t &)
      : _delegate(nullptr) { }

    /// Transfer ownership
    HD_API
    HdPluginRenderDelegateUniqueHandle(HdPluginRenderDelegateUniqueHandle &&);

    HD_API
    ~HdPluginRenderDelegateUniqueHandle();

    /// Transfer ownership
    HD_API
    HdPluginRenderDelegateUniqueHandle &operator=(
        HdPluginRenderDelegateUniqueHandle &&);

    HD_API
    HdPluginRenderDelegateUniqueHandle &operator=(
        const std::nullptr_t &);

    /// Get render delegate
    HdRenderDelegate *Get() const { return _delegate; }

    HdRenderDelegate *operator->() const { return _delegate; }
    HdRenderDelegate &operator*() const { return *_delegate; }

    /// Is the wrapped HdRenderDelegate valid?
    explicit operator bool() const { return _delegate; }

    /// Get the id of the plugin used to create render delegate
    HD_API
    TfToken GetPluginId() const;

private:
    friend class HdRendererPlugin;

    HdPluginRenderDelegateUniqueHandle(
        const HdRendererPluginHandle &plugin, HdRenderDelegate * delegate)
        : _plugin(plugin), _delegate(delegate) { }

    HdRendererPluginHandle _plugin;
    HdRenderDelegate *_delegate;
};

FORGE_NAMESPACE_END

#endif
