#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/renderPassShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_RENDER_PASS_SHADER_H
#define FORGE_IMAGING_HD_PH_RENDER_PASS_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hd/binding.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"
#include "forge/imaging/hio/glslfx.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/token.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPhRenderPassShaderSharedPtr = std::shared_ptr<class HdPhRenderPassShader>;

/// \class HdPhRenderPassShader
///
/// A shader that supports common renderPass functionality.
///
class HdPhRenderPassShader : public HdPhShaderCode {
 public:
  HDPH_API
  HdPhRenderPassShader();
  HDPH_API
  HdPhRenderPassShader(TfToken const &glslfxFile);
  HDPH_API
  virtual ~HdPhRenderPassShader() override;

  /// HdShader overrides
  HDPH_API
  virtual ID ComputeHash() const override;
  HDPH_API
  virtual std::string GetSource(TfToken const &shaderStageKey) const override;
  HDPH_API
  virtual void BindResources(int program,
                             HdPh_ResourceBinder const &binder,
                             HdRenderPassState const &state) override;
  HDPH_API
  virtual void UnbindResources(int program,
                               HdPh_ResourceBinder const &binder,
                               HdRenderPassState const &state) override;
  HDPH_API
  virtual void AddBindings(HdBindingRequestVector *customBindings) override;
  HDPH_API
  virtual HdPh_MaterialParamVector const &GetParams() const override;

  /// Add a custom binding request for use when this shader executes.
  HDPH_API
  void AddBufferBinding(HdBindingRequest const &req);

  /// Remove \p name from custom binding.
  HDPH_API
  void RemoveBufferBinding(TfToken const &name);

  /// Clear all custom bindings associated with this shader.
  HDPH_API
  void ClearBufferBindings();

  /// Add a request to read an AOV back in the shader. The shader can
  /// access the requested AOV as HdGet_NAMEReadback().
  HDPH_API
  void AddAovReadback(TfToken const &name);

  /// Remove \p name from requests to read AOVs.
  HDPH_API
  void RemoveAovReadback(TfToken const &name);

  HdCullStyle GetCullStyle() const
  {
    return _cullStyle;
  }

  void SetCullStyle(HdCullStyle cullStyle)
  {
    _cullStyle = cullStyle;
  }

 private:
  TfToken _glslfxFile;
  std::unique_ptr<HioGlslfx> _glslfx;
  mutable size_t _hash;
  mutable bool _hashValid;

  TfHashMap<TfToken, HdBindingRequest, TfToken::HashFunctor> _customBuffers;
  HdCullStyle _cullStyle;

  TfHashSet<TfToken, TfToken::HashFunctor> _aovReadbackRequests;
  HdPh_MaterialParamVector _params;

  // No copying
  HdPhRenderPassShader(const HdPhRenderPassShader &) = delete;
  HdPhRenderPassShader &operator=(const HdPhRenderPassShader &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_RENDER_PASS_SHADER_H
