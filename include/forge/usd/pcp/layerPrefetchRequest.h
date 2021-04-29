#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/layerPrefetchRequest.h"
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
#ifndef FORGE_USD_PCP_LAYER_PREFETCH_REQUEST_H
#define FORGE_USD_PCP_LAYER_PREFETCH_REQUEST_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/sdf/layer.h"

#include <set>
#include <utility>

FORGE_NAMESPACE_BEGIN

class Pcp_MutedLayers;

/// \class PcpLayerPrefetchRequest
///
/// PcpLayerPrefetchRequest represents a request to pre-fetch and retain
/// a set of layers in memory. It performs the fetch as a parallel
/// operation using a thread pool. Fetched layers are retained by the
/// request to keep them alive until the client can decide what to do
/// with them.
///
class PcpLayerPrefetchRequest
{
public:
    /// Enqueue a request to pre-fetch of the sublayers of \a layer.
    /// This recursively includes any nested sublayers. Arguments in \a args
    /// will be passed to Sdf when finding or opening sublayers.
    PCP_API
    void RequestSublayerStack(
        const SdfLayerRefPtr &layer,
        const SdfLayer::FileFormatArguments &args);

    /// Run the queued requests, returning when complete.
    PCP_API
    void Run(const Pcp_MutedLayers& mutedLayers);

private:
    // The request object retains both the layer requests and
    // the pre-fetched sublayers.
    typedef std::pair<SdfLayerRefPtr, SdfLayer::FileFormatArguments> _Request;
    std::set<_Request> _sublayerRequests;

    std::set<SdfLayerRefPtr> _retainedLayers;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_LAYER_PREFETCH_REQUEST_H
