#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/node_Iterator.h"
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
#ifndef FORGE_USD_PCP_NODE_ITERATOR_H
#define FORGE_USD_PCP_NODE_ITERATOR_H

/// \file pcp/node_Iterator.h

#include "forge/forge.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/pcp/primIndex_Graph.h"

FORGE_NAMESPACE_BEGIN

// These classes exist because we want to optimize the iteration of a
// node's children while not exposing the PcpPrimIndex_Graph implementation
// detail outside of Pcp.  PcpNodeRef_ChildrenIterator and
// PcpNodeRef_ChildrenReverseIterator perform the same functions but can't
// inline access to PcpPrimIndex_Graph.

/// \class PcpNodeRef_PrivateChildrenConstIterator
///
/// Object used to iterate over child nodes (not all descendant nodes) of a
/// node in the prim index graph in strong-to-weak order.
///
class PcpNodeRef_PrivateChildrenConstIterator
    : public boost::iterator_facade<
                 /* Derived =   */ PcpNodeRef_PrivateChildrenConstIterator,
                 /* ValueType = */ const PcpNodeRef,
                 /* Category =  */ boost::forward_traversal_tag
             >
{
public:
    // Required by TF_FOR_ALL but always assigned to afterwards.
    PcpNodeRef_PrivateChildrenConstIterator() { }

    /// Constructs an iterator pointing to \p node's first or past its
    /// last child.
    PcpNodeRef_PrivateChildrenConstIterator(const PcpNodeRef& node,
                                            bool end = false) :
        _node(node),
        _nodes(&_node._graph->_data->nodes[0])
    {
        _node._nodeIdx = end
            ? PcpPrimIndex_Graph::_Node::_invalidNodeIndex
            : _nodes[_node._nodeIdx].smallInts.firstChildIndex;
    }

private:
    friend class boost::iterator_core_access;
    void increment()
    {
        _node._nodeIdx = _nodes[_node._nodeIdx].smallInts.nextSiblingIndex;
    }

    bool equal(const PcpNodeRef_PrivateChildrenConstIterator& other) const
    {
        return _node == other._node;
    }

    reference dereference() const
    {
        return _node;
    }

private:
    // Current graph node this iterator is pointing at.
    PcpNodeRef _node;
    const PcpPrimIndex_Graph::_Node* _nodes;
};

/// \class PcpNodeRef_PrivateChildrenConstReverseIterator
///
/// Object used to iterate over child nodes (not all descendant nodes) of a
/// node in the prim index graph in weak-to-strong order.
///
class PcpNodeRef_PrivateChildrenConstReverseIterator
    : public boost::iterator_facade<
                 /* Derived =   */ PcpNodeRef_PrivateChildrenConstReverseIterator,
                 /* ValueType = */ const PcpNodeRef,
                 /* Category =  */ boost::forward_traversal_tag
             >
{
public:
    // Required by TF_FOR_ALL but always assigned to afterwards.
    PcpNodeRef_PrivateChildrenConstReverseIterator() { }

    /// Constructs an iterator pointing to \p node's first or past its
    /// last child.
    PcpNodeRef_PrivateChildrenConstReverseIterator(const PcpNodeRef& node,
                                                   bool end = false) :
        _node(node),
        _nodes(&_node._graph->_data->nodes[0])
    {
        _node._nodeIdx = end
            ? PcpPrimIndex_Graph::_Node::_invalidNodeIndex
            : _nodes[_node._nodeIdx].smallInts.lastChildIndex;
    }

private:
    friend class boost::iterator_core_access;
    void increment()
    {
        _node._nodeIdx = _nodes[_node._nodeIdx].smallInts.prevSiblingIndex;
    }

    bool equal(const PcpNodeRef_PrivateChildrenConstReverseIterator& other)const
    {
        return _node == other._node;
    }

    reference dereference() const
    {
        return _node;
    }

private:
    // Current graph node this iterator is pointing at.
    PcpNodeRef _node;
    const PcpPrimIndex_Graph::_Node* _nodes;
};

// Wrapper type for TF_FOR_ALL().
class PcpNodeRef_PrivateChildrenConstRange {
public:
    PcpNodeRef_PrivateChildrenConstRange(const PcpNodeRef& node_):node(node_){}
    PcpNodeRef node;
};

// TF_FOR_ALL() traits.  We build the iterators on demand.
template <>
struct Tf_IteratorInterface<PcpNodeRef_PrivateChildrenConstRange, false> {
    typedef PcpNodeRef_PrivateChildrenConstRange RangeType;
    typedef PcpNodeRef_PrivateChildrenConstIterator IteratorType;
    static IteratorType Begin(RangeType const &c)
    {
        return IteratorType(c.node, /* end = */ false);
    }
    static IteratorType End(RangeType const &c)
    {
        return IteratorType(c.node, /* end = */ true);
    }
};
template <>
struct Tf_IteratorInterface<PcpNodeRef_PrivateChildrenConstRange, true> {
    typedef PcpNodeRef_PrivateChildrenConstRange RangeType;
    typedef PcpNodeRef_PrivateChildrenConstReverseIterator IteratorType;
    static IteratorType Begin(RangeType const &c)
    {
        return IteratorType(c.node, /* end = */ false);
    }
    static IteratorType End(RangeType const &c)
    {
        return IteratorType(c.node, /* end = */ true);
    }
};
template <>
struct Tf_ShouldIterateOverCopy<PcpNodeRef_PrivateChildrenConstRange> :
    boost::true_type {};

// Wrap a node for use by TF_FOR_ALL().
inline
PcpNodeRef_PrivateChildrenConstRange
Pcp_GetChildrenRange(const PcpNodeRef& node)
{
    return PcpNodeRef_PrivateChildrenConstRange(node);
}

// Return all of a node's children, strong-to-weak.
inline
PcpNodeRefVector
Pcp_GetChildren(const PcpNodeRef& node)
{
    typedef PcpNodeRef_PrivateChildrenConstIterator IteratorType;
    return PcpNodeRefVector(IteratorType(node, /* end = */ false),
                            IteratorType(node, /* end = */ true));
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_NODE_ITERATOR_H
