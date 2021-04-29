#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureUtils.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_UTILS_H
#define FORGE_IMAGING_HD_PH_TEXTURE_UTILS_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hgi/types.h"
#include "forge/imaging/hio/image.h"
#include "forge/imaging/hio/types.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

/// \class HdPhTextureUtils
///
/// Helpers for loading textures.
///
class HdPhTextureUtils {
 public:
  /// Converts given number of texels.
  ///
  /// Conversion can be in-place if the ends of the source and destination
  /// buffers align.
  using ConversionFunction = void (*)(const void *src, size_t numTexels, void *dst);

  /// Get the Hgi format suitable for a given Hio format.
  ///
  /// Premultiply alpha indicates whether a conversion function
  /// multiplying RGB with alpha should be created.
  HDPH_API
  static HgiFormat GetHgiFormat(HioFormat hioFormat, bool premultiplyAlpha);

  /// Returns the conversion function to return a HioFormat
  /// to the corresponding HgiFormat given by GetHgiFormat.
  ///
  /// Returns nullptr if no conversion necessary.
  HDPH_API
  static ConversionFunction GetHioToHgiConversion(HioFormat hioFormat, bool premultiplyAlpha);

  /// Get all mip levels from a file.
  HDPH_API
  static std::vector<HioImageSharedPtr> GetAllMipImages(
      const std::string &filePath, HioImage::SourceColorSpace sourceColorSpace);

  // Compute dimensions so that all tiles fit into the given target memory.
  // First by traversing the given images and then by computing a mip chain
  // starting with the lowest resolution image.
  // Optionally, can also give the index of the image in mips that was used
  // to compute the dimensions.
  HDPH_API
  static GfVec3i ComputeDimensionsFromTargetMemory(const std::vector<HioImageSharedPtr> &mips,
                                                   HgiFormat targetFormat,
                                                   size_t tileCount,
                                                   size_t targetMemory,
                                                   size_t *mipIndex = nullptr);

  // Read given HioImage and convert it to corresponding Hgi format.
  // Returns false if reading the HioImage failed.
  //
  // bufferStart is assumed to point at the beginning of a mip chain
  // with mipInfo describing what mip level of the mip chain to be
  // filled. layer gives the layer number if the mip chain is for an
  // array texture.
  HDPH_API
  static bool ReadAndConvertImage(HioImageSharedPtr const &image,
                                  bool flipped,
                                  bool premultiplyAlpha,
                                  const HgiMipInfo &mipInfo,
                                  size_t layer,
                                  void *bufferStart);
};

FORGE_NAMESPACE_END

#endif
