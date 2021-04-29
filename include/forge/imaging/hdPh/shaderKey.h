#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/shaderKey.h"
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
#ifndef FORGE_IMAGING_HD_PH_SHADER_KEY_H
#define FORGE_IMAGING_HD_PH_SHADER_KEY_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/geometricShader.h"  // XXX: for PrimitiveType

FORGE_NAMESPACE_BEGIN

// Abstract interface for geometric shader keys that may be used to
// construct a geometric shader.
struct HdPh_ShaderKey {
  typedef size_t ID;

  HDPH_API
  virtual ~HdPh_ShaderKey();

  // The hash computed identifies each geometric shader instance, and is used
  // for deduplication in the resource registry.
  HDPH_API
  ID ComputeHash() const;

  // Stitches the glslfx filename and the shader stage mixin names into
  // a string for consumption by HioGlslfx.
  HDPH_API
  std::string GetGlslfxString() const;

  // -------------------------------------------------------------------------
  // Virtual interface
  // -------------------------------------------------------------------------

  // Return the name of the glslfx file that houses the entry point mixins
  // that define the main() function for the relevant shader stages.
  // The expectation is that this file includes the glslfx files that
  // define any functions it uses.
  virtual TfToken const &GetGlslfxFilename() const = 0;

  // Each shader stage specifies the various mixins to stitch together
  // via their token names. The Get* flavor of methods return the first
  // token in the array.
  HDPH_API
  virtual TfToken const *GetVS() const;
  HDPH_API
  virtual TfToken const *GetTCS() const;
  HDPH_API
  virtual TfToken const *GetTES() const;
  HDPH_API
  virtual TfToken const *GetGS() const;
  HDPH_API
  virtual TfToken const *GetFS() const;

  // An implementation detail of code gen, which generates slightly
  // different code for the VS stage for the frustum culling pass.
  HDPH_API
  virtual bool IsFrustumCullingPass() const;

  // Returns the geometric shader primitive type that is used in code gen
  // and to figure out the primitive mode during draw submission.
  virtual HdPh_GeometricShader::PrimitiveType GetPrimitiveType() const = 0;

  // Implementation details of the geometric shader that sets hardware
  // pipeline state (cull face, polygon mode, line width) or queues upload of
  // data (cullstyle) to the GPU.
  HDPH_API
  virtual HdCullStyle GetCullStyle() const;
  HDPH_API
  virtual bool UseHardwareFaceCulling() const;
  HDPH_API
  virtual bool HasMirroredTransform() const;
  HDPH_API
  virtual bool IsDoubleSided() const;
  HDPH_API
  virtual HdPolygonMode GetPolygonMode() const;
  HDPH_API
  virtual float GetLineWidth() const;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_SHADER_KEY_H
