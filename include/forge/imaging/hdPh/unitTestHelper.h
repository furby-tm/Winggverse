#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/unitTestHelper.h"
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
#ifndef FORGE_IMAGING_HD_PH_UNIT_TEST_HELPER_H
#define FORGE_IMAGING_HD_PH_UNIT_TEST_HELPER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/lightingShader.h"
#include "forge/imaging/hdPh/renderDelegate.h"
#include "forge/imaging/hdPh/renderPassState.h"

#include "forge/imaging/hd/driver.h"
#include "forge/imaging/hd/engine.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hd/unitTestDelegate.h"
#include "forge/imaging/hio/glslfx.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec4d.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

using HgiUniquePtr = std::unique_ptr<class Hgi>;

/// \class HdPh_TestDriver
///
/// A unit test driver that exercises the core engine.
///
/// \note This test driver does NOT assume OpenGL is available; in the even
/// that is is not available, all OpenGL calls become no-ops, but all other work
/// is performed as usual.
///
class HdPh_TestDriver final {
 public:
  HdPh_TestDriver();
  HdPh_TestDriver(TfToken const &reprName);
  HdPh_TestDriver(HdReprSelector const &reprToken);
  ~HdPh_TestDriver();

  /// Draw
  void Draw(bool withGuides = false);

  /// Draw with external renderPass
  void Draw(HdRenderPassSharedPtr const &renderPass, bool withGuides);

  /// Set camera to renderpass
  void SetCamera(GfMatrix4d const &modelViewMatrix,
                 GfMatrix4d const &projectionMatrix,
                 GfVec4d const &viewport);

  void SetCameraClipPlanes(std::vector<GfVec4d> const &clipPlanes);

  /// Set cull style
  void SetCullStyle(HdCullStyle cullStyle);

  /// Returns the renderpass
  HdRenderPassSharedPtr const &GetRenderPass();

  /// Returns the renderPassState
  HdPhRenderPassStateSharedPtr const &GetRenderPassState() const
  {
    return _renderPassState;
  }

  /// Returns the UnitTest delegate
  HdUnitTestDelegate &GetDelegate()
  {
    return *_sceneDelegate;
  }

  /// Switch repr
  void SetRepr(HdReprSelector const &reprToken);

 private:
  void _Init(HdReprSelector const &reprToken);

  // Hgi and HdDriver should be constructed before HdEngine to ensure they
  // are destructed last. Hgi may be used during engine/delegate destruction.
  HgiUniquePtr _hgi;
  HdDriver _hgiDriver;

  HdEngine _engine;
  HdPhRenderDelegate _renderDelegate;
  HdRenderIndex *_renderIndex;
  HdUnitTestDelegate *_sceneDelegate;

  SdfPath _cameraId;
  HdReprSelector _reprToken;

  HdRenderPassSharedPtr _renderPass;
  HdPhRenderPassStateSharedPtr _renderPassState;
  HdRprimCollection _collection;
};

/// \class HdPh_TestLightingShader
///
/// A custom lighting shader for unit tests.
///
using HdPh_TestLightingShaderSharedPtr = std::shared_ptr<class HdPh_TestLightingShader>;

class HdPh_TestLightingShader : public HdPhLightingShader {
 public:
  HDPH_API
  HdPh_TestLightingShader();
  HDPH_API
  ~HdPh_TestLightingShader() override;

  /// HdPhShaderCode overrides
  HDPH_API
  ID ComputeHash() const override;
  std::string GetSource(TfToken const &shaderStageKey) const override;
  HDPH_API
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;
  HDPH_API
  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;
  void AddBindings(HdBindingRequestVector *customBindings) override;

  /// HdPhLightingShader overrides
  void SetCamera(GfMatrix4d const &worldToViewMatrix, GfMatrix4d const &projectionMatrix) override;

  void SetSceneAmbient(GfVec3f const &color);
  void SetLight(int light, GfVec3f const &dir, GfVec3f const &color);

 private:
  struct Light {
    GfVec3f dir;
    GfVec3f eyeDir;
    GfVec3f color;
  };
  Light _lights[2];
  GfVec3f _sceneAmbient;
  std::unique_ptr<HioGlslfx> _glslfx;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_UNIT_TEST_HELPER_H
