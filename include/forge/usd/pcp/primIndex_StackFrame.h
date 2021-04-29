#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/primIndex_StackFrame.h"
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
#ifndef FORGE_USD_PCP_PRIM_INDEX_STACK_FRAME_H
#define FORGE_USD_PCP_PRIM_INDEX_STACK_FRAME_H

#include "forge/forge.h"
#include "forge/usd/pcp/arc.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/pcp/site.h"

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex;

/// \class PcpPrimIndex_StackFrame
///
/// Internal helper class for tracking recursive invocations of
/// the prim indexing algorithm.
///
class PcpPrimIndex_StackFrame
{
public:
    PcpPrimIndex_StackFrame(PcpLayerStackSite const &requestedSite,
                            PcpNodeRef const &parentNode,
                            PcpArc *arcToParent,
                            PcpPrimIndex_StackFrame *previousFrame,
                            PcpPrimIndex const *originatingIndex,
                            bool skipDuplicateNodes)
        : previousFrame(previousFrame)
        , requestedSite(requestedSite)
        , parentNode(parentNode)
        , arcToParent(arcToParent)
        , originatingIndex(originatingIndex)
        , skipDuplicateNodes(skipDuplicateNodes) {}

    /// Link to the previous recursive invocation.
    PcpPrimIndex_StackFrame* previousFrame;

    /// The site of the prim index being built by this recursive
    /// call to Pcp_BuildPrimIndex.
    PcpLayerStackSite requestedSite;

    /// The node in the parent graph that will be the parent of the prim index
    /// being built by this recursive call.
    PcpNodeRef parentNode;

    /// The arc connecting the prim index being built by this recursive
    /// call to the parent node in the previous stack frame.
    PcpArc* arcToParent;

    /// The outer-most index whose computation originated this recursive chain.
    /// This is meant for debugging support.
    PcpPrimIndex const *originatingIndex;

    /// Whether the prim index being built by this recursive call should
    /// skip adding nodes if another node exists with the same site.
    bool skipDuplicateNodes;
};

/// \class PcpPrimIndex_StackFrameIterator
///
/// Iterator for walking up a node's ancestors while potentially crossing
/// stack frames.
///
class PcpPrimIndex_StackFrameIterator
{
public:
    PcpNodeRef node;
    PcpPrimIndex_StackFrame* previousFrame;

    PcpPrimIndex_StackFrameIterator(
        const PcpNodeRef& n, PcpPrimIndex_StackFrame* f)
        : node(n)
        , previousFrame(f)
    {
    }

    /// Step to the next parent node.
    void Next()
    {
        if (node.GetArcType() != PcpArcTypeRoot) {
            // Step to the next parent within this graph.
            node = node.GetParentNode();
        } else if (previousFrame) {
            // No more parents in this graph, but there is an outer
            // prim index that this node will become part of.
            // Step to the (eventual) parent in that graph.
            node = previousFrame->parentNode;
            previousFrame = previousFrame->previousFrame;
        } else {
            // No more parents.
            node = PcpNodeRef();
        }
    }

    /// Step to the first parent node in the next recursive call.
    void NextFrame()
    {
        if (previousFrame) {
            node = previousFrame->parentNode;
            previousFrame = previousFrame->previousFrame;
        }
        else {
            node = PcpNodeRef();
        }
    }

    /// Get the type of arc connecting the current node with its parent.
    PcpArcType GetArcType()
    {
        if (node.GetArcType() != PcpArcTypeRoot) {
            // Use the current node's arc type.
            return node.GetArcType();
        } else if (previousFrame) {
            // No more parents in this graph, but there is an outer
            // prim index, so consult arcToParent.
            return previousFrame->arcToParent->type;
        } else {
            // No more parents; this must be the absolute final root.
            return PcpArcTypeRoot;
        }
    }
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_PRIM_INDEX_STACK_FRAME_H
