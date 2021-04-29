#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/discoveryPlugin.h"
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
#ifndef FORGE_USD_USDLUX_DISCOVERY_PLUGIN_H
#define FORGE_USD_USDLUX_DISCOVERY_PLUGIN_H

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"

#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/discoveryPlugin.h"

FORGE_NAMESPACE_BEGIN

/// \class UsdLux_DiscoveryPlugin
///
/// Discovers nodes for corresponding concrete light and light filter types that
/// come from derived UsdLuxLight and UsdLuxLightFilter schema classes.
///
class UsdLux_DiscoveryPlugin : public NdrDiscoveryPlugin {
public:
    USDLUX_API
    UsdLux_DiscoveryPlugin() = default;

    USDLUX_API
    ~UsdLux_DiscoveryPlugin() override = default;

    USDLUX_API
    virtual NdrNodeDiscoveryResultVec DiscoverNodes(const Context &context)
        override;

    USDLUX_API
    virtual const NdrStringVec& GetSearchURIs() const override;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USDLUX_DISCOVERY_PLUGIN_H
