#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/arc.h"
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
#ifndef FORGE_USD_PCP_ARC_H
#define FORGE_USD_PCP_ARC_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/mapExpression.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/pcp/types.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex_Graph;

/// \class PcpArc
///
/// Represents an arc connecting two nodes in the prim index.
/// The arc is owned by a node (source) and points to its parent node (target)
/// in the index.
///
class PcpArc
{
public:
    PcpArc()
        : type(PcpArcTypeRoot)
        , siblingNumAtOrigin(0)
        , namespaceDepth(0)
    { }

    /// The type of this arc.
    PcpArcType type;

    /// The parent (or target) node of this arc.
    /// If this arc's source node is a root node (i.e., type == PcpArcTypeRoot),
    /// this will be an invalid node.
    PcpNodeRef parent;

    /// The origin node of this arc.
    /// This is the node that caused this arc's source node to be brought into
    /// the prim index. In most cases, this will be the same as the parent node.
    /// For implied inherits, this is the node from which this inherit arc was
    /// propagated. This affects strength ordering.
    PcpNodeRef origin;

    /// The value-mapping function used to map values from this arc's source
    /// node to its parent node.
    PcpMapExpression mapToParent;

    // index among sibling arcs at origin; lower is stronger
    int siblingNumAtOrigin;

    // Absolute depth in namespace of node that introduced this node.
    // Note that this does *not* count any variant selections.
    int namespaceDepth;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_ARC_H
