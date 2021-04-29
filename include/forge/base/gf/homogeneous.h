#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/homogeneous.h"
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
#ifndef FORGE_BASE_GF_HOMOGENEOUS_H
#define FORGE_BASE_GF_HOMOGENEOUS_H

/// \file gf/homogeneous.h
/// \ingroup group_gf_LinearAlgebra
/// Utility functions for GfVec4f and GfVec4d as homogeneous vectors

#include "forge/forge.h"
#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/vec4f.h"
#include "forge/base/gf/api.h"

FORGE_NAMESPACE_BEGIN

/// Returns a vector which is \p v homogenized.  If the fourth element of \p v
/// is 0, it is set to 1.
/// \ingroup group_gf_LinearAlgebra
GF_API
GfVec4f GfGetHomogenized(const GfVec4f &v);

/// Homogenizes \p a and \p b and then performs the cross product on the first
/// three elements of each.  Returns the cross product as a homogenized
/// vector.
/// \ingroup group_gf_LinearAlgebra
GF_API
GfVec4f GfHomogeneousCross(const GfVec4f &a, const GfVec4f &b);

GF_API
GfVec4d GfGetHomogenized(const GfVec4d &v);

/// Homogenizes \p a and \p b and then performs the cross product on the first
/// three elements of each.  Returns the cross product as a homogenized
/// vector.
/// \ingroup group_gf_LinearAlgebra
GF_API
GfVec4d GfHomogeneousCross(const GfVec4d &a, const GfVec4d &b);

/// Projects homogeneous \p v into Euclidean space and returns the result as a
/// Vec3f.
inline GfVec3f GfProject(const GfVec4f &v) {
    float inv = (v[3] != 0.0f) ? 1.0f/v[3] : 1.0f;
    return GfVec3f(inv * v[0], inv * v[1], inv * v[2]);
}

/// Projects homogeneous \p v into Euclidean space and returns the result as a
/// Vec3d.
inline GfVec3d GfProject(const GfVec4d &v) {
    double inv = (v[3] != 0.0) ? 1.0/v[3] : 1.0;
    return GfVec3d(inv * v[0], inv * v[1], inv * v[2]);
}

FORGE_NAMESPACE_END

#endif /* FORGE_BASE_GF_HOMOGENEOUS_H */
