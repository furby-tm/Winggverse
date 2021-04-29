#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/flatNormals.h"
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
#ifndef FORGE_IMAGING_HD_FLAT_NORMALS_H
#define FORGE_IMAGING_HD_FLAT_NORMALS_H

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

class HdMeshTopology;

/// \class Hd_FlatNormals
///
/// Hd_FlatNormals encapsulates mesh flat normals information.
/// It uses passed-in face index data and points data to compute
/// flat per-face normals.  It does this by breaking each face into
/// a triangle fan centered at vertex 0, and averaging triangle normals.
///
class Hd_FlatNormals final {
public:
    /// Computes the flat normals result using the supplied face coord
    /// information and points data. Returns an array of the same size and
    /// type as the source points, with optional packing.
    HD_API
    static VtArray<GfVec3f> ComputeFlatNormals(
                                        HdMeshTopology const * topology,
                                        GfVec3f const * pointsPtr);
    HD_API
    static VtArray<GfVec3d> ComputeFlatNormals(
                                        HdMeshTopology const * topology,
                                        GfVec3d const * pointsPtr);
    HD_API
    static VtArray<HdVec4f_2_10_10_10_REV> ComputeFlatNormalsPacked(
                                        HdMeshTopology const * topology,
                                        GfVec3f const * pointsPtr);
    HD_API
    static VtArray<HdVec4f_2_10_10_10_REV> ComputeFlatNormalsPacked(
                                        HdMeshTopology const * topology,
                                        GfVec3d const * pointsPtr);

private:
    Hd_FlatNormals() = delete;
    ~Hd_FlatNormals() = delete;
};

/// \class Hd_FlatNormalsComputation
///
/// Flat normal computation CPU.
///
class Hd_FlatNormalsComputation : public HdComputedBufferSource {
public:
    HD_API
    Hd_FlatNormalsComputation(HdMeshTopology const *topology,
                              HdBufferSourceSharedPtr const &points,
                              TfToken const &dstName,
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
    HdMeshTopology const *_topology;
    HdBufferSourceSharedPtr const _points;
    TfToken _dstName;
    bool _packed;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_FLAT_NORMALS_H
