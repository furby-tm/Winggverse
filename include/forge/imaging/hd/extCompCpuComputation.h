#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/extCompCpuComputation.h"
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
#ifndef FORGE_IMAGING_HD_EXT_COMP_CPU_COMPUTATION_H
#define FORGE_IMAGING_HD_EXT_COMP_CPU_COMPUTATION_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/extCompInputSource.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
class HdExtComputation;
class HdExtCompCpuComputation;

using HdExtCompCpuComputationSharedPtr =
    std::shared_ptr<HdExtCompCpuComputation>;

///
/// A Buffer Source that represents a CPU implementation of a ExtComputation.
///
/// The computation implements the basic: input->processing->output model
/// where the inputs are other buffer sources and processing happens during
/// resolve.
///
/// As a computation may have many outputs, the outputs from the CPU
/// Computation can not be directly associated with a BAR.  Instead
/// other buffer source computation bind the output to sources that can
/// be used in a BAR.
///
/// Outputs to a computation are in SOA form, so a computation may have
/// many outputs, but each output has the same number of elements in it.
class HdExtCompCpuComputation final : public HdNullBufferSource {
public:
    static const size_t INVALID_OUTPUT_INDEX;

    /// Constructs a new Cpu ExtComputation source.
    /// inputs provides a list of buffer sources that this computation
    /// requires.
    /// outputs is a list of outputs by names that the computation produces.
    ///
    /// Num elements specifies the number of elements in the output.
    ///
    /// sceneDelegate and id are used to callback to the scene delegate
    /// in order to invoke computation processing.
    HdExtCompCpuComputation(const SdfPath &id,
                            const Hd_ExtCompInputSourceSharedPtrVector &inputs,
                            const TfTokenVector &outputs,
                            int numElements,
                            HdSceneDelegate *sceneDelegate);

    /// Create a CPU computation implementing the given abstract computation.
    /// The scene delegate identifies which delegate to pull scene inputs from.
    HD_API
    static HdExtCompCpuComputationSharedPtr
    CreateComputation(HdSceneDelegate *sceneDelegate,
                      const HdExtComputation &computation,
                      HdBufferSourceSharedPtrVector *computationSources);

    HD_API
    virtual ~HdExtCompCpuComputation() = default;

    /// Returns the id for this computation as a token.
    HD_API
    virtual TfToken const &GetName() const override;

    /// Ask the scene delegate to run the computation and captures the output
    /// signals.
    HD_API
    virtual bool Resolve() override;

    HD_API
    virtual size_t GetNumElements() const override;


    /// Converts a output name token into an index.
    HD_API
    size_t GetOutputIndex(const TfToken &outputName) const;

    /// Returns the value of the specified output
    /// (after the computations been Resolved).
    HD_API
    const VtValue &GetOutputByIndex(size_t index) const;

protected:
    /// Returns if the computation is specified correctly.
    HD_API
    virtual bool _CheckValid() const override;

private:
    SdfPath                               _id;
    Hd_ExtCompInputSourceSharedPtrVector  _inputs;
    TfTokenVector                         _outputs;
    size_t                                _numElements;
    HdSceneDelegate                      *_sceneDelegate;

    std::vector<VtValue>                  _outputValues;

    HdExtCompCpuComputation()                                          = delete;
    HdExtCompCpuComputation(const HdExtCompCpuComputation &)           = delete;
    HdExtCompCpuComputation &operator = (const HdExtCompCpuComputation &)
                                                                       = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_EXT_COMP_CPU_COMPUTATION_H
