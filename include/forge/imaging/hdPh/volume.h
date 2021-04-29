#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/volume.h"
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
#ifndef FORGE_IMAGING_HD_PH_VOLUME_H
#define FORGE_IMAGING_HD_PH_VOLUME_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/volume.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

class HdPhDrawItem;

/// Represents a Volume Prim.
///
class HdPhVolume final : public HdVolume {
 public:
  HDPH_API
  HdPhVolume(SdfPath const &id);
  HDPH_API
  ~HdPhVolume() override;

  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  HDPH_API
  void Sync(HdSceneDelegate *delegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits,
            TfToken const &reprToken) override;

  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  /// Default step size used for raymarching
  static const float defaultStepSize;

  /// Default step size used for raymarching for lighting computation
  static const float defaultStepSizeLighting;

  /// Default memory limit for a field texture (in Mb) if not
  /// overridden by field prim with textureMemory.
  static const float defaultMaxTextureMemoryPerField;

 protected:
  void _InitRepr(TfToken const &reprToken, HdDirtyBits *dirtyBits) override;

  HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

  void _UpdateRepr(HdSceneDelegate *sceneDelegate,
                   HdRenderParam *renderParam,
                   TfToken const &reprToken,
                   HdDirtyBits *dirtyBitsState);

 private:
  void _UpdateDrawItem(HdSceneDelegate *sceneDelegate,
                       HdRenderParam *renderParam,
                       HdPhDrawItem *drawItem,
                       HdDirtyBits *dirtyBits);

  HdReprSharedPtr _volumeRepr;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_VOLUME_H
