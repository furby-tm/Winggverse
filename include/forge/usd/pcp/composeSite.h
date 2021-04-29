#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/composeSite.h"
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
#ifndef FORGE_USD_PCP_COMPOSE_SITE_H
#define FORGE_USD_PCP_COMPOSE_SITE_H

/// \file pcp/composeSite.h
///
/// Single-site composition.
///
/// These are helpers that compose specific fields at single sites.
/// They compose the field for a given path across a layer stack,
/// using field-specific rules to combine the values.
///
/// These helpers are low-level utilities used by the rest of the
/// Pcp algorithms, to discover composition arcs in scene description.
/// These arcs are what guide the algorithm to pull additional
/// sites of scene description into the PcpPrimIndex.
///
/// Some of these field types support list-editing.  (See SdListOp.)
/// List-editing for these fields is applied across the fixed domain
/// of a single site; you cannot apply list-ops across sites.
/// The intention is to avoid subtle ordering issues in composition
/// semantics.
///
/// Note that these helpers do not take PcpSite as a literal parameter;
/// instead, they require the actual computed layer stack that a site
/// identified.  Rather than tying these helpers to PcpCache and its
/// process of computing layer stacks, they just employ the result.
/// Conceptually, though, they are operating on the scene description
/// identified by a PcpSite.

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/sdf/layerOffset.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/payload.h"
#include "forge/usd/sdf/reference.h"
#include "forge/usd/sdf/types.h"
#include "forge/usd/sdf/site.h"

#include <set>
#include <vector>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(PcpLayerStack);

class PcpLayerStackSite;

/// \struct PcpSourceArcInfo
///
/// Information about the source of the target of an arc.
/// All arcs have a layer that the arc comes from. References and payloads
/// have a resolved layer offset and authored asset path as well.
///
struct PcpSourceArcInfo {
    SdfLayerHandle layer;
    SdfLayerOffset layerOffset;
    std::string authoredAssetPath;
};

/// A vector of reference or payload arc information.
typedef std::vector<PcpSourceArcInfo> PcpSourceArcInfoVector;

/// References
PCP_API
void
PcpComposeSiteReferences(PcpLayerStackRefPtr const &layerStack,
                         SdfPath const &path,
                         SdfReferenceVector *result,
                         PcpSourceArcInfoVector *info);
inline void
PcpComposeSiteReferences(PcpNodeRef const &node,
                         SdfReferenceVector *result,
                         PcpSourceArcInfoVector *info)
{
    return PcpComposeSiteReferences(node.GetLayerStack(), node.GetPath(),
                                    result, info);
}

/// Payloads
PCP_API
void
PcpComposeSitePayloads(PcpLayerStackRefPtr const &layerStack,
                       SdfPath const &path,
                       SdfPayloadVector *result,
                       PcpSourceArcInfoVector *info);
inline void
PcpComposeSitePayloads(PcpNodeRef const &node,
                       SdfPayloadVector *result,
                       PcpSourceArcInfoVector *info)
{
    return PcpComposeSitePayloads(node.GetLayerStack(), node.GetPath(),
                                  result, info);
}

/// Permission
PCP_API
SdfPermission
PcpComposeSitePermission(PcpLayerStackRefPtr const &layerStack,
                         SdfPath const &path);

inline SdfPermission
PcpComposeSitePermission(PcpNodeRef const &node)
{
    return PcpComposeSitePermission(node.GetLayerStack(), node.GetPath());
}

/// Prim sites
PCP_API
void
PcpComposeSitePrimSites(PcpLayerStackRefPtr const &layerStack,
                        SdfPath const &path,
                        SdfSiteVector *result);

inline void
PcpComposeSitePrimSites(PcpNodeRef const &node, SdfSiteVector *result)
{
    return PcpComposeSitePrimSites(
        node.GetLayerStack(), node.GetPath(), result);
}

/// Relocates
PCP_API
void
PcpComposeSiteRelocates(PcpLayerStackRefPtr const &layerStack,
                        SdfPath const &path,
                        SdfRelocatesMap *result);

inline void
PcpComposeSiteRelocates(PcpNodeRef const &node, SdfRelocatesMap *result)
{
    return PcpComposeSiteRelocates(
        node.GetLayerStack(), node.GetPath(), result);
}

/// Has prim specs.
PCP_API
bool
PcpComposeSiteHasPrimSpecs(PcpLayerStackRefPtr const &layerStack,
                           SdfPath const &path);
inline bool
PcpComposeSiteHasPrimSpecs(PcpNodeRef const &node)
{
    return PcpComposeSiteHasPrimSpecs(node.GetLayerStack(), node.GetPath());
}

/// Symmetry
PCP_API
bool
PcpComposeSiteHasSymmetry(PcpLayerStackRefPtr const &layerStack,
                          SdfPath const &path);
inline bool
PcpComposeSiteHasSymmetry(PcpNodeRef const &node)
{
    return PcpComposeSiteHasSymmetry(node.GetLayerStack(), node.GetPath());
}

/// Inherits
PCP_API
void
PcpComposeSiteInherits(PcpLayerStackRefPtr const &layerStack,
                       SdfPath const &path, SdfPathVector *result,
                       PcpSourceArcInfoVector *info);

PCP_API
void
PcpComposeSiteInherits(PcpLayerStackRefPtr const &layerStack,
                       SdfPath const &path, SdfPathVector *result);

inline void
PcpComposeSiteInherits(PcpNodeRef const &node, SdfPathVector *result)
{
    return PcpComposeSiteInherits(node.GetLayerStack(), node.GetPath(), result);
}

/// Specializes
PCP_API
void
PcpComposeSiteSpecializes(PcpLayerStackRefPtr const &layerStack,
                          SdfPath const &path, SdfPathVector *result,
                          PcpSourceArcInfoVector *info);

PCP_API
void
PcpComposeSiteSpecializes(PcpLayerStackRefPtr const &layerStack,
                          SdfPath const &path, SdfPathVector *result);

inline void
PcpComposeSiteSpecializes(PcpNodeRef const &node, SdfPathVector *result)
{
    return PcpComposeSiteSpecializes(
        node.GetLayerStack(), node.GetPath(), result);
}

/// VariantSets
PCP_API
void
PcpComposeSiteVariantSets(PcpLayerStackRefPtr const &layerStack,
                          SdfPath const &path,
                          std::vector<std::string> *result,
                          PcpSourceArcInfoVector *info);

PCP_API
void
PcpComposeSiteVariantSets(PcpLayerStackRefPtr const &layerStack,
                          SdfPath const &path,
                          std::vector<std::string> *result);
inline void
PcpComposeSiteVariantSets(PcpNodeRef const &node,
                          std::vector<std::string> *result) {
    return PcpComposeSiteVariantSets(
        node.GetLayerStack(), node.GetPath(), result);
}

/// VariantSetOptions
PCP_API
void
PcpComposeSiteVariantSetOptions(PcpLayerStackRefPtr const &layerStack,
                                SdfPath const &path,
                                std::string const &vsetName,
                                std::set<std::string> *result);
inline void
PcpComposeSiteVariantSetOptions(PcpNodeRef const &node,
                                std::string const &vsetName,
                                std::set<std::string> *result)
{
    return PcpComposeSiteVariantSetOptions(
        node.GetLayerStack(), node.GetPath(), vsetName, result);
}

/// VariantSelection
PCP_API
bool
PcpComposeSiteVariantSelection(PcpLayerStackRefPtr const &layerStack,
                               SdfPath const &path,
                               std::string const &vsetName,
                               std::string *result);
inline bool
PcpComposeSiteVariantSelection(PcpNodeRef const &node,
                               std::string const &vsetName,
                               std::string *result)
{
    return PcpComposeSiteVariantSelection(node.GetLayerStack(), node.GetPath(),
                                          vsetName, result);
}

/// VariantSelections
PCP_API
void
PcpComposeSiteVariantSelections(PcpLayerStackRefPtr const &layerStack,
                                SdfPath const &path,
                                SdfVariantSelectionMap *result);
inline void
PcpComposeSiteVariantSelections(PcpNodeRef const &node,
                                SdfVariantSelectionMap *result)
{
    return PcpComposeSiteVariantSelections(node.GetLayerStack(), node.GetPath(),
                                           result);
}

/// Compose child names.
/// If the optional \p orderField is provided, its order will be applied.
PCP_API
void
PcpComposeSiteChildNames(SdfLayerRefPtrVector const &layers,
                         SdfPath const &path,
                         const TfToken & namesField,
                         TfTokenVector *nameOrder,
                         PcpTokenSet *nameSet,
                         const TfToken *orderField = nullptr);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_COMPOSE_SITE_H
