#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdr/shaderMetadataHelpers.h"
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

#ifndef FORGE_USD_SDR_SHADER_METADATA_HELPERS_H
#define FORGE_USD_SDR_SHADER_METADATA_HELPERS_H

/// \file sdr/shaderMetadataHelpers.h

#include "forge/forge.h"
#include "forge/usd/sdr/api.h"
#include "forge/base/tf/token.h"
#include "forge/usd/sdr/declare.h"

FORGE_NAMESPACE_BEGIN

/// \namespace ShaderMetadataHelpers
///
/// Various utilities for parsing metadata contained within shaders.
///
namespace ShaderMetadataHelpers
{
    /// Determines if the given property in the metadata dictionary has a
    /// truthy value. All values are considered to be true except the following
    /// (case-insensitive): '0', 'false', and 'f'. The absence of `propName`
    /// in the metadata also evaluates to false.
    SDR_API
    bool
    IsTruthy(const TfToken& propName, const NdrTokenMap& metadata);

    /// Extracts the string value from the given property if it exists,
    /// otherwise returns \p defaultValue.
    SDR_API
    std::string
    StringVal(const TfToken& propName, const NdrTokenMap& metadata,
              const std::string& defaultValue = std::string());

    /// Extracts the tokenized value from the given property. An empty token is
    /// returned if the property does not exist.
    SDR_API
    TfToken
    TokenVal(const TfToken& propName, const NdrTokenMap& metadata,
             const TfToken& defaultValue = TfToken());

    /// Extracts a vector of strings from the given property.
    SDR_API
    NdrStringVec
    StringVecVal(const TfToken& propName, const NdrTokenMap& metadata);

    /// Extracts a vector of tokenized values from the given property. An empty
    /// vector is returned if the property does not exist.
    SDR_API
    NdrTokenVec
    TokenVecVal(const TfToken& propName, const NdrTokenMap& metadata);

    /// Extracts an "options" vector from the given string.
    SDR_API
    NdrOptionVec
    OptionVecVal(const std::string& optionStr);

    /// Serializes a vector of strings into a string using the pipe character
    /// as the delimiter.
    SDR_API
    std::string
    CreateStringFromStringVec(const NdrStringVec& stringVec);

    /// Determines if the specified property metadata has a widget that
    /// indicates the property is an asset identifier.
    SDR_API
    bool
    IsPropertyAnAssetIdentifier(const NdrTokenMap& metadata);

    /// Determines if the specified property metadata has a 'renderType' that
    /// indicates the property should be a SdrPropertyTypes->Terminal
    SDR_API
    bool
    IsPropertyATerminal(const NdrTokenMap& metadata);

    /// Gets the "role" from metadata if one is provided. Only returns a value
    // if it's a valid role as defined by SdrPropertyRole tokens.
    SDR_API
    TfToken
    GetRoleFromMetadata(const NdrTokenMap& metadata);
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDR_SHADER_METADATA_HELPERS_H
