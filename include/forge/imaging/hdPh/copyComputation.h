#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/copyComputation.h"
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
#ifndef FORGE_IMAGING_HD_PH_COPY_COMPUTATION_H
#define FORGE_IMAGING_HD_PH_COPY_COMPUTATION_H

#include "forge/forge.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPhCopyComputationGPU
///
/// A GPU computation which transfers a vbo range specified by src and name to
/// the given range.
///
class HdPhCopyComputationGPU : public HdComputation {
 public:
  HDPH_API
  HdPhCopyComputationGPU(HdBufferArrayRangeSharedPtr const &src, TfToken const &name);

  HDPH_API
  virtual void Execute(HdBufferArrayRangeSharedPtr const &range,
                       HdResourceRegistry *resourceRegistry) override;

  HDPH_API
  virtual int GetNumOutputElements() const override;

  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;

 private:
  HdBufferArrayRangeSharedPtr _src;
  TfToken _name;
};

FORGE_NAMESPACE_END

#endif  // HDPH_COMPUTATION_H
