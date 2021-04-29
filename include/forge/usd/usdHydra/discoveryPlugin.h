#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdHydra/discoveryPlugin.h"
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
#ifndef FORGE_USD_USD_HYDRA_DISCOVERY_PLUGIN_H
#define FORGE_USD_USD_HYDRA_DISCOVERY_PLUGIN_H

#include "forge/forge.h"
#include "forge/usd/usdHydra/api.h"
#include "forge/base/tf/token.h"

#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/discoveryPlugin.h"
#include "forge/usd/ndr/parserPlugin.h"

FORGE_NAMESPACE_BEGIN

class UsdHydraDiscoveryPlugin : public NdrDiscoveryPlugin {
public:
    UsdHydraDiscoveryPlugin() = default;

    ~UsdHydraDiscoveryPlugin() override = default;

    virtual NdrNodeDiscoveryResultVec DiscoverNodes(const Context &context)
        override;

    virtual const NdrStringVec& GetSearchURIs() const override;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_HYDRA_DISCOVERY_PLUGIN_H
