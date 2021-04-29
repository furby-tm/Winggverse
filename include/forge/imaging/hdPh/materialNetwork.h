#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/materialNetwork.h"
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
#ifndef FORGE_IMAGING_HD_PH_MATERIAL_NETWORK_H
#define FORGE_IMAGING_HD_PH_MATERIAL_NETWORK_H

#include "forge/forge.h"
#include "forge/imaging/hd/material.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/textureIdentifier.h"

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;
using HioGlslfxSharedPtr = std::shared_ptr<class HioGlslfx>;
using HdPh_MaterialParamVector = std::vector<class HdPh_MaterialParam>;

/// \class HdPhMaterialNetwork
///
/// Helps HdPhMaterial process a Hydra material network into shader source code
/// and parameters values.
class HdPhMaterialNetwork final {
 public:
  HDPH_API
  HdPhMaterialNetwork();

  HDPH_API
  ~HdPhMaterialNetwork();

  /// Process a material network topology and extract all the information we
  /// need from it.
  HDPH_API
  void ProcessMaterialNetwork(SdfPath const &materialId,
                              HdMaterialNetworkMap const &hdNetworkMap,
                              HdPhResourceRegistry *resourceRegistry);

  HDPH_API
  TfToken const &GetMaterialTag() const;

  HDPH_API
  std::string const &GetFragmentCode() const;

  HDPH_API
  std::string const &GetGeometryCode() const;

  HDPH_API
  VtDictionary const &GetMetadata() const;

  HDPH_API
  HdPh_MaterialParamVector const &GetMaterialParams() const;

  // Information necessary to allocate a texture.
  struct TextureDescriptor {
    // Name by which the texture will be accessed, i.e., the name
    // of the accesor for thexture will be HdGet_name(...).
    // It is generated from the input name the corresponding texture
    // node is connected to.
    TfToken name;
    HdPhTextureIdentifier textureId;
    HdTextureType type;
    HdSamplerParameters samplerParameters;
    // Memory request in bytes.
    size_t memoryRequest;

    // The texture is not just identified by a file path attribute
    // on the texture prim but there is special API to texture prim
    // to obtain the texture.
    //
    // This is used for draw targets.
    bool useTexturePrimToFindTexture;
    // This is used for draw targets and hashing.
    SdfPath texturePrim;
  };

  using TextureDescriptorVector = std::vector<TextureDescriptor>;

  HDPH_API
  TextureDescriptorVector const &GetTextureDescriptors() const;

 private:
  TfToken _materialTag;
  std::string _fragmentSource;
  std::string _geometrySource;
  VtDictionary _materialMetadata;
  HdPh_MaterialParamVector _materialParams;
  TextureDescriptorVector _textureDescriptors;
  HioGlslfxSharedPtr _surfaceGfx;
  size_t _surfaceGfxHash;
};

FORGE_NAMESPACE_END

#endif
