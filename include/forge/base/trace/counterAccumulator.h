#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/counterAccumulator.h"
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

#ifndef FORGE_BASE_TRACE_COUNTER_ACCUMULATOR_H
#define FORGE_BASE_TRACE_COUNTER_ACCUMULATOR_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/collection.h"

#include "forge/base/tf/token.h"

#include <map>
#include <unordered_map>
#include <vector>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceCounterAccumulator
///
/// This class accumulates counter values from TraceCollection instances.
/// A TraceCounterAccumulator instance can accumulate counters from multiple
/// collections or the state of the counters can be set explicitly through
/// SetCurrentValues().
///
///
class TraceCounterAccumulator : private TraceCollection::Visitor {
public:
    using CounterValues = std::vector<std::pair<TraceEvent::TimeStamp, double>>;
    using CounterValuesMap =
        std::unordered_map<TfToken, CounterValues, TfToken::HashFunctor>;
    using CounterMap =
        std::unordered_map<TfToken, double, TfToken::HashFunctor>;

    /// Constructor.
    TraceCounterAccumulator() = default;

    /// Returns a map of the counter values over time.
    const CounterValuesMap& GetCounters() const {
        return _counterValuesOverTime;
    }

    /// Sets the current value of the counters.
    TRACE_API void SetCurrentValues(const CounterMap&);

    /// Returns the current value of the counters.
    const CounterMap& GetCurrentValues() const {
        return _currentValues;
    }

    /// Reads events /p collection and updates the current values of the
    /// counters.
    TRACE_API void Update(const TraceCollection& collection);

protected:
    /// Determines whether or not counter events with \p id should be processed.
    virtual bool _AcceptsCategory(TraceCategoryId id) = 0;

private:
    // TraceCollection::Visitor Interface
    virtual void OnBeginCollection() override;
    virtual void OnEndCollection() override;
    virtual void OnBeginThread(const TraceThreadId&) override;
    virtual void OnEndThread(const TraceThreadId&) override;
    virtual bool AcceptsCategory(TraceCategoryId) override;
    virtual void OnEvent(
        const TraceThreadId&, const TfToken&, const TraceEvent&) override;

    struct _CounterValue {
        double value;
        bool isDelta;
    };

    using _CounterDeltaValues =
        std::multimap<TraceEvent::TimeStamp, _CounterValue>;
    using _CounterDeltaMap = std::map<TfToken, _CounterDeltaValues>;

    _CounterDeltaMap _counterDeltas;
    CounterValuesMap _counterValuesOverTime;
    CounterMap _currentValues;
};

FORGE_NAMESPACE_END

#endif //FORGE_BASE_TRACE_COUNTER_ACCUMULATOR_H