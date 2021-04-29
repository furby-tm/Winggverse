#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/smoothNormals.h"
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
#ifndef FORGE_IMAGING_HD_SMOOTH_NORMALS_H
#define FORGE_IMAGING_HD_SMOOTH_NORMALS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hd/types.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN


class Hd_VertexAdjacency;

/// \class Hd_SmoothNormals
///
/// Hd_SmoothNormals encapsulates mesh smooth normals information.
/// It uses passed-in adjacency information and points data to compute
/// smooth per-vertex normals.  It does this by averaging face normals of
/// faces surrounding a vertex.
///
class Hd_SmoothNormals final {
public:
    /// Computes the smooth normals result using the supplied adjacency
    /// information and points data. Returns an array of the same size and
    /// type as the source points, with optional packing.
    HD_API
    static VtArray<GfVec3f> ComputeSmoothNormals(
                                          Hd_VertexAdjacency const * adjacency,
                                          int numPoints,
                                          GfVec3f const * pointsPtr);
    HD_API
    static VtArray<GfVec3d> ComputeSmoothNormals(
                                          Hd_VertexAdjacency const * adjacency,
                                          int numPoints,
                                          GfVec3d const * pointsPtr);
    HD_API
    static VtArray<HdVec4f_2_10_10_10_REV> ComputeSmoothNormalsPacked(
                                          Hd_VertexAdjacency const * adjacency,
                                          int numPoints,
                                          GfVec3f const * pointsPtr);
    HD_API
    static VtArray<HdVec4f_2_10_10_10_REV> ComputeSmoothNormalsPacked(
                                          Hd_VertexAdjacency const * adjacency,
                                          int numPoints,
                                          GfVec3d const * pointsPtr);

private:
    Hd_SmoothNormals() = delete;
    ~Hd_SmoothNormals() = delete;
};

/// \class Hd_SmoothNormalsComputation
///
/// Smooth normal computation CPU.
///
class Hd_SmoothNormalsComputation : public HdComputedBufferSource {
public:
    HD_API
    Hd_SmoothNormalsComputation(Hd_VertexAdjacency const *adjacency,
                                HdBufferSourceSharedPtr const &points,
                                TfToken const &dstName,
                                HdBufferSourceSharedPtr const &adjacencyBuilder,
                                bool packed);

    /// overrides
    HD_API
    virtual void GetBufferSpecs(HdBufferSpecVector *specs) const override;
    HD_API
    virtual bool Resolve() override;
    HD_API
    virtual TfToken const &GetName() const override;

protected:
    HD_API
    virtual bool _CheckValid() const override;

private:
    Hd_VertexAdjacency const *_adjacency;
    HdBufferSourceSharedPtr _points;
    TfToken _dstName;
    HdBufferSourceSharedPtr _adjacencyBuilder;
    bool _packed;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_SMOOTH_NORMALS_H
