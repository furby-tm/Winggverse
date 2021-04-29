#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/dependencies.h"
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
#ifndef FORGE_USD_PCP_DEPENDENCIES_H
#define FORGE_USD_PCP_DEPENDENCIES_H

/// \file pcp/dependencies.h

#include "forge/forge.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/pcp/types.h"
#include "forge/usd/pcp/layerStack.h"
#include "forge/usd/pcp/layerStackRegistry.h"
#include "forge/usd/pcp/primIndex.h"
#include "forge/usd/pcp/cache.h"
#include "forge/usd/sdf/layer.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/site.h"

#if !defined(Q_MOC_RUN)
# include <tbb/spin_mutex.h>
#endif /* Q_MOC_RUN */

#include <iosfwd>
#include <set>
#include <unordered_map>

FORGE_NAMESPACE_BEGIN

class PcpLifeboat;
class PcpPrimIndexDependencies;

TF_DECLARE_WEAK_PTRS(PcpLayerStack);

/// \class Pcp_Dependencies
///
/// Tracks the dependencies of PcpPrimIndex entries in a PcpCache.
/// This is an internal class only meant for use by PcpCache.
///
class Pcp_Dependencies {
public:
    /// Construct with no dependencies.
    Pcp_Dependencies();
    ~Pcp_Dependencies();

    Pcp_Dependencies(Pcp_Dependencies const &) = delete;
    Pcp_Dependencies &operator=(Pcp_Dependencies const &) = delete;

    /// \name Registration
    /// @{

    /// Add dependency information for the given PcpPrimIndex along with a
    /// dynamic file format dependency data object if the prim index has
    /// any arcs that depend on a dynamic file format.
    ///
    /// Assumptions:
    /// - A computed prim index will be added exactly once
    /// - Parent indices will be added before children
    void Add(const PcpPrimIndex &primIndex,
        PcpDynamicFileFormatDependencyData &&fileFormatDependencyData);

    /// Remove dependency information for the given PcpPrimIndex.
    /// Any layer stacks in use by any site are added to \p lifeboat,
    /// if not \c NULL.
    ///
    /// Assumptions:
    /// - The prim index has previously been added exactly once
    void Remove(const PcpPrimIndex &primIndex, PcpLifeboat *lifeboat);

    /// Remove all dependencies.  Any layer stacks in use by any site are
    /// added to \p lifeboat, if not \c NULL.
    void RemoveAll(PcpLifeboat* lifeboat);

    /// \struct ConcurrentPopulationContext
    ///
    /// Structure for enabling cache population via concurrent calls to Add().
    /// Protects member data with a mutex during its lifetime.
    /// \sa Add().
    struct ConcurrentPopulationContext
    {
        explicit ConcurrentPopulationContext(Pcp_Dependencies &deps);
        ~ConcurrentPopulationContext();
        Pcp_Dependencies &_deps;
        tbb::spin_mutex _mutex;
    };

    /// @}
    /// \name Queries
    /// @{

    /// Invokes \p fn for every \c PcpPrimIndex that uses
    /// the site represented by (siteLayerStack, sitePath).
    ///
    /// The arguments to \p fn are: (depIndexPath, depSitePath).
    ///
    /// If \p includeAncestral is \c true, this will also walk up
    /// ancestral dependencies introduced by parent prims.
    ///
    /// If \p recurseBelowSite is \c true, then also runs the callback
    /// of every \c PcpSite that uses any descendant of \p path.
    /// depSitePath provides the descendent dependency path.
    ///
    /// If \p recurseBelowSite is \c false, depSitePath is always
    /// the sitePath supplied and can be ignored.
    template <typename FN>
    void
    ForEachDependencyOnSite( const PcpLayerStackPtr &siteLayerStack,
                             const SdfPath &sitePath,
                             bool includeAncestral,
                             bool recurseBelowSite,
                             const FN &fn ) const
    {
        _LayerStackDepMap::const_iterator i = _deps.find(siteLayerStack);
        if (i == _deps.end()) {
            return;
        }
        const _SiteDepMap & siteDepMap = i->second;
        if (recurseBelowSite) {
            auto range = siteDepMap.FindSubtreeRange(sitePath);
            for (auto iter = range.first; iter != range.second; ++iter) {
                for(const SdfPath &primIndexPath: iter->second) {
                    fn(primIndexPath, iter->first);
                }
            }
        } else {
            _SiteDepMap::const_iterator j = siteDepMap.find(sitePath);
            if (j != siteDepMap.end()) {
                for(const SdfPath &primIndexPath: j->second) {
                    fn(primIndexPath, sitePath);
                }
            }
        }
        if (includeAncestral) {
            for (SdfPath ancestorSitePath = sitePath.GetParentPath();
                 !ancestorSitePath.IsEmpty();
                 ancestorSitePath = ancestorSitePath.GetParentPath())
            {
                _SiteDepMap::const_iterator j =
                    siteDepMap.find(ancestorSitePath);
                if (j != siteDepMap.end()) {
                    for(const SdfPath &ancestorPrimIndexPath: j->second) {
                        fn(ancestorPrimIndexPath, ancestorSitePath);
                    }
                }
            }
        }
    }

    /// Returns all layers from all layer stacks with dependencies recorded
    /// against them.
    SdfLayerHandleSet GetUsedLayers() const;

    /// Returns the root layers of all layer stacks with dependencies
    /// recorded against them.
    SdfLayerHandleSet GetUsedRootLayers() const;

    /// Returns true if there are dependencies recorded against the given
    /// layer stack.
    bool UsesLayerStack(const PcpLayerStackPtr& layerStack) const;

    /// Returns true if there are any dynamic file format argument dependencies
    /// in this dependencies object.
    bool HasAnyDynamicFileFormatArgumentDependencies() const;

    /// Returns true if the given \p field name is a field that was
    /// composed while generating dynamic file format arguments for any prim
    /// index that was added to this dependencies object.
    bool IsPossibleDynamicFileFormatArgumentField(
        const TfToken &field) const;

    /// Returns the dynamic file format dependency data object for the prim
    /// index with the given \p primIndexPath. This will return an empty
    /// dependency data if either there is no cache prim index for the path or
    /// if the prim index has no dynamic file formats that it depends on.
    const PcpDynamicFileFormatDependencyData &
    GetDynamicFileFormatArgumentDependencyData(
        const SdfPath &primIndexPath) const;

    /// @}

private:
    // Map of site paths to dependencies, as cache paths.  Stores cache
    // paths as an unordered vector: for our datasets this is both more
    // compact and faster than std::set.
    using _SiteDepMap = SdfPathTable<SdfPathVector>;

    // Map of layer stacks to dependencies on that layerStack.
    // Retains references to those layer stacks, which in turn
    // retain references to their constituent layers.
    using _LayerStackDepMap =
        std::unordered_map<PcpLayerStackRefPtr, _SiteDepMap, TfHash>;
    _LayerStackDepMap _deps;

    // Map of prim index paths to the dynamic file format dependency info for
    // the prim index.
    using _FileFormatArgumentDependencyMap = std::unordered_map<
        SdfPath, PcpDynamicFileFormatDependencyData, SdfPath::Hash>;
    _FileFormatArgumentDependencyMap _fileFormatArgumentDependencyMap;

    // Map of field name to the number of cached prim indices that depend on
    // the field for dynamic file format arguments. This for quick lookup of
    // possible file format argument relevant field changes.
    using _FileFormatArgumentFieldDepMap =
        std::unordered_map<TfToken, int, TfToken::HashFunctor>;
    _FileFormatArgumentFieldDepMap _possibleDynamicFileFormatArgumentFields;

    ConcurrentPopulationContext *_concurrentPopulationContext;
};

template <typename FN>
static void
Pcp_ForEachDependentNode( const SdfPath &sitePath,
                          const SdfLayerHandle &layer,
                          const SdfPath &depIndexPath,
                          const PcpCache &cache,
                          const FN &fn )
{
    PcpNodeRef nodeUsingSite;

    // Walk up as needed to find a containing prim index.
    SdfPath indexPath;
    const PcpPrimIndex *primIndex = nullptr;
    for (indexPath = depIndexPath.GetAbsoluteRootOrPrimPath();
         indexPath != SdfPath();
         indexPath = indexPath.GetParentPath())
    {
        primIndex = cache.FindPrimIndex(indexPath);
        if (primIndex) {
            break;
        }
    }
    if (primIndex) {
        // Find which node corresponds to (layer, oldPath).
        for (const PcpNodeRef &node: primIndex->GetNodeRange()) {
            if (PcpNodeIntroducesDependency(node) &&
                node.GetLayerStack()->HasLayer(layer) &&
                sitePath.HasPrefix(node.GetPath()))
            {
                nodeUsingSite = node;
                fn(depIndexPath, nodeUsingSite);
            }
        }
    }

    TF_VERIFY(
            nodeUsingSite,
            "Unable to find node that introduced dependency on site "
            "<%s>@%s@ for prim <%s>",
            sitePath.GetText(),
            layer->GetIdentifier().c_str(),
            depIndexPath.GetText());
}

template <typename FN>
static void
Pcp_ForEachDependentNode( const SdfPath &sitePath,
                          const PcpLayerStackPtr &layerStack,
                          const SdfPath &depIndexPath,
                          const PcpCache &cache,
                          const FN &fn )
{
    PcpNodeRef nodeUsingSite;

    // Walk up as needed to find a containing prim index.
    SdfPath indexPath;
    const PcpPrimIndex *primIndex = nullptr;
    for (indexPath = depIndexPath.GetAbsoluteRootOrPrimPath();
         indexPath != SdfPath();
         indexPath = indexPath.GetParentPath())
    {
        primIndex = cache.FindPrimIndex(indexPath);
        if (primIndex) {
            break;
        }
    }
    if (primIndex) {
        // Find which node corresponds to (layerStack, oldPath).
        for (const PcpNodeRef &node: primIndex->GetNodeRange()) {
            if (PcpNodeIntroducesDependency(node) &&
                node.GetLayerStack() == layerStack &&
                sitePath.HasPrefix(node.GetPath()))
            {
                nodeUsingSite = node;
                fn(depIndexPath, nodeUsingSite);
            }
        }
    }

    TF_VERIFY(
            nodeUsingSite,
            "Unable to find node that introduced dependency on site "
            "<%s>%s for prim <%s> in %s",
            sitePath.GetText(),
            TfStringify(layerStack->GetIdentifier()).c_str(),
            depIndexPath.GetText(),
            TfStringify(cache.GetLayerStack()->GetIdentifier()).c_str()
            );
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_DEPENDENCIES_H
