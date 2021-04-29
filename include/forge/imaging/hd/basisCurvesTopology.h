#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/basisCurvesTopology.h"
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
#ifndef FORGE_IMAGING_HD_BASIS_CURVES_TOPOLOGY_H
#define FORGE_IMAGING_HD_BASIS_CURVES_TOPOLOGY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/topology.h"
#include "forge/imaging/hd/tokens.h"

#include "forge/base/vt/array.h"
#include "forge/base/vt/value.h"

#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

/// \class HdBasisCurvesTopology
///
/// Topology data for basisCurves.
///
/// HdBasisCurvesTopology holds the raw input topology data for basisCurves
///
/// The Type, Basis and Wrap mode combined describe the curve and it's
/// segments.
///
/// If Type == linear, the curve is a bunch of line segments and basis is
/// ignored.
///
/// The wrap mode defines how the curve segments are specified:
///
///   If Wrap == segmented, this is equivalent to GL_LINES and curve vertex
///      counts is 2 * number of segments (multiple entries in curve vertex
///      array is optional).
///
///   If Wrap == nonperiodic, this is equivalent to GL_LINE_STRIP and curve
///     counts is an array where each entry is the number of vertices in that
///     line segment.  The first and last vertex in the segment are not joined.
///
///   If Wrap == periodic, this is equivalent to GL_LINE_LOOP  and curve counts
///     is an array where each entry is the number of vertices in that line
///     segment. An additional line is place between the first and last vertex
///     in each segment.
///
///  If Type == cubic, the type of curve is specified by basis:
///     The Basis can be bezier, bspline or catmullRom.
///
///     Wrap can be either periodic or nonperiodic (segmented is unsupported).
///
///  For each type of line, the generated vertex indices can pass through an
///  optional index buffer to map the generated indices to actual indices in
///  the vertex buffer.
///
class HdBasisCurvesTopology : public HdTopology {
public:

    HD_API
    HdBasisCurvesTopology();
    HD_API
    HdBasisCurvesTopology(const HdBasisCurvesTopology &src);

    HD_API
    HdBasisCurvesTopology(const TfToken &curveType,
                          const TfToken &curveBasis,
                          const TfToken &curveWrap,
                          const VtIntArray &curveVertexCounts,
                          const VtIntArray &curveIndices);
    HD_API
    virtual ~HdBasisCurvesTopology();

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
    void SetInvisibleCurves(VtIntArray const &invisibleCurves) {
        _invisibleCurves = invisibleCurves;
    }

    HD_API
    VtIntArray const & GetInvisibleCurves() const {
        return _invisibleCurves;
    }
    /// @}

    /// Returns segment vertex counts.
    VtIntArray const &GetCurveVertexCounts() const {
        return _curveVertexCounts;
    }

    /// Returns indices.
    VtIntArray const &GetCurveIndices() const {
        return _curveIndices;
    }

    /// Returns the number of curves
    size_t GetNumCurves() const {
        return _curveVertexCounts.size();
    }

    /// See class documentation for valid combination of values
    TfToken GetCurveType() const { return _curveType; }
    TfToken GetCurveBasis() const { return _curveBasis; }
    TfToken GetCurveWrap() const { return _curveWrap; }

    /// Does the topology use an index buffer
    bool HasIndices() const { return !_curveIndices.empty(); }

    /// Returns the hash value of this topology to be used for instancing.
    HD_API
    virtual ID ComputeHash() const;

    /// Equality check between two basisCurves topologies.
    HD_API
    bool operator==(HdBasisCurvesTopology const &other) const;
    HD_API
    bool operator!=(HdBasisCurvesTopology const &other) const;

    /// Figure out how many vertices / control points this topology references
    HD_API
    size_t CalculateNeededNumberOfControlPoints() const;

    /// Figure out how many control points with varying data this topology needs
    HD_API
    size_t CalculateNeededNumberOfVaryingControlPoints() const;

private:
    TfToken _curveType;
    TfToken _curveBasis;
    TfToken _curveWrap;
    VtIntArray _curveVertexCounts;
    VtIntArray _curveIndices;
    VtIntArray _invisiblePoints;
    VtIntArray _invisibleCurves;
};

HD_API
std::ostream& operator << (std::ostream &out, HdBasisCurvesTopology const &topo);


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_BASIS_CURVES_TOPOLOGY_H
