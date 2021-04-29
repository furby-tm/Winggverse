#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/collection.h"
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

#ifndef FORGE_BASE_TRACE_COLLECTION_H
#define FORGE_BASE_TRACE_COLLECTION_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/event.h"
#include "forge/base/trace/eventList.h"
#include "forge/base/trace/threads.h"

#include "forge/base/tf/mallocTag.h"

#include <map>
#include <unordered_map>

FORGE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
///
/// \class TraceCollection
///
/// This class owns lists of TraceEvent instances per thread, and allows
/// read access to them.
///
class TraceCollection {
public:
    TF_MALLOC_TAG_NEW("Trace", "TraceCollection");

    using This = TraceCollection;

    using EventList = TraceEventList;
    using EventListPtr = std::unique_ptr<EventList>;

    /// Constructor.
    TraceCollection() = default;

    /// Move constructor.
    TraceCollection(TraceCollection&&) = default;

    /// Move assignment operator.
    TraceCollection& operator=(TraceCollection&&) = default;

    // Collections should not be copied because TraceEvents contain
    // pointers to elements in the Key cache.
    TraceCollection(const TraceCollection&) = delete;
    TraceCollection& operator=(const TraceCollection&) = delete;


    /// Appends \p events to the collection. The collection will
    /// take ownership of the data.
    TRACE_API void AddToCollection(const TraceThreadId& id, EventListPtr&& events);

    ////////////////////////////////////////////////////////////////////////
    ///
    /// \class Visitor
    ///
    /// This interface provides a way to access data a TraceCollection.
    ///
    class Visitor {
    public:
        /// Destructor
        TRACE_API virtual ~Visitor();

        /// Called at the beginning of an iteration.
        virtual void OnBeginCollection() = 0;

        /// Called at the end of an iteration.
        virtual void OnEndCollection() = 0;

        /// Called before the first event of from the thread with
        /// \p threadId is encountered.
        virtual void OnBeginThread(const TraceThreadId& threadId) = 0;

        /// Called after the last event of from the thread with
        /// \p threadId is encountered.
        virtual void OnEndThread(const TraceThreadId& threadId) = 0;

        /// Called before an event with \p categoryId is visited. If the
        /// return value is false, the event will be visited.
        virtual bool AcceptsCategory(TraceCategoryId categoryId) = 0;

        /// Called for every event \p event with \p key on thread
        /// \p threadId if AcceptsCategory returns true.
        virtual void OnEvent(
            const TraceThreadId& threadId,
            const TfToken& key,
            const TraceEvent& event) = 0;
    };

    /// Forward iterates over the events of the collection and calls the
    /// \p visitor callbacks.
    TRACE_API void Iterate(Visitor& visitor) const;

    /// Reverse iterates over the events of the collection and calls the
    /// \p visitor callbacks.
    TRACE_API void ReverseIterate(Visitor& visitor) const;

private:
    using KeyTokenCache =
        std::unordered_map<TraceKey, TfToken, TraceKey::HashFunctor>;

    /// Iterate through threads, then choose either forward or reverse
    /// iteration for the events in the threads
    void _Iterate(Visitor& visitor, bool doReverse) const;

    // Iterate through events in either forward or reverse order, depending on
    // the templated arguments
    template <class I>
    void _IterateEvents(Visitor&, KeyTokenCache&,
        const TraceThreadId&, I, I) const;

    using EventTable = std::map<TraceThreadId, EventListPtr>;

    EventTable _eventsPerThread;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_COLLECTION_H
