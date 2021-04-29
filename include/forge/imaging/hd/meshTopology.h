#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/meshTopology.h"
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
#ifndef FORGE_IMAGING_HD_MESH_TOPOLOGY_H
#define FORGE_IMAGING_HD_MESH_TOPOLOGY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/geomSubset.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/topology.h"

#include "forge/imaging/pxOsd/meshTopology.h"

#include "forge/base/vt/array.h"
#include "forge/base/vt/value.h"

#include "forge/base/tf/token.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


using HdMeshTopologySharedPtr = std::shared_ptr<class HdMeshTopology>;

/// \class HdMeshTopology
///
/// Topology data for meshes.
///
/// HdMeshTopology holds the raw input topology data for a mesh and is capable
/// of computing derivative topological data (such as indices or subdivision
/// stencil tables and patch tables).
///
class HdMeshTopology : public HdTopology {
public:
    HD_API
    HdMeshTopology();
    HD_API
    HdMeshTopology(const HdMeshTopology &, int refineLevel=0);
    HD_API
    HdMeshTopology(const PxOsdMeshTopology &, int refineLevel=0);
    HD_API
    HdMeshTopology(const TfToken    &scheme,
                   const TfToken    &orientation,
                   const VtIntArray &faceVertexCounts,
                   const VtIntArray &faceVertexIndices,
                   int refineLevel = 0);
    HD_API
    HdMeshTopology(const TfToken &scheme,
                   const TfToken &orientation,
                   const VtIntArray &faceVertexCounts,
                   const VtIntArray &faceVertexIndices,
                   const VtIntArray &holeIndices,
                   int refineLevel = 0);
    HD_API
    virtual ~HdMeshTopology();

    HD_API
    HdMeshTopology &operator =(const HdMeshTopology &copy);

    /// Returns whether adaptive subdivision is enabled or not.
    HD_API
    static bool IsEnabledAdaptive();

    PxOsdMeshTopology const & GetPxOsdMeshTopology() const {
        return _topology;
    }

    /// Returns the num faces
    HD_API
    int GetNumFaces() const;

    /// Returns the num facevarying primvars
    HD_API
    int GetNumFaceVaryings() const;

    /// Returns the num points of the topology vert indices array
    HD_API
    int GetNumPoints() const;

    /// Returns the num points by looking vert indices array
    HD_API
    static int ComputeNumPoints(VtIntArray const &verts);

    /// Returns the subdivision scheme
    TfToken const GetScheme() const {
        return _topology.GetScheme();
    }

    /// Returns the refinement level
    int GetRefineLevel() const {
        return _refineLevel;
    }

    /// Returns face vertex counts.
    VtIntArray const &GetFaceVertexCounts() const {
        return _topology.GetFaceVertexCounts();
    }

    /// Returns face vertex indics.
    VtIntArray const &GetFaceVertexIndices() const {
        return _topology.GetFaceVertexIndices();
    }

    /// Returns orientation.
    TfToken const &GetOrientation() const {
        return _topology.GetOrientation();
    }

    /// Returns the hash value of this topology to be used for instancing.
    HD_API
    virtual ID ComputeHash() const;

    /// Equality check between two mesh topologies.
    HD_API
    bool operator==(HdMeshTopology const &other) const;

    ///
    /// \name Hole
    /// @{

    /// Sets hole face indices. faceIndices needs to be sorted in
    /// ascending order.
    void SetHoleIndices(VtIntArray const &holeIndices) {
        _topology = _topology.WithHoleIndices(holeIndices);
    }

    /// Returns the hole face indices.
    VtIntArray const &GetHoleIndices() const {
        return _topology.GetHoleIndices();
    }

    /// @}

    ///
    /// \name Subdivision
    /// @{

    /// Sets subdivision tags.
    void SetSubdivTags(PxOsdSubdivTags const &subdivTags) {
        _topology = _topology.WithSubdivTags(subdivTags);
    }

    /// Returns subdivision tags
    PxOsdSubdivTags const&GetSubdivTags() const {
        return _topology.GetSubdivTags();
    }

    /// @}

    ///
    /// \name Geometry subsets
    /// @{

    /// Sets geometry subsets
    HD_API
    void SetGeomSubsets(HdGeomSubsets const &geomSubsets) {
        _geomSubsets = geomSubsets;
    }

    /// Returns geometry subsets
    HD_API
    HdGeomSubsets const &GetGeomSubsets() const {
        return _geomSubsets;
    }

    /// @}

    ///
    /// \name Topological invisibility
    /// @{
    ///
    HD_API
    void SetInvisiblePoints(VtIntArray const &invisiblePoints) {
        _invisiblePoints = invisiblePoints;
    }

    HD_API
    VtIntArray const & GetInvisiblePoints() const {
        return _invisiblePoints;
    }

    HD_API
    void SetInvisibleFaces(VtIntArray const &invisibleFaces) {
        _invisibleFaces = invisibleFaces;
    }

    HD_API
    VtIntArray const & GetInvisibleFaces() const {
        return _invisibleFaces;
    }
    /// @}

protected:
    PxOsdMeshTopology _topology;
    HdGeomSubsets _geomSubsets;
    VtIntArray _invisiblePoints;
    VtIntArray _invisibleFaces;
    int _refineLevel;
    int _numPoints;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_MESH_TOPOLOGY_H
