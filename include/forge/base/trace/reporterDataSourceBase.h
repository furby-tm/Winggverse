#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/reporterDataSourceBase.h"
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

#ifndef FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_BASE_H
#define FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_BASE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/collection.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceReporterDataSourceBase
///
/// This class is a base class for TraceReporterBase data sources.
/// TraceReporterBase uses an instance of a TraceReporterDataSourceBase derived
/// class to access TraceCollections.
///
class TraceReporterDataSourceBase {
public:
    using CollectionPtr = std::shared_ptr<TraceCollection>;

    /// Destructor
    TRACE_API virtual ~TraceReporterDataSourceBase();

    /// Removes all references to TraceCollections.
    virtual void Clear() = 0;

    /// Returns the next TraceCollections which need to be processed.
    virtual std::vector<CollectionPtr> ConsumeData() = 0;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_BASE_H