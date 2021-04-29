#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/drawBatch.h"
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
#ifndef FORGE_IMAGING_HD_PH_DRAW_BATCH_H
#define FORGE_IMAGING_HD_PH_DRAW_BATCH_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hd/repr.h"
#include "forge/imaging/hdPh/resourceBinder.h"
#include "forge/imaging/hdPh/shaderCode.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdPhDrawItem;
class HdPhDrawItemInstance;

using HdPh_DrawBatchSharedPtr = std::shared_ptr<class HdPh_DrawBatch>;
using HdPh_DrawBatchSharedPtrVector = std::vector<HdPh_DrawBatchSharedPtr>;
using HdPh_GeometricShaderSharedPtr = std::shared_ptr<class HdPh_GeometricShader>;
using HdPhGLSLProgramSharedPtr = std::shared_ptr<class HdPhGLSLProgram>;

using HdPhRenderPassStateSharedPtr = std::shared_ptr<class HdPhRenderPassState>;
using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

/// \class HdPh_DrawBatch
///
/// A drawing batch.
///
/// This is the finest grained element of drawing, representing potentially
/// aggregated drawing resources dispatched with a minimal number of draw
/// calls.
///
class HdPh_DrawBatch {
 public:
  HDPH_API
  HdPh_DrawBatch(HdPhDrawItemInstance *drawItemInstance);

  HDPH_API
  virtual ~HdPh_DrawBatch();

  /// Attempts to append \a drawItemInstance to the batch, returning \a false
  /// if the item could not be appended, e.g. if there was an aggregation
  /// conflict.
  HDPH_API
  bool Append(HdPhDrawItemInstance *drawItemInstance);

  /// Attempt to rebuild the batch in-place, returns false if draw items are
  /// no longer compatible.
  HDPH_API
  bool Rebuild();

  enum class ValidationResult { ValidBatch = 0, RebuildBatch, RebuildAllBatches };

  /// Validates whether the  batch can be reused (i.e., submitted) as-is, or
  /// if it needs to be rebuilt, or if all batches need to be rebuilt.
  virtual ValidationResult Validate(bool deepValidation) = 0;

  /// Prepare draw commands and apply view frustum culling for this batch.
  virtual void PrepareDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                           HdPhResourceRegistrySharedPtr const &resourceRegistry) = 0;

  /// Executes the drawing commands for this batch.
  virtual void ExecuteDraw(HdPhRenderPassStateSharedPtr const &renderPassState,
                           HdPhResourceRegistrySharedPtr const &resourceRegistry) = 0;

  /// Let the batch know that one of it's draw item instances has changed
  /// NOTE: This callback is called from multiple threads, so needs to be
  /// threadsafe.
  HDPH_API
  virtual void DrawItemInstanceChanged(HdPhDrawItemInstance const *instance);

  /// Let the batch know whether to use tiny prim culling.
  HDPH_API
  virtual void SetEnableTinyPrimCulling(bool tinyPrimCulling);

 protected:
  HDPH_API
  virtual void _Init(HdPhDrawItemInstance *drawItemInstance);

  /// \class _DrawingProgram
  ///
  /// This wraps glsl code generation and keeps track of
  /// binding assigments for bindable resources.
  ///
  class _DrawingProgram {
   public:
    _DrawingProgram()
    {
    }

    HDPH_API
    bool CompileShader(HdPhDrawItem const *drawItem,
                       bool indirect,
                       HdPhResourceRegistrySharedPtr const &resourceRegistry);

    HdPhGLSLProgramSharedPtr GetGLSLProgram() const
    {
      return _glslProgram;
    }

    /// Returns the resouce binder, which is used for buffer resource
    /// bindings at draw time.
    const HdPh_ResourceBinder &GetBinder() const
    {
      return _resourceBinder;
    }

    void Reset()
    {
      _glslProgram.reset();
      _surfaceShader.reset();
      _geometricShader.reset();
      _resourceBinder = HdPh_ResourceBinder();
      _shaders.clear();
    }

    void SetSurfaceShader(HdPhShaderCodeSharedPtr shader)
    {
      _surfaceShader = shader;
    }

    const HdPhShaderCodeSharedPtr &GetSurfaceShader()
    {
      return _surfaceShader;
    }

    void SetGeometricShader(HdPh_GeometricShaderSharedPtr shader)
    {
      _geometricShader = shader;
    }

    const HdPh_GeometricShaderSharedPtr &GetGeometricShader()
    {
      return _geometricShader;
    }

    /// Set shaders (lighting/renderpass). In the case of Geometric Shaders
    /// or Surface shaders you can use the specific setters.
    void SetShaders(HdPhShaderCodeSharedPtrVector shaders)
    {
      _shaders = shaders;
    }

    /// Returns array of shaders, this will not include the surface shader
    /// passed via SetSurfaceShader (or the geometric shader).
    const HdPhShaderCodeSharedPtrVector &GetShaders() const
    {
      return _shaders;
    }

    /// Returns array of composed shaders, this include the shaders passed
    /// via SetShaders and the shader passed to SetSurfaceShader.
    HdPhShaderCodeSharedPtrVector GetComposedShaders() const
    {
      HdPhShaderCodeSharedPtrVector shaders = _shaders;
      if (_surfaceShader) {
        shaders.push_back(_surfaceShader);
      }
      return shaders;
    }

   protected:
    // overrides populate customBindings and enableInstanceDraw which
    // will be used to determine if glVertexAttribDivisor needs to be
    // enabled or not.
    HDPH_API
    virtual void _GetCustomBindings(HdBindingRequestVector *customBindings,
                                    bool *enableInstanceDraw) const;

    HDPH_API
    virtual bool _Link(HdPhGLSLProgramSharedPtr const &glslProgram);

   private:
    HdPhGLSLProgramSharedPtr _glslProgram;
    HdPh_ResourceBinder _resourceBinder;
    HdPhShaderCodeSharedPtrVector _shaders;
    HdPh_GeometricShaderSharedPtr _geometricShader;
    HdPhShaderCodeSharedPtr _surfaceShader;
  };

  HDPH_API
  _DrawingProgram &_GetDrawingProgram(HdPhRenderPassStateSharedPtr const &state,
                                      bool indirect,
                                      HdPhResourceRegistrySharedPtr const &resourceRegistry);

 protected:
  HDPH_API
  static bool _IsAggregated(HdPhDrawItem const *drawItem0, HdPhDrawItem const *drawItem1);

  std::vector<HdPhDrawItemInstance const *> _drawItemInstances;

 private:
  _DrawingProgram _program;
  HdPhShaderCode::ID _shaderHash;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DRAW_BATCH_H
