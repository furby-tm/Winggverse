#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extCompGpuComputationBufferSource.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_BUFFER_SOURCE_H
#define FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_BUFFER_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/extCompGpuComputationResource.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPhExtCompGpuComputationBufferSource
///
/// A Buffer Source that represents input processing for a GPU implementation
/// of an ExtComputation.
///
/// The source is responsible for resolving the inputs that are directed
/// at the computation itself rather than coming from the HdRprim the
/// computation is attached to. All the inputs bound through this source are
/// reflected in the compute kernel as read-only accessors accessible
/// via HdGet_<name>.
///
/// A GLSL example kernel using an input from a primvar computation would be:
/// \code
/// void compute(int index) {
///   // assumes the input buffer is named 'sourcePoints'
///   vec3 point = HdGet_sourcePoints(index);
///   // 'points' is an rprim primvar (HdToken->points)
///   HdSet_points(index, point * 2.0);
/// }
/// \endcode
///
/// In the example above a buffer source was given a input source named
/// 'sourcePoints' of type vec3. HdPhCodeGen generated the corresponding
/// accessor allowing the kernel to use it.
/// \see HdPhExtCompGpuComputation
class HdPhExtCompGpuComputationBufferSource final : public HdNullBufferSource {
 public:
  /// Constructs a GPU ExtComputation buffer source.
  /// \param[in] inputs the vector of HdBufferSource that are inputs to the
  /// computation only. This should not include inputs that are already
  /// assigned to an HdRprim that the computation is executing on.
  /// \param[inout] resource the GPU resident resource that will contain the data
  /// in the inputs after Resolve is called.
  /// \see HdExtComputation
  HdPhExtCompGpuComputationBufferSource(
      HdBufferSourceSharedPtrVector const &inputs,
      HdPhExtCompGpuComputationResourceSharedPtr const &resource);

  HDPH_API
  virtual ~HdPhExtCompGpuComputationBufferSource() = default;

  /// Resolves the source and populates the HdPhExtCompGpuComputationResource.
  /// This in effect commits resources to the GPU for use in one or more
  /// computations.
  /// As with all other sources this is called by the HdResourceRegistry
  /// during the Resolve phase of HdResourceRegistry::Commit
  HDPH_API
  virtual bool Resolve() override;

  /// Returns the vector of HdBufferSource inputs that this source intends
  /// to commit to GPU.
  virtual HdBufferSourceSharedPtrVector const &GetInputs() const
  {
    return _inputs;
  }

 protected:
  virtual bool _CheckValid() const override;

 private:
  HdBufferSourceSharedPtrVector _inputs;
  HdPhExtCompGpuComputationResourceSharedPtr _resource;

  HdPhExtCompGpuComputationBufferSource() = delete;
  HdPhExtCompGpuComputationBufferSource(const HdPhExtCompGpuComputationBufferSource &) = delete;
  HdPhExtCompGpuComputationBufferSource &operator=(const HdPhExtCompGpuComputationBufferSource &) =
      delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_BUFFER_SOURCE_H
