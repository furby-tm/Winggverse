#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/aggregateNode.h"
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

#ifndef FORGE_BASE_TRACE_AGGREGATE_NODE_H
#define FORGE_BASE_TRACE_AGGREGATE_NODE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/event.h"
#include "forge/base/trace/threads.h"

#include "forge/base/tf/refBase.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/token.h"
#include "forge/base/tf/weakBase.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/arch/timing.h"

#include <vector>
#include "forge/base/tf/denseHashMap.h"

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(TraceAggregateNode);

////////////////////////////////////////////////////////////////////////////////
/// \class TraceAggregateNode
///
/// A representation of a call tree. Each node represents one or more calls that
/// occurred in the trace. Multiple calls to a child node are aggregated into one
/// node.
///

class TraceAggregateNode : public TfRefBase, public TfWeakBase {
public:

    using This = TraceAggregateNode;
    using ThisPtr = TraceAggregateNodePtr;
    using ThisRefPtr = TraceAggregateNodeRefPtr;

    using TimeStamp = TraceEvent::TimeStamp;

    // This class is only used for validity checks.
    // FIXME: This class should be removed.
    class Id
    {
    public:
        Id() : _valid(false) {}
        Id(const TraceThreadId&) : _valid(true) {}
        bool IsValid() const { return _valid; }
    private:
        bool _valid;
    };

    static ThisRefPtr New() {
        return This::New(Id(), TfToken("root"), 0, 0);
    }

    static ThisRefPtr New(const Id &id,
                          const TfToken &key,
                          const TimeStamp ts,
                          const int count = 1,
                          const int exclusiveCount = 1) {
        return TfCreateRefPtr(new This(id, key, ts, count, exclusiveCount));
    }

    TRACE_API TraceAggregateNodeRefPtr
    Append(Id id, const TfToken &key, TimeStamp ts,
           int c = 1, int xc = 1);

    TRACE_API void Append(TraceAggregateNodeRefPtr child);

    /// Returns the node's key.
    TfToken GetKey() { return _key;}

    /// Returns the node's id.
    const Id &GetId() { return _id;}

    /// \name Profile Data Accessors
    /// @{

    /// Returns the total time of this node ands its children.
    TimeStamp GetInclusiveTime() { return _ts; }

    /// Returns the time spent in this node but not its children.
    TRACE_API TimeStamp GetExclusiveTime(bool recursive = false);

    /// Returns the call count of this node. \p recursive determines if
    /// recursive calls are counted.
    int GetCount(bool recursive = false) const {
        return recursive ? _recursiveCount : _count;
    }

    /// Returns the exclusive count.
    int GetExclusiveCount() const { return _exclusiveCount; }

    /// @}


    /// \name Counter Value Accessors
    /// @{

    TRACE_API void AppendInclusiveCounterValue(int index, double value);

    TRACE_API double GetInclusiveCounterValue(int index) const;

    TRACE_API void AppendExclusiveCounterValue(int index, double value);

    TRACE_API double GetExclusiveCounterValue(int index) const;

    /// @}

    /// Recursively calculates the inclusive counter values from the inclusive
    /// and exclusive counts of child nodes.
    TRACE_API void CalculateInclusiveCounterValues();


    /// \name Children Accessors
    /// @{
    const TraceAggregateNodePtrVector GetChildren() {
        // convert to a vector of weak ptrs
        return TraceAggregateNodePtrVector( _children.begin(),_children.end() );
    }

    const TraceAggregateNodeRefPtrVector &GetChildrenRef() {
        return _children;
    }

    TRACE_API TraceAggregateNodeRefPtr GetChild(const TfToken &key);
    TraceAggregateNodeRefPtr GetChild(const std::string &key) {
        return GetChild(TfToken(key));
    }

    /// @}


    /// Sets whether or not this node is expanded in a gui.
    void SetExpanded(bool expanded) {
        _expanded = expanded;
    }

    /// Returns whether this node is expanded in a gui.
    bool IsExpanded() {
        return _expanded;
    }

    /// \name Recursion
    /// @{

    /// Scans the tree for recursive calls and updates the recursive counts.
    ///
    /// This call leaves the tree topology intact, and only updates the
    /// recursion-related data in the node.  Prior to this call, recursion
    /// data is invalid in the node.
    TRACE_API void MarkRecursiveChildren();

    /// Returns true if this node is simply a marker for a merged recursive
    /// subtree; otherwise returns false.
    ///
    /// This value is meaningless until this node or any of its ancestors have
    /// been marked with MarkRecursiveChildren().
    bool IsRecursionMarker() const { return _isRecursionMarker; }

    /// Returns true if this node is the head of a recursive call tree
    /// (i.e. the function has been called recursively).
    ///
    /// This value is meaningless until this node or any of its ancestors have
    /// been marked with MarkRecursiveChildren().
    bool IsRecursionHead() const { return _isRecursionHead; }

    /// @}


private:

    TraceAggregateNode(const Id &id, const TfToken &key, TimeStamp ts,
              int count, int exclusiveCount) :
        _id(id), _key(key), _ts(ts), _exclusiveTs(ts),
        _count(count), _exclusiveCount(exclusiveCount),
        _recursiveCount(count), _recursiveExclusiveTs(ts), _expanded(false),
        _isRecursionMarker(false), _isRecursionHead(false),
        _isRecursionProcessed(false) {}

    using _ChildDictionary = TfDenseHashMap<TfToken, size_t, TfHash>;

    void _MergeRecursive(const TraceAggregateNodeRefPtr &node);

    void _SetAsRecursionMarker(TraceAggregateNodePtr parent);

    Id _id;
    TfToken _key;

    TimeStamp _ts;
    TimeStamp _exclusiveTs;
    int _count;
    int _exclusiveCount;

    // We keep the recursive counts separate so that we don't mess with
    // the collected data.
    int _recursiveCount;
    TraceAggregateNodePtr _recursionParent;
    TimeStamp _recursiveExclusiveTs;

    TraceAggregateNodeRefPtrVector _children;
    _ChildDictionary _childrenByKey;

    // A structure that holds on to the inclusive and exclusive counter
    // values. These values are usually populated together, so it's beneficial
    // to maintain them in a tightly packed structure.
    struct _CounterValue {
        _CounterValue() : inclusive(0.0), exclusive(0.0) {}
        double inclusive;
        double exclusive;
    };

    using _CounterValues = TfDenseHashMap<int, _CounterValue, TfHash>;

    // The counter values associated with specific counter indices
    _CounterValues _counterValues;

    unsigned int
    // If multiple Trace Editors are to be pointed at the same Reporter, this
    // might have to be changed
                _expanded:1,

    // This flag keeps track of whether or not this node is simply intended
    // as a marker for the start of a recursive call tree.
                _isRecursionMarker:1,

    // This flag keeps track of whether or not a node is the head of a
    // recursive call tree.  In other words, if it is a function that has been
    // called recursively.
                _isRecursionHead:1,

    // This flag is used during recursive traversal to mark the node as having
    // been visited and avoid too much processing.
                _isRecursionProcessed:1;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_AGGREGATE_NODE_H
