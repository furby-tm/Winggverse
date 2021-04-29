#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/namespaceEdits.h"
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
#ifndef FORGE_USD_PCP_NAMESPACE_EDITS_H
#define FORGE_USD_PCP_NAMESPACE_EDITS_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/cache.h"
#include "forge/base/tf/hashset.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

// Forward declarations:
class PcpChanges;
class PcpCacheChanges;
class Pcp_Dependencies;
class PcpLayerStackIdentifier;
class PcpLifeboat;
class PcpNodeRef;
class PcpMapFunction;

TF_DECLARE_WEAK_AND_REF_PTRS(PcpLayerStack);
TF_DECLARE_WEAK_AND_REF_PTRS(Pcp_LayerStackRegistry);
SDF_DECLARE_HANDLES(SdfSpec);

/// Sites that must respond to a namespace edit.
struct PcpNamespaceEdits {

    /// Types of namespace edits that a given layer stack site could need
    /// to perform to respond to a namespace edit.
    enum EditType {
        EditPath,        ///< Must namespace edit spec
        EditInherit,     ///< Must fixup inherits
        EditSpecializes, ///< Must fixup specializes
        EditReference,   ///< Must fixup references
        EditPayload,     ///< Must fixup payload
        EditRelocate,    ///< Must fixup relocates
    };

    void Swap(PcpNamespaceEdits& rhs)
    {
        cacheSites.swap(rhs.cacheSites);
        layerStackSites.swap(rhs.layerStackSites);
        invalidLayerStackSites.swap(rhs.invalidLayerStackSites);
    }

    /// Cache site that must respond to a namespace edit.
    struct CacheSite {
        size_t cacheIndex;  ///< Index of cache of site.
        SdfPath oldPath;    ///< Old path of site.
        SdfPath newPath;    ///< New path of site.
    };
    typedef std::vector<CacheSite> CacheSites;

    /// Layer stack site that must respond to a namespace edit.  All
    /// of the specs at the site will respond the same way.
    struct LayerStackSite {
        size_t cacheIndex;              ///< Index of cache of site.
        EditType type;                  ///< Type of edit.
        PcpLayerStackPtr layerStack;    ///< Layer stack needing fix.
        SdfPath sitePath;               ///< Path of site needing fix.
        SdfPath oldPath;                ///< Old path.
        SdfPath newPath;                ///< New path.
    };
    typedef std::vector<LayerStackSite> LayerStackSites;

    /// Cache sites that must respond to a namespace edit.
    CacheSites cacheSites;

    /// Layer stack sites that must respond to a namespace edit.
    LayerStackSites layerStackSites;

    /// Layer stack sites that are affected by a namespace edit but
    /// cannot respond properly. For example, in situations involving
    /// relocates, a valid namespace edit in one cache may result in
    /// an invalid edit in another cache in response.
    LayerStackSites invalidLayerStackSites;
};

/// Returns the changes caused in any cache in \p caches due to
/// namespace editing the object at \p curPath in this cache to
/// have the path \p newPath.  \p caches should have all caches,
/// including this cache.  If \p caches includes this cache then
/// the result includes the changes caused at \p curPath in this
/// cache itself.
///
/// To keep everything consistent, a namespace edit requires that
/// everything using the namespace edited site to be changed in an
/// appropriate way.  For example, if a referenced prim /A is renamed
/// to /B then everything referencing /A must be changed to reference
/// /B instead.  There are many other possibilities.
///
/// One possibility is that there are no opinions at \p curPath in
/// this cache's layer stack and the site exists due to some ancestor
/// arc.  This requires a relocation and only sites using \p curPath
/// that include the layer with the relocation must be changed in
/// response.  To find those sites, \p relocatesLayer indicates which
/// layer the client will write the relocation to.
///
/// Clients must perform the changes to correctly perform a namespace
/// edit.  All changes must be performed in a change block, otherwise
/// notices could be sent prematurely.
///
/// This method only works when the affected prim indexes have been
/// computed.  In general, this means you must have computed the prim
/// index of everything in any existing cache, otherwise you might miss
/// changes to objects in those caches that use the namespace edited
/// object.  Using the above example, if a prim with an uncomputed prim
/// index referenced /A then this method would not report that prim.
/// As a result that prim would continue to reference /A, which no
/// longer exists.
PCP_API
PcpNamespaceEdits
PcpComputeNamespaceEdits(const PcpCache *primaryCache,
                         const std::vector<PcpCache*>& caches,
                         const SdfPath& curPath,
                         const SdfPath& newPath,
                         const SdfLayerHandle& relocatesLayer);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_NAMESPACE_EDITS_H
