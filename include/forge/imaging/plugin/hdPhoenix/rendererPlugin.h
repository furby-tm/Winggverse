#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdPhoenix/rendererPlugin.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_PHOENIX_RENDERER_PLUGIN_H
#define FORGE_IMAGING_PLUGIN_HD_PHOENIX_RENDERER_PLUGIN_H

#include "forge/forge.h"
#include "forge/imaging/hd/rendererPlugin.h"

FORGE_NAMESPACE_BEGIN

class HdPhoenixRendererPlugin final : public HdRendererPlugin {
public:
    HdPhoenixRendererPlugin()          = default;
    virtual ~HdPhoenixRendererPlugin() = default;

    virtual HdRenderDelegate *CreateRenderDelegate() override;
    virtual HdRenderDelegate *CreateRenderDelegate(
        HdRenderSettingsMap const& settingsMap) override;

    virtual void DeleteRenderDelegate(HdRenderDelegate *renderDelegate)
        override;

    virtual bool IsSupported() const override;

private:
    HdPhoenixRendererPlugin(const HdPhoenixRendererPlugin &)             = delete;
    HdPhoenixRendererPlugin &operator =(const HdPhoenixRendererPlugin &) = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_PHOENIX_RENDERER_PLUGIN_H
