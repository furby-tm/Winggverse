#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extComputation.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMPUTATION_H
#define FORGE_IMAGING_HD_PH_EXT_COMPUTATION_H

#include "forge/base/vt/value.h"
#include "forge/forge.h"
#include "forge/imaging/hd/extComputation.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/usd/sdf/path.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

/// \class HdPhExtComputation
///
/// Specialization of HdExtComputation which manages inputs as GPU resources.
///
class HdPhExtComputation : public HdExtComputation {
 public:
  /// Construct a new ExtComputation identified by id.
  HDPH_API
  HdPhExtComputation(SdfPath const &id);

  HDPH_API
  ~HdPhExtComputation() override;

  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  HDPH_API
  HdBufferArrayRangeSharedPtr const &GetInputRange() const
  {
    return _inputRange;
  }

 private:
  // No default construction or copying
  HdPhExtComputation() = delete;
  HdPhExtComputation(const HdPhExtComputation &) = delete;
  HdPhExtComputation &operator=(const HdPhExtComputation &) = delete;

  HdBufferArrayRangeSharedPtr _inputRange;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMPUTATION_H
