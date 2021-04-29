#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/immediateDrawBatch.h"
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
#ifndef FORGE_IMAGING_HD_PH_IMMEDIATE_DRAW_BATCH_H
#define FORGE_IMAGING_HD_PH_IMMEDIATE_DRAW_BATCH_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/drawBatch.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class HdPh_ImmediateDrawBatch
///
/// Drawing batch that is executed immediately.
///
class HdPh_ImmediateDrawBatch : public HdPh_DrawBatch {
 public:
  HDPH_API
  HdPh_ImmediateDrawBatch(HdPhDrawItemInstance *drawItemInstance);
  HDPH_API
  ~HdPh_ImmediateDrawBatch() override;

  // HdPh_DrawBatch overrides
  HDPH_API
  ValidationResult Validate(bool deepValidation) override;

  /// Prepare draw commands and apply view frustum culling for this batch.
  HDPH_API
  void PrepareDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                   HdPhResourceRegistrySharedPtr const &resourceRegistry) override;

  /// Executes the drawing commands for this batch.
  HDPH_API
  void ExecuteDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                   HdPhResourceRegistrySharedPtr const &resourceRegistry) override;

 protected:
  HDPH_API
  void _Init(HdPhDrawItemInstance *drawItemInstance) override;

 private:
  size_t _bufferArraysHash;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_IMMEDIATE_DRAW_BATCH_H
