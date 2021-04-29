#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/layerStackRegistry.h"
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
#ifndef FORGE_USD_PCP_LAYER_STACK_REGISTRY_H
#define FORGE_USD_PCP_LAYER_STACK_REGISTRY_H

/// \file pcp/layerStackRegistry.h

#include "forge/forge.h"
#include "forge/usd/pcp/errors.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refBase.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(PcpLayerStack);
TF_DECLARE_REF_PTRS(Pcp_LayerStackRegistry);

class PcpLayerStackIdentifier;
class Pcp_LayerStackRegistryData;
class Pcp_MutedLayers;

/// \class Pcp_LayerStackRegistry
///
/// A registry of layer stacks.
///
class Pcp_LayerStackRegistry : public TfRefBase, public TfWeakBase {
public:
    /// Create a new Pcp_LayerStackRegistry.
    static Pcp_LayerStackRegistryRefPtr New(
        const std::string& fileFormatTarget = std::string(),
        bool isUsd=false);

    /// Adds layers specified in \p layersToMute and removes layers
    /// specified in \p layersToUnmute from the registry's set of muted
    /// layers.  Any relative paths will be anchored to the given
    /// \p anchorLayer. On completion, \p layersToMute and \p layersToUnmute
    /// will be filled with the canonical identifiers for layers that were
    /// actually added or removed.
    void MuteAndUnmuteLayers(const SdfLayerHandle& anchorLayer,
                             std::vector<std::string>* layersToMute,
                             std::vector<std::string>* layersToUnmute);

    /// Returns the list of canonical identifiers for muted layers
    /// in this cache.
    const std::vector<std::string>& GetMutedLayers() const;

    /// Returns true if the layer identified by \p layerIdentifier is muted,
    /// false otherwise.  If \p layerIdentifier is relative, \p anchorLayer
    /// used to anchor the layer.  If this function returns true,
    /// \p canonicalLayerIdentifier will be populated with the canonical
    /// identifier for the muted layer.
    bool IsLayerMuted(const SdfLayerHandle& anchorLayer,
                      const std::string& layerIdentifier,
                      std::string* canonicalLayerIdentifier = nullptr) const;

    /// Returns the layer stack for \p identifier if it exists, otherwise
    /// creates a new layer stack for \p identifier.  This returns \c NULL
    /// if \p identifier is invalid (i.e. its root layer is \c NULL).
    PcpLayerStackRefPtr FindOrCreate(const PcpLayerStackIdentifier& identifier,
                                     PcpErrorVector *allErrors);

    /// Returns the layer stack for \p identifier if it exists, otherwise
    /// returns \c NULL.
    PcpLayerStackPtr Find(const PcpLayerStackIdentifier&) const;

    /// Returns every layer stack that includes \p layer.
    const PcpLayerStackPtrVector&
    FindAllUsingLayer(const SdfLayerHandle& layer) const;

    /// Returns every layer stack that uses the muted layer identified
    /// \p layerId, which is assumed to be a canonical muted layer
    /// identifier.
    const PcpLayerStackPtrVector&
    FindAllUsingMutedLayer(const std::string& layerId) const;

    /// Returns every layer stack known to this registry.
    std::vector<PcpLayerStackPtr> GetAllLayerStacks() const;

private:
    /// Private constructor -- see New().
    Pcp_LayerStackRegistry(const std::string& fileFormatTarget,
                           bool isUsd);
    ~Pcp_LayerStackRegistry();

    // Find that doesn't lock.
    PcpLayerStackPtr _Find(const PcpLayerStackIdentifier&) const;

    // Remove the layer stack with the given identifier from the registry.
    void _Remove(const PcpLayerStackIdentifier&,
                 const PcpLayerStack *);

    // Update the layer-stack-by-layer maps by setting the layers for the
    // given layer stack.
    void _SetLayers(const PcpLayerStack*);

    // Returns the file format target for layer stacks managed by this
    // registry.
    const std::string& _GetFileFormatTarget() const;

    // Returns whether or not we are in USD mode for avoiding
    // extra calls such as Pcp_ComputeRelocationForLayerStack()
    bool _IsUsd() const;

    // Returns the muted layer collection so that layer stack
    // computation can easily query whether a layer is muted.
    const Pcp_MutedLayers& _GetMutedLayers() const;

    // PcpLayerStack can access private _GetFileFormatTarget(),
    // _Remove(), and _SetLayers().
    friend class PcpLayerStack;

private:
    std::unique_ptr<Pcp_LayerStackRegistryData> _data;
};

/// \class Pcp_MutedLayers
///
/// Helper for maintaining and querying a collection of muted layers.
///
class Pcp_MutedLayers
{
public:
    const std::vector<std::string>& GetMutedLayers() const;
    void MuteAndUnmuteLayers(const SdfLayerHandle& anchorLayer,
                             std::vector<std::string>* layersToMute,
                             std::vector<std::string>* layersToUnmute);
    bool IsLayerMuted(const SdfLayerHandle& anchorLayer,
                      const std::string& layerIdentifier,
                      std::string* canonicalLayerIdentifier = nullptr) const;

private:
    std::vector<std::string> _layers;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_LAYER_STACK_REGISTRY_H
