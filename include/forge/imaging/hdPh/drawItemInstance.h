#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/drawItemInstance.h"
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
#ifndef FORGE_IMAGING_HD_PH_DRAW_ITEM_INSTANCE_H
#define FORGE_IMAGING_HD_PH_DRAW_ITEM_INSTANCE_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/drawItem.h"

FORGE_NAMESPACE_BEGIN

using HdPh_DrawBatchSharedPtr = std::shared_ptr<class HdPh_DrawBatch>;

/// \class HdPhDrawItemInstance
///
/// A container to store instance state for a drawitem.
///
/// During culling, the visibility state will be set. If the instance
/// has a batch, the batch will get a DrawItemInstanceChanged
/// callback.
///
/// The Batch is responsible for calling SetBatch and SetBatchIndex
/// when adding / appending the instance. If the batch does not require
/// the DrawItemInstanceChanged callback, then this step can be skipped
///
class HdPhDrawItemInstance {
 public:
  HDPH_API
  HdPhDrawItemInstance(HdPhDrawItem const *drawItem);
  HDPH_API
  ~HdPhDrawItemInstance();

  /// Set visibility state
  HDPH_API
  void SetVisible(bool visible);

  /// Query visibility state
  bool IsVisible() const
  {
    return _visible;
  }

  /// Set index into batch list. Can be used by
  /// batch during DrawItemInstanceChanged callback
  HDPH_API
  void SetBatchIndex(size_t batchIndex);

  /// Query batch index
  size_t GetBatchIndex() const
  {
    return _batchIndex;
  }

  /// Set the batch that will receive the DrawItemInstanceChanged
  /// callback when visibility is updated. Setting batch to NULL
  /// will disable this callback.
  // HDPH_API
  void SetBatch(HdPh_DrawBatch *batch);

  /// Return a const pointer to draw item
  HdPhDrawItem const *GetDrawItem() const
  {
    return _drawItem;
  }

 private:
  HdPhDrawItemInstance();

  HdPh_DrawBatch *_batch;
  HdPhDrawItem const *_drawItem;
  size_t _batchIndex;
  bool _visible;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DRAW_ITEM_INSTANCE_H
