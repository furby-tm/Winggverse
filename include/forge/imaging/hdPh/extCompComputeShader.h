#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/extCompComputeShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_EXT_COMP_COMPUTE_SHADER_H
#define FORGE_IMAGING_HD_PH_EXT_COMP_COMPUTE_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPh_ExtCompComputeShaderSharedPtr = std::shared_ptr<class HdPh_ExtCompComputeShader>;

class HdExtComputation;

/// \class HdPh_ExtCompComputeShader
///
/// An internal representation of a compute shader in Phoenix that allows the
/// use of the code generation and resource binding system to generate a
/// shader program.
///
class HdPh_ExtCompComputeShader final : public HdPhShaderCode {
 public:
  HDPH_API
  HdPh_ExtCompComputeShader(HdExtComputation const *extComp);

  HDPH_API
  ~HdPh_ExtCompComputeShader() override;

  // ---------------------------------------------------------------------- //
  /// \name HdPhShaderCode (pure) virtual interface                         //
  // ---------------------------------------------------------------------- //

  HDPH_API
  std::string GetSource(TfToken const &shaderStageKey) const override;

  HDPH_API
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;

  HDPH_API
  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;

  HDPH_API
  void AddBindings(HdBindingRequestVector *customBindings) override;

  HDPH_API
  ID ComputeHash() const override;

  // ---------------------------------------------------------------------- //

  HDPH_API
  SdfPath const &GetExtComputationId() const;

 private:
  // No copying
  HdPh_ExtCompComputeShader(const HdPh_ExtCompComputeShader &) = delete;
  HdPh_ExtCompComputeShader &operator=(const HdPh_ExtCompComputeShader &) = delete;

  HdExtComputation const *const _extComp;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_EXT_COMP_COMPUTE_SHADER_H
