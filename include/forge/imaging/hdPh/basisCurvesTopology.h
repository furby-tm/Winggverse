#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/basisCurvesTopology.h"
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
#ifndef FORGE_IMAGING_HD_PH_BASIS_CURVES_TOPOLOGY_H
#define FORGE_IMAGING_HD_PH_BASIS_CURVES_TOPOLOGY_H

#include "forge/forge.h"
#include "forge/imaging/hd/basisCurvesTopology.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPh_BasisCurvesTopologySharedPtr = std::shared_ptr<class HdPh_BasisCurvesTopology>;

using HdBufferSourceSharedPtr = std::shared_ptr<class HdBufferSource>;

// HdPh_BasisCurvesTopology
//
// Phoenix implementation for basisCurves topology.
//
class HdPh_BasisCurvesTopology final : public HdBasisCurvesTopology {
 public:
  static HdPh_BasisCurvesTopologySharedPtr New(const HdBasisCurvesTopology &src);

  virtual ~HdPh_BasisCurvesTopology();

  HdBufferSourceSharedPtr GetPointsIndexBuilderComputation();
  HdBufferSourceSharedPtr GetIndexBuilderComputation(bool forceLines);

 private:
  // Must be created through factory
  explicit HdPh_BasisCurvesTopology(const HdBasisCurvesTopology &src);

  // No default construction or copying.
  HdPh_BasisCurvesTopology() = delete;
  HdPh_BasisCurvesTopology(const HdPh_BasisCurvesTopology &) = delete;
  HdPh_BasisCurvesTopology &operator=(const HdPh_BasisCurvesTopology &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_BASIS_CURVES_TOPOLOGY_H
