#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdr/registry.h"
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

#ifndef FORGE_USD_SDR_REGISTRY_H
#define FORGE_USD_SDR_REGISTRY_H

/// \file sdr/registry.h

#include "forge/forge.h"
#include "forge/base/tf/singleton.h"
#include "forge/usd/sdr/api.h"
#include "forge/usd/ndr/registry.h"
#include "forge/usd/sdr/declare.h"
#include "forge/usd/sdr/shaderNode.h"

FORGE_NAMESPACE_BEGIN

/// \class SdrRegistry
///
/// The shading-specialized version of `NdrRegistry`.
///
class SdrRegistry : public NdrRegistry
{
public:
    /// Get the single `SdrRegistry` instance.
    SDR_API
    static SdrRegistry& GetInstance();

    /// Exactly like `NdrRegistry::GetNodeByIdentifier()`, but returns a
    /// `SdrShaderNode` pointer instead of a `NdrNode` pointer.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeByIdentifier(
        const NdrIdentifier& identifier,
        const NdrTokenVec& typePriority = NdrTokenVec());

    /// Exactly like `NdrRegistry::GetNodeByIdentifierAndType()`, but returns
    /// a `SdrShaderNode` pointer instead of a `NdrNode` pointer.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeByIdentifierAndType(
        const NdrIdentifier& identifier,
        const TfToken& nodeType);

    /// Exactly like `NdrRegistry::GetNodeByName()`, but returns a
    /// `SdrShaderNode` pointer instead of a `NdrNode` pointer.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeByName(
        const std::string& name,
        const NdrTokenVec& typePriority = NdrTokenVec(),
        NdrVersionFilter filter = NdrVersionFilterDefaultOnly);

    /// Exactly like `NdrRegistry::GetNodeByNameAndType()`, but returns a
    /// `SdrShaderNode` pointer instead of a `NdrNode` pointer.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeByNameAndType(
        const std::string& name,
        const TfToken& nodeType,
        NdrVersionFilter filter = NdrVersionFilterDefaultOnly);

    /// Wrapper method for NdrRegistry::GetNodeFromAsset().
    /// Returns a valid SdrShaderNode pointer upon success.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeFromAsset(
        const SdfAssetPath &shaderAsset,
        const NdrTokenMap &metadata=NdrTokenMap(),
        const TfToken &subIdentifier=TfToken(),
        const TfToken &sourceType=TfToken());

    /// Wrapper method for NdrRegistry::GetNodeFromSourceCode().
    /// Returns a valid SdrShaderNode pointer upon success.
    SDR_API
    SdrShaderNodeConstPtr GetShaderNodeFromSourceCode(
        const std::string &sourceCode,
        const TfToken &sourceType,
        const NdrTokenMap &metadata=NdrTokenMap());

    /// Exactly like `NdrRegistry::GetNodesByIdentifier()`, but returns a vector
    /// of `SdrShaderNode` pointers instead of a vector of `NdrNode` pointers.
    SDR_API
    SdrShaderNodePtrVec GetShaderNodesByIdentifier(const NdrIdentifier& identifier);

    /// Exactly like `NdrRegistry::GetNodesByName()`, but returns a vector of
    /// `SdrShaderNode` pointers instead of a vector of `NdrNode` pointers.
    SDR_API
    SdrShaderNodePtrVec GetShaderNodesByName(
        const std::string& name,
        NdrVersionFilter filter = NdrVersionFilterDefaultOnly);

    /// Exactly like `NdrRegistry::GetNodesByFamily()`, but returns a vector of
    /// `SdrShaderNode` pointers instead of a vector of `NdrNode` pointers.
    SDR_API
    SdrShaderNodePtrVec GetShaderNodesByFamily(
        const TfToken& family = TfToken(),
        NdrVersionFilter filter = NdrVersionFilterDefaultOnly);

protected:
    // Allow TF to construct the class
    friend class TfSingleton<SdrRegistry>;

    SdrRegistry();
    ~SdrRegistry();
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDR_REGISTRY_H
