#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/glConversions.h"
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
#ifndef FORGE_IMAGING_HD_PH_GL_CONVERSIONS_H
#define FORGE_IMAGING_HD_PH_GL_CONVERSIONS_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hio/types.h"

FORGE_NAMESPACE_BEGIN

class HdPhGLConversions {
 public:
  /// Returns the size of glDataType.
  /// For example: sizeof(GLuint)
  HDPH_API
  static size_t GetComponentSize(int glDataType);

  HDPH_API
  static GLenum GetGlDepthFunc(HdCompareFunction func);

  HDPH_API
  static GLenum GetGlStencilFunc(HdCompareFunction func);

  HDPH_API
  static GLenum GetGlStencilOp(HdStencilOp op);

  HDPH_API
  static GLenum GetGlBlendOp(HdBlendOp op);

  HDPH_API
  static GLenum GetGlBlendFactor(HdBlendFactor factor);

  HDPH_API
  static int GetGLAttribType(HdType type);

  /// Return the name of the given type as represented in GLSL.
  HDPH_API
  static TfToken GetGLSLTypename(HdType type);

  /// Return a GLSL-safe, mangled name identifier.
  HDPH_API
  static TfToken GetGLSLIdentifier(TfToken const &identifier);
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_GL_CONVERSIONS_H
