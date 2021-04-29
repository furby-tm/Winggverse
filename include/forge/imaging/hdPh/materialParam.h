#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/materialParam.h"
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
#ifndef FORGE_IMAGING_HD_PH_MATERIAL_PARAM_H
#define FORGE_IMAGING_HD_PH_MATERIAL_PARAM_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/vt/value.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/types.h"
#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPh_MaterialParamVector = std::vector<class HdPh_MaterialParam>;

// XXX: Docs
class HdPh_MaterialParam final {
 public:
  typedef size_t ID;

  // Indicates the kind of material parameter.
  enum ParamType {
    // This is a shader specified fallback value that is
    // not connected to either a primvar or texture.
    ParamTypeFallback,
    // This is a parameter that is connected to a texture.
    ParamTypeTexture,
    // Creates an accessor HdGet_name() that either reads a
    // primvar with a potentially different name (given in
    // samplerCoords) if it exists or uses the fallback value.
    // It corresponds to a primvar reader shading node.
    ParamTypePrimvarRedirect,
    // Creates an accessor HdGet_name(vec3) that either reads
    // from a field texture with a potentially different name (given
    // in samplerCoords) if it exists or uses the fallback value.
    // It corresponds to a field reader shading node.
    ParamTypeFieldRedirect,
    // Additional primvar needed by material. One that is not connected to
    // a input parameter (ParamTypePrimvar).
    ParamTypeAdditionalPrimvar,
    // This is a parameter that is connected to a transform2d node
    ParamTypeTransform2d
  };

  HDPH_API
  HdPh_MaterialParam();

  HDPH_API
  HdPh_MaterialParam(ParamType paramType,
                     TfToken const &name,
                     VtValue const &fallbackValue,
                     TfTokenVector const &samplerCoords = TfTokenVector(),
                     HdTextureType textureType = HdTextureType::Uv,
                     std::string const &swizzle = std::string(),
                     bool const isPremultiplied = false);

  // No d'tor so that we pick up the implicitly declared default
  // move c'tor.

  /// Computes a hash for all parameters using structural information
  /// (name, texture type, primvar names) but not the fallback value.
  HDPH_API
  static ID ComputeHash(HdPh_MaterialParamVector const &shaders);

  HDPH_API
  HdTupleType GetTupleType() const;

  bool IsTexture() const
  {
    return paramType == ParamTypeTexture;
  }
  bool IsPrimvarRedirect() const
  {
    return paramType == ParamTypePrimvarRedirect;
  }
  bool IsFieldRedirect() const
  {
    return paramType == ParamTypeFieldRedirect;
  }
  bool IsFallback() const
  {
    return paramType == ParamTypeFallback;
  }
  bool IsAdditionalPrimvar() const
  {
    return paramType == ParamTypeAdditionalPrimvar;
  }
  bool IsTransform2d() const
  {
    return paramType == ParamTypeTransform2d;
  }

  ParamType paramType;
  TfToken name;
  VtValue fallbackValue;
  TfTokenVector samplerCoords;
  HdTextureType textureType;
  std::string swizzle;
  bool isPremultiplied;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MATERIAL_PARAM_H
