#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureCpuData.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_CPU_DATA_H
#define FORGE_IMAGING_HD_PH_TEXTURE_CPU_DATA_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

struct HgiTextureDesc;

/// \class HdPhTextureCpuData
///
/// Represents CPU data that can be stored in a HdPhUvTextureObject, mostly,
/// likely during the load phase to be committed to the GPU.
///
class HdPhTextureCpuData {
 public:
  HDPH_API
  virtual ~HdPhTextureCpuData();

  /// The metadata of the texture (width, height, ...) including a
  /// pointer to the CPU data (as initialData).
  virtual const HgiTextureDesc &GetTextureDesc() const = 0;

  /// Make GPU generate mipmaps. The number of mipmaps is specified
  /// in the texture descriptor and the mipmaps are generate from
  /// the mip level 0 data.
  virtual bool GetGenerateMipmaps() const = 0;

  /// Are the data valid (e.g., false if file could not be found).
  virtual bool IsValid() const = 0;
};

FORGE_NAMESPACE_END

#endif
