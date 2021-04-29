#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/smoothNormals.h"
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
#ifndef FORGE_IMAGING_HD_PH_SMOOTH_NORMALS_H
#define FORGE_IMAGING_HD_PH_SMOOTH_NORMALS_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

class Hd_VertexAdjacency;

/// smooth normal computation GPU
///
///
class HdPh_SmoothNormalsComputationGPU : public HdComputation {
 public:
  /// Constructor
  HDPH_API
  HdPh_SmoothNormalsComputationGPU(Hd_VertexAdjacency const *adjacency,
                                   TfToken const &srcName,
                                   TfToken const &dstName,
                                   HdType srcDataType,
                                   bool packed);

  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  HDPH_API
  virtual void Execute(HdBufferArrayRangeSharedPtr const &range,
                       HdResourceRegistry *resourceRegistry) override;

  /// This computation doesn't generate buffer source (i.e. 2nd phase)
  /// This is a gpu computation, but no need to resize the destination
  /// since it belongs the same range as src buffer.
  virtual int GetNumOutputElements() const override
  {
    return 0;
  }

 private:
  Hd_VertexAdjacency const *_adjacency;
  TfToken _srcName;
  TfToken _dstName;
  HdType _srcDataType;
  HdType _dstDataType;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_SMOOTH_NORMALS_H
