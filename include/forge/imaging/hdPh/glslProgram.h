#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/glslProgram.h"
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
#ifndef FORGE_IMAGING_HD_PH_GLSL_PROGRAM_H
#define FORGE_IMAGING_HD_PH_GLSL_PROGRAM_H

#include "forge/forge.h"

#include "forge/base/tf/token.h"

#include "forge/imaging/hd/version.h"

#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hgi/buffer.h"
#include "forge/imaging/hgi/shaderProgram.h"
#include "forge/imaging/hgi/enums.h"

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;
using HdPhGLSLProgramSharedPtr = std::shared_ptr<class HdPhGLSLProgram>;

using HgiShaderProgramHandle = HgiHandle<class HgiShaderProgram>;

/// \class HdPhGLSLProgram
///
/// An instance of a glsl program.
///
class HdPhGLSLProgram final {
 public:
  typedef size_t ID;

  HDPH_API
  HdPhGLSLProgram(TfToken const &role, HdPhResourceRegistry *const registry);
  
  HDPH_API
  ~HdPhGLSLProgram();

  /// Returns the hash value of the program for \a sourceFile
  HDPH_API
  static ID ComputeHash(TfToken const &sourceFile);

  /// Compile shader source for a shader stage.
  HDPH_API
  bool CompileShader(HgiShaderStage stage, std::string const &source);

  /// Link the compiled shaders together.
  HDPH_API
  bool Link();

  /// Validate if this program is a valid progam in the current context.
  HDPH_API
  bool Validate() const;

  /// Returns HdResource of the program object.
  HgiShaderProgramHandle const &GetProgram() const
  {
    return _program;
  }

  /// Convenience method to get a shared compute shader program
  HDPH_API
  static HdPhGLSLProgramSharedPtr GetComputeProgram(TfToken const &shaderToken,
                                                    HdPhResourceRegistry *resourceRegistry);

  HDPH_API
  static HdPhGLSLProgramSharedPtr GetComputeProgram(TfToken const &shaderFileName,
                                                    TfToken const &shaderToken,
                                                    HdPhResourceRegistry *resourceRegistry);

  /// Returns the role of the GPU data in this resource.
  TfToken const &GetRole() const
  {
    return _role;
  }

 private:
  HdPhResourceRegistry *const _registry;
  TfToken _role;

  HgiShaderProgramDesc _programDesc;
  HgiShaderProgramHandle _program;

  // An identifier for uniquely identifying the program, for debugging
  // purposes - programs that fail to compile for one reason or another
  // will get deleted, and their GL program IDs reused, so we can't use
  // that to identify it uniquely
  size_t _debugID;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_GLSL_PROGRAM_H
