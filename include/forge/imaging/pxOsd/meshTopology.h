#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/pxOsd/meshTopology.h"
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
#ifndef FORGE_IMAGING_PX_OSD_MESH_TOPOLOGY_H
#define FORGE_IMAGING_PX_OSD_MESH_TOPOLOGY_H

/// \file pxOsd/meshTopology.h

#include "forge/forge.h"
#include "forge/imaging/pxOsd/api.h"
#include "forge/imaging/pxOsd/subdivTags.h"
#include "forge/imaging/pxOsd/meshTopologyValidation.h"

#include "forge/base/vt/array.h"
#include "forge/base/vt/value.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

/// \class PxOsdMeshTopology
///
/// Topology data for meshes.
///
/// Once constructed, this class is immutable (except when assigned
/// or moved).
///
/// To make changing certain properties easier, several methods are
/// provided. WithScheme, WithHoleIndices, and WithSubdivTags will
/// return copies of the object with certain specific properites changed.
///
/// \code{.cpp}
/// PxOsdMeshTopology otherTopology =
///     originalTopology.WithScheme(PxOsdOpenSubdivTokens->catmullClark);
/// TF_VERIFY(otherTopology.GetScheme() ==
///           PxOsdOpenSubdivTokens->catmullClark);
/// TF_VERIFY(otherTopology.GetOrientation() ==
///           originalTopology.GetOrientation());
/// TF_VERIFY(otherTopology.GetSubdivTags() ==
///           originalTopology.GetSubdivTags());
/// TF_VERIFY(otherTopology.GetFaceVertexCounts() ==
///           originalTopology.GetFaceVertexCounts());
/// TF_VERIFY(otherTopology.GetFaceVertexIndices() ==
///           originalTopology.GetFaceVertexIndices());
/// \endcode
///
/// The cost of copying should be mitigated by the copy semantics of VtArray and
/// TfToken.
class PxOsdMeshTopology {

public:

    typedef uint64_t ID;

    PXOSD_API
    PxOsdMeshTopology();

    PxOsdMeshTopology& operator=(const PxOsdMeshTopology &) = default;
    PxOsdMeshTopology(const PxOsdMeshTopology &) = default;
    PxOsdMeshTopology(PxOsdMeshTopology&&) = default;
    PxOsdMeshTopology& operator=(PxOsdMeshTopology&&) = default;
    ~PxOsdMeshTopology() = default;

    /// Construct a topology without holes or subdiv tags
    PXOSD_API
    PxOsdMeshTopology(
        TfToken const& scheme,
        TfToken const& orientation,
        VtIntArray const& faceVertexCounts,
        VtIntArray const& faceVertexIndices);

    /// Construct a topology with holes
    PXOSD_API
    PxOsdMeshTopology(
        TfToken const& scheme,
        TfToken const& orientation,
        VtIntArray const& faceVertexCounts,
        VtIntArray const& faceVertexIndices,
        VtIntArray const& holeIndices);

    /// Construct a topology with holes and subdiv tags
    PXOSD_API
    PxOsdMeshTopology(
        TfToken const& scheme,
        TfToken const& orientation,
        VtIntArray const& faceVertexCounts,
        VtIntArray const& faceVertexIndices,
        VtIntArray const& holeIndices,
        PxOsdSubdivTags const& subdivTags);

    /// Construct a topology with subdiv tags
    PXOSD_API
    PxOsdMeshTopology(
        TfToken const& scheme,
        TfToken const& orientation,
        VtIntArray const& faceVertexCounts,
        VtIntArray const& faceVertexIndices,
        PxOsdSubdivTags const& subdivTags);

public:

    /// Returns the subdivision scheme
    TfToken const GetScheme() const {
        return _scheme;
    }

    /// Returns face vertex counts.
    VtIntArray const &GetFaceVertexCounts() const {
        return _faceVertexCounts;
    }

    /// Returns face vertex indices.
    VtIntArray const &GetFaceVertexIndices() const {
        return _faceVertexIndices;
    }

    /// Returns orientation.
    TfToken const &GetOrientation() const {
        return _orientation;
    }


    ///
    /// \name Holes
    /// @{
    /// Returns the hole face indices.
    VtIntArray const &GetHoleIndices() const {
        return _holeIndices;
    }

    /// @}

    ///
    /// \name Tags
    /// @{

    /// Returns subdivision tags
    PxOsdSubdivTags const & GetSubdivTags() const {
        return _subdivTags;
    }

    /// @}

    /// Return a copy of the topology, changing only the scheme.
    /// Valid values include: catmullClark, loop, bilinear.
    ///
    /// Note that the token "catmark" is also supported for backward
    /// compatibility, but has been deprecated.
    PXOSD_API PxOsdMeshTopology WithScheme(TfToken const& scheme) const {
        return PxOsdMeshTopology(scheme, GetOrientation(),
                                 GetFaceVertexCounts(), GetFaceVertexIndices(),
                                 GetHoleIndices(), GetSubdivTags());
    }

    /// Return a copy of the topology, changing only the subdiv tags.
    PXOSD_API PxOsdMeshTopology WithSubdivTags(PxOsdSubdivTags const& tags) const {
        return PxOsdMeshTopology(GetScheme(), GetOrientation(),
                                 GetFaceVertexCounts(), GetFaceVertexIndices(),
                                 GetHoleIndices(), tags);
    }

    /// Return a copy of the topology, changing only the hole indices.
    PXOSD_API PxOsdMeshTopology WithHoleIndices(VtIntArray const& holeIndices) const {
        return PxOsdMeshTopology(GetScheme(), GetOrientation(),
                                 GetFaceVertexCounts(), GetFaceVertexIndices(),
                                 holeIndices, GetSubdivTags());
    }
public:

    /// Returns the hash value of this topology to be used for instancing.
    PXOSD_API
    ID ComputeHash() const;

    /// Equality check between two mesh topologies.
    PXOSD_API
    bool operator==(PxOsdMeshTopology const &other) const;

    /// Returns a validation object which is empty if the topology is valid
    ///
    /// \code{.cpp}
    /// // Validation with minimal reporting
    /// if (!topology.Validate()) TF_CODING_ERROR("Invalid topology.");
    /// \endcode
    ///
    /// \code{.cpp}
    /// {
    ///    PxOsdMeshTopologyValidation validation = topology.Validate();
    ///    if (!validation){
    ///        for (auto const& elem: validation){
    ///             TF_WARN(elem.message);
    ///        }
    ///    }
    /// }
    /// \endcode
    ///
    /// \note Internally caches the result of the validation if the topology is
    /// valid
    PXOSD_API
    PxOsdMeshTopologyValidation Validate() const;

private:

    // note: if you're going to add more members, make sure
    // ComputeHash will be updated too.

    TfToken _scheme,
            _orientation;

    VtIntArray _faceVertexCounts;
    VtIntArray _faceVertexIndices;
    VtIntArray _holeIndices;

    PxOsdSubdivTags _subdivTags;

    struct _Validated {
        std::atomic<bool> value;

        _Validated() : value(false) {}
        _Validated(const _Validated& other) : value(other.value.load()) {}
        _Validated(_Validated&& other) : value(other.value.load()) {
            other.value = false;
        }
        _Validated& operator=(const _Validated& other) {
            value.store(other.value.load());
            return *this;
        }
        _Validated& operator=(_Validated&& other) {
            value.store(other.value.load());
            other.value = false;
            return *this;
        }
    };

    // This should NOT be included in the hash
    // This evaluates to true if the topology has been successfully
    // pre-validated. If this is false, the topology is either invalid
    // or it hasn't been validated yet.
    mutable _Validated _validated;
};

PXOSD_API
std::ostream& operator << (std::ostream &out, PxOsdMeshTopology const &);
PXOSD_API
bool operator!=(const PxOsdMeshTopology& lhs, const PxOsdMeshTopology& rhs);


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PX_OSD_MESH_TOPOLOGY_H
