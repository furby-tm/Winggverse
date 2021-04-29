#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureHandle.h"
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
#ifndef HD_ST_TEXTURE_HANDLE_H
#define HD_ST_TEXTURE_HANDLE_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/types.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPhShaderCodePtr = std::weak_ptr<class HdPhShaderCode>;
using HdPhTextureObjectSharedPtr = std::shared_ptr<class HdPhTextureObject>;
using HdPhSamplerObjectSharedPtr = std::shared_ptr<class HdPhSamplerObject>;

using HdPhTextureHandleSharedPtr = std::shared_ptr<class HdPhTextureHandle>;

class HdPh_TextureHandleRegistry;

/// \class HdPhTextureHandle
///
/// Represents a texture and sampler that will be allocated and loaded
/// from a texture file during commit, possibly a texture sampler
/// handle and a memory request. It is intended for HdPhShaderCode and
/// HdPhShaderCode::AddResourcesFromTextures() is called whenever
/// the underlying texture and sampler gets allocated and (re-)loaded
/// so that the shader code can react to, e.g., changing texture
/// sampler handle for bindless or changing texture metadata such as a
/// field bounding box for volumes.
///
class HdPhTextureHandle {
 public:
  /// See HdPhResourceRegistry::AllocateTextureHandle for details.
  HDPH_API
  HdPhTextureHandle(HdPhTextureObjectSharedPtr const &textureObject,
                    const HdSamplerParameters &samplerParams,
                    size_t memoryRequest,
                    bool createBindlessHandle,
                    HdPhShaderCodePtr const &shaderCode,
                    HdPh_TextureHandleRegistry *textureHandleRegistry);

  HDPH_API
  ~HdPhTextureHandle();

  /// Get texture object.
  ///
  /// Can be accessed after commit.
  HdPhTextureObjectSharedPtr const &GetTextureObject() const
  {
    return _textureObject;
  }

  /// Get sampler object.
  ///
  /// Can be accessed after commit.
  HdPhSamplerObjectSharedPtr const &GetSamplerObject() const
  {
    return _samplerObject;
  }

  /// Get sampler parameters.
  ///
  HdSamplerParameters const &GetSamplerParameters() const
  {
    return _samplerParams;
  }

  /// Get how much memory this handle requested for the texture.
  ///
  size_t GetMemoryRequest() const
  {
    return _memoryRequest;
  }

  /// Get the shader code associated with this handle.
  ///
  HdPhShaderCodePtr const &GetShaderCode() const
  {
    return _shaderCode;
  }

  /// Allocate sampler for this handle (not thread-safe).
  ///
  /// This also creates the texture sampler handle (for bindless
  /// textures) and updates it on subsequent calls.
  ///
  HDPH_API
  void ReallocateSamplerIfNecessary();

 private:
  HdPhTextureObjectSharedPtr _textureObject;
  HdPhSamplerObjectSharedPtr _samplerObject;
  HdSamplerParameters _samplerParams;
  size_t _memoryRequest;
  bool _createBindlessHandle;
  HdPhShaderCodePtr _shaderCode;
  HdPh_TextureHandleRegistry *_textureHandleRegistry;
};

FORGE_NAMESPACE_END

#endif
