#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureObjectRegistry.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_OBJECT_REGISTRY_H
#define FORGE_IMAGING_HD_PH_TEXTURE_OBJECT_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/instanceRegistry.h"
#include "forge/imaging/hdPh/api.h"

#include <atomic>

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_vector.h>
#endif /* Q_MOC_RUN */

#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPhTextureObjectSharedPtr = std::shared_ptr<class HdPhTextureObject>;
using HdPhTextureObjectPtr = std::weak_ptr<class HdPhTextureObject>;
using HdPhTextureObjectPtrVector = std::vector<HdPhTextureObjectPtr>;
class HdPhResourceRegistry;
class HdPhTextureIdentifier;

/// \class HdPh_TextureObjectRegistry
///
/// A central registry for texture GPU resources.
///
class HdPh_TextureObjectRegistry final {
 public:
  explicit HdPh_TextureObjectRegistry(HdPhResourceRegistry *registry);
  ~HdPh_TextureObjectRegistry();

  /// Allocate texture.
  ///
  /// This just creates the HdPhTextureObject, the actual GPU
  /// resources won't be allocated until the Commit phase.
  ///
  HDPH_API
  HdPhTextureObjectSharedPtr AllocateTextureObject(const HdPhTextureIdentifier &textureId,
                                                   HdTextureType textureType);

  /// Create GPU texture objects, load textures from files and
  /// upload to GPU.
  ///
  HDPH_API
  std::set<HdPhTextureObjectSharedPtr> Commit();

  /// Free GPU resources of textures not used by any client.
  ///
  HDPH_API
  void GarbageCollect();

  /// Mark texture file path as dirty. All textures whose identifier
  /// contains the file path will be reloaded during the next Commit.
  ///
  HDPH_API
  void MarkTextureFilePathDirty(const TfToken &filePath);

  /// Mark that the GPU resource for a texture needs to be
  /// (re-)loaded, e.g., because the memory request changed.
  ///
  HDPH_API
  void MarkTextureObjectDirty(HdPhTextureObjectPtr const &textureObject);

  /// Get resource registry
  ///
  HDPH_API
  HdPhResourceRegistry *GetResourceRegistry() const
  {
    return _resourceRegistry;
  }

  /// The total GPU memory consumed by all textures managed by this registry.
  ///
  int64_t GetTotalTextureMemory() const
  {
    return _totalTextureMemory;
  }

  /// Add signed number to total texture memory amount. Called from
  /// texture objects when (de-)allocated GPU resources.
  ///
  HDPH_API
  void AdjustTotalTextureMemory(int64_t memDiff);

  /// The number of texture objects.
  size_t GetNumberOfTextureObjects() const
  {
    return _textureObjectRegistry.size();
  }

 private:
  HdPhTextureObjectSharedPtr _MakeTextureObject(const HdPhTextureIdentifier &textureId,
                                                HdTextureType textureType);

  std::atomic<int64_t> _totalTextureMemory;

  // Registry for texture and sampler objects.
  HdInstanceRegistry<HdPhTextureObjectSharedPtr> _textureObjectRegistry;

  // Map file paths to texture objects for quick invalidation
  // by file path.
  std::unordered_map<TfToken, HdPhTextureObjectPtrVector, TfToken::HashFunctor>
      _filePathToTextureObjects;

  // File paths for which GPU resources need to be (re-)loaded
  tbb::concurrent_vector<TfToken> _dirtyFilePaths;

  // Texture for which GPU resources need to be (re-)loaded
  tbb::concurrent_vector<HdPhTextureObjectPtr> _dirtyTextures;

  HdPhResourceRegistry *_resourceRegistry;
};

FORGE_NAMESPACE_END

#endif
