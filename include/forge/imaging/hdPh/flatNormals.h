#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/flatNormals.h"
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
#ifndef FORGE_IMAGING_HD_PH_FLAT_NORMALS_H
#define FORGE_IMAGING_HD_PH_FLAT_NORMALS_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

class Hd_FaceCoords;

/// flat normal computation GPU
///
///
class HdPh_FlatNormalsComputationGPU : public HdComputation {
 public:
  /// Constructor
  HDPH_API
  HdPh_FlatNormalsComputationGPU(HdBufferArrayRangeSharedPtr const &topologyRange,
                                 HdBufferArrayRangeSharedPtr const &vertexRange,
                                 int numFaces,
                                 TfToken const &srcName,
                                 TfToken const &dstName,
                                 HdType srcDataType,
                                 bool packed);

  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
  HDPH_API
  virtual void Execute(HdBufferArrayRangeSharedPtr const &range,
                       HdResourceRegistry *resourceRegistry) override;

  virtual int GetNumOutputElements() const override;

 private:
  HdBufferArrayRangeSharedPtr const _topologyRange;
  HdBufferArrayRangeSharedPtr const _vertexRange;
  int _numFaces;
  TfToken _srcName;
  TfToken _dstName;
  HdType _srcDataType;
  HdType _dstDataType;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_FLAT_NORMALS_H
