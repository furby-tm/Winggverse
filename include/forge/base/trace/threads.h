#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/threads.h"
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

#ifndef FORGE_BASE_TRACE_THREADS_H
#define FORGE_BASE_TRACE_THREADS_H

#include "forge/forge.h"
#include "forge/base/trace/api.h"

#include <string>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class ThraceThreadId
///
/// This class represents an identifier for a thread.
///
class TraceThreadId {
public:
    /// Constructor which creates an identifier based on std::thread_id. .
    /// It is either"Main Thread" if this id is marked as the main thread or
    ///  "Thread XXX" where XXX is the string representation of the thread id.
    TRACE_API TraceThreadId();

    /// Constructor which creates an identifier from \p id.
    TRACE_API explicit TraceThreadId(const std::string& id);

    /// Returns the string representation of the id.
    const std::string& ToString() const { return _id; }

    /// Equality operator.
    TRACE_API bool operator==(const TraceThreadId&) const;

    /// Less than operator.
    TRACE_API bool operator<(const TraceThreadId&) const;
private:
    std::string _id;
};

inline TraceThreadId TraceGetThreadId() {
    return  TraceThreadId();
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_THREADS_H
