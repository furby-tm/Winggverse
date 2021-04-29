#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/udimTextureObject.h"
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
#ifndef FORGE_IMAGING_HD_PH_UDIM_TEXTURE_OBJECT_H
#define FORGE_IMAGING_HD_PH_UDIM_TEXTURE_OBJECT_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/textureObject.h"

#include "forge/imaging/hgi/handle.h"

#include "forge/base/gf/vec3i.h"

FORGE_NAMESPACE_BEGIN

enum HgiFormat : int;
using HgiTextureHandle = HgiHandle<class HgiTexture>;

/// Returns true if the file given by \p imageFilePath represents a udim file,
/// and false otherwise.
///
/// This function simply checks the existence of the <udim> tag in the
/// file name and does not otherwise guarantee that
/// the file is in any way valid for reading.
///
HDPH_API bool HdPhIsSupportedUdimTexture(std::string const &imageFilePath);

/// \class HdPhUdimTextureObject
///
/// A UDIM texture.
///
class HdPhUdimTextureObject final : public HdPhTextureObject {
 public:
  HDPH_API
  HdPhUdimTextureObject(const HdPhTextureIdentifier &textureId,
                        HdPh_TextureObjectRegistry *textureObjectRegistry);

  HDPH_API
  ~HdPhUdimTextureObject() override;

  /// Get the gpu texture name for the texels
  ///
  /// Only valid after commit phase.
  ///
  HgiTextureHandle const &GetTexelTexture() const
  {
    return _texelTexture;
  }

  /// Get the gpu texture name for the layout
  ///
  /// Only valid after commit phase.
  ///
  HgiTextureHandle const &GetLayoutTexture() const
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
  std::vector<uint8_t> _textureData;
  std::vector<float> _layoutData;

  GfVec3i _dimensions;
  size_t _tileCount;
  size_t _mipCount;
  HgiFormat _hgiFormat;

  HgiTextureHandle _texelTexture;
  HgiTextureHandle _layoutTexture;

  void _DestroyTextures();
};

template<> struct HdPh_TypedTextureObjectHelper<HdTextureType::Udim> {
  using type = HdPhUdimTextureObject;
};

FORGE_NAMESPACE_END

#endif
