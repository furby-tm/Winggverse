#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/meshShaderKey.h"
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
#ifndef FORGE_IMAGING_HD_PH_MESH_SHADER_KEY_H
#define FORGE_IMAGING_HD_PH_MESH_SHADER_KEY_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/geometricShader.h"
#include "forge/imaging/hdPh/shaderKey.h"

FORGE_NAMESPACE_BEGIN

struct HdPh_MeshShaderKey : public HdPh_ShaderKey {
  enum NormalSource {
    NormalSourceScene,
    NormalSourceSmooth,
    NormalSourceLimit,
    NormalSourceFlat,
    NormalSourceGeometryShader
  };

  HdPh_MeshShaderKey(HdPh_GeometricShader::PrimitiveType primType,
                     TfToken shadingTerminal,
                     bool useCustomDisplacement,
                     NormalSource normalsSource,
                     HdInterpolation normalsInterpolation,
                     bool doubleSided,
                     bool forceGeometryShader,
                     bool hasTopologicalVisibility,
                     bool blendWireframeColor,
                     HdCullStyle cullStyle,
                     HdMeshGeomStyle geomStyle,
                     float lineWidth,
                     bool hasMirroredTransform,
                     bool hasInstancer,
                     bool enableScalarOverride);

  // Note: it looks like gcc 4.8 has a problem issuing
  // a wrong warning as "array subscript is above array bounds"
  // when the default destructor is automatically generated at callers.
  // Having an empty destructor explicitly within this linkage apparently
  // avoids the issue.
  ~HdPh_MeshShaderKey();

  HdCullStyle GetCullStyle() const override
  {
    return cullStyle;
  }
  bool UseHardwareFaceCulling() const override
  {
    return useHardwareFaceCulling;
  }
  bool HasMirroredTransform() const override
  {
    return hasMirroredTransform;
  }
  bool IsDoubleSided() const override
  {
    return doubleSided;
  }

  HdPolygonMode GetPolygonMode() const override
  {
    return polygonMode;
  }
  float GetLineWidth() const override
  {
    return lineWidth;
  }
  HdPh_GeometricShader::PrimitiveType GetPrimitiveType() const override
  {
    return primType;
  }

  HdPh_GeometricShader::PrimitiveType primType;
  HdCullStyle cullStyle;
  bool useHardwareFaceCulling;
  bool hasMirroredTransform;
  bool doubleSided;
  HdPolygonMode polygonMode;
  float lineWidth;

  TfToken const &GetGlslfxFilename() const override
  {
    return glslfx;
  }
  TfToken const *GetVS() const override
  {
    return VS;
  }
  TfToken const *GetTCS() const override
  {
    return TCS;
  }
  TfToken const *GetTES() const override
  {
    return TES;
  }
  TfToken const *GetGS() const override
  {
    return GS;
  }
  TfToken const *GetFS() const override
  {
    return FS;
  }

  TfToken glslfx;
  TfToken VS[7];
  TfToken TCS[3];
  TfToken TES[4];
  TfToken GS[11];
  TfToken FS[15];
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MESH_SHADER_KEY_H
