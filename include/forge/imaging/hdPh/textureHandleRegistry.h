#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureHandleRegistry.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_HANDLE_REGISTRY_H
#define FORGE_IMAGING_HD_PH_TEXTURE_HANDLE_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/textureObject.h"

#include "forge/imaging/hd/enums.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_vector.h>
#endif /* Q_MOC_RUN */

#include <memory>
#include <set>

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;
class HdPhTextureIdentifier;
class HdSamplerParameters;
class HdPh_SamplerObjectRegistry;

using HdPhTextureHandlePtr = std::weak_ptr<class HdPhTextureHandle>;
using HdPhTextureHandleSharedPtr = std::shared_ptr<class HdPhTextureHandle>;
using HdPhTextureObjectPtr = std::weak_ptr<class HdPhTextureObject>;
using HdPhTextureObjectSharedPtr = std::shared_ptr<class HdPhTextureObject>;
using HdPhSamplerObjectSharedPtr = std::shared_ptr<class HdPhSamplerObject>;
using HdPhShaderCodePtr = std::weak_ptr<class HdPhShaderCode>;
using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;

/// \class HdPh_TextureHandleRegistry
///
/// Keeps track of texture handles and allocates the textures and
/// samplers using the HdPh_TextureObjectRegistry, respectively,
/// HdPh_SamplerObjectRegistry.  Its responsibilities including
/// tracking what texture handles are associated to a texture,
/// computing the target memory of a texture from the memory requests
/// in the texture handles, triggering sampler and texture garbage
/// collection, and determining what HdPhShaderCode instances are
/// affecting by (re-)committing a texture.
///
class HdPh_TextureHandleRegistry final {
 public:
  HDPH_API
  explicit HdPh_TextureHandleRegistry(HdPhResourceRegistry *registry);

  HDPH_API
  ~HdPh_TextureHandleRegistry();

  /// Allocate texture handle (thread-safe).
  ///
  /// See HdPhResourceRegistry::AllocateTextureHandle for details.
  ///
  HDPH_API
  HdPhTextureHandleSharedPtr AllocateTextureHandle(const HdPhTextureIdentifier &textureId,
                                                   HdTextureType textureType,
                                                   const HdSamplerParameters &samplerParams,
                                                   /// memoryRequest in bytes.
                                                   size_t memoryRequest,
                                                   bool createBindlessHandle,
                                                   HdPhShaderCodePtr const &shaderCode);

  /// Mark texture dirty (thread-safe).
  ///
  /// If set, the target memory of the texture will be recomputed
  /// during commit and the data structure tracking the associated
  /// handles will be updated potentially triggering texture garbage
  /// collection.
  ///
  HDPH_API
  void MarkDirty(HdPhTextureObjectPtr const &texture);

  /// Mark shader dirty (thread-safe).
  ///
  /// If set, the shader is scheduled to be updated (i.e., have its
  /// AddResourcesFromTextures called) on the next commit.
  ///
  HDPH_API
  void MarkDirty(HdPhShaderCodePtr const &shader);

  /// Mark that sampler garbage collection needs to happen during
  /// next commit (thead-safe).
  ///
  HDPH_API
  void MarkSamplerGarbageCollectionNeeded();

  /// Get texture object registry.
  ///
  HdPh_TextureObjectRegistry *GetTextureObjectRegistry() const
  {
    return _textureObjectRegistry.get();
  }

  /// Get sampler object registry.
  ///
  HdPh_SamplerObjectRegistry *GetSamplerObjectRegistry() const
  {
    return _samplerObjectRegistry.get();
  }

  /// Commit textures. Return shader code instances that
  /// depend on the (re-)loaded textures so that they can add
  /// buffer sources based on the texture meta-data.
  ///
  /// Also garbage collect textures and samplers if necessary.
  ///
  HDPH_API
  std::set<HdPhShaderCodeSharedPtr> Commit();

  /// Sets how much memory a single texture can consume in bytes by
  /// texture type.
  ///
  /// Only has an effect if non-zero and only applies to textures if
  /// no texture handle referencing the texture has a memory
  /// request.
  ///
  HDPH_API
  void SetMemoryRequestForTextureType(HdTextureType textureType, size_t memoryRequest);

  HDPH_API
  size_t GetNumberOfTextureHandles() const;

 private:
  void _ComputeMemoryRequest(HdPhTextureObjectSharedPtr const &);
  void _ComputeMemoryRequests(const std::set<HdPhTextureObjectSharedPtr> &);
  void _ComputeAllMemoryRequests();

  bool _GarbageCollectHandlesAndComputeTargetMemory();
  void _GarbageCollectAndComputeTargetMemory();
  std::set<HdPhShaderCodeSharedPtr> _Commit();

  class _TextureToHandlesMap;

  // Maps texture type to memory a single texture of that type can consume
  // (in bytes).
  // Will be taken into account when computing the maximum of all the
  // memory requests of the texture handles.
  std::map<HdTextureType, size_t> _textureTypeToMemoryRequest;
  // Has _textureTypeToMemoryRequest changed since the last commit.
  bool _textureTypeToMemoryRequestChanged;

  // Handles that are new or for which the underlying texture has
  // changed: samplers might need to be (re-)allocated and the
  // corresponding shader code might need to update the shader bar.
  tbb::concurrent_vector<HdPhTextureHandlePtr> _dirtyHandles;

  // Textures whose set of associated handles and target memory
  // might have changed.
  tbb::concurrent_vector<HdPhTextureObjectPtr> _dirtyTextures;

  // Shaders that dropped a texture handle also need to be notified
  // (for example because they re-allocated the shader bar after dropping
  // the texture).
  tbb::concurrent_vector<HdPhShaderCodePtr> _dirtyShaders;

  std::unique_ptr<class HdPh_SamplerObjectRegistry> _samplerObjectRegistry;
  std::unique_ptr<class HdPh_TextureObjectRegistry> _textureObjectRegistry;
  std::unique_ptr<_TextureToHandlesMap> _textureToHandlesMap;
};

FORGE_NAMESPACE_END

#endif
