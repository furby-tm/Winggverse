#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/vertexAdjacency.h"
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
#ifndef FORGE_IMAGING_HD_VERTEX_ADJACENCY_H
#define FORGE_IMAGING_HD_VERTEX_ADJACENCY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferArrayRange.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"

#include "forge/base/vt/array.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


using Hd_VertexAdjacencySharedPtr =
    std::shared_ptr<class Hd_VertexAdjacency>;
using Hd_AdjacencyBuilderComputationSharedPtr =
    std::shared_ptr<class Hd_AdjacencyBuilderComputation>;
using Hd_AdjacencyBuilderComputationPtr =
    std::weak_ptr<class Hd_AdjacencyBuilderComputation>;

class HdMeshTopology;

/// \class Hd_VertexAdjacency
///
/// Hd_VertexAdjacency encapsulates mesh adjacency information,
/// which is used for smooth normal computation.
///
/// The Adjacency table (built by the AdjacencyBuilder computation)
/// provides the index of the previous and next vertex for each face
/// that uses that vertex.
///
/// The table is split into two parts. The first part of the table
/// provides a offset to the prev/next data for the vertex as well as the
/// number of faces that use the vertex.  The second part of the table
/// provides the actual prev/next indices.
///
/// For example, The following prim has 4 vertices and 2 faces and uses
/// a CCW winding order:
///
///     3.---.2
///      |  /|
///      | / |
///      |/  |
///     0.---.1
///
/// Picking one vertex, 0, it is used by 2 faces, so it contains 2 previous/
/// next pairs: (2, 1) and (3, 2)
///
/// The full adjacency table for this prim would be:
///
///  0  1 |  2  3 |  4  5 |  6  7 || 8  9  10 11 | 12 13 | 14 15 16 17 | 18 19
///  8  2 | 12  1 | 14  2 | 18  1 || 2  1   3  2 |  0  2 |  1  0  0  3 |  2  0
///   Offset / Count pairs        ||            Prev / Next Pairs
///      per vertex               ||           Per Vertex, Per Face.
///
class Hd_VertexAdjacency final {
public:
    HD_API
    Hd_VertexAdjacency();

    HD_API
    ~Hd_VertexAdjacency();

    /// Updates the internal adjacency table using the supplied topology.
    /// Important! The adjacency table needs to be computed before smooth
    /// normals.
    HD_API
    bool BuildAdjacencyTable(HdMeshTopology const *topology);

    /// Returns a shared adjacency builder computation which will call
    /// BuildAdjacencyTable.  The shared computation is useful if multiple
    /// meshes share a topology and adjacency table, and only want to build the
    /// adjacency table once.
    HD_API
    HdBufferSourceSharedPtr GetSharedAdjacencyBuilderComputation(
        HdMeshTopology const *topology);

    /// Sets the buffer range used for adjacency table storage.
    void SetAdjacencyRange(HdBufferArrayRangeSharedPtr const &range) {
        _adjacencyRange = range;
    }

    /// Returns the buffer range used for adjacency table storage.
    HdBufferArrayRangeSharedPtr const &GetAdjacencyRange() const {
        return _adjacencyRange;
    }

    /// Returns the number of points in the adjacency table.
    int GetNumPoints() const {
        return _numPoints;
    }

    /// Returns the adjacency table.
    VtIntArray const &GetAdjacencyTable() const {
        return _adjacencyTable;
    }

private:
    int _numPoints;
    VtIntArray _adjacencyTable;

    // adjacency buffer range
    HdBufferArrayRangeSharedPtr _adjacencyRange;

    // weak ptr of adjacency builder used for dependent computations
    Hd_AdjacencyBuilderComputationPtr _sharedAdjacencyBuilder;
};

/// \class Hd_AdjacencyBuilderComputation
///
/// A null buffer source to compute the adjacency table.
/// Since this is a null buffer source, it won't actually produce buffer
/// output; but other computations can depend on this to ensure
/// BuildAdjacencyTable is called.
///
class Hd_AdjacencyBuilderComputation : public HdNullBufferSource {
public:
    HD_API
    Hd_AdjacencyBuilderComputation(Hd_VertexAdjacency *adjacency,
                                   HdMeshTopology const *topology);
    HD_API
    virtual bool Resolve() override;

protected:
    HD_API
    virtual bool _CheckValid() const override;

private:
    Hd_VertexAdjacency *_adjacency;
    HdMeshTopology const *_topology;
};

/// \class Hd_AdjacencyBufferSource
///
/// A buffer source that puts an already computed adjacency table into
/// a resource registry buffer. This computation should be dependent on an
/// Hd_AdjacencyBuilderComputation.
///
class Hd_AdjacencyBufferSource : public HdComputedBufferSource {
public:
    HD_API
    Hd_AdjacencyBufferSource(
        Hd_VertexAdjacency const *adjacency,
        HdBufferSourceSharedPtr const &adjacencyBuilder);

    // overrides
    HD_API
    virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
    HD_API
    virtual bool Resolve() override;

protected:
    HD_API
    virtual bool _CheckValid() const override;

private:
    Hd_VertexAdjacency const *_adjacency;
    HdBufferSourceSharedPtr const _adjacencyBuilder;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_VERTEX_ADJACENCY_H
