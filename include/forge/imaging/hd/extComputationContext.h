#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/extComputationContext.h"
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
#ifndef FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_H
#define FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

///
/// Interface class that defines the execution environment for the client
/// to run a computation.
///
class HdExtComputationContext {
public:
    HdExtComputationContext() = default;
    virtual ~HdExtComputationContext();

    ///
    /// Obtains the value of an named input to the computation.
    ///
    /// The code will issue a coding error and return a empty array
    /// if the input is missing or of a different type.
    ///
    virtual const VtValue &GetInputValue(const TfToken &name) const = 0;

    ///
    /// Obtains the value of an named input to the computation.
    ///
    /// If the input isn't present or of a different type
    /// nullptr will be returned.
    ///
    virtual const VtValue *GetOptionalInputValuePtr(
                                                 const TfToken &name) const = 0;

    ///
    /// Set the value of the specified output.
    ///
    virtual void SetOutputValue(const TfToken &name, const VtValue &output) = 0;

    ///
    /// Called to indicate an error occurred while executing a computation
    /// so that its output are invalid.
    ///
    virtual void RaiseComputationError() = 0;

private:
    HdExtComputationContext(const HdExtComputationContext &)           = delete;
    HdExtComputationContext &operator = (const HdExtComputationContext &)
                                                                       = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_H
