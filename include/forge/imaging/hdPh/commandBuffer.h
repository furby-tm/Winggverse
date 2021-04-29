#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/commandBuffer.h"
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
#ifndef FORGE_IMAGING_HD_PH_COMMAND_BUFFER_H
#define FORGE_IMAGING_HD_PH_COMMAND_BUFFER_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/drawItemInstance.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/matrix4f.h"
#include "forge/base/gf/vec2f.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdPhDrawItem;
class HdPhDrawItemInstance;

using HdPhRenderPassStateSharedPtr = std::shared_ptr<class HdPhRenderPassState>;
using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

using HdPh_DrawBatchSharedPtr = std::shared_ptr<class HdPh_DrawBatch>;
using HdPh_DrawBatchSharedPtrVector = std::vector<HdPh_DrawBatchSharedPtr>;

/// \class HdPhCommandBuffer
///
/// A buffer of commands (HdPhDrawItem or HdComputeItem objects) to be executed.
///
/// The HdPhCommandBuffer is responsible for accumulating draw items and sorting
/// them for correctness (e.g. alpha transparency) and efficiency (e.g. the
/// fewest number of GPU state changes).
///
class HdPhCommandBuffer {
 public:
  HDPH_API
  HdPhCommandBuffer();
  HDPH_API
  ~HdPhCommandBuffer();

  /// Prepare the command buffer for draw
  HDPH_API
  void PrepareDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                   HdPhResourceRegistrySharedPtr const &resourceRegistry);

  /// Execute the command buffer
  HDPH_API
  void ExecuteDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                   HdPhResourceRegistrySharedPtr const &resourceRegistry);

  /// Cull drawItemInstances based on passed in combined view and projection matrix
  HDPH_API
  void FrustumCull(GfMatrix4d const &cullMatrix);

  /// Sync visibility state from RprimSharedState to DrawItemInstances.
  HDPH_API
  void SyncDrawItemVisibility(unsigned visChangeCount);

  /// Destructively swaps the contents of \p items with the internal list of
  /// all draw items. Culling state is reset, with no items visible.
  HDPH_API
  void SwapDrawItems(std::vector<HdPhDrawItem const *> *items, unsigned currentBatchVersion);

  /// Rebuild all draw batches if any underlying buffer array is invalidated.
  HDPH_API
  void RebuildDrawBatchesIfNeeded(unsigned currentBatchVersion);

  /// Returns the total number of draw items, including culled items.
  size_t GetTotalSize() const
  {
    return _drawItems.size();
  }

  /// Returns the number of draw items, excluding culled items.
  size_t GetVisibleSize() const
  {
    return _visibleSize;
  }

  /// Returns the number of culled draw items.
  size_t GetCulledSize() const
  {
    return _drawItems.size() - _visibleSize;
  }

  HDPH_API
  void SetEnableTinyPrimCulling(bool tinyPrimCulling);

 private:
  void _RebuildDrawBatches();

  std::vector<HdPhDrawItem const *> _drawItems;
  std::vector<HdPhDrawItemInstance> _drawItemInstances;
  HdPh_DrawBatchSharedPtrVector _drawBatches;
  size_t _visibleSize;
  unsigned int _visChangeCount;
  unsigned int _drawBatchesVersion;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_COMMAND_BUFFER_H
