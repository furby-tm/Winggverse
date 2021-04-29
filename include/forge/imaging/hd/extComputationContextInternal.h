#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/extComputationContextInternal.h"
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
#ifndef FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_INTERNAL_H
#define FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_INTERNAL_H

#include "forge/forge.h"

#include "forge/imaging/hd/extComputationContext.h"

FORGE_NAMESPACE_BEGIN

///
/// Hydra implementation of the HdExtComputationContext public interface.
/// The class provides additional internal API for setting up the context.
///
class Hd_ExtComputationContextInternal final : public HdExtComputationContext {
public:
    Hd_ExtComputationContextInternal();
    virtual ~Hd_ExtComputationContextInternal();

    ///
    /// Obtains the value of an named input to the computation.
    ///
    /// The code will issue a coding error and return a empty value
    /// if the input is missing.
    ///
    virtual const VtValue &GetInputValue(const TfToken &name) const override;

    ///
    /// Obtains the value of an named input to the computation.
    ///
    /// If the input isn't present, nullptr will be returned.
    ///
    virtual const VtValue *GetOptionalInputValuePtr(
                                            const TfToken &name) const override;
    ///
    /// Sets the value of the specified output.
    ///
    virtual void SetOutputValue(const TfToken &name,
                                 const VtValue &output) override;


    /// Adds the named input to the execution environment.
    /// If the input already exists, the value is not replaced.
    void SetInputValue(const TfToken &name, const VtValue &input);

    /// Fetches the named output from the execution environment.
    /// returns false if the output is not present.
    bool GetOutputValue(const TfToken &name, VtValue *output) const;

    /// returns true is an error occur in processing, such that the
    /// outputs are invalid.
    bool HasComputationError();

    ///
    /// Called to indicate an error occurred while executing a computation
    /// so that it's output are invalid.
    ///
    virtual void RaiseComputationError() override;

private:
    typedef std::map<TfToken, VtValue> ValueMap;

    ValueMap m_inputs;
    ValueMap m_outputs;
    bool     m_compuationError;


    Hd_ExtComputationContextInternal(const Hd_ExtComputationContextInternal &)
                                                                       = delete;
    Hd_ExtComputationContextInternal &operator = (
                             const Hd_ExtComputationContextInternal &) = delete;

};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_EXT_COMPUTATION_CONTEXT_INTERNAL_H
