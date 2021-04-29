#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/indirectDrawBatch.h"
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
#ifndef FORGE_IMAGING_HD_PH_INDIRECT_DRAW_BATCH_H
#define FORGE_IMAGING_HD_PH_INDIRECT_DRAW_BATCH_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/dispatchBuffer.h"
#include "forge/imaging/hdPh/drawBatch.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

using HdBindingRequestVector = std::vector<HdBindingRequest>;

/// \class HdPh_IndirectDrawBatch
///
/// Drawing batch that is executed from an indirect dispatch buffer.
///
/// An indirect drawing batch accepts draw items that have the same
/// primitive mode and that share aggregated drawing resources,
/// e.g. uniform and non uniform primvar buffers.
///
class HdPh_IndirectDrawBatch : public HdPh_DrawBatch {
 public:
  HDPH_API
  HdPh_IndirectDrawBatch(HdPhDrawItemInstance *drawItemInstance);
  HDPH_API
  ~HdPh_IndirectDrawBatch() override;

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

  HDPH_API
  void DrawItemInstanceChanged(HdPhDrawItemInstance const *instance) override;

  HDPH_API
  void SetEnableTinyPrimCulling(bool tinyPrimCulling) override;

  /// Returns whether to do frustum culling on the GPU
  HDPH_API
  static bool IsEnabledGPUFrustumCulling();

  /// Returns whether to read back the count of visible items from the GPU
  /// Disabled by default, since there is some performance penalty.
  HDPH_API
  static bool IsEnabledGPUCountVisibleInstances();

  /// Returns whether to do per-instance culling on the GPU
  HDPH_API
  static bool IsEnabledGPUInstanceFrustumCulling();

 protected:
  HDPH_API
  void _Init(HdPhDrawItemInstance *drawItemInstance) override;

 private:
  void _ValidateCompatibility(
      HdPhBufferArrayRangeSharedPtr const &constantBar,
      HdPhBufferArrayRangeSharedPtr const &indexBar,
      HdPhBufferArrayRangeSharedPtr const &topologyVisibilityBar,
      HdPhBufferArrayRangeSharedPtr const &elementBar,
      HdPhBufferArrayRangeSharedPtr const &fvarBar,
      HdPhBufferArrayRangeSharedPtr const &varyingBar,
      HdPhBufferArrayRangeSharedPtr const &vertexBar,
      int instancerNumLevels,
      HdPhBufferArrayRangeSharedPtr const &instanceIndexBar,
      std::vector<HdPhBufferArrayRangeSharedPtr> const &instanceBars) const;

  // Culling requires custom resource binding.
  class _CullingProgram : public _DrawingProgram {
   public:
    _CullingProgram() : _useDrawArrays(false), _useInstanceCulling(false), _bufferArrayHash(0)
    {
    }
    void Initialize(bool useDrawArrays, bool useInstanceCulling, size_t bufferArrayHash);

   protected:
    // _DrawingProgram overrides
    void _GetCustomBindings(HdBindingRequestVector *customBindings,
                            bool *enableInstanceDraw) const override;

   private:
    bool _useDrawArrays;
    bool _useInstanceCulling;
    size_t _bufferArrayHash;
  };

  _CullingProgram &_GetCullingProgram(HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _CompileBatch(HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _GPUFrustumInstanceCulling(HdPhDrawItem const *item,
                                  HdPhRenderPassStateSharedPtr const &renderPassState,
                                  HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _GPUFrustumNonInstanceCulling(HdPhDrawItem const *item,
                                     HdPhRenderPassStateSharedPtr const &renderPassState,
                                     HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _BeginGPUCountVisibleInstances(HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _EndGPUCountVisibleInstances(HdPhResourceRegistrySharedPtr const &resourceRegistry,
                                    size_t *result);

  HdPhDispatchBufferSharedPtr _dispatchBuffer;
  HdPhDispatchBufferSharedPtr _dispatchBufferCullInput;

  std::vector<uint32_t> _drawCommandBuffer;
  bool _drawCommandBufferDirty;
  size_t _bufferArraysHash;
  size_t _barElementOffsetsHash;

  HdPhBufferResourceSharedPtr _resultBuffer;

  size_t _numVisibleItems;
  size_t _numTotalVertices;
  size_t _numTotalElements;

  _CullingProgram _cullingProgram;
  bool _useTinyPrimCulling;
  bool _dirtyCullingProgram;

  bool _useDrawArrays;
  bool _useInstancing;
  bool _useGpuCulling;
  bool _useGpuInstanceCulling;

  int _instanceCountOffset;
  int _cullInstanceCountOffset;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_INDIRECT_DRAW_BATCH_H
