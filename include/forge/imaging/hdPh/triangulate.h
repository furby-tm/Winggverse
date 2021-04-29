#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/triangulate.h"
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
#ifndef FORGE_IMAGING_HD_PH_TRIANGULATE_H
#define FORGE_IMAGING_HD_PH_TRIANGULATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/version.h"

#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

class HdPh_MeshTopology;

/// \class HdPh_TriangleIndexBuilderComputation
///
/// Triangle indices computation CPU.
///

// Index triangulation generates a mapping from triangle ID to authored
// face index domain, called primitiveParams. The primitive params are stored
// alongside topology index buffers, so that the same aggregation locators can
// be used for such an additional buffer as well. This change transforms index
// buffer from int array to int[3] array or int[4] array at first. Thanks to
// the heterogenius non-interleaved buffer aggregation ability in hd,
// we'll get this kind of buffer layout:
//
// ----+--------+--------+------
// ... |i0 i1 i2|i3 i4 i5| ...   index buffer (for triangles)
// ----+--------+--------+------
// ... |   m0   |   m1   | ...   primitive param buffer (coarse face index)
// ----+--------+--------+------

class HdPh_TriangleIndexBuilderComputation : public HdComputedBufferSource {
 public:
  HdPh_TriangleIndexBuilderComputation(HdPh_MeshTopology *topology, SdfPath const &id);
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual bool Resolve() override;

  virtual bool HasChainedBuffer() const override;
  virtual HdBufferSourceSharedPtrVector GetChainedBuffers() const override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  HdBufferSourceSharedPtr _primitiveParam;
  HdBufferSourceSharedPtr _trianglesEdgeIndices;
};

//

/// \class HdPh_TriangulateFaceVaryingComputation
///
/// CPU face-varying triangulation.
///
class HdPh_TriangulateFaceVaryingComputation : public HdComputedBufferSource {
 public:
  HdPh_TriangulateFaceVaryingComputation(HdPh_MeshTopology *topolgoy,
                                         HdBufferSourceSharedPtr const &source,
                                         SdfPath const &id);

  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual bool Resolve() override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  HdBufferSourceSharedPtr _source;
};

FORGE_NAMESPACE_END

#endif  // HdPh_TRIANGULATE_H
