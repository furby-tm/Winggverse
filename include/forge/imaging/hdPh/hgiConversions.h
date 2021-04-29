#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/hgiConversions.h"
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
#ifndef FORGE_IMAGING_HD_PH_HGI_CONVERSIONS_H
#define FORGE_IMAGING_HD_PH_HGI_CONVERSIONS_H

#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/types.h"

FORGE_NAMESPACE_BEGIN

///
/// \class HdPhHgiConversions
///
/// Converts from Hd types to Hgi types
///
class HdPhHgiConversions {
 public:
  HDPH_API
  static HgiFormat GetHgiFormat(HdFormat hdFormat);

  HDPH_API
  static HgiSamplerAddressMode GetHgiSamplerAddressMode(HdWrap hdWrap);

  HDPH_API
  static HgiSamplerFilter GetHgiMagFilter(HdMagFilter hdMagFilter);

  /// The HdMinFilter translates into two Hgi enums for
  /// HgiSamplerDesc::minFilter and HgiSamplerDesc::mipFilter.
  ///
  HDPH_API
  static void GetHgiMinAndMipFilter(HdMinFilter hdMinFilter,
                                    HgiSamplerFilter *hgiSamplerFilter,
                                    HgiMipFilter *hgiMipFilter);
};

FORGE_NAMESPACE_END

#endif
