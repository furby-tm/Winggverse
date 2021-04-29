#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extCompGpuPrimvarBufferSource.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H
#define FORGE_IMAGING_HD_PH_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/tf/token.h"

#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPhExtCompGpuPrimvarBufferSource
/// A buffer source mapped to an output of an ExtComp CPU computation.
///
class HdPhExtCompGpuPrimvarBufferSource final : public HdNullBufferSource {
 public:
  HdPhExtCompGpuPrimvarBufferSource(TfToken const &name,
                                    HdTupleType const &valueType,
                                    int numElements,
                                    SdfPath const &compId);

  HDPH_API
  virtual ~HdPhExtCompGpuPrimvarBufferSource() = default;

  HDPH_API
  virtual size_t ComputeHash() const override;

  HDPH_API
  virtual bool Resolve() override;

  HD_API
  virtual TfToken const &GetName() const override;

  HDPH_API
  virtual size_t GetNumElements() const override;

  HD_API
  virtual HdTupleType GetTupleType() const override;

  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;

 protected:
  virtual bool _CheckValid() const override;

 private:
  TfToken _name;
  HdTupleType _tupleType;
  size_t _numElements;
  SdfPath _compId;

  HdPhExtCompGpuPrimvarBufferSource() = delete;
  HdPhExtCompGpuPrimvarBufferSource(const HdPhExtCompGpuPrimvarBufferSource &) = delete;
  HdPhExtCompGpuPrimvarBufferSource &operator=(const HdPhExtCompGpuPrimvarBufferSource &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMP_GPU_PRIMVAR_BUFFER_SOURCE_H
