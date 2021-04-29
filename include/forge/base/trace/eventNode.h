#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/eventNode.h"
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

#ifndef FORGE_BASE_TRACE_EVENT_NODE_H
#define FORGE_BASE_TRACE_EVENT_NODE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/event.h"
#include "forge/base/trace/eventData.h"

#include "forge/base/tf/refBase.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/token.h"
#include "forge/base/tf/declarePtrs.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_REF_PTRS(TraceEventNode);

////////////////////////////////////////////////////////////////////////////////
/// \class TraceEventNode
///
/// TraceEventNode is used to represents call tree of a trace. Each node
/// represents a Begin-End trace event pair, or a single Timespan event. This is
/// useful for timeline views of a trace.
///

class TraceEventNode : public TfRefBase {
public:

    using TimeStamp = TraceEvent::TimeStamp;
    using AttributeData = TraceEventData;
    using AttributeMap = std::multimap<TfToken, AttributeData>;

    /// Creates a new root node.
    ///
    static TraceEventNodeRefPtr New() {
        return TraceEventNode::New(
            TfToken("root"), TraceCategory::Default, 0.0, 0.0, {}, false);
    }

    /// Creates a new node with \p key, \p category, \p beginTime and
    /// \p endTime.
    static TraceEventNodeRefPtr New(const TfToken &key,
                          const TraceCategoryId category,
                          const TimeStamp beginTime,
                          const TimeStamp endTime,
                          TraceEventNodeRefPtrVector&& children,
                          const bool separateEvents) {
        return TfCreateRefPtr(
            new TraceEventNode(
                key,
                category,
                beginTime,
                endTime,
                std::move(children),
                separateEvents));
    }

    /// Appends a new child node with \p key, \p category, \p beginTime and
    /// \p endTime.
    TraceEventNodeRefPtr Append(const TfToken &key,
                                      TraceCategoryId category,
                                      TimeStamp beginTime,
                                      TimeStamp endTime,
                                      bool separateEvents);

    /// Appends \p node as a child node.
    void Append(TraceEventNodeRefPtr node);

    /// Returns the name of this node.
    TfToken GetKey() { return _key;}

    /// Returns the category of this node.
    TraceCategoryId GetCategory() const { return _category; }

    /// Sets this node's begin and end time to the time extents of its direct
    /// children.
    void SetBeginAndEndTimesFromChildren();

    /// \name Profile Data Accessors
    /// @{

    /// Returns the time that this scope started.
    TimeStamp GetBeginTime() { return _beginTime; }

    /// Returns the time that this scope ended.
    TimeStamp GetEndTime()   { return _endTime; }

    /// @}

    /// \name Children Accessors
    /// @{

    /// Returns references to the children of this node.
    const TraceEventNodeRefPtrVector &GetChildrenRef() {
        return _children;
    }

    /// @}

    /// Return the data associated with this node.
    const AttributeMap& GetAttributes() const { return _attributes; }

    /// Add data to this node.
    void AddAttribute(const TfToken& key, const AttributeData& attr);

    /// Returns whether this node was created from a Begin-End pair or a single
    /// Timespan event.
    bool IsFromSeparateEvents() const {
        return _fromSeparateEvents;
    }

private:

    TraceEventNode(
        const TfToken &key,
        TraceCategoryId category,
        TimeStamp beginTime,
        TimeStamp endTime,
        TraceEventNodeRefPtrVector&& children,
        bool separateEvents)

        : _key(key)
        , _category(category)
        , _beginTime(beginTime)
        , _endTime(endTime)
        , _children(std::move(children))
        , _fromSeparateEvents(separateEvents)
    {}


    TfToken _key;
    TraceCategoryId _category;
    TimeStamp _beginTime;
    TimeStamp _endTime;
    TraceEventNodeRefPtrVector _children;
    bool _fromSeparateEvents;

    AttributeMap _attributes;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_EVENT_NODE_H
