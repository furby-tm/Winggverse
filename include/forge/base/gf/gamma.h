#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/gamma.h"
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
#ifndef FORGE_BASE_GF_GAMMA_H
#define FORGE_BASE_GF_GAMMA_H

#include "forge/forge.h"
#include "forge/base/gf/api.h"

/// \file gf/gamma.h
/// Utilities to map colors between gamma spaces.

FORGE_NAMESPACE_BEGIN

class GfVec3f;
class GfVec3d;
class GfVec4f;
class GfVec4d;
class GfVec3h;
class GfVec4h;

/// Return a new vector with each component of \p v raised to the power \p
/// gamma
GF_API
GfVec3f GfApplyGamma(const GfVec3f &v, double gamma);

/// Return a new vector with each component of \p v raised to the power \p
/// gamma
GF_API
GfVec3d GfApplyGamma(const GfVec3d &v, double gamma);

/// \copydoc GfApplyGamma(GfVec3d,double)
GF_API
GfVec3h GfApplyGamma(const GfVec3h &v, double gamma);

/// Return a new vector with the first three components of \p v raised to the
/// power \p gamma and the fourth component unchanged.
GF_API
GfVec4f GfApplyGamma(const GfVec4f &v, double gamma);

/// Return a new vector with the first three components of \p v raised to the
/// power \p gamma and the fourth component unchanged.
GF_API
GfVec4d GfApplyGamma(const GfVec4d &v, double gamma);

/// \copydoc GfApplyGamma(GfVec4h,double)
GF_API
GfVec4h GfApplyGamma(const GfVec4h &v, double gamma);

/// Return a new float raised to the power \p gamma
GF_API
float GfApplyGamma(const float &v, double gamma);

/// Return a new char raised to the power \p gamma
GF_API
unsigned char GfApplyGamma(const unsigned char &v, double gamma);

/// Return the system display gamma
GF_API
double GfGetDisplayGamma();

/// Given a vec, \p v, representing an energy-linear RGB(A) color, return a
/// vec of the same type converted to the system's display gamma.
GF_API GfVec3f GfConvertLinearToDisplay(const GfVec3f &v);
GF_API GfVec3d GfConvertLinearToDisplay(const GfVec3d &v);
GF_API GfVec3h GfConvertLinearToDisplay(const GfVec3h &v);
GF_API GfVec4f GfConvertLinearToDisplay(const GfVec4f &v);
GF_API GfVec4d GfConvertLinearToDisplay(const GfVec4d &v);
GF_API GfVec4h GfConvertLinearToDisplay(const GfVec4h &v);
GF_API float GfConvertLinearToDisplay(const float &v);
GF_API unsigned char GfConvertLinearToDisplay(const unsigned char &v);

/// Given a vec, \p v, representing an RGB(A) color in the system's display
/// gamma space, return an energy-linear vec of the same type.
GF_API GfVec3f GfConvertDisplayToLinear(const GfVec3f &v);
GF_API GfVec3d GfConvertDisplayToLinear(const GfVec3d &v);
GF_API GfVec3h GfConvertDisplayToLinear(const GfVec3h &v);
GF_API GfVec4f GfConvertDisplayToLinear(const GfVec4f &v);
GF_API GfVec4d GfConvertDisplayToLinear(const GfVec4d &v);
GF_API GfVec4h GfConvertDisplayToLinear(const GfVec4h &v);
GF_API float GfConvertDisplayToLinear(const float &v);
GF_API unsigned char GfConvertDisplayToLinear(const unsigned char &v);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_GF_GAMMA_H
