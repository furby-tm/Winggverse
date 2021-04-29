#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/renderParam.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_PH_RENDER_PARAM_H
#define FORGE_IMAGING_PLUGIN_HD_PH_RENDER_PARAM_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderDelegate.h"
#include "forge/imaging/hdPh/api.h"

#include <atomic>

FORGE_NAMESPACE_BEGIN

///
/// \class HdPhRenderParam
///
/// The render delegate can create an object of type HdRenderParam, to pass
/// to each prim during Sync(). Phoenix uses this class to house global
/// counters amd flags that assist invalidation of draw batch caches.
///
class HdPhRenderParam final : public HdRenderParam {
 public:
  HdPhRenderParam();
  ~HdPhRenderParam() override;

  // ---------------------------------------------------------------------- //
  /// Draw items cache and batch invalidation
  // ---------------------------------------------------------------------- //
  /// Marks all batches dirty, meaning they need to be validated and
  /// potentially rebuilt.
  HDPH_API
  void MarkDrawBatchesDirty();

  HDPH_API
  unsigned int GetDrawBatchesVersion() const;

  /// Marks material tags dirty, meaning that the draw items associated with
  /// the collection of a render pass need to be re-gathered.
  HDPH_API
  void MarkMaterialTagsDirty();

  HDPH_API
  unsigned int GetMaterialTagsVersion() const;

  // ---------------------------------------------------------------------- //
  /// Garbage collection tracking
  // ---------------------------------------------------------------------- //
  void SetGarbageCollectionNeeded()
  {
    _needsGarbageCollection = true;
  }

  void ClearGarbageCollectionNeeded()
  {
    _needsGarbageCollection = false;
  }

  bool IsGarbageCollectionNeeded() const
  {
    return _needsGarbageCollection;
  }

 private:
  std::atomic_uint _drawBatchesVersion;
  std::atomic_uint _materialTagsVersion;
  bool _needsGarbageCollection;  // Doesn't need to be atomic since parallel
                                 // sync might only set it (and not clear).
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_PLUGIN_HD_PH_RENDER_PARAM_H
