#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/fallbackLightingShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_FALLBACK_LIGHTING_SHADER_H
#define FORGE_IMAGING_HD_PH_FALLBACK_LIGHTING_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/lightingShader.h"

#include "forge/base/gf/vec4d.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HioGlslfx;

/// \class HdPh_FallbackLightingShader
///
/// A shader that provides fallback lighting behavior.
///
class HdPh_FallbackLightingShader : public HdPhLightingShader {
 public:
  HDPH_API
  HdPh_FallbackLightingShader();
  HDPH_API
  ~HdPh_FallbackLightingShader() override;

  // HdPhShaderCode overrides
  HDPH_API
  ID ComputeHash() const override;
  HDPH_API
  std::string GetSource(TfToken const &shaderStageKey) const override;
  HDPH_API
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;
  HDPH_API
  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;
  HDPH_API
  void AddBindings(HdBindingRequestVector *customBindings) override;

  // HdPhLightingShader overrides
  HDPH_API
  void SetCamera(GfMatrix4d const &worldToViewMatrix, GfMatrix4d const &projectionMatrix) override;

 private:
  std::unique_ptr<HioGlslfx> _glslfx;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_FALLBACK_LIGHTING_SHADER_H
