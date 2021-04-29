#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/mixinShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_MIXIN_SHADER_H
#define FORGE_IMAGING_HD_PH_MIXIN_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPh_MixinShader
///
/// A final shader code class representing a mixin of a shader with a
/// base shader.
///
/// This interface provides a simple way for clients to extend a given
/// shader without mutating the original shader.
class HdPhMixinShader final : public HdPhShaderCode {
 public:
  HDPH_API
  HdPhMixinShader(std::string mixinSource, HdPhShaderCodeSharedPtr baseShader);

  HDPH_API
  ~HdPhMixinShader() override;

  /// Returns the hash value of this shader.
  HDPH_API
  HdPhShaderCode::ID ComputeHash() const override;

  HDPH_API
  ID ComputeTextureSourceHash() const override;

  /// Returns the shader source provided by this shader
  /// for \a shaderStageKey
  HDPH_API
  std::string GetSource(TfToken const &shaderStageKey) const override;

  HDPH_API
  HdPh_MaterialParamVector const &GetParams() const override;

  HDPH_API
  bool IsEnabledPrimvarFiltering() const override;

  HDPH_API
  TfTokenVector const &GetPrimvarNames() const override;

  /// Returns a buffer which stores parameter fallback values and texture
  /// handles.
  HDPH_API
  HdBufferArrayRangeSharedPtr const &GetShaderData() const override;

  /// Binds shader-specific resources to \a program
  HDPH_API
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;

  /// Unbinds shader-specific resources.
  HDPH_API
  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;

  /// Add custom bindings (used by codegen)
  HDPH_API
  void AddBindings(HdBindingRequestVector *customBindings) override;

  /// Returns the render pass tag of this shader.
  HDPH_API
  TfToken GetMaterialTag() const override;

 private:
  std::string _mixinSource;
  HdPhShaderCodeSharedPtr _baseShader;

  HdPhMixinShader() = delete;
  HdPhMixinShader(const HdPhMixinShader &) = delete;
  HdPhMixinShader &operator=(const HdPhMixinShader &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MIXIN_SHADER_H
