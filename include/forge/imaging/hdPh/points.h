#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/points.h"
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
#ifndef FORGE_IMAGING_HD_PH_POINTS_H
#define FORGE_IMAGING_HD_PH_POINTS_H

#include "forge/forge.h"
#include "forge/imaging/hd/drawingCoord.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/points.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/vt/array.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPhPoints
///
/// Points.
///
class HdPhPoints final : public HdPoints {
 public:
  HF_MALLOC_TAG_NEW("new HdPhPoints");

  HDPH_API
  HdPhPoints(SdfPath const &id);

  HDPH_API
  ~HdPhPoints() override;

  HDPH_API
  void Sync(HdSceneDelegate *delegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits,
            TfToken const &reprToken) override;

  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

 protected:
  HDPH_API
  void _InitRepr(TfToken const &reprToken, HdDirtyBits *dirtyBits) override;

  HDPH_API
  HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

  void _UpdateRepr(HdSceneDelegate *sceneDelegate,
                   HdRenderParam *renderParam,
                   TfToken const &reprToken,
                   HdDirtyBits *dirtyBitsState);

  void _PopulateVertexPrimvars(HdSceneDelegate *sceneDelegate,
                               HdRenderParam *renderParam,
                               HdPhDrawItem *drawItem,
                               HdDirtyBits *dirtyBitsState);

 private:
  HdReprSharedPtr _smoothHullRepr;

  bool _displayOpacity;

  enum DrawingCoord { InstancePrimvar = HdDrawingCoord::CustomSlotsBegin };

  void _UpdateDrawItem(HdSceneDelegate *sceneDelegate,
                       HdRenderParam *renderParam,
                       HdPhDrawItem *drawItem,
                       HdDirtyBits *dirtyBits);
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_POINTS_H
