#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/renderPassState.h"
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
#ifndef FORGE_IMAGING_HD_PH_RENDER_PASS_STATE_H
#define FORGE_IMAGING_HD_PH_RENDER_PASS_STATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/renderPassState.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hgi/graphicsCmdsDesc.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdResourceRegistrySharedPtr = std::shared_ptr<class HdResourceRegistry>;
using HdPhRenderPassStateSharedPtr = std::shared_ptr<class HdPhRenderPassState>;

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;
using HdPhLightingShaderSharedPtr = std::shared_ptr<class HdPhLightingShader>;
using HdPhRenderPassShaderSharedPtr = std::shared_ptr<class HdPhRenderPassShader>;
using HdPh_FallbackLightingShaderSharedPtr = std::shared_ptr<class HdPh_FallbackLightingShader>;
using HdPhShaderCodeSharedPtrVector = std::vector<HdPhShaderCodeSharedPtr>;
class HdRenderIndex;

/// \class HdPhRenderPassState
///
/// A set of rendering parameters used among render passes.
///
/// Parameters are expressed as GL states, uniforms or shaders.
///
class HdPhRenderPassState : public HdRenderPassState {
 public:
  HDPH_API
  HdPhRenderPassState();
  HDPH_API
  HdPhRenderPassState(HdPhRenderPassShaderSharedPtr const &shader);
  HDPH_API
  ~HdPhRenderPassState() override;

  HDPH_API
  void Prepare(HdResourceRegistrySharedPtr const &resourceRegistry) override;

  /// XXX: Bind and Unbind set./restore the following GL state.
  /// This will be reworked to use Hgi in the near future.
  /// Following states may be changed and restored to
  /// the GL default at Unbind().
  ///   glEnable(GL_BLEND);
  ///   glEnable(GL_CULL_FACE);
  ///   glEnable(GL_POLYGON_OFFSET_FILL)
  ///   glEnable(GL_PROGRAM_POINT_SIZE);
  ///   glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE)
  ///   glEnable(GL_DEPTH_TEST);
  ///   glEnable(GL_STENCIL_TEST);
  ///   glPolygonOffset()
  ///   glBlend*()
  ///   glColorMask()
  ///   glCullFace()
  ///   glDepthFunc()
  ///   glDepthMask()
  ///   glLineWidth()
  ///   glStencilFunc()
  ///   glStencilOp()
  HDPH_API
  void Bind();
  HDPH_API
  void Unbind();

  /// If set to true (default) and the render pass is rendering into a
  /// multi-sampled aovs, the aovs will be resolved at the end of the render
  /// pass. If false or the aov is not multi-sampled or the render pass is not
  /// rendering into the multi-sampled aov, no resolution takes place.
  HD_API
  void SetResolveAovMultiSample(bool state);
  HD_API
  bool GetResolveAovMultiSample() const;

  /// Set lighting shader
  HDPH_API
  void SetLightingShader(HdPhLightingShaderSharedPtr const &lightingShader);
  HdPhLightingShaderSharedPtr const &GetLightingShader() const
  {
    return _lightingShader;
  }

  /// renderpass shader
  HDPH_API
  void SetRenderPassShader(HdPhRenderPassShaderSharedPtr const &renderPassShader);
  HdPhRenderPassShaderSharedPtr const &GetRenderPassShader() const
  {
    return _renderPassShader;
  }

  /// scene materials
  HDPH_API
  void SetUseSceneMaterials(bool state);
  bool GetUseSceneMaterials() const
  {
    return _useSceneMaterials;
  }

  /// returns shaders (lighting/renderpass)
  HDPH_API
  HdPhShaderCodeSharedPtrVector GetShaders() const;

  HDPH_API
  size_t GetShaderHash() const;

  /// Camera setter API
  /// Option 1: Specify matrices, viewport and clipping planes (defined in
  /// camera space) directly.
  HD_API
  void SetCameraFramingState(GfMatrix4d const &worldToViewMatrix,
                             GfMatrix4d const &projectionMatrix,
                             GfVec4d const &viewport,
                             ClipPlanesVector const &clipPlanes);

  // Helper to get graphics cmds descriptor describing textures
  // we render into and the blend state, constructed from
  // AOV bindings.
  //
  HDPH_API
  HgiGraphicsCmdsDesc MakeGraphicsCmdsDesc(const HdRenderIndex *) const;

 private:
  bool _UseAlphaMask() const;

  // ---------------------------------------------------------------------- //
  // Shader Objects
  // ---------------------------------------------------------------------- //
  HdPhRenderPassShaderSharedPtr _renderPassShader;
  HdPh_FallbackLightingShaderSharedPtr _fallbackLightingShader;
  HdPhLightingShaderSharedPtr _lightingShader;

  HdBufferArrayRangeSharedPtr _renderPassStateBar;
  size_t _clipPlanesBufferSize;
  float _alphaThresholdCurrent;
  bool _resolveMultiSampleAov;
  bool _useSceneMaterials;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_RENDER_PASS_STATE_H
