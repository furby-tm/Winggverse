#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/geomSubset.h"
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
#ifndef FORGE_IMAGING_HD_GEOM_SUBSET_H
#define FORGE_IMAGING_HD_GEOM_SUBSET_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/vt/array.h"
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class HdGeomSubset
///
/// Describes a subset of a piece of geometry as a set of indices.
///
struct HdGeomSubset {
    enum Type {
        /// A subset of faces
        TypeFaceSet,

        // For now, there is only one type, but this may grow in the future
        // to accomodate edges, points, etc.
    };

    /// The type of elements this geometry subset includes.
    Type type;
    /// The path used to identify this subset in the scene.
    SdfPath id;
    /// The path used to identify this material bound to the subset.
    SdfPath materialId;
    /// The list of element indices contained in the subset.
    VtIntArray indices;
};

/// A group of geometry subsets.
typedef std::vector<HdGeomSubset> HdGeomSubsets;

HD_API
bool operator==(const HdGeomSubset& lhs, const HdGeomSubset& rhs);

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_GEOM_SUBSET_H
