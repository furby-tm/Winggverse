#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/dynamicUvTextureImplementation.h"
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
#ifndef FORGE_IMAGING_HD_PH_DYNAMIC_UV_TEXTURE_IMPLEMENTATION_H
#define FORGE_IMAGING_HD_PH_DYNAMIC_UV_TEXTURE_IMPLEMENTATION_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

class HdPhDynamicUvTextureObject;

/// \class HdPhDynamicUvTextureImplementation
///
/// Allows external clients to specify how a UV texture is loaded from, e.g.,
/// a file and how it is committed to the GPU.
///
class HdPhDynamicUvTextureImplementation {
 public:
  /// Called during the load phase of the Phoenix texture system
  /// when a texture file is supposed to be loaded to the CPU.
  ///
  /// This method has to be thread-safe.
  ///
  virtual void Load(HdPhDynamicUvTextureObject *textureObject) = 0;

  /// Called during the commit phase of the Phoenix texture system
  /// when the CPU texture is committed to the GPU.
  virtual void Commit(HdPhDynamicUvTextureObject *textureObject) = 0;

  /// Queried by, e.g., the material system to determine whether
  /// to use, e.g., the fallback value of a texture node.
  virtual bool IsValid(const HdPhDynamicUvTextureObject *textureObject) = 0;
};

FORGE_NAMESPACE_END

#endif
