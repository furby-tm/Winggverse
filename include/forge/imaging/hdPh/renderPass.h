#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/renderPass.h"
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
#ifndef FORGE_IMAGING_HD_PH_RENDER_PASS_H
#define FORGE_IMAGING_HD_PH_RENDER_PASS_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/commandBuffer.h"

#include <unordered_map>

FORGE_NAMESPACE_BEGIN

class Hgi;

/// \class HdPh_RenderPass
///
/// A single draw pass to a render target/buffer. Stream implementation.
///
class HdPh_RenderPass : public HdRenderPass {
 public:
  HDPH_API
  HdPh_RenderPass(HdRenderIndex *index, HdRprimCollection const &collection);
  HDPH_API
  virtual ~HdPh_RenderPass();

  /// Returns the number of draw items used by this render pass.
  /// Will only return the correct value after Prepare() has been called on
  /// HdRenderPass. Calling this during Sync() will return last frame's
  /// drawItem count.
  HDPH_API
  size_t GetDrawItemCount() const;

 protected:
  virtual void _Prepare(TfTokenVector const &renderTags) override;

  /// Execute the buckets corresponding to renderTags
  virtual void _Execute(HdRenderPassStateSharedPtr const &renderPassState,
                        TfTokenVector const &renderTags) override;

  virtual void _MarkCollectionDirty() override;

 private:
  void _PrepareDrawItems(TfTokenVector const &renderTags);
  void _PrepareCommandBuffer(TfTokenVector const &renderTags);

  // XXX: This should really be in HdPh_DrawBatch::PrepareDraw.
  void _FrustumCullCPU(HdPhRenderPassStateSharedPtr const &renderPasssState);

  // -----------------------------------------------------------------------
  // Drawing state
  HdPhCommandBuffer _cmdBuffer;

  int _lastSettingsVersion;
  bool _useTinyPrimCulling;

  // -----------------------------------------------------------------------
  // Change tracking state.

  // The version number of the currently held collection.
  int _collectionVersion;

  // The version number of the currently active render tags
  int _renderTagVersion;

  // The version number of the material tags (of the rprims).
  unsigned int _materialTagsVersion;

  // A flag indicating that the held collection changed since this renderPass
  // was last drawn.
  //
  // When _collectionChanged is true, it indicates that _collectionVersion is
  // no longer accurate, because _collectionVersion was stored for the
  // previously held collection.
  bool _collectionChanged;

  // DrawItems that are used to build the draw batches.
  HdRenderIndex::HdDrawItemPtrVector _drawItems;
  size_t _drawItemCount;
  bool _drawItemsChanged;

  Hgi *_hgi;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_RENDER_PASS_H
