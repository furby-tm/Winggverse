#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/meshTopology.h"
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
#ifndef FORGE_IMAGING_HD_PH_MESH_TOPOLOGY_H
#define FORGE_IMAGING_HD_PH_MESH_TOPOLOGY_H

#include "forge/forge.h"
#include "forge/imaging/hd/meshTopology.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hd/version.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;
class HdPh_Subdivision;
struct HdQuadInfo;
class SdfPath;

using HdBufferSourceWeakPtr = std::weak_ptr<class HdBufferSource>;
using HdBufferSourceSharedPtr = std::shared_ptr<class HdBufferSource>;

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

using HdComputationSharedPtr = std::shared_ptr<class HdComputation>;

using HdPh_AdjacencyBuilderComputationPtr = std::weak_ptr<class HdPh_AdjacencyBuilderComputation>;

using HdPh_QuadInfoBuilderComputationPtr = std::weak_ptr<class HdPh_QuadInfoBuilderComputation>;
using HdPh_QuadInfoBuilderComputationSharedPtr =
    std::shared_ptr<class HdPh_QuadInfoBuilderComputation>;

using HdPh_MeshTopologySharedPtr = std::shared_ptr<class HdPh_MeshTopology>;

/// \class HdPh_MeshTopology
///
/// Phoenix implementation for mesh topology.
///
class HdPh_MeshTopology final : public HdMeshTopology {
 public:
  /// Specifies how subdivision mesh topology is refined.
  enum RefineMode { RefineModeUniform = 0, RefineModePatches };

  static HdPh_MeshTopologySharedPtr New(const HdMeshTopology &src,
                                        int refineLevel,
                                        RefineMode refineMode = RefineModeUniform);

  virtual ~HdPh_MeshTopology();

  /// Equality check between two mesh topologies.
  bool operator==(HdPh_MeshTopology const &other) const;

  /// \name Triangulation
  /// @{

  /// Returns the triangle indices (for drawing) buffer source computation.
  HdBufferSourceSharedPtr GetTriangleIndexBuilderComputation(SdfPath const &id);

  /// Returns the CPU face-varying triangulate computation
  HdBufferSourceSharedPtr GetTriangulateFaceVaryingComputation(
      HdBufferSourceSharedPtr const &source, SdfPath const &id);

  /// @}

  ///
  /// \name Quadrangulation
  /// @{

  /// Returns the quadinfo computation for the use of primvar
  /// quadrangulation.
  /// If gpu is true, the quadrangulate table will be transferred to GPU
  /// via the resource registry.
  HdPh_QuadInfoBuilderComputationSharedPtr GetQuadInfoBuilderComputation(
      bool gpu, SdfPath const &id, HdPhResourceRegistry *resourceRegistry = nullptr);

  /// Returns the quad indices (for drawing) buffer source computation.
  HdBufferSourceSharedPtr GetQuadIndexBuilderComputation(SdfPath const &id);

  /// Returns the CPU quadrangulated buffer source.
  HdBufferSourceSharedPtr GetQuadrangulateComputation(HdBufferSourceSharedPtr const &source,
                                                      SdfPath const &id);

  /// Returns the GPU quadrangulate computation.
  HdComputationSharedPtr GetQuadrangulateComputationGPU(TfToken const &name,
                                                        HdType dataType,
                                                        SdfPath const &id);

  /// Returns the CPU face-varying quadrangulate computation
  HdBufferSourceSharedPtr GetQuadrangulateFaceVaryingComputation(
      HdBufferSourceSharedPtr const &source, SdfPath const &id);

  /// Returns the quadrangulation table range on GPU
  HdBufferArrayRangeSharedPtr const &GetQuadrangulateTableRange() const
  {
    return _quadrangulateTableRange;
  }

  /// Clears the quadrangulation table range
  void ClearQuadrangulateTableRange()
  {
    _quadrangulateTableRange.reset();
  }

  /// Sets the quadrangulation struct. HdMeshTopology takes an
  /// ownership of quadInfo (caller shouldn't free)
  void SetQuadInfo(HdQuadInfo const *quadInfo);

  /// Returns the quadrangulation struct.
  HdQuadInfo const *GetQuadInfo() const
  {
    return _quadInfo;
  }

  /// @}

  ///
  /// \name Points
  /// @{

  /// Returns the point indices buffer source computation.
  HdBufferSourceSharedPtr GetPointsIndexBuilderComputation();

  /// @}

  ///
  /// \name Subdivision
  /// @{

  /// Returns the subdivision struct.
  HdPh_Subdivision const *GetSubdivision() const
  {
    return _subdivision;
  }

  /// Returns the subdivision struct (non-const).
  HdPh_Subdivision *GetSubdivision()
  {
    return _subdivision;
  }

  /// Returns true if the subdivision on this mesh produces
  /// triangles (otherwise quads)
  bool RefinesToTriangles() const;

  /// Returns true if the subdivision of this mesh produces bspline patches
  bool RefinesToBSplinePatches() const;

  /// Returns true if the subdivision of this mesh produces box spline
  /// triangle patches
  bool RefinesToBoxSplineTrianglePatches() const;

  /// Returns the subdivision topology computation. It computes
  /// far mesh and produces refined quad-indices buffer.
  HdBufferSourceSharedPtr GetOsdTopologyComputation(SdfPath const &debugId);

  /// Returns the refined indices builder computation.
  /// this just returns index and primitive buffer, and should be preceded by
  /// topology computation.
  HdBufferSourceSharedPtr GetOsdIndexBuilderComputation();

  /// Returns the subdivision primvar refine computation on CPU.
  HdBufferSourceSharedPtr GetOsdRefineComputation(HdBufferSourceSharedPtr const &source,
                                                  bool varying);

  /// Returns the subdivision primvar refine computation on GPU.
  HdComputationSharedPtr GetOsdRefineComputationGPU(TfToken const &name, HdType dataType);

  /// @}

 private:
  // quadrangulation info on CPU
  HdQuadInfo const *_quadInfo;

  // quadrangulation info on GPU
  HdBufferArrayRangeSharedPtr _quadrangulateTableRange;

  HdPh_QuadInfoBuilderComputationPtr _quadInfoBuilder;

  // OpenSubdiv
  RefineMode _refineMode;
  HdPh_Subdivision *_subdivision;
  HdBufferSourceWeakPtr _osdTopologyBuilder;

  // Must be created through factory
  explicit HdPh_MeshTopology(const HdMeshTopology &src, int refineLevel, RefineMode refineMode);

  // No default construction or copying.
  HdPh_MeshTopology() = delete;
  HdPh_MeshTopology(const HdPh_MeshTopology &) = delete;
  HdPh_MeshTopology &operator=(const HdPh_MeshTopology &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MESH_TOPOLOGY_H
