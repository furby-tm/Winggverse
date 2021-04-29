#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/pointsShaderKey.h"
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
#ifndef FORGE_IMAGING_HD_PH_POINTS_SHADER_KEY_H
#define FORGE_IMAGING_HD_PH_POINTS_SHADER_KEY_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/geometricShader.h"
#include "forge/imaging/hdPh/shaderKey.h"

FORGE_NAMESPACE_BEGIN

struct HdPh_PointsShaderKey : public HdPh_ShaderKey {
  HdPh_PointsShaderKey();
  ~HdPh_PointsShaderKey();

  TfToken const &GetGlslfxFilename() const override
  {
    return glslfx;
  }
  TfToken const *GetVS() const override
  {
    return VS;
  }
  // Skip TCS, TES and GS stages
  TfToken const *GetFS() const override
  {
    return FS;
  }

  HdPh_GeometricShader::PrimitiveType GetPrimitiveType() const override
  {
    return HdPh_GeometricShader::PrimitiveType::PRIM_POINTS;
  }

  TfToken glslfx;
  TfToken VS[6];
  TfToken FS[6];
};

FORGE_NAMESPACE_END

#endif  // HDPH_POINTS_SHADER_KEY
