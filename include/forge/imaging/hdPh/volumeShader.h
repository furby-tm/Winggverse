#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/volumeShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_VOLUME_SHADER_H
#define FORGE_IMAGING_HD_PH_VOLUME_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/surfaceShader.h"

FORGE_NAMESPACE_BEGIN

class HdRenderDelegate;

using HdPh_VolumeShaderSharedPtr = std::shared_ptr<class HdPh_VolumeShader>;
using HdPh_MaterialParamVector = std::vector<class HdPh_MaterialParam>;
using HdVolumeFieldDescriptorVector = std::vector<struct HdVolumeFieldDescriptor>;

/// \class HdPh_VolumeShader
///
/// Adds the following behaviors to HdPhSurfaceShader:
/// - walk through field descriptors to allocate textures and update
///   the NamedTextureHandle's.
/// - compute volume bounding box, adds it to the shader bar and
///   computes points for the points bar (if requested)
/// - bind raymarching step sizes (querried from render delegate)
///   to uniforms in the shader
///
class HdPh_VolumeShader final : public HdPhSurfaceShader {
 public:
  explicit HdPh_VolumeShader(HdRenderDelegate *const renderDelegate);
  ~HdPh_VolumeShader() override;

  /// Adds custom bindings for step sizes so that codegen will make them
  /// available as HdGet_stepSize and HdGet_stepSizeLighting.
  ///
  void AddBindings(HdBindingRequestVector *customBindings) override;

  /// Querries render delegate for step sizes and binds the uniforms and
  /// calls base class's method.
  ///
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;

  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;

  /// Adds buffer sources to the shader bar (for volume bounding
  /// box) and points bar if requested (besides calling
  /// HdPh_TextureBinder::ComputeBufferSources).
  ///
  void AddResourcesFromTextures(ResourceContext &ctx) const override;

  /// Whether the volume shader is responsible for filling buffer
  /// sources from the volume bounding box computation.
  ///
  void SetPointsBar(HdBufferArrayRangeSharedPtr const &pointsBar);

  /// Set whether this shader is responsible for filling the points bar.
  ///
  /// If there are fields, it is the volume shader's responsibility
  /// to compute the volume bounding box after the field textures
  /// are committed. Otherwise, volume prim is falling back to the
  /// authored extents and uses them to create the corresponding
  /// buffer sources.
  ///
  void SetFillsPointsBar(bool fillsPointsBar);

  /// Check whether this shader is responsible for filling the points bar.
  ///
  bool GetFillsPointsBar() const
  {
    return _fillsPointsBar;
  }

  /// Set information to identify the field prims specifying what
  /// textures to load.
  ///
  /// Must line up with the NamedTextureHandle's passed to
  /// SetNamedTextureHandles.
  ///
  void SetFieldDescriptors(const HdVolumeFieldDescriptorVector &fieldDescs);

  /// Using the above field descriptors, (re-)allocate texture handles
  /// for the associated textures to update the NamedTextureHandle's.
  ///
  void UpdateTextureHandles(HdSceneDelegate *);

  /// Add params and specs to communicate volume bounding box and sample
  /// distance to shader.
  ///
  static void GetParamsAndBufferSpecsForBBoxAndSampleDistance(HdPh_MaterialParamVector *params,
                                                              HdBufferSpecVector *specs);

  /// Add buffer sources to communicate volume bounding box and sample
  /// distance to shader.
  ///
  static void GetBufferSourcesForBBoxAndSampleDistance(
      const std::pair<GfBBox3d, float> &bboxAndSampleDistance,
      HdBufferSourceSharedPtrVector *sources);

  /// GfRange3d encodes empty range by (infinity, -infinity).
  /// Avoid those insane values by returning (0,0).
  ///
  static GfVec3d GetSafeMin(const GfRange3d &range);

  /// GfRange3d encodes empty range by (infinity, -infinity).
  /// Avoid those insane values by returning (0,0).
  ///
  static GfVec3d GetSafeMax(const GfRange3d &range);

 private:
  HdRenderDelegate *const _renderDelegate;
  int _lastRenderSettingsVersion;
  float _stepSize;
  float _stepSizeLighting;

  HdBufferArrayRangeSharedPtr _pointsBar;
  bool _fillsPointsBar;

  HdVolumeFieldDescriptorVector _fieldDescriptors;
};

FORGE_NAMESPACE_END

#endif
