#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/ptexTextureObject.h"
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
#ifndef FORGE_IMAGING_HD_PH_PTEX_TEXTURE_OBJECT_H
#define FORGE_IMAGING_HD_PH_PTEX_TEXTURE_OBJECT_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/textureObject.h"

#include "forge/imaging/hgi/handle.h"

#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec3i.h"

#ifdef FORGE_PTEX_SUPPORT_ENABLED
#  include "forge/imaging/hdPh/ptexMipmapTextureLoader.h"
#endif

FORGE_NAMESPACE_BEGIN

/// Returns true if the file given by \p imageFilePath represents a ptex file,
/// and false otherwise.
///
/// This function simply checks the extension of the file name and does not
/// otherwise guarantee that the file is in any way valid for reading.
///
/// If ptex support is disabled, this function will always return false.
///
HDPH_API bool HdPhIsSupportedPtexTexture(std::string const &imageFilePath);

enum HgiFormat : int;
using HgiTextureHandle = HgiHandle<class HgiTexture>;

/// \class HdPhPtexTextureObject
///
/// A Ptex texture.
///
class HdPhPtexTextureObject final : public HdPhTextureObject {
 public:
  HDPH_API
  HdPhPtexTextureObject(const HdPhTextureIdentifier &textureId,
                        HdPh_TextureObjectRegistry *textureObjectRegistry);

  HDPH_API
  ~HdPhPtexTextureObject() override;

  /// Get the GPU texture handle for the texels
  ///
  /// Only valid after commit phase.
  ///
  HgiTextureHandle GetTexelTexture() const
  {
    return _texelTexture;
  }

  /// Get the GPU texture handle for the layout
  ///
  /// Only valid after commit phase.
  ///
  HgiTextureHandle GetLayoutTexture() const
  {
    return _layoutTexture;
  }

  HDPH_API
  bool IsValid() const override;

  HDPH_API
  HdTextureType GetTextureType() const override;

 protected:
  HDPH_API
  void _Load() override;

  HDPH_API
  void _Commit() override;

 private:
  HgiFormat _format;
  GfVec3i _texelDimensions;
  int _texelLayers;
  size_t _texelDataSize;
  GfVec2i _layoutDimensions;
  size_t _layoutDataSize;

  std::unique_ptr<uint8_t[]> _texelData;
  std::unique_ptr<uint8_t[]> _layoutData;

  HgiTextureHandle _texelTexture;
  HgiTextureHandle _layoutTexture;

  void _DestroyTextures();
};

template<> struct HdPh_TypedTextureObjectHelper<HdTextureType::Ptex> {
  using type = HdPhPtexTextureObject;
};

FORGE_NAMESPACE_END

#endif
