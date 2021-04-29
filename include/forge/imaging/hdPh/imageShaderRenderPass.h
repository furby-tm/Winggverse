#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/imageShaderRenderPass.h"
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
#ifndef FORGE_IMAGING_HD_PH_IMAGE_SHADER_RENDER_PASS_H
#define FORGE_IMAGING_HD_PH_IMAGE_SHADER_RENDER_PASS_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/drawItemInstance.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

using HdPh_ImageShaderRenderPassSharedPtr = std::shared_ptr<class HdPh_ImageShaderRenderPass>;
using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

class Hgi;

/// \class HdPh_ImageShaderRenderPass
///
/// A single, full-screen triangle render pass.
/// The task that creates this RenderPass should set a RenderPassShader on the
/// RenderPassState. The RenderPassShader is your full-screen post-effect.
/// The benefit of using RenderPassShader is that it participates in codegen.
/// This means your full-screen shader can use buffers created by other tasks.
///
class HdPh_ImageShaderRenderPass final : public HdRenderPass {
 public:
  HDPH_API
  HdPh_ImageShaderRenderPass(HdRenderIndex *index, HdRprimCollection const &collection);

  HDPH_API
  virtual ~HdPh_ImageShaderRenderPass();

 protected:
  virtual void _Prepare(TfTokenVector const &renderTags) override;

  virtual void _Execute(HdRenderPassStateSharedPtr const &renderPassState,
                        TfTokenVector const &renderTags) override;

  virtual void _MarkCollectionDirty() override;

 private:
  // Setup a BAR for a single triangle
  void _SetupVertexPrimvarBAR(HdPhResourceRegistrySharedPtr const &);

  // We re-use the immediateBatch to draw the full-screen triangle.
  HdRprimSharedData _sharedData;
  HdPhDrawItem _drawItem;
  HdPhDrawItemInstance _drawItemInstance;
  HdPh_DrawBatchSharedPtr _immediateBatch;
  Hgi *_hgi;
};

FORGE_NAMESPACE_END

#endif
