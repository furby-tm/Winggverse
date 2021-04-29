#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/eventTreeBuilder.h"
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

#ifndef FORGE_BASE_TRACE_EVENT_TREE_BUILDER_H
#define FORGE_BASE_TRACE_EVENT_TREE_BUILDER_H

#include "forge/forge.h"

#include "forge/base/trace/collection.h"
#include "forge/base/trace/counterAccumulator.h"
#include "forge/base/trace/eventNode.h"
#include "forge/base/trace/eventTree.h"

FORGE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
///
/// \class Trace_EventTreeBuilder
///
/// This class creates a tree of TraceEventTree instances from
/// TraceCollection instances.
///
class Trace_EventTreeBuilder
    : protected TraceCollection::Visitor {
public:
    /// Constructor.
    Trace_EventTreeBuilder();

    /// Returns the created tree.
    TraceEventTreeRefPtr GetTree() { return _tree; }

    /// Creates a TraceEventTree from the data in /p collection.
    TRACE_API void CreateTree(const TraceCollection& collection);

    /// Set the value of the counters.
    void SetCounterValues(
        const TraceEventTree::CounterMap& counterValues) {
        _counterAccum.SetCurrentValues(counterValues);
    }

protected:
    /// \name TraceCollection::Visitor Interface
    /// @{
    virtual void OnBeginCollection() override;
    virtual void OnEndCollection() override;
    virtual bool AcceptsCategory(TraceCategoryId) override;
    virtual void OnBeginThread(const TraceThreadId&) override;
    virtual void OnEndThread(const TraceThreadId&) override;
    virtual void OnEvent(
        const TraceThreadId&, const TfToken&, const TraceEvent&) override;
    /// @}

private:

    // Helper class for event graph creation.
    struct _PendingEventNode {
        using TimeStamp = TraceEvent::TimeStamp;

        struct AttributeData {
            TimeStamp time;
            TfToken key;
            TraceEventNode::AttributeData data;
        };

        _PendingEventNode( const TfToken& key,
                                 TraceCategoryId category,
                                 TimeStamp start,
                                 TimeStamp end,
                                 bool separateEvents,
                                 bool isComplete);
        TraceEventNodeRefPtr Close();

        // Can move this, but not copy it
        _PendingEventNode(const _PendingEventNode&) = delete;
        _PendingEventNode& operator= (const _PendingEventNode&) = delete;

        _PendingEventNode(_PendingEventNode&&) = default;
        _PendingEventNode& operator= (_PendingEventNode&&) = default;

        TfToken key;
        TraceCategoryId category;
        TimeStamp start;
        TimeStamp end;
        bool separateEvents;
        bool isComplete;
        std::vector<TraceEventNodeRefPtr> children;
        std::vector<AttributeData> attributes;
    };

    void _OnBegin(const TraceThreadId&, const TfToken&, const TraceEvent&);
    void _OnEnd(const TraceThreadId&, const TfToken&, const TraceEvent&);
    void _OnData(const TraceThreadId&, const TfToken&, const TraceEvent&);
    void _OnTimespan(const TraceThreadId&, const TfToken&, const TraceEvent&);
    void _OnMarker(const TraceThreadId&, const TfToken&, const TraceEvent&);

    using _PendingNodeStack = std::vector<_PendingEventNode>;
    using _ThreadStackMap = std::map<TraceThreadId, _PendingNodeStack>;

    void _PopAndClose(_PendingNodeStack& stack);

    TraceEventNodeRefPtr _root;
    _ThreadStackMap _threadStacks;
    TraceEventTreeRefPtr _tree;

    class _CounterAccumulator : public TraceCounterAccumulator {
    protected:
        bool _AcceptsCategory(TraceCategoryId) override;
    };
    _CounterAccumulator _counterAccum;

    TraceEventTree::MarkerValuesMap _markersMap;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_EVENT_TREE_BUILDER_H