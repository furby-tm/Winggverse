#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/reporterBase.h"
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

#ifndef FORGE_BASE_TRACE_REPORTER_BASE_H
#define FORGE_BASE_TRACE_REPORTER_BASE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/collectionNotice.h"
#include "forge/base/trace/collection.h"
#include "forge/base/trace/reporterDataSourceBase.h"

#include "forge/base/tf/declarePtrs.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_vector.h>
#endif /* Q_MOC_RUN */

#include <ostream>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(TraceReporterBase);

////////////////////////////////////////////////////////////////////////////////
/// \class TraceReporterBase
///
/// This class is a base class for report implementations. It handles receiving
/// and processing of TraceCollections.
///
///
class TraceReporterBase :
    public TfRefBase, public TfWeakBase {
public:
    using This = TraceReporterBase;
    using ThisPtr = TraceReporterBasePtr;
    using ThisRefPtr = TraceReporterBaseRefPtr;
    using CollectionPtr = std::shared_ptr<TraceCollection>;
    using DataSourcePtr = std::unique_ptr<TraceReporterDataSourceBase>;

    /// Constructor taking ownership of \p dataSource.
    TRACE_API TraceReporterBase(DataSourcePtr dataSource);

    /// Destructor.
    TRACE_API virtual ~TraceReporterBase();

    /// Write all collections that were processed by this reporter to \p ostr.
    TRACE_API bool SerializeProcessedCollections(std::ostream& ostr) const;
protected:
    /// Removes all references to TraceCollections.
    TRACE_API void _Clear();

    /// Gets the latest data from the TraceCollector singleton and processes all
    /// collections that have been received since the last call to _Update().
    TRACE_API void _Update();

    /// Called once per collection from _Update()
    virtual void _ProcessCollection(const CollectionPtr&) = 0;

private:
    DataSourcePtr _dataSource;
    tbb::concurrent_vector<CollectionPtr> _processedCollections;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_REPORTER_BASE_H
