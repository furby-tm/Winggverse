#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/mesh.h"
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
#ifndef FORGE_IMAGING_HD_PH_MESH_H
#define FORGE_IMAGING_HD_PH_MESH_H

#include "forge/forge.h"
#include "forge/imaging/hd/changeTracker.h"
#include "forge/imaging/hd/drawingCoord.h"
#include "forge/imaging/hd/mesh.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/vt/array.h"
#include "forge/usd/sdf/path.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhDrawItem;
class HdSceneDelegate;

using Hd_VertexAdjacencySharedPtr = std::shared_ptr<class Hd_VertexAdjacency>;
using HdBufferSourceSharedPtr = std::shared_ptr<class HdBufferSource>;
using HdPh_MeshTopologySharedPtr = std::shared_ptr<class HdPh_MeshTopology>;

using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;

/// A subdivision surface or poly-mesh object.
///
class HdPhMesh final : public HdMesh {
 public:
  HF_MALLOC_TAG_NEW("new HdPhMesh");

  HDPH_API
  HdPhMesh(SdfPath const &id);

  HDPH_API
  ~HdPhMesh() override;

  HDPH_API
  void Sync(HdSceneDelegate *delegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits,
            TfToken const &reprToken) override;

  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  /// Topology (member) getter
  HDPH_API
  HdMeshTopologySharedPtr GetTopology() const override;

  /// Returns whether packed (10_10_10 bits) normals to be used
  HDPH_API
  static bool IsEnabledPackedNormals();

 protected:
  HDPH_API
  void _InitRepr(TfToken const &reprToken, HdDirtyBits *dirtyBits) override;

  HDPH_API
  HdDirtyBits _PropagateDirtyBits(HdDirtyBits bits) const override;

  void _UpdateRepr(HdSceneDelegate *sceneDelegate,
                   HdRenderParam *renderParam,
                   TfToken const &reprToken,
                   HdDirtyBits *dirtyBitsState);

  HdBufferArrayRangeSharedPtr _GetSharedPrimvarRange(
      uint64_t primvarId,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayRangeSharedPtr const &curRange,
      bool *isFirstInstance,
      HdPhResourceRegistrySharedPtr const &resourceRegistry) const;

  bool _UseQuadIndices(const HdRenderIndex &renderIndex,
                       HdPh_MeshTopologySharedPtr const &topology) const;

  bool _UseLimitRefinement(const HdRenderIndex &renderIndex) const;

  bool _UseSmoothNormals(HdPh_MeshTopologySharedPtr const &topology) const;

  bool _UseFlatNormals(const HdMeshReprDesc &desc) const;

  void _UpdateDrawItem(HdSceneDelegate *sceneDelegate,
                       HdRenderParam *renderParam,
                       HdPhDrawItem *drawItem,
                       HdDirtyBits *dirtyBits,
                       const HdMeshReprDesc &desc,
                       bool requireSmoothNormals,
                       bool requireFlatNormals);

  void _UpdateDrawItemGeometricShader(HdSceneDelegate *sceneDelegate,
                                      HdRenderParam *renderParam,
                                      HdPhDrawItem *drawItem,
                                      const HdMeshReprDesc &desc);

  void _UpdateShadersForAllReprs(HdSceneDelegate *sceneDelegate,
                                 HdRenderParam *renderParam,
                                 bool updateMaterialShader,
                                 bool updateGeometricShader);

  void _PopulateTopology(HdSceneDelegate *sceneDelegate,
                         HdRenderParam *renderParam,
                         HdPhDrawItem *drawItem,
                         HdDirtyBits *dirtyBits,
                         const HdMeshReprDesc &desc);

  void _PopulateAdjacency(HdPhResourceRegistrySharedPtr const &resourceRegistry);

  void _PopulateVertexPrimvars(HdSceneDelegate *sceneDelegate,
                               HdRenderParam *renderParam,
                               HdPhDrawItem *drawItem,
                               HdDirtyBits *dirtyBits,
                               bool requireSmoothNormals);

  void _PopulateFaceVaryingPrimvars(HdSceneDelegate *sceneDelegate,
                                    HdRenderParam *renderParam,
                                    HdPhDrawItem *drawItem,
                                    HdDirtyBits *dirtyBits,
                                    const HdMeshReprDesc &desc);

  void _PopulateElementPrimvars(HdSceneDelegate *sceneDelegate,
                                HdRenderParam *renderParam,
                                HdPhDrawItem *drawItem,
                                HdDirtyBits *dirtyBits,
                                bool requireFlatNormals);

  int _GetRefineLevelForDesc(const HdMeshReprDesc &desc) const;

 private:
  enum DrawingCoord {
    HullTopology = HdDrawingCoord::CustomSlotsBegin,
    PointsTopology,
    InstancePrimvar  // has to be at the very end
  };

  enum DirtyBits : HdDirtyBits {
    DirtySmoothNormals = HdChangeTracker::CustomBitsBegin,
    DirtyFlatNormals = (DirtySmoothNormals << 1),
    DirtyIndices = (DirtyFlatNormals << 1),
    DirtyHullIndices = (DirtyIndices << 1),
    DirtyPointsIndices = (DirtyHullIndices << 1)
  };

  HdPh_MeshTopologySharedPtr _topology;
  Hd_VertexAdjacencySharedPtr _vertexAdjacency;

  HdTopology::ID _topologyId;
  HdTopology::ID _vertexPrimvarId;
  HdDirtyBits _customDirtyBitsInUse;

  HdType _pointsDataType;
  HdInterpolation _sceneNormalsInterpolation;
  HdCullStyle _cullStyle;
  bool _hasMirroredTransform : 1;
  bool _doubleSided : 1;
  bool _flatShadingEnabled : 1;
  bool _displacementEnabled : 1;
  bool _limitNormals : 1;
  bool _sceneNormals : 1;
  bool _hasVaryingTopology : 1;  // The prim's topology has changed since
                                 // the prim was created
  bool _displayOpacity : 1;
  bool _occludedSelectionShowsThrough : 1;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MESH_H
