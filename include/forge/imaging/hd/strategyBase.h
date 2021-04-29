#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/strategyBase.h"
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
#ifndef FORGE_IMAGING_HD_STRATEGY_BASE_H
#define FORGE_IMAGING_HD_STRATEGY_BASE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/bufferArray.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/dictionary.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


using HdBufferArraySharedPtr = std::shared_ptr<class HdBufferArray>;
using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

/// \class HdAggregationStrategy
///
/// Aggregation strategy base class.
///
class HdAggregationStrategy {
public:
    /// Aggregation ID
    typedef size_t AggregationId;

    HD_API
    virtual ~HdAggregationStrategy();

    /// Factory for creating HdBufferArray
    virtual HdBufferArraySharedPtr CreateBufferArray(
        TfToken const &role,
        HdBufferSpecVector const &bufferSpecs,
        HdBufferArrayUsageHint usageHint) = 0;

    /// Factory for creating HdBufferArrayRange
    virtual HdBufferArrayRangeSharedPtr CreateBufferArrayRange() = 0;


    /// Returns id for given bufferSpecs to be used for aggregation
    virtual AggregationId ComputeAggregationId(
        HdBufferSpecVector const &bufferSpecs,
        HdBufferArrayUsageHint usageHint) const = 0;

    /// Returns the buffer specs from a given buffer array
    virtual HdBufferSpecVector GetBufferSpecs(
        HdBufferArraySharedPtr const &bufferArray) const = 0;

    /// Returns the accumulated GPU resource allocation      /// for items in the BufferArray passed as parameter
    virtual size_t GetResourceAllocation(
        HdBufferArraySharedPtr const &bufferArray,
        VtDictionary &result) const = 0;

    /// (Optional) called to Flush consolidated / staging buffers.
    HD_API
    virtual void Flush() {}
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_STRATEGY_BASE_H
