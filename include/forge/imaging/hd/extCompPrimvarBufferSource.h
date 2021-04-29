#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/extCompPrimvarBufferSource.h"
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
#ifndef FORGE_IMAGING_HD_EXT_COMP_PRIMVAR_BUFFER_SOURCE_H
#define FORGE_IMAGING_HD_EXT_COMP_PRIMVAR_BUFFER_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/types.h"
#include "forge/base/tf/token.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdExtCompCpuComputation;

using HdExtCompCpuComputationSharedPtr =
    std::shared_ptr<HdExtCompCpuComputation>;

/// Hd Buffer Source that binds a primvar to a Ext Computation output.
/// This buffer source is compatible with being bound to a Bar.
class HdExtCompPrimvarBufferSource final : public HdBufferSource {
public:

    /// Constructs a new primvar buffer source called primvarName and
    /// binds it to the output called sourceOutputName from the
    /// computation identified by source.
    ///
    /// Default value provides type information for the primvar and may
    /// be used in the event of an error.
    HD_API
    HdExtCompPrimvarBufferSource(const TfToken &primvarName,
                                 const HdExtCompCpuComputationSharedPtr &source,
                                 const TfToken &sourceOutputName,
                                 const HdTupleType &valueType);

    HD_API
    virtual ~HdExtCompPrimvarBufferSource() = default;

    /// Returns the name of the primvar.
    HD_API
    virtual TfToken const &GetName() const override;

    /// Adds this Primvar's buffer description to the buffer spec vector.
    HD_API
    virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;

    /// Computes and returns a hash value for the underlying data.
    HD_API
    virtual size_t ComputeHash() const override;

    /// Extracts the primvar from the source computation.
    HD_API
    virtual bool Resolve() override;

    /// Returns a raw pointer to the primvar data.
    HD_API
    virtual void const *GetData() const override;

    /// Returns the tuple data format of the primvar data.
    HD_API
    virtual HdTupleType GetTupleType() const override;

    /// Returns a count of the number of elements.
    HD_API
    virtual size_t GetNumElements() const override;

protected:
    /// Returns true if the binding to the source computation was successful.
    HD_API
    virtual bool _CheckValid() const override;

private:
    // TfHash support.
    template <class HashState>
    friend void TfHashAppend(HashState &h,
                             HdExtCompPrimvarBufferSource const &);

    TfToken                          _primvarName;
    HdExtCompCpuComputationSharedPtr _source;
    size_t                           _sourceOutputIdx;
    HdTupleType                      _tupleType;
    void const                      *_rawDataPtr;

    HdExtCompPrimvarBufferSource()                                     = delete;
    HdExtCompPrimvarBufferSource(const HdExtCompPrimvarBufferSource &)
                                                                       = delete;
    HdExtCompPrimvarBufferSource &operator = (
                                           const HdExtCompPrimvarBufferSource &)
                                                                       = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_EXT_COMP_PRIMVAR_BUFFER_SOURCE_H
