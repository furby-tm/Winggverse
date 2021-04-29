#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/lightDefParser.h"
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
#ifndef FORGE_USD_USD_LUX_LIGHT_DEF_PARSER_H
#define FORGE_USD_USD_LUX_LIGHT_DEF_PARSER_H

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"

#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/parserPlugin.h"

FORGE_NAMESPACE_BEGIN

/// \class UsdLux_LightDefParserPlugin
///
/// Parses shader definitions from the registered prim definitions for
/// UsdLuxLight and UsdLuxLightFilter derived schema classes.
///
class UsdLux_LightDefParserPlugin : public NdrParserPlugin
{
public:
    USDLUX_API
    UsdLux_LightDefParserPlugin() = default;

    USDLUX_API
    ~UsdLux_LightDefParserPlugin() override = default;

    USDLUX_API
    NdrNodeUniquePtr Parse(const NdrNodeDiscoveryResult &discoveryResult)
        override;

    USDLUX_API
    const NdrTokenVec &GetDiscoveryTypes() const override;

    USDLUX_API
    const TfToken &GetSourceType() const override;

private:
    // The discovery plugin needs to match the source type and discovery types
    // that instances of this parser returns when discovering nodes.
    friend class UsdLux_DiscoveryPlugin;
    static const TfToken &_GetSourceType();
    static const TfToken &_GetDiscoveryType();
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_LUX_LIGHT_DEF_PARSER_H
