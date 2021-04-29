#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/aggregateTree.h"
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

#ifndef FORGE_BASE_TRACE_AGGREGATE_TREE_H
#define FORGE_BASE_TRACE_AGGREGATE_TREE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/aggregateNode.h"

FORGE_NAMESPACE_BEGIN

class TraceCollection;

TF_DECLARE_WEAK_AND_REF_PTRS(TraceAggregateTree);
TF_DECLARE_WEAK_AND_REF_PTRS(TraceEventTree);

////////////////////////////////////////////////////////////////////////////////
/// \class TraceAggregateTree
///
/// A representation of a call tree. Each node represents one or more calls that
/// occurred in the trace. Multiple calls to a child node are aggregated into one
/// node.
///

class TraceAggregateTree : public TfRefBase, public TfWeakBase {
public:
    using This = TraceAggregateTree;
    using ThisPtr = TraceAggregateTreePtr;
    using ThisRefPtr = TraceAggregateTreeRefPtr;

    using TimeStamp = TraceEvent::TimeStamp;
    using EventTimes = std::map<TfToken, TimeStamp>;
    using CounterMap = TfHashMap<TfToken, double, TfToken::HashFunctor>;

    /// Create an empty tree
    static ThisRefPtr New() {
        return TfCreateRefPtr(new This());
    }

    /// Returns the root node of the tree.
    TraceAggregateNodePtr GetRoot() { return _root; }

    /// Returns a map of event keys to total inclusive time.
    const EventTimes& GetEventTimes() const { return _eventTimes; }

    /// Returns a map of counters (counter keys), associated with their total
    /// accumulated value. Each individual event node in the tree may also hold
    /// on to an inclusive and exclusive value for the given counter.
    const CounterMap& GetCounters() const { return _counters; }

    /// Returns the numeric index associated with a counter key. Counter values
    /// on the event nodes will have to be looked up by the numeric index.
    TRACE_API int GetCounterIndex(const TfToken &key) const;

    /// Add a counter to the tree. This method can be used to restore a
    /// previous trace state and tree. Note, that the counter being added must
    /// have a unique key and index. The method will return false if a key or
    /// index already exists.
    TRACE_API bool AddCounter(const TfToken &key, int index, double totalValue);

    /// Removes all data and nodes from the tree.
    TRACE_API void Clear();

    /// Creates new nodes and counter data from data in \p eventTree and \p
    /// collection.
    TRACE_API void Append(
        const TraceEventTreeRefPtr& eventTree,
        const TraceCollection& collection);

private:
    TRACE_API TraceAggregateTree();

    using _CounterIndexMap =TfHashMap<TfToken, int, TfToken::HashFunctor>;

    TraceAggregateNodeRefPtr _root;
    EventTimes _eventTimes;
    CounterMap _counters;
    _CounterIndexMap _counterIndexMap;
    int _counterIndex;

    friend class Trace_AggregateTreeBuilder;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_AGGREGATE_TREE_H
