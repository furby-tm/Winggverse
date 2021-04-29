#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/simpleLightingShader.h"
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
#ifndef FORGE_IMAGING_HDPH_SIMPLE_LIGHTING_SHADER_H
#define FORGE_IMAGING_HDPH_SIMPLE_LIGHTING_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/lightingShader.h"

#include "forge/imaging/hd/version.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/imaging/glf/simpleLightingContext.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
using HdPhSimpleLightingShaderSharedPtr = std::shared_ptr<class HdPhSimpleLightingShader>;
TF_DECLARE_REF_PTRS(GlfBindingMap);

/// \class HdPhSimpleLightingShader
///
/// A shader that supports simple lighting functionality.
///
class HdPhSimpleLightingShader : public HdPhLightingShader {
 public:
  HDPH_API
  HdPhSimpleLightingShader();
  HDPH_API
  ~HdPhSimpleLightingShader() override;

  /// HdShader overrides
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

  /// Adds computations to create the dome light textures that
  /// are pre-calculated from the environment map texture.
  HDPH_API
  void AddResourcesFromTextures(ResourceContext &ctx) const override;

  /// HdPhShaderCode overrides
  HDPH_API
  HdPh_MaterialParamVector const &GetParams() const override;

  /// HdPhLightingShader overrides
  HDPH_API
  void SetCamera(GfMatrix4d const &worldToViewMatrix, GfMatrix4d const &projectionMatrix) override;
  HDPH_API
  void SetLightingStateFromOpenGL();
  HDPH_API
  void SetLightingState(GlfSimpleLightingContextPtr const &lightingContext);

  GlfSimpleLightingContextRefPtr GetLightingContext() const
  {
    return _lightingContext;
  };

  /// Allocates texture handles (texture loading happens later during commit)
  /// needed for lights.
  ///
  /// Call after lighting context has been set or updated in Sync-phase.
  ///
  HDPH_API
  void AllocateTextureHandles(HdSceneDelegate *delegate);

  /// The dome light environment map used as source for the other
  /// dome light textures.
  const HdPhTextureHandleSharedPtr &GetDomeLightEnvironmentTextureHandle() const
  {
    return _domeLightEnvironmentTextureHandle;
  }

  /// The textures computed from the dome light environment map that
  /// the shader needs to bind for the dome light shading.
  HDPH_API
  NamedTextureHandleVector const &GetNamedTextureHandles() const override;

  /// Get one of the textures that need to be computed from the dome
  /// light environment map.
  HDPH_API
  const HdPhTextureHandleSharedPtr &GetTextureHandle(const TfToken &name) const;

 private:
  GlfSimpleLightingContextRefPtr _lightingContext;
  GlfBindingMapRefPtr _bindingMap;
  bool _useLighting;
  std::unique_ptr<class HioGlslfx> _glslfx;

  // The environment map used as source for the dome light textures.
  //
  // Handle is allocated in AllocateTextureHandles. Actual loading
  // happens during commit.
  HdPhTextureHandleSharedPtr _domeLightEnvironmentTextureHandle;

  // Other dome light textures.
  NamedTextureHandleVector _namedTextureHandles;

  HdPh_MaterialParamVector _lightTextureParams;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HDPH_SIMPLE_LIGHTING_SHADER_H
