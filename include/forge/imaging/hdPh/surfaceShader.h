#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/surfaceShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_SURFACE_SHADER_H
#define FORGE_IMAGING_HD_PH_SURFACE_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

using HdPhSurfaceShaderSharedPtr = std::shared_ptr<class HdPhSurfaceShader>;

using HdBufferSpecVector = std::vector<struct HdBufferSpec>;
using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

/// \class HdPhSurfaceShader
///
/// A scene-based SurfaceShader object.
///
/// When surface shaders are expresed in the scene graph, the HdSceneDelegate
/// can use this object to express these surface shaders in Phoenix. In addition
/// to the shader itself, a binding from the Rprim to the SurfaceShader must be
/// expressed as well.
class HdPhSurfaceShader : public HdPhShaderCode {
 public:
  HDPH_API
  HdPhSurfaceShader();
  HDPH_API
  ~HdPhSurfaceShader() override;

  // ---------------------------------------------------------------------- //
  /// \name HdShader Virtual Interface                                      //
  // ---------------------------------------------------------------------- //
  HDPH_API
  std::string GetSource(TfToken const &shaderStageKey) const override;
  HDPH_API
  HdPh_MaterialParamVector const &GetParams() const override;
  HDPH_API
  void SetEnabledPrimvarFiltering(bool enabled);
  HDPH_API
  bool IsEnabledPrimvarFiltering() const override;
  HDPH_API
  TfTokenVector const &GetPrimvarNames() const override;
  HDPH_API
  HdBufferArrayRangeSharedPtr const &GetShaderData() const override;
  HDPH_API
  NamedTextureHandleVector const &GetNamedTextureHandles() const override;
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
  HDPH_API
  ID ComputeHash() const override;

  HDPH_API
  ID ComputeTextureSourceHash() const override;

  HDPH_API
  TfToken GetMaterialTag() const override;

  /// Setter method for prim
  HDPH_API
  void SetFragmentSource(const std::string &source);
  HDPH_API
  void SetGeometrySource(const std::string &source);
  HDPH_API
  void SetParams(const HdPh_MaterialParamVector &params);
  HDPH_API
  void SetNamedTextureHandles(const NamedTextureHandleVector &);
  HDPH_API
  void SetBufferSources(HdBufferSpecVector const &bufferSpecs,
                        HdBufferSourceSharedPtrVector &&bufferSources,
                        HdPhResourceRegistrySharedPtr const &resourceRegistry);

  /// Called after textures have been committed.
  ///
  /// Shader can return buffer sources for different BARs (most
  /// likely, the shader bar) that require texture metadata such as
  /// the bindless texture handle which is only available after the
  /// commit.
  ///
  HDPH_API
  void AddResourcesFromTextures(ResourceContext &ctx) const override;

  HDPH_API
  void SetMaterialTag(TfToken const &materialTag);

  /// If the prim is based on asset, reload that asset.
  HDPH_API
  virtual void Reload();

  /// Returns if the two shaders can be aggregated into the same draw batch.
  HDPH_API
  static bool CanAggregate(HdPhShaderCodeSharedPtr const &shaderA,
                           HdPhShaderCodeSharedPtr const &shaderB);

  /// Adds the fallback value of the given material param to
  /// buffer specs and sources using the param's name.
  ///
  HDPH_API
  static void AddFallbackValueToSpecsAndSources(const HdPh_MaterialParam &param,
                                                HdBufferSpecVector *const specs,
                                                HdBufferSourceSharedPtrVector *const sources);

 protected:
  HDPH_API
  void _SetSource(TfToken const &shaderStageKey, std::string const &source);

  HDPH_API
  ID _ComputeHash() const;

  HDPH_API
  ID _ComputeTextureSourceHash() const;

 private:
  std::string _fragmentSource;
  std::string _geometrySource;

  // Shader Parameters
  HdPh_MaterialParamVector _params;
  HdBufferSpecVector _paramSpec;
  HdBufferArrayRangeSharedPtr _paramArray;
  TfTokenVector _primvarNames;
  bool _isEnabledPrimvarFiltering;

  mutable size_t _computedHash;
  mutable bool _isValidComputedHash;

  mutable size_t _computedTextureSourceHash;
  mutable bool _isValidComputedTextureSourceHash;

  NamedTextureHandleVector _namedTextureHandles;

  TfToken _materialTag;

  // No copying
  HdPhSurfaceShader(const HdPhSurfaceShader &) = delete;
  HdPhSurfaceShader &operator=(const HdPhSurfaceShader &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_SURFACE_SHADER_H
