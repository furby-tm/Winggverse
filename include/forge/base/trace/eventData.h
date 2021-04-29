#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/eventData.h"
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

#ifndef FORGE_BASE_TRACE_EVENT_DATA_H
#define FORGE_BASE_TRACE_EVENT_DATA_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/event.h"

#include <boost/variant.hpp>
#include <string>

FORGE_NAMESPACE_BEGIN

class JsWriter;
////////////////////////////////////////////////////////////////////////////////
///
/// \class TraceEventData
///
/// This class holds data that can be stored in TraceEvents.
///
class TraceEventData {
public:
    /// Ctor for Invalid type.
    TraceEventData() : _data(_NoData()) {}

    /// Ctor for Bool type.
    explicit TraceEventData(bool b) : _data(b) {}

    /// Ctor for Int type.
    explicit TraceEventData(int64_t i) : _data(i) {}

    /// Ctor for UInt type.
    explicit TraceEventData(uint64_t i) : _data(i) {}

    /// Ctor for Float type.
    explicit TraceEventData(double d) : _data(d) {}

    /// Ctor for String type.
    explicit TraceEventData(const std::string& s) : _data(s) {}

    /// Returns the Type of the data stored.
    TRACE_API TraceEvent::DataType GetType() const;

    /// Returns a pointer to the data or nullptr if the type is not Int.
    TRACE_API const int64_t* GetInt() const;

    /// Returns a pointer to the data or nullptr if the type is not UInt.
    TRACE_API const uint64_t* GetUInt() const;

    /// Returns a pointer to the data or nullptr if the type is not Float.
    TRACE_API const double* GetFloat() const;

    /// Returns a pointer to the data or nullptr if the type is not Bool.
    TRACE_API const bool* GetBool() const;

    /// Returns a pointer to the data or nullptr if the type is not String.
    TRACE_API const std::string* GetString() const;

    /// Writes a json representation of the data.
    TRACE_API void WriteJson(JsWriter&) const;

private:
    // Type that represents no data was stored in an event.
    struct _NoData {};

    using Variant =
        boost::variant<_NoData, std::string, bool, int64_t, uint64_t, double>;
    Variant _data;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_EVENT_DATA_H