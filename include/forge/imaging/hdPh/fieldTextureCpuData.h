#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/fieldTextureCpuData.h"
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

#ifndef FORGE_IMAGING_HD_PH_FIELD_TEXTURE_CPU_DATA_H
#define FORGE_IMAGING_HD_PH_FIELD_TEXTURE_CPU_DATA_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/textureCpuData.h"
#include "forge/imaging/hgi/texture.h"

#include "forge/base/tf/declarePtrs.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HioFieldTextureDataSharedPtr = std::shared_ptr<class HioFieldTextureData>;

/// \class HdPhTextureCpuData
///
/// An implmentation of HdPhTextureCpuData that can be initialized
/// from HioFieldTextureData.
///
class HdPh_FieldTextureCpuData : public HdPhTextureCpuData {
 public:
  /// It is assumed that Read(...) has already been called
  /// on textureData.

  HDPH_API
  HdPh_FieldTextureCpuData(HioFieldTextureDataSharedPtr const &textureData,
                           const std::string &debugName,
                           bool premultiplyAlpha = true);

  HDPH_API
  ~HdPh_FieldTextureCpuData() override;

  HDPH_API
  const HgiTextureDesc &GetTextureDesc() const override;

  HDPH_API
  bool GetGenerateMipmaps() const override;

  HDPH_API
  bool IsValid() const override;

 private:
  // The result, including a pointer to the potentially
  // converted texture data in _textureDesc.initialData.
  HgiTextureDesc _textureDesc;

  // If true, initialData only contains mip level 0 data
  // and the GPU is supposed to generate the other mip levels.
  bool _generateMipmaps;

  // To avoid a copy, hold on to original data if we
  // can use them.
  HioFieldTextureDataSharedPtr _textureData;

  // Buffer if we had to convert the data.
  std::unique_ptr<const unsigned char[]> _convertedData;
};

FORGE_NAMESPACE_END

#endif
