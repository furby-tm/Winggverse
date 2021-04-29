#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/lightingShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_LIGHTING_SHADER_H
#define FORGE_IMAGING_HD_PH_LIGHTING_SHADER_H

#include "forge/base/gf/matrix4d.h"
#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"

FORGE_NAMESPACE_BEGIN

using HdPhLightingShaderSharedPtr = std::shared_ptr<class HdPhLightingShader>;

/// \class HdPhLightingShader
///
/// A lighting shader base class.
///
class HdPhLightingShader : public HdPhShaderCode {
 public:
  HDPH_API
  HdPhLightingShader();
  HDPH_API
  virtual ~HdPhLightingShader();

  /// Sets camera state.
  virtual void SetCamera(GfMatrix4d const &worldToViewMatrix,
                         GfMatrix4d const &projectionMatrix) = 0;

 private:
  // No copying
  HdPhLightingShader(const HdPhLightingShader &) = delete;
  HdPhLightingShader &operator=(const HdPhLightingShader &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_LIGHTING_SHADER_H
