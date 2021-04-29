#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/assetUvTextureCpuData.h"
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
#ifndef FORGE_IMAGING_HDPH_ASSET_UV_TEXTURE_CPU_DATA_H
#define FORGE_IMAGING_HDPH_ASSET_UV_TEXTURE_CPU_DATA_H

#include "forge/forge.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/textureCpuData.h"
#include "forge/imaging/hgi/texture.h"
#include "forge/imaging/hio/image.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

/// \class HdPhAssetUvTextureCpuData
///
/// Implements HdPhTextureCpuData by reading a uv texture from
/// a file.
///
class HdPhAssetUvTextureCpuData : public HdPhTextureCpuData {
 public:
  HDPH_API
  HdPhAssetUvTextureCpuData(std::string const &filePath,
                            size_t targetMemory,
                            bool premultiplyAlpha,
                            HioImage::ImageOriginLocation originLocation,
                            HioImage::SourceColorSpace sourceColorSpace);

  HDPH_API
  ~HdPhAssetUvTextureCpuData() override;

  HDPH_API
  const HgiTextureDesc &GetTextureDesc() const override;

  HDPH_API
  bool GetGenerateMipmaps() const override;

  HDPH_API
  bool IsValid() const override;

  /// The wrap info extracted from the image file.
  HDPH_API
  const std::pair<HdWrap, HdWrap> &GetWrapInfo() const
  {
    return _wrapInfo;
  }

 private:
  void _SetWrapInfo(HioImageSharedPtr const &image);

  // Pointer to the potentially converted data.
  std::unique_ptr<unsigned char[]> _rawBuffer;

  // The result, including a pointer to the potentially
  // converted texture data in _textureDesc.initialData.
  HgiTextureDesc _textureDesc;

  // If true, initialData only contains mip level 0 data
  // and the GPU is supposed to generate the other mip levels.
  bool _generateMipmaps;

  // Wrap modes
  std::pair<HdWrap, HdWrap> _wrapInfo;
};

FORGE_NAMESPACE_END

#endif
