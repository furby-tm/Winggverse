#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureBinder.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_BINDER_H
#define FORGE_IMAGING_HD_PH_TEXTURE_BINDER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/shaderCode.h"

FORGE_NAMESPACE_BEGIN

using HdBufferSpecVector = std::vector<struct HdBufferSpec>;

/// \class HdPh_TextureBinder
///
/// A class helping HdPhShaderCode with binding textures.
///
/// This class helps binding GL texture names or populating the shader
/// bar with texture sampler handles if bindless textures are used. It
/// also includes writing texture metadata such as the sampling
/// transform to the shader bar.
///
class HdPh_TextureBinder {
 public:
  using NamedTextureHandle = HdPhShaderCode::NamedTextureHandle;
  using NamedTextureHandleVector = HdPhShaderCode::NamedTextureHandleVector;

  /// Add buffer specs necessary for the textures (e.g., for
  /// bindless texture sampler handles or sampling transform).
  ///
  /// Specify whether to use the texture by binding it or by
  /// using bindless handles with useBindlessHandles.
  ///
  static void GetBufferSpecs(const NamedTextureHandleVector &textures,
                             bool useBindlessHandles,
                             HdBufferSpecVector *specs);

  /// Compute buffer sources for shader bar.
  ///
  /// This works in conjunction with GetBufferSpecs, but unlike
  /// GetBufferSpecs is extracting information from the texture
  /// handles and thus can only be called after the textures have
  /// been committed in
  /// HdPhShaderCode::AddResourcesFromTextures().
  ///
  /// Specify whether to use the texture by binding it or by
  /// using bindless handles with useBindlessHandles.
  ///
  static void ComputeBufferSources(const NamedTextureHandleVector &textures,
                                   bool useBindlessHandles,
                                   HdBufferSourceSharedPtrVector *sources);

  /// Bind textures.
  ///
  /// Specify whether to use the texture by binding it or by
  /// using bindless handles with useBindlessHandles.
  ///
  static void BindResources(HdPh_ResourceBinder const &binder,
                            bool useBindlessHandles,
                            const NamedTextureHandleVector &textures);

  /// Unbind textures.
  ///
  /// Specify whether to use the texture by binding it or by
  /// using bindless handles with useBindlessHandles.
  ///
  static void UnbindResources(HdPh_ResourceBinder const &binder,
                              bool useBindlessHandles,
                              const NamedTextureHandleVector &textures);
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_TEXTURE_BINDER_H
