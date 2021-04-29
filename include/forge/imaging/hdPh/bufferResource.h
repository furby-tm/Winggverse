#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/bufferResource.h"
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
#ifndef FORGE_IMAGING_HD_PH_BUFFER_RESOURCE_H
#define FORGE_IMAGING_HD_PH_BUFFER_RESOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferResource.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hgi/buffer.h"

#include "forge/base/tf/token.h"

#include <memory>
#include <utility>
#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPhBufferResourceSharedPtr = std::shared_ptr<class HdPhBufferResource>;

using HdPhBufferResourceNamedPair = std::pair<TfToken, HdPhBufferResourceSharedPtr>;
using HdPhBufferResourceNamedList = std::vector<HdPhBufferResourceNamedPair>;

/// \class HdPhBufferResource
///
/// A specific type of HdBufferResource (GPU resource) representing
/// an HgiBufferHandle.
///
class HdPhBufferResource final : public HdBufferResource {
 public:
  HDPH_API
  HdPhBufferResource(TfToken const &role, HdTupleType tupleType, int offset, int stride);
  HDPH_API
  ~HdPhBufferResource();

  /// Sets the HgiBufferHandle for this resource and its size.
  /// also caches the gpu address of the buffer.
  HDPH_API
  void SetAllocation(HgiBufferHandle const &handle, size_t size);

  /// Returns the HgiBufferHandle for this GPU resource
  HgiBufferHandle &GetHandle()
  {
    return _handle;
  }

  /// Returns the gpu address (if available. otherwise returns 0).
  uint64_t GetGPUAddress() const
  {
    return _gpuAddr;
  }

 private:
  uint64_t _gpuAddr;
  HgiBufferHandle _handle;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_BUFFER_RESOURCE_H
