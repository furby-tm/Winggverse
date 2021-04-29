#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/compExtCompInputSource.h"
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

#ifndef FORGE_IMAGING_HD_COMP_EXT_COMP_INPUT_SOURCE_H
#define FORGE_IMAGING_HD_COMP_EXT_COMP_INPUT_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/extCompInputSource.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdExtCompCpuComputation;

using HdExtCompCpuComputationSharedPtr =
    std::shared_ptr<HdExtCompCpuComputation>;

///
/// An Hd Buffer Source Computation that is used to bind an ExtComputation input
/// to a specific output of another ExtComputation.
///
class Hd_CompExtCompInputSource final : public Hd_ExtCompInputSource {
public:
    /// Constructs the computation, binding inputName to sourceOutputName
    /// on buffer source representation of the source computation.
    HD_API
    Hd_CompExtCompInputSource(const TfToken &inputName,
                              const HdExtCompCpuComputationSharedPtr &source,
                              const TfToken &sourceOutputName);

    HD_API
    virtual ~Hd_CompExtCompInputSource() = default;

    /// Returns true once the source computation has been resolved.
    HD_API
    virtual bool Resolve() override;

    /// Obtains the value of the output from the source computation.
    HD_API
    virtual const VtValue &GetValue() const override;

protected:
    /// Returns true if the binding is successful.
    virtual bool _CheckValid() const override;

private:
    HdExtCompCpuComputationSharedPtr _source;
    size_t                           _sourceOutputIdx;

    Hd_CompExtCompInputSource()                                        = delete;
    Hd_CompExtCompInputSource(const Hd_CompExtCompInputSource &)       = delete;
    Hd_CompExtCompInputSource &operator = (const Hd_CompExtCompInputSource &)
                                                                       = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_COMP_EXT_COMP_INPUT_SOURCE_H
