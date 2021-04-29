#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/basisCurvesShaderKey.h"
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
#ifndef FORGE_IMAGING_HD_PH_BASIS_CURVES_SHADER_KEY_H
#define FORGE_IMAGING_HD_PH_BASIS_CURVES_SHADER_KEY_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/geometricShader.h"
#include "forge/imaging/hdPh/shaderKey.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPh_BasisCurvesShaderKey
///
/// The draw styles are designed to strike a balance between matching offline
/// renderers like RenderMan and providing high interactive performance. At
/// the time of this writing, RenderMan (as of R22) only provides two curve
/// drawing modes: a round ray oriented half tube (HALFTUBE, ROUND) and a
/// flat primvar oriented ribbon (RIBBON, ORIENTED).
///
/// We allow all curves to be drawn as wires: for interactive guides which
/// may not have authored width and as a performance optimization.
///
/// We allow for the combination of (RIBBON, ROUND) as a cheaper code path
/// which fakes a round normal on a flat camera oriented ribbon as an
/// optimization for half tubes. To alleviate aliasing, for very thin curves,
/// we provide a HAIR mode.
///
/// Not all combinations of DrawStyle and NormalStyle are meaningful. For
/// example ORIENTED only makes sense with RIBBON. In the future, we hope to
/// eliminate NormalStyle, perhaps by merging the (RIBBON, ROUND) mode into a
/// more automatic HALFTUBE and by relying more on materials for HAIR.
struct HdPh_BasisCurvesShaderKey : public HdPh_ShaderKey {
  enum DrawStyle {
    POINTS,   // Draws only the control vertices.
    WIRE,     // Draws as lines or isolines, tessellated along length
    RIBBON,   // Draws as patch, tessellated along length only
    HALFTUBE  // Draws as patch, displaced into a half tube shape
  };

  enum NormalStyle {
    ORIENTED,  // Orient to user supplied normals
    HAIR,      // Generated camera oriented normal
    ROUND      // Generated camera oriented normal as a tube
  };

  HdPh_BasisCurvesShaderKey(TfToken const &type,
                            TfToken const &basis,
                            DrawStyle drawStyle,
                            NormalStyle normalStyle,
                            bool basisWidthInterpolation,
                            bool basisNormalInterpolation,
                            TfToken shadingTerminal,
                            bool hasAuthoredTopologicalVisibility);
  ~HdPh_BasisCurvesShaderKey();

  TfToken const &GetGlslfxFilename() const override
  {
    return glslfx;
  }
  TfToken const *GetVS() const override
  {
    return VS;
  }
  TfToken const *GetTCS() const override
  {
    return TCS;
  }
  TfToken const *GetTES() const override
  {
    return TES;
  }
  TfToken const *GetFS() const override
  {
    return FS;
  }

  HdPh_GeometricShader::PrimitiveType GetPrimitiveType() const override
  {
    return primType;
  }

  HdPh_GeometricShader::PrimitiveType primType;
  TfToken glslfx;
  TfToken VS[7];
  TfToken TCS[4];
  TfToken TES[9];
  TfToken FS[8];
};

FORGE_NAMESPACE_END

#endif  // HDPH_BASIS_CURVES_SHADER_KEY
