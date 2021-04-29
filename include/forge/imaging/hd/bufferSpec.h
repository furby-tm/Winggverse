#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/bufferSpec.h"
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
#ifndef FORGE_IMAGING_HD_BUFFER_SPEC_H
#define FORGE_IMAGING_HD_BUFFER_SPEC_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/types.h"
#include "forge/base/tf/stl.h"
#include "forge/base/tf/token.h"
#include <vector>

FORGE_NAMESPACE_BEGIN


typedef std::vector<struct HdBufferSpec> HdBufferSpecVector;

/// \class HdBufferSpec
///
/// Describes each named resource of buffer array.
/// This specifies the buffer's value type as HdTupleType,
/// which specifies the value type, number of components, and
/// number of array entries (which may be 1).
///
/// for example:
/// HdBufferSpecVector
///    0: name = points,  tupleType = {HdTypeFloatVec3, 1}
///    1: name = normals, tupleType = {HdTypeFloatVec3, 1}
///    2: name = colors,  tupleType = {HdTypeFloatVec3, 1}
///
struct HdBufferSpec final {
    /// Constructor.
    HdBufferSpec(TfToken const &name, HdTupleType tupleType) :
        name(name), tupleType(tupleType) {}

    /// Util function for adding buffer specs of sources into bufferspecs.
    template<typename T>
    static void GetBufferSpecs(T const &sources,
                               HdBufferSpecVector *bufferSpecs) {
        for (auto const &src : sources) {
            if (src->IsValid()) {
                src->GetBufferSpecs(bufferSpecs);
            }
        }
    }

    /// Returns true if \p subset is a subset of \p superset.
    /// An empty set is considered a valid subset of the superset.
    HD_API
    static bool IsSubset(HdBufferSpecVector const &subset,
                         HdBufferSpecVector const &superset);

    /// Returns union set of \p spec1 and \p spec2.
    /// Duplicated entries are uniquified.
    HD_API
    static HdBufferSpecVector ComputeUnion(HdBufferSpecVector const &spec1,
                                           HdBufferSpecVector const &spec2);

    /// Returns difference set of \p spec1 and \p spec2, i.e., entries in spec1
    /// that are not in spec2.
    HD_API
    static HdBufferSpecVector ComputeDifference(HdBufferSpecVector const &spec1,
                                           HdBufferSpecVector const &spec2);

    /// Debug output.
    HD_API
    static void Dump(HdBufferSpecVector const &specs);

    /// Return a size_t hash for this spec.
    HD_API
    size_t Hash() const;

    /// Functor to use for unorderd sets, maps.
    struct HashFunctor {
        size_t operator()(HdBufferSpec const& spec) const {
            return spec.Hash();
        }
    };

    /// Equality checks.
    bool operator == (HdBufferSpec const &other) const {
        return name == other.name && tupleType == other.tupleType;
    }
    bool operator != (HdBufferSpec const &other) const {
        return !(*this == other);
    }

    /// Ordering.
    bool operator < (HdBufferSpec const &other) const {
        return name < other.name || (name == other.name &&
            tupleType < other.tupleType);
    }

    TfToken name;
    HdTupleType tupleType;
};

// Support TfHash.
template <class HashState>
void
TfHashAppend(HashState &h, HdBufferSpec const &bs)
{
    h.Append(bs.name, bs.tupleType);
}

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_BUFFER_SPEC_H
