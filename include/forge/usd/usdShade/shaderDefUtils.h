#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdShade/shaderDefUtils.h"
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
#ifndef FORGE_USD_USD_SHADE_SHADER_DEF_UTILS_H
#define FORGE_USD_USD_SHADE_SHADER_DEF_UTILS_H

#include "forge/forge.h"
#include "forge/usd/usdShade/api.h"
#include "forge/usd/usdShade/connectableAPI.h"

#include "forge/usd/ndr/nodeDiscoveryResult.h"

#include <string>

FORGE_NAMESPACE_BEGIN

class UsdShadeShader;

/// \class UsdShadeShaderDefUtils
///
/// This class contains a set of utility functions used for populating the
/// shader registry with shaders definitions specified using UsdShade schemas.
///
class UsdShadeShaderDefUtils {
public:
    /// Given a shader's \p identifier token, computes the corresponding
    /// SdrShaderNode's family name, implementation name and shader version
    /// (as NdrVersion).
    ///
    /// * \p familyName is the prefix of \p identifier up to and not
    /// including the first underscore.
    /// * \p version is the suffix of \p identifier comprised of one or
    /// two integers representing the major and minor version numbers.
    /// * \p implementationName is the string we get by joining
    /// <i>familyName</i> with everything that's in between <i>familyName</i>
    /// and <i>version</i> with an underscore.
    ///
    /// Returns true if \p identifier is valid and was successfully split
    /// into the different components.
    ///
    /// \note The python version of this function returns a tuple containing
    /// (famiyName, implementationName, version).
    USDSHADE_API
    static bool SplitShaderIdentifier(const TfToken &identifier,
                TfToken *familyName,
                TfToken *implementationName,
                NdrVersion *version);

    /// Returns the list of NdrNodeDiscoveryResult objects that must be added
    /// to the shader registry for the given shader \p shaderDef, assuming it
    /// is found in a shader definition file found by an Ndr discovery plugin.
    ///
    /// To enable the shaderDef parser to find and parse this shader,
    /// \p sourceUri should have the resolved path to the usd file containing
    /// this shader prim.
    USDSHADE_API
    static NdrNodeDiscoveryResultVec GetNodeDiscoveryResults(
        const UsdShadeShader &shaderDef,
        const std::string &sourceUri);

    /// Gets all input and output properties of the given \p shaderDef and
    /// translates them into NdrProperties that can be used as the properties
    /// for an SdrShaderNode.
    USDSHADE_API
    static NdrPropertyUniquePtrVec GetShaderProperties(
        const UsdShadeConnectableAPI &shaderDef);

    /// Collects all the names of valid primvar inputs of the given \p metadata
    /// and the given \p shaderDef and returns the string used to represent
    /// them in SdrShaderNode metadata.
    USDSHADE_API
    static std::string GetPrimvarNamesMetadataString(
        const NdrTokenMap metadata,
        const UsdShadeConnectableAPI &shaderDef);
};

FORGE_NAMESPACE_END

#endif
