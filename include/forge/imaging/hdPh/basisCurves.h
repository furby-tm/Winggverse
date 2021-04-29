#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/basisCurves.h"
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
#ifndef FORGE_IMAGING_HD_PH_BASIS_CURVES_H
#define FORGE_IMAGING_HD_PH_BASIS_CURVES_H

#include "forge/forge.h"
#include "forge/imaging/hd/basisCurves.h"
#include "forge/imaging/hd/drawingCoord.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/vt/array.h"
#include "forge/usd/sdf/path.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhDrawItem;
using HdPh_BasisCurvesTopologySharedPtr = std::shared_ptr<class HdPh_BasisCurvesTopology>;

/// \class HdPhBasisCurves
///
/// A collection of curves using a particular basis.
///
/// Render mode is dependent on both the HdBasisCurvesGeomStyle, refinement
/// level, and the authored primvars.
///
/// If style is set to HdBasisCurvesGeomStyleWire, the curves will always draw
/// as infinitely thin wires.  Cubic curves will be refined if complexity is
/// above 0, otherwise they draw the unrefined control points. (This may
/// provide a misleading representation for Catmull-Rom and Bspline curves.)
///
/// If style is set to HdBasisCurvesGeomStylePatch, the curves will draw as
/// patches ONLY if refinement level is above 0.  Otherwise, they draw
/// as the unrefined control points (see notes on HdBasisCurvesGeomStyleWire).
///
/// Curves rendered as patches may be rendered as ribbons or halftubes.
/// Curves with primvar authored normals will always render as ribbons.
/// Curves without primvar authored normals are assumed to be round and may be
/// rendered in one of three styles:
///   * if complexity is 1, a camera facing normal is used
///   * if complexity is 2, a fake "bumped" round normal is used
///   * if complexity is 3 or above, the patch is displaced into a half tube
/// We plan for future checkins will remove the need for the camera facing normal
/// mode, using the fake "bumped" round normal instead.
class HdPhBasisCurves final : public HdBasisCurves {
 public:
  HF_MALLOC_TAG_NEW("new HdPhBasisCurves");

  HDPH_API
  HdPhBasisCurves(SdfPath const &id);

  HDPH_API
  ~HdPhBasisCurves() override;

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

  void _PopulateTopology(HdSceneDelegate *sceneDelegate,
                         HdRenderParam *renderParam,
                         HdPhDrawItem *drawItem,
                         HdDirtyBits *dirtyBits,
                         const HdBasisCurvesReprDesc &desc);

  void _PopulateVertexPrimvars(HdSceneDelegate *sceneDelegate,
                               HdRenderParam *renderParam,
                               HdPhDrawItem *drawItem,
                               HdDirtyBits *dirtyBits);

  void _PopulateVaryingPrimvars(HdSceneDelegate *sceneDelegate,
                                HdRenderParam *renderParam,
                                HdPhDrawItem *drawItem,
                                HdDirtyBits *dirtyBits);

  void _PopulateElementPrimvars(HdSceneDelegate *sceneDelegate,
                                HdRenderParam *renderParam,
                                HdPhDrawItem *drawItem,
                                HdDirtyBits *dirtyBits);

 private:
  enum DrawingCoord {
    HullTopology = HdDrawingCoord::CustomSlotsBegin,
    PointsTopology,
    InstancePrimvar  // has to be at the very end
  };

  enum DirtyBits : HdDirtyBits {
    DirtyIndices = HdChangeTracker::CustomBitsBegin,
    DirtyHullIndices = (DirtyIndices << 1),
    DirtyPointsIndices = (DirtyHullIndices << 1)
  };

  // When processing primvars, these will get set to if we determine that
  // we should do cubic basis interpolation on the normals and widths.
  // NOTE: I worry that it may be possible for these to get out of sync.
  // The right long term fix is likely to maintain proper separation between
  // varying and vertex primvars throughout the HdPh rendering pipeline.
  bool _basisWidthInterpolation = false;
  bool _basisNormalInterpolation = false;

  bool _SupportsRefinement(int refineLevel);
  bool _SupportsUserWidths(HdPhDrawItem *drawItem);
  bool _SupportsUserNormals(HdPhDrawItem *drawItem);

  void _UpdateDrawItem(HdSceneDelegate *sceneDelegate,
                       HdRenderParam *renderParam,
                       HdPhDrawItem *drawItem,
                       HdDirtyBits *dirtyBits,
                       const HdBasisCurvesReprDesc &desc);

  void _UpdateDrawItemGeometricShader(HdSceneDelegate *sceneDelegate,
                                      HdRenderParam *renderParam,
                                      HdPhDrawItem *drawItem,
                                      const HdBasisCurvesReprDesc &desc);

  void _UpdateShadersForAllReprs(HdSceneDelegate *sceneDelegate,
                                 HdRenderParam *renderParam,
                                 bool updateMaterialShader,
                                 bool updateGeometricShader);

  HdPh_BasisCurvesTopologySharedPtr _topology;
  HdTopology::ID _topologyId;
  HdDirtyBits _customDirtyBitsInUse;
  int _refineLevel;  // XXX: could be moved into HdBasisCurveTopology.
  bool _displayOpacity : 1;
  bool _occludedSelectionShowsThrough : 1;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_BASIS_CURVES_H
