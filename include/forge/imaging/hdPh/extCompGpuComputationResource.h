#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extCompGpuComputationResource.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_RESOURCE_H
#define FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_RESOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/extCompComputeShader.h"
#include "forge/imaging/hdPh/resourceBinder.h"
#include "forge/imaging/hdPh/resourceRegistry.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPhExtCompGpuComputationResourceSharedPtr =
    std::shared_ptr<class HdPhExtCompGpuComputationResource>;
using HdPhGLSLProgramSharedPtr = std::shared_ptr<class HdPhGLSLProgram>;
using HdBufferArrayRangeSharedPtrVector = std::vector<HdBufferArrayRangeSharedPtr>;

/// \class HdPhExtCompGpuComputationResource
///
/// A resource that represents the persistent GPU resources of an ExtComputation.
///
/// The persistent resources are shared between the ephemeral
/// HdPhExtCompGpuComputationBufferSource and the actual
/// HdPhExtCompGpuComputation. Once the buffer source is resolved the resource
/// is configured for the computation and it will then persist until the
/// computation is released.
///
/// All program and binding data required for compiling and loading HdRprim and
/// internal primvar data is held by this object. The companion source and
/// computation appeal to this object to access the GPU resources.
///
/// \see HdPhExtCompGpuComputation
/// \see HdPhExtCompGpuComputationBufferSource
class HdPhExtCompGpuComputationResource final {
 public:
  /// Creates a GPU computation resource that can bind resources matching
  /// the layout of the compute kernel.
  /// The registry passed is the registry that the kernel program will
  /// be shared amongst. De-duplication of the compiled and linked program
  /// for runtime execution happens on a per-registry basis.
  ///
  /// Memory for the input computation buffers must be provided
  /// This must be done prior to a HdResourceRegistry::Commit in
  /// which the computation has been added.
  /// Note that the Resource allocates no memory on its own and can be
  /// speculatively created and later de-duplicated, or discarded,
  /// without wasting resources.
  ///
  /// \param[in] outputBufferSpecs the buffer specs that the computation is
  /// expecting to output.
  /// \param[in] kernel the compute kernel source to run as the computation.
  /// \param[in] registry the registry that the internal computation
  /// will cache and de-duplicate its compute shader instance with.
  HdPhExtCompGpuComputationResource(HdBufferSpecVector const &outputBufferSpecs,
                                    HdPh_ExtCompComputeShaderSharedPtr const &kernel,
                                    HdBufferArrayRangeSharedPtrVector const &inputs,
                                    HdPhResourceRegistrySharedPtr const &registry);

  virtual ~HdPhExtCompGpuComputationResource() = default;

  /// Gets the HdBufferArrayRange that inputs should be loaded into using the
  /// resource binder.
  HdBufferArrayRangeSharedPtrVector const &GetInputs() const
  {
    return _inputs;
  }

  /// Gets the GPU HdPhGLSLProgram to run to execute the computation.
  /// This may have been shared with many other instances in the same
  /// registry.
  /// The program is only valid for execution after Resolve has been called.
  HdPhGLSLProgramSharedPtr const &GetProgram() const
  {
    return _computeProgram;
  }

  /// Gets the resource binder that matches the layout of the compute program.
  /// The binder is only valid for resolving layouts after Resolve has been
  /// called.
  HdPh_ResourceBinder const &GetResourceBinder() const
  {
    return _resourceBinder;
  }

  /// Resolve the resource bindings and program for use by a computation.
  /// The compute program is resolved and linked against the input and output
  /// resource bindings and the kernel source in this step.
  HDPH_API
  bool Resolve();

 private:
  HdBufferSpecVector _outputBufferSpecs;
  HdPh_ExtCompComputeShaderSharedPtr _kernel;
  HdPhResourceRegistrySharedPtr _registry;

  size_t _shaderSourceHash;
  HdBufferArrayRangeSharedPtrVector _inputs;
  HdPhGLSLProgramSharedPtr _computeProgram;
  HdPh_ResourceBinder _resourceBinder;

  HdPhExtCompGpuComputationResource() = delete;
  HdPhExtCompGpuComputationResource(const HdPhExtCompGpuComputationResource &) = delete;
  HdPhExtCompGpuComputationResource &operator=(const HdPhExtCompGpuComputationResource &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_RESOURCE_H
