#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/dynamicUvTextureObject.h"
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
#ifndef FORGE_IMAGING_HD_PH_DYNAMIC_UV_TEXTURE_OBJECT_H
#define FORGE_IMAGING_HD_PH_DYNAMIC_UV_TEXTURE_OBJECT_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/textureObject.h"

FORGE_NAMESPACE_BEGIN

class HdPhDynamicUvTextureImplementation;

/// \class HdPhDynamicUvTextureObject
///
/// A uv texture that is managed but not populated by the Phoenix texture system.
///
/// Clients can allocate an instance of this class through
/// HdPhResourceRegistry::AllocateTextureHandle or AllocateTextureObject
/// by passing an HdPhTextureIdentifier with a
/// HdPhDynamicUvSubtextureIdentifier.
///
/// The client can allocate the GPU resource with CreateTexture and populate it
/// by either giving data in the HgiTextureDesc or binding the texture as target
/// for a computation or render.
///
/// Bindless texture sampler handles can only be created correctly if
/// a client has created the texture before the texture commit phase
/// is finished.
///
class HdPhDynamicUvTextureObject final : public HdPhUvTextureObject {
 public:
  HDPH_API
  HdPhDynamicUvTextureObject(const HdPhTextureIdentifier &textureId,
                             HdPh_TextureObjectRegistry *textureObjectRegistry);

  HDPH_API
  ~HdPhDynamicUvTextureObject() override;

  /// Allocate GPU resource using the texture descriptor. Populate
  /// if data are given in the descriptor.
  ///
  void CreateTexture(const HgiTextureDesc &desc)
  {
    _CreateTexture(desc);
  }

  /// Make GPU generate mipmaps.
  ///
  void GenerateMipmaps()
  {
    _GenerateMipmaps();
  }

  /// Release GPU resource.
  void DestroyTexture()
  {
    _DestroyTexture();
  }

  /// Set wrap mode hints used when a texture node's wrap mode
  /// is use metadata.
  ///
  /// This is typically called from HdPhDynamicUvTextureImplementation::Load
  /// when the texture file has wrap mode hints.
  void SetWrapParameters(const std::pair<HdWrap, HdWrap> &wrapParameters)
  {
    _SetWrapParameters(wrapParameters);
  }

  /// Save CPU data for this texture (transfering ownership).
  ///
  /// This is typically called from HdPhDynamicUvTextureImplementation::Load
  /// so that the CPU data can be uploaded during commit.
  ///
  /// To free the CPU data, call with nullptr.
  ///
  void SetCpuData(std::unique_ptr<HdPhTextureCpuData> &&cpuData)
  {
    _SetCpuData(std::move(cpuData));
  }

  /// Get the CPU data stored for this texture.
  ///
  /// Typically used in HdPhDynamicUvTextureImplementation::Commit to
  /// commit CPU data to GPU.
  HdPhTextureCpuData *GetCpuData() const
  {
    return _GetCpuData();
  }

  /// Always returns true - so that samplers for this texture are
  /// created.
  ///
  HDPH_API
  bool IsValid() const override;

 protected:
  HDPH_API
  void _Load() override;

  HDPH_API
  void _Commit() override;

 private:
  HdPhDynamicUvTextureImplementation *_GetImpl() const;
};

FORGE_NAMESPACE_END

#endif
