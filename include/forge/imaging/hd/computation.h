#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/computation.h"
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
#ifndef FORGE_IMAGING_HD_COMPUTATION_H
#define FORGE_IMAGING_HD_COMPUTATION_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/perfLog.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN


using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

using HdComputationSharedPtr = std::shared_ptr<class HdComputation>;
using HdComputationSharedPtrVector = std::vector<HdComputationSharedPtr>;

/// \class HdComputation
///
/// An interface class for GPU computation.
///
/// GPU computation fills the result into range, which has to be allocated
/// using buffer specs determined by GetBufferSpecs, and registered as a pair
/// of computation and range.
///
class HdComputation
{
public:
    HD_API
    virtual ~HdComputation();

    /// Execute computation.
    virtual void Execute(
        HdBufferArrayRangeSharedPtr const &range,
        HdResourceRegistry *resourceRegistry) = 0;

    /// Returns the size of its destination buffer (located by range argument
    /// of Execute()). This function will be called after all HdBufferSources
    /// have been resolved and commited, so it can use the result of those
    /// buffer source results.
    /// Returning 0 means it doesn't need to resize.
    virtual int GetNumOutputElements() const = 0;

    /// Add the buffer spec for this computation into given bufferspec vector.
    /// Caller has to allocate the destination buffer with respect to the
    /// BufferSpecs, and passes the range when registering the computation.
    virtual void GetBufferSpecs(HdBufferSpecVector *specs) const = 0;

    /// This function is needed as HdComputation shares a templatized interface
    /// with HdBufferSource.
    ///
    /// It is a check to see if the GetBufferSpecs would produce a valid result.
    bool IsValid() { return true; }
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_COMPUTATION_H
