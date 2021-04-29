#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/dependency.h"
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
#ifndef FORGE_USD_PCP_DEPENDENCY_H
#define FORGE_USD_PCP_DEPENDENCY_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/mapFunction.h"
#include "forge/usd/sdf/path.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

class PcpNodeRef;

/// \enum PcpDependencyType
///
/// A classification of PcpPrimIndex->PcpSite dependencies
/// by composition structure.
///
enum PcpDependencyType {
    /// No type of dependency.
    PcpDependencyTypeNone = 0,

    /// The root dependency of a cache on its root site.
    /// This may be useful to either include, as when invalidating
    /// caches in response to scene edits, or to exclude, as when
    /// scanning dependency arcs to compensate for a namespace edit.
    PcpDependencyTypeRoot = (1 << 0),

    /// Purely direct dependencies involve only arcs introduced
    /// directly at this level of namespace.
    PcpDependencyTypePurelyDirect = (1 << 1),

    /// Partly direct dependencies involve at least one arc introduced
    /// directly at this level of namespace; they may also involve
    /// ancestral arcs along the chain as well.
    PcpDependencyTypePartlyDirect = (1 << 2),

    /// Ancestral dependencies involve only arcs from ancestral
    /// levels of namespace, and no direct arcs.
    PcpDependencyTypeAncestral = (1 << 3),

    /// Virtual dependencies do not contribute scene description,
    /// yet represent sites whose scene description (or ancestral
    /// scene description) informed the structure of the cache.
    ///
    /// One case of this is when a reference or payload arc
    /// does not specify a prim, and the target layerStack does
    /// not provide defaultPrim metadata either.  In that case
    /// a virtual dependency to the root of that layer stack will
    /// represent the latent dependency on that site's metadata.
    ///
    /// Another case of this is "spooky ancestral" dependencies from
    /// relocates. These are referred to as "spooky" dependencies
    /// because they can be seen as a form of action-at-a-distance. They
    /// only occur as a result of relocation arcs.
    PcpDependencyTypeVirtual = (1 << 4),
    PcpDependencyTypeNonVirtual = (1 << 5),

    /// Combined mask value representing both pure and partly direct
    /// deps.
    PcpDependencyTypeDirect =
        PcpDependencyTypePartlyDirect
        | PcpDependencyTypePurelyDirect,

    /// Combined mask value representing any kind of dependency,
    /// except virtual ones.
    PcpDependencyTypeAnyNonVirtual =
        PcpDependencyTypeRoot
        | PcpDependencyTypeDirect
        | PcpDependencyTypeAncestral
        | PcpDependencyTypeNonVirtual,

    /// Combined mask value representing any kind of dependency.
    PcpDependencyTypeAnyIncludingVirtual =
        PcpDependencyTypeAnyNonVirtual
        | PcpDependencyTypeVirtual,
};

/// A typedef for a bitmask of flags from PcpDependencyType.
typedef unsigned int PcpDependencyFlags;

/// Description of a dependency.
struct PcpDependency {
    /// The path in this PcpCache's root layer stack that depends
    /// on the site.
    SdfPath indexPath;
    /// The site path.  When using recurseDownNamespace, this may
    /// be a path beneath the initial sitePath.
    SdfPath sitePath;
    /// The map function that applies to values from the site.
    PcpMapFunction mapFunc;

    bool operator==(const PcpDependency &rhs) const {
        return indexPath == rhs.indexPath &&
            sitePath == rhs.sitePath &&
            mapFunc == rhs.mapFunc;
    }
    bool operator!=(const PcpDependency &rhs) const {
        return !(*this == rhs);
    }
};

typedef std::vector<PcpDependency> PcpDependencyVector;

/// Returns true if this node introduces a dependency in its
/// PcpPrimIndex, false otherwise.  This is equivalent to
/// PcpClassifyNodeDependency(n) != PcpDependencyTypeNone, but
/// is faster.
PCP_API
bool PcpNodeIntroducesDependency(const PcpNodeRef &n);

/// Classify the dependency represented by a node, by analyzing
/// its structural role in its PcpPrimIndex.  Returns a
/// bitmask of flags from PcpDependencyType.
PCP_API
PcpDependencyFlags PcpClassifyNodeDependency(const PcpNodeRef &n);

PCP_API
std::string PcpDependencyFlagsToString(const PcpDependencyFlags flags);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_DEPENDENCY_H
