#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/domeLightComputations.h"
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
#ifndef FORGE_IMAGING_HD_PH_DOME_LIGHT_COMPUTATIONS_H
#define FORGE_IMAGING_HD_PH_DOME_LIGHT_COMPUTATIONS_H

#include "forge/forge.h"
#include "forge/imaging/hd/computation.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

/// Dome Light texture computations GPU
///
///
using HdPh_DomeLightComputationGPUSharedPtr = std::shared_ptr<class HdPh_DomeLightComputationGPU>;
using HdPhSimpleLightingShaderPtr = std::weak_ptr<class HdPhSimpleLightingShader>;

////
//// \class HdPh_DomeLightComputationGPU
///
/// Given an OpenGL texture at construction time, create a new OpenGL
/// texture (computed from the contents of the given texture) and sets
/// the GL name on the given lighting shader during Execute (also
/// freeing previous texture).
///
/// If the texture to be created has several mip levels, the texture
/// will only be created by the computation with level = 0 and the
/// computations with level > 0 will use the same texture.
///
class HdPh_DomeLightComputationGPU : public HdComputation {
 public:
  /// Constructor
  HDPH_API
  HdPh_DomeLightComputationGPU(
      // Name of computation shader to use, also used as
      // key when setting the GL name on the lighting shader
      const TfToken &shaderToken,
      // Lighting shader that remembers the GL texture names
      HdPhSimpleLightingShaderPtr const &lightingShader,
      // Number of mip levels.
      unsigned int numLevels = 1,
      // Level to be filled (0 means also to allocate texture)
      unsigned int level = 0,
      float roughness = -1.0);

  HDPH_API
  void GetBufferSpecs(HdBufferSpecVector *specs) const override
  {
  }

  HDPH_API
  void Execute(HdBufferArrayRangeSharedPtr const &range,
               HdResourceRegistry *resourceRegistry) override;

  /// This computation doesn't generate buffer source (i.e. 2nd phase)
  /// This is a gpu computation, but no need to resize the destination
  /// since it belongs the same range as src buffer.
  int GetNumOutputElements() const override
  {
    return 0;
  }

 private:
  const TfToken _shaderToken;
  HdPhSimpleLightingShaderPtr const _lightingShader;
  const unsigned int _numLevels;
  const unsigned int _level;
  const float _roughness;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DOME_LIGHT_COMPUTATIONS_H
