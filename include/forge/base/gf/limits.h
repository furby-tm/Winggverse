#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/limits.h"
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
#ifndef FORGE_BASE_GF_LIMITS_H
#define FORGE_BASE_GF_LIMITS_H

/// \file gf/limits.h
/// \ingroup group_gf_BasicMath
/// Defines useful mathematical limits.

/// This constant is used to determine whether the length of a vector is too
/// small to handle accurately.
/// \ingroup group_gf_BasicMath
#define GF_MIN_VECTOR_LENGTH  1e-10

/// This constant is used to determine when a set of basis vectors is close to
/// orthogonal.
/// \ingroup group_gf_LinearAlgebra
#define GF_MIN_ORTHO_TOLERANCE 1e-6

#endif
