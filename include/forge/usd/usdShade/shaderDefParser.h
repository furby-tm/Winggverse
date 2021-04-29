#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdShade/shaderDefParser.h"
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
#ifndef FORGE_USD_USD_SHADE_SHADER_DEF_PARSER_H
#define FORGE_USD_USD_SHADE_SHADER_DEF_PARSER_H

#include "forge/usd/usdShade/api.h"

#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/discoveryPlugin.h"
#include "forge/usd/ndr/parserPlugin.h"

FORGE_NAMESPACE_BEGIN

class UsdStageCache;

/// \class UsdShadeShaderDefParserPlugin
///
/// Parses shader definitions represented using USD scene description using the
/// schemas provided by UsdShade.
///
class UsdShadeShaderDefParserPlugin : public NdrParserPlugin
{
public:
    USDSHADE_API
    UsdShadeShaderDefParserPlugin() = default;

    USDSHADE_API
    ~UsdShadeShaderDefParserPlugin() override = default;

    USDSHADE_API
    NdrNodeUniquePtr Parse(const NdrNodeDiscoveryResult &discoveryResult)
        override;

    USDSHADE_API
    const NdrTokenVec &GetDiscoveryTypes() const override;

    USDSHADE_API
    const TfToken &GetSourceType() const override;

private:
    static UsdStageCache _cache;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SHADE_SHADER_DEF_PARSER_H
