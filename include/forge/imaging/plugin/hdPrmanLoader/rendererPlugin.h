#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdPrmanLoader/rendererPlugin.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_PRMAN_LOADER_RENDERER_PLUGIN_H
#define FORGE_IMAGING_PLUGIN_HD_PRMAN_LOADER_RENDERER_PLUGIN_H

#include "forge/forge.h"
#include "forge/imaging/hd/rendererPlugin.h"

FORGE_NAMESPACE_BEGIN

class HdPrmanLoaderRendererPlugin final : public HdRendererPlugin {
public:
    HdPrmanLoaderRendererPlugin();
    virtual ~HdPrmanLoaderRendererPlugin();

    virtual HdRenderDelegate *CreateRenderDelegate() override;
    virtual HdRenderDelegate *CreateRenderDelegate(
        HdRenderSettingsMap const& settingsMap) override;
    virtual void DeleteRenderDelegate(HdRenderDelegate *) override;
    virtual bool IsSupported() const override;

private:
    // This class does not support copying.
    HdPrmanLoaderRendererPlugin(
        const HdPrmanLoaderRendererPlugin&) = delete;
    HdPrmanLoaderRendererPlugin &operator =(
        const HdPrmanLoaderRendererPlugin&) = delete;
};

// These macros are used to shim the actual hdPrman delegate implementation
#define HDPRMAN_LOADER_CREATE_DELEGATE \
    extern "C" ARCH_EXPORT HdRenderDelegate* HdPrmanLoaderCreateDelegate( \
        HdRenderSettingsMap const& settingsMap)
#define HDPRMAN_LOADER_DELETE_DELEGATE \
    extern "C" ARCH_EXPORT void HdPrmanLoaderDeleteDelegate( \
        HdRenderDelegate *renderDelegate)

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_PRMAN_LOADER_RENDERER_PLUGIN_H
