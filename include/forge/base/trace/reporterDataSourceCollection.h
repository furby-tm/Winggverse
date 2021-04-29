#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/reporterDataSourceCollection.h"
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

#ifndef FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_COLLECTION_H
#define FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_COLLECTION_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/trace/collection.h"
#include "forge/base/trace/reporterDataSourceBase.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceReporterDataSourceCollection
///
/// This class is an implementation of TraceReporterDataSourceBase which provides
/// access to a set number of TraceCollection instances. This class is useful if
/// you want to generate reports from serialized TraceCollections.
///
class TraceReporterDataSourceCollection : public TraceReporterDataSourceBase {
public:
    using This = TraceReporterDataSourceCollection;
    using ThisRefPtr = std::unique_ptr<This>;

    static ThisRefPtr New(CollectionPtr collection) {
        return ThisRefPtr(new This(collection));
    }
    static ThisRefPtr New(std::vector<CollectionPtr> collections) {
        return ThisRefPtr(new This(std::move(collections)));
    }

    /// Removes all references to TraceCollections.
    TRACE_API void Clear() override;

    /// Returns the next TraceCollections which need to be processed.
    TRACE_API std::vector<CollectionPtr> ConsumeData() override;

private:
    TRACE_API TraceReporterDataSourceCollection(CollectionPtr collection);
    TRACE_API TraceReporterDataSourceCollection(
        std::vector<CollectionPtr> collections);

    std::vector<CollectionPtr> _data;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_REPORTER_DATA_SOURCE_COLLECTION_H