#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/quadrangulate.h"
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
#ifndef FORGE_IMAGING_HD_PH_QUADRANGULATE_H
#define FORGE_IMAGING_HD_PH_QUADRANGULATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/tokens.h"
#include "forge/imaging/hd/version.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/array.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

using HdPh_QuadInfoBuilderComputationSharedPtr =
    std::shared_ptr<class HdPh_QuadInfoBuilderComputation>;

class HdPh_MeshTopology;

/*
  Computation classes for quadrangulation.

   *CPU quadrangulation

    (buffersource)
     QuadIndexBuilderComputation  (quad indices)
      |
      +--QuadrangulateComputation (primvar quadrangulation)

     note: QuadrangulateComputation also copies the original primvars.
           no need to transfer the original primvars to GPU separately.

       +--------------------+
   CPU |  original primvars |
       +--------------------+
                |
                v
       +--------------------+-------------------------+
   CPU |  original primvars | quadrangulated primvars |
       +--------------------+-------------------------+
       <---------------------------------------------->
                    filled by computation
                          |
                          v
                         GPU

   *GPU quadrangulation

    (buffersource)
     QuadIndexBuilderComputation  (quad indices)
      |
      +--QuadrangulateTableComputation  (quadrangulate table on GPU)

    (computation)
     QuadrangulateComputationGPU  (primvar quadrangulation)

     note: QuadrangulateComputationGPU just fills quadrangulated primvars.
           the original primvars has to be transfered before the computation.

       +--------------------+
   CPU |  original primvars |
       +--------------------+
                |
                v
               GPU
                |
                v
       +--------------------+-------------------------+
   GPU |  original primvars | quadrangulated primvars |
       +--------------------+-------------------------+
                            <------------------------->
                               filled by computation

   *Computation dependencies

    Topology ---> QuadInfo --->  QuadIndices
                           --->  QuadrangulateComputation(CPU)
                           --->  QuadrangulateTable --->
                           ----------------------------> QuadrangulateComputationGPU
 */

/// \class HdPh_QuadInfoBuilderComputation
///
/// Quad info computation.
///
class HdPh_QuadInfoBuilderComputation : public HdNullBufferSource {
 public:
  HdPh_QuadInfoBuilderComputation(HdPh_MeshTopology *topology, SdfPath const &id);
  virtual bool Resolve() override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
};

/// \class HdPh_QuadIndexBuilderComputation
///
/// Quad indices computation CPU.
///

// Index quadrangulation generates a mapping from triangle ID to authored
// face index domain, called primitiveParams. The primitive params are
// stored alongisde topology index buffers, so that the same aggregation
// locators can be used for such an additional buffer as well. This change
// transforms index buffer from int array to int[3] array or int[4] array at
// first. Thanks to the heterogenius non-interleaved buffer aggregation ability
// in hd, we'll get this kind of buffer layout:
//
// ----+-----------+-----------+------
// ... |i0 i1 i2 i3|i4 i5 i6 i7| ...    index buffer (for quads)
// ----+-----------+-----------+------
// ... |     m0    |     m1    | ...    primitive param buffer (coarse face index)
// ----+-----------+-----------+------

class HdPh_QuadIndexBuilderComputation : public HdComputedBufferSource {
 public:
  HdPh_QuadIndexBuilderComputation(HdPh_MeshTopology *topology,
                                   HdPh_QuadInfoBuilderComputationSharedPtr const &quadInfoBuilder,
                                   SdfPath const &id);
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual bool Resolve() override;

  virtual bool HasChainedBuffer() const override;
  virtual HdBufferSourceSharedPtrVector GetChainedBuffers() const override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  HdPh_QuadInfoBuilderComputationSharedPtr _quadInfoBuilder;
  HdBufferSourceSharedPtr _primitiveParam;
  HdBufferSourceSharedPtr _quadsEdgeIndices;
};

/// \class HdPh_QuadrangulateTableComputation
///
/// Quadrangulate table computation (for GPU quadrangulation).
///
class HdPh_QuadrangulateTableComputation : public HdComputedBufferSource {
 public:
  HdPh_QuadrangulateTableComputation(HdPh_MeshTopology *topology,
                                     HdBufferSourceSharedPtr const &quadInfoBuilder);
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual bool Resolve() override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  HdBufferSourceSharedPtr _quadInfoBuilder;
};

/// \class HdPh_QuadrangulateComputation
///
/// CPU quadrangulation.
///
class HdPh_QuadrangulateComputation : public HdComputedBufferSource {
 public:
  HdPh_QuadrangulateComputation(HdPh_MeshTopology *topology,
                                HdBufferSourceSharedPtr const &source,
                                HdBufferSourceSharedPtr const &quadInfoBuilder,
                                SdfPath const &id);
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual bool Resolve() override;
  virtual HdTupleType GetTupleType() const override;

  virtual bool HasPreChainedBuffer() const override;
  virtual HdBufferSourceSharedPtr GetPreChainedBuffer() const override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  HdBufferSourceSharedPtr _source;
  HdBufferSourceSharedPtr _quadInfoBuilder;
};

/// \class HdPh_QuadrangulateFaceVaryingComputation
///
/// CPU face-varying quadrangulation.
///
class HdPh_QuadrangulateFaceVaryingComputation : public HdComputedBufferSource {
 public:
  HdPh_QuadrangulateFaceVaryingComputation(HdPh_MeshTopology *topolgoy,
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

/// \class HdPh_QuadrangulateComputationGPU
///
/// GPU quadrangulation.
///
class HdPh_QuadrangulateComputationGPU : public HdComputation {
 public:
  /// This computaion doesn't generate buffer source (i.e. 2nd phase)
  HdPh_QuadrangulateComputationGPU(HdPh_MeshTopology *topology,
                                   TfToken const &sourceName,
                                   HdType dataType,
                                   SdfPath const &id);
  virtual void Execute(HdBufferArrayRangeSharedPtr const &range,
                       HdResourceRegistry *resourceRegistry) override;
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  virtual int GetNumOutputElements() const override;

 private:
  SdfPath const _id;
  HdPh_MeshTopology *_topology;
  TfToken _name;
  HdType _dataType;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_QUADRANGULATE_H
