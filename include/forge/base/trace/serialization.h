#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/serialization.h"
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

#ifndef FORGE_BASE_TRACE_SERIALIZATION_H
#define FORGE_BASE_TRACE_SERIALIZATION_H

#include "forge/forge.h"
#include "forge/base/trace/api.h"
#include "forge/base/trace/collection.h"

#include <istream>
#include <ostream>
#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceSerialization
///
/// This class contains methods to read and write TraceCollection.
///
class TraceSerialization {
public:
    /// Writes \p col to \p ostr.
    /// Returns true if the write was successful, false otherwise.
    TRACE_API static bool Write(std::ostream& ostr,
        const std::shared_ptr<TraceCollection>& col);

    /// Writes \p collections to \p ostr.
    /// Returns true if the write was successful, false otherwise.
    TRACE_API static bool Write(
        std::ostream& ostr,
        const std::vector<std::shared_ptr<TraceCollection>>& collections);

    /// Tries to create a TraceCollection from the contexts of \p istr.
    /// Returns a pointer to the created collection if it was successful.
    /// If there is an error reading \p istr, \p error will be populated with a
    /// description.
    TRACE_API static std::unique_ptr<TraceCollection> Read(std::istream& istr,
        std::string* error = nullptr);
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_SERIALIZATION_H