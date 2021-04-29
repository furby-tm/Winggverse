#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/bufferResource.h"
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
#ifndef FORGE_IMAGING_HD_BUFFER_RESOURCE_H
#define FORGE_IMAGING_HD_BUFFER_RESOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/resource.h"
#include "forge/imaging/hd/types.h"

#include "forge/base/tf/token.h"

#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

FORGE_NAMESPACE_BEGIN


class HdBufferResource;

using HdBufferResourceSharedPtr = std::shared_ptr<HdBufferResource>;
using HdBufferResourceNamedList = std::vector<
    std::pair<TfToken, HdBufferResourceSharedPtr> >;

/// \class HdBufferResource
///
/// A specific type of HdResource (GPU resource) representing a buffer object.
///
class HdBufferResource : public HdResource {
public:
    HD_API
    HdBufferResource(TfToken const &role,
                     HdTupleType tupleType,
                     int offset,
                     int stride);
    HD_API
    ~HdBufferResource();

    /// Data type and count
    HdTupleType GetTupleType() const { return _tupleType; }

    /// Returns the interleaved offset (in bytes) of this data.
    int GetOffset() const {return _offset;}

    /// Returns the stride (in bytes) of underlying buffer.
    int GetStride() const {return _stride;}

protected:
    HdTupleType _tupleType;
    int _offset;
    int _stride;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_BUFFER_RESOURCE_H
