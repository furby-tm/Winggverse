#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/category.h"
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

#ifndef FORGE_BASE_TRACE_CATEGORY_H
#define FORGE_BASE_TRACE_CATEGORY_H

/// \file trace/category.h

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/tf/singleton.h"
#include "forge/base/trace/stringHash.h"

#include <cstdint>
#include <map>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// Categories that a TraceReporter can use to filter events.
using TraceCategoryId = uint32_t;

///////////////////////////////////////////////////////////////////////////////
///
/// \class TraceCategory
///
/// This singleton class provides a way to mark TraceEvent instances with
/// category Ids which can be used to filter them. This class also provides a
/// way to associate TraceCategoryId values with human readable names.
///
class TraceCategory {
public:
    /// Computes an id for the given a string literal \p str.
    template <int N>
    static constexpr TraceCategoryId CreateTraceCategoryId(
        const char (&str)[N]) {
        return TraceStringHash::Hash(str);
    }

    /// Default category if none are explicitly specified when creating a
    /// TraceEvent.
    enum : TraceCategoryId { Default = 0 };

    /// Associates the \p id with \p name. These associates are not necessarily
    /// unique.
    TRACE_API void RegisterCategory(TraceCategoryId id, const std::string& name);

    /// Returns all names associated with the \p id.
    TRACE_API std::vector<std::string> GetCategories(TraceCategoryId id) const;

    /// Singleton accessor.
    TRACE_API static TraceCategory& GetInstance();

private:
    friend class TfSingleton<TraceCategory>;

    TraceCategory();

    // Mapping of ids to names.
    std::multimap<TraceCategoryId, std::string> _idToNames;
};

TRACE_API_TEMPLATE_CLASS(TfSingleton<TraceCategory>);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_CATEGORY_H
