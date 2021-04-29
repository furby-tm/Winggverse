#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extCompGpuComputation.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_H
#define FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_H

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"
#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/extCompGpuComputationBufferSource.h"
#include "forge/usd/sdf/path.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
class HdExtComputation;
using HdPhGLSLProgramSharedPtr = std::shared_ptr<class HdPhGLSLProgram>;
using HdExtComputationPrimvarDescriptorVector =
    std::vector<struct HdExtComputationPrimvarDescriptor>;

using HdPhExtCompGpuComputationSharedPtr = std::shared_ptr<class HdPhExtCompGpuComputation>;

/// \class HdPhExtCompGpuComputation
/// A Computation that represents a GPU implementation of a ExtComputation.
///
/// The computation implements the basic:
///    input HdBufferArrayRange -> processing -> output HdBufferArrayRange
/// model of HdComputations where processing happens in Execute during the
/// Execute phase of HdResourceRegistry::Commit.
///
/// The computation is performed in three stages by three companion classes:
///
/// 1. HdPhExtCompGpuComputationBufferSource is responsible for loading
/// input HdBuffersources into the input HdBufferArrayRange during the Resolve
/// phase of the HdResourceRegistry::Commit processing.
///
/// 2. HdPhExtCompGpuComputationResource holds the committed GPU resident
/// resources along with the compiled compute shading kernel to execute.
/// The values of the HdBufferArrayRanges for the inputs are stored in this
/// object. The resource can store heterogenous sources with differing number
/// of elements as may be required by computations.
///
/// 3. HdPhExtCompGpuComputation executes the kernel using the committed GPU
/// resident resources and stores the results to the destination
/// HdBufferArrayRange given in Execute. The destination HdBufferArrayRange is
/// allocated by the owning HdRprim that registers the computation with the
/// HdResourceRegistry by calling HdResourceRegistry::AddComputation.
///
/// \see HdPhExtCompGpuComputationBufferSource
/// \see HdPhExtCompGpuComputationResource
/// \see HdRprim
/// \see HdComputation
/// \see HdResourceRegistry
/// \see HdExtComputation
/// \see HdBufferArrayRange
class HdPhExtCompGpuComputation final : public HdComputation {
 public:
  /// Constructs a new GPU ExtComputation computation.
  /// resource provides the set of input data and kernel to execute this
  /// computation.
  /// compPrimvars identifies the primvar data being computed
  ///
  /// dispatchCount specifies the number of kernel invocations to execute.
  /// elementCount specifies the number of elements to allocate for output.
  HdPhExtCompGpuComputation(SdfPath const &id,
                            HdPhExtCompGpuComputationResourceSharedPtr const &resource,
                            HdExtComputationPrimvarDescriptorVector const &compPrimvars,
                            int dispatchCount,
                            int elementCount);

  /// Creates a GPU computation implementing the given abstract computation.
  /// When created this allocates HdPhExtCompGpuComputationResource to be
  /// shared with the HdPhExtCompGpuComputationBufferSource. Nothing
  /// is assigned GPU resources unless the source is subsequently added to
  /// the hdResourceRegistry and the registry is committed.
  ///
  /// This delayed allocation allow Rprims to share computed primvar data and
  /// avoid duplicate allocations GPU resources for computation inputs and
  /// outputs.
  ///
  /// \param[in] sceneDelegate the delegate to pull scene inputs from.
  /// \param[in] sourceComp the abstract computation in the HdRenderIndex
  /// this instance actually implements.
  /// \param[in] compPrimvars identifies the primvar data being computed.
  /// \see HdExtComputation
  HDPH_API
  static HdPhExtCompGpuComputationSharedPtr CreateGpuComputation(
      HdSceneDelegate *sceneDelegate,
      HdExtComputation const *sourceComp,
      HdExtComputationPrimvarDescriptorVector const &compPrimvars);

  HDPH_API
  virtual ~HdPhExtCompGpuComputation() = default;

  /// Adds the output buffer specs generated by this computation to the
  /// passed in vector of buffer specs.
  /// \param[out] specs the vector of HdBufferSpec to add this computation
  /// output buffer layout requirements to.
  HDPH_API
  virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;

  /// Executes the computation on the GPU.
  /// Called by HdResourceRegistry::Commit with the HdBufferArrayRange given
  /// to the HdResourceRegistry when the computation was added to the
  /// registry.
  /// \param[inout] range the buffer array range to save the computation
  /// result to.
  /// \param[in] resourceRegistry the registry that is current committing
  /// resources to the GPU.
  HDPH_API
  virtual void Execute(HdBufferArrayRangeSharedPtr const &range,
                       HdResourceRegistry *resourceRegistry) override;

  /// Gets the number of GPU kernel invocations to execute.
  /// It can be useful for this to be different than the number of output
  /// elements, e.g. to run a per-curve kernel computing multiple points
  /// per-curve.
  HDPH_API
  int GetDispatchCount() const;

  /// Gets the number of elements in the output primvar.
  /// The number of elements produced by the computation must be known before
  /// doing the computation. The allocation of GPU resources needs to know
  /// the size to allocate before the kernel can run.
  HDPH_API
  virtual int GetNumOutputElements() const override;

  /// Gets the shared GPU resource holder for the computation.
  /// HdPhExtCompGPUComputationBufferSource will copy its data into this if
  /// it had been added to the HdResourceRegistry.
  HDPH_API
  virtual HdPhExtCompGpuComputationResourceSharedPtr const &GetResource() const;

 private:
  SdfPath _id;
  HdPhExtCompGpuComputationResourceSharedPtr _resource;
  HdExtComputationPrimvarDescriptorVector _compPrimvars;
  int _dispatchCount;
  int _elementCount;

  HdPhExtCompGpuComputation() = delete;
  HdPhExtCompGpuComputation(const HdPhExtCompGpuComputation &) = delete;
  HdPhExtCompGpuComputation &operator=(const HdPhExtCompGpuComputation &) = delete;
};

/// Obtains a set of ExtComputation primvar source computations needed for this
/// Rprim.
///
/// The list of computed primvar descriptors for an interpolation mode
/// is passed in.
///
/// The scene delegate also provides information about which output on
/// which computation is providing the source of the primvar.
///
/// Based on the information, the function creates the necessary
/// computations and appends them on to the sources list (the sources vector
/// need not be empty).
///
/// The caller is expected to pass these computation on these computations
/// onto the resource registry (associating them with BARs if it is
/// expected the primvar will be downloaded)  Additional sources that
/// should be associated with BARs but do not otherwise need to be scheduled
/// for commit will be returned in reserveOnlySources.
///
/// The computation may also need to add sources that are resolved against
/// internal BARs that are not to be associated with the primvar BAR. Those
/// are returned in the separateComputationSources vector.
/// The caller is expected to add them to the resource registry if the
/// computation is needed.
HDPH_API
void HdPh_GetExtComputationPrimvarsComputations(
    const SdfPath &id,
    HdSceneDelegate *sceneDelegate,
    HdExtComputationPrimvarDescriptorVector const &allCompPrimvars,
    HdDirtyBits dirtyBits,
    HdBufferSourceSharedPtrVector *sources,
    HdBufferSourceSharedPtrVector *reserveOnlySources,
    HdBufferSourceSharedPtrVector *separateComputationSources,
    HdPhComputationSharedPtrVector *computations);

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMP_GPU_COMPUTATION_H
