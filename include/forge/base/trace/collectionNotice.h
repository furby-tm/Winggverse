#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/collectionNotice.h"
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

#ifndef FORGE_BASE_TRACE_COLLECTION_NOTICE_H
#define FORGE_BASE_TRACE_COLLECTION_NOTICE_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"
#include "forge/base/tf/notice.h"
#include "forge/base/trace/collection.h"

FORGE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
/// \class TraceCollectionAvailable
///
/// A TfNotice that is sent when the TraceCollector creates a TraceCollection.
/// This can potentially be sent from multiple threads. Listeners must be
/// thread safe.
class TraceCollectionAvailable : public TfNotice
{
public:
    /// Constructor.
    TraceCollectionAvailable(const std::shared_ptr<TraceCollection>& collection)
        : _collection(collection)
    {}

    /// Destructor.
    TRACE_API virtual ~TraceCollectionAvailable();

    /// Returns the TraceCollection which was produced.
    const std::shared_ptr<TraceCollection>& GetCollection() const {
        return _collection;
    }

private:
    std::shared_ptr<TraceCollection> _collection;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_COLLECTION_NOTICE_H