#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/samplerObjectRegistry.h"
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
#ifndef FORGE_IMAGING_HD_PH_SAMPLER_OBJECT_REGISTRY_H
#define FORGE_IMAGING_HD_PH_SAMPLER_OBJECT_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSamplerParameters;
using HdPhTextureObjectSharedPtr = std::shared_ptr<class HdPhTextureObject>;
using HdPhSamplerObjectSharedPtr = std::shared_ptr<class HdPhSamplerObject>;
class HdPhResourceRegistry;

/// \class HdPh_SamplerObjectRegistry
///
/// A simple registry for GPU samplers and GL texture sampler handles
/// (for bindless textures).
///
/// The registry makes no attempt at de-duplication. But construction
/// is dispatched by texture type returing a matching sampler (e.g.,
/// HdPhFieldSamplerObject for a HdPhFieldTextureObject or
/// HdPhPtexSamplerObject for the (not yet existing)
/// HdPhPtexTextureObject). Also, it keeps a shared pointer to a sampler
/// around until garbage collection so that clients can safely drop their
/// shared pointers from different threads.
///
class HdPh_SamplerObjectRegistry final {
 public:
  HDPH_API
  explicit HdPh_SamplerObjectRegistry(HdPhResourceRegistry *registry);

  HDPH_API
  ~HdPh_SamplerObjectRegistry();

  /// Create new sampler object matching the given texture object.
  ///
  /// If createBindlessHandle, also creates a texture sampler handle
  /// (for bindless textures). The associated GPU resource is
  /// created immediately and the call is not thread-safe.
  HDPH_API
  HdPhSamplerObjectSharedPtr AllocateSampler(HdPhTextureObjectSharedPtr const &texture,
                                             HdSamplerParameters const &samplerParameters,
                                             bool createBindlessHandle);

  /// Delete samplers no longer used by a client.
  HDPH_API
  void GarbageCollect();

  HDPH_API
  void MarkGarbageCollectionNeeded();

  /// Get resource registry
  ///
  HDPH_API
  HdPhResourceRegistry *GetResourceRegistry() const;

 private:
  std::vector<HdPhSamplerObjectSharedPtr> _samplerObjects;

  bool _garbageCollectionNeeded;
  HdPhResourceRegistry *_resourceRegistry;
};

FORGE_NAMESPACE_END

#endif
