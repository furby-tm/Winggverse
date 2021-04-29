#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/aggregateTreeBuilder.h"
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

#ifndef FORGE_BASE_TRACE_AGGREGATE_TREE_BUILDER_H
#define FORGE_BASE_TRACE_AGGREGATE_TREE_BUILDER_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/collection.h"
#include "forge/base/trace/aggregateTree.h"
#include "forge/base/trace/eventTree.h"

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class Trace_AggregateTreeBuilder
///
/// This class populates a tree of TraceAggregateTree instances from
/// TraceCollection instances.
///
///
class Trace_AggregateTreeBuilder : private TraceCollection::Visitor
{
public:
    static void AddEventTreeToAggregate(
        TraceAggregateTree* aggregateTree,
        const TraceEventTreeRefPtr& eventTree,
        const TraceCollection& collection);

private:
    Trace_AggregateTreeBuilder(
        TraceAggregateTree* tree, const TraceEventTreeRefPtr& eventTree);

    void _ProcessCounters(const TraceCollection& collection);

    void _CreateAggregateNodes();

    // TraceCollection::Visitor interface
    virtual void OnBeginCollection() override;
    virtual void OnEndCollection() override;
    virtual void OnBeginThread(const TraceThreadId& threadId) override;
    virtual void OnEndThread(const TraceThreadId& threadId) override;
    virtual bool AcceptsCategory(TraceCategoryId categoryId) override;
    virtual void OnEvent(
        const TraceThreadId& threadIndex,
        const TfToken& key,
        const TraceEvent& e) override;

    void _OnCounterEvent(const TraceThreadId& threadIndex,
        const TfToken& key,
        const TraceEvent& e);

    TraceAggregateNodePtr _FindAggregateNode(
        const TraceThreadId& threadId, const TraceEvent::TimeStamp ts) const ;

    TraceAggregateTree* _aggregateTree;
    TraceEventTreeRefPtr _tree;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_AGGREGATE_TREE_BUILDER_H
