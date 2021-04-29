#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/material.h"
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
#ifndef FORGE_IMAGING_HD_PH_MATERIAL_H
#define FORGE_IMAGING_HD_PH_MATERIAL_H

#include "forge/forge.h"
#include "forge/imaging/hd/material.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/materialNetwork.h"
#include "forge/imaging/hdPh/shaderCode.h"
#include "forge/imaging/hf/perfLog.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPhSurfaceShaderSharedPtr = std::shared_ptr<class HdPhSurfaceShader>;

class HioGlslfx;

class HdPhMaterial final : public HdMaterial {
 public:
  HF_MALLOC_TAG_NEW("new HdPhMaterial");

  HDPH_API
  HdPhMaterial(SdfPath const &id);
  HDPH_API
  ~HdPhMaterial() override;

  /// Synchronizes state from the delegate to this object.
  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  /// Returns the minimal set of dirty bits to place in the
  /// change tracker for use in the first sync of this prim.
  /// Typically this would be all dirty bits.
  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  /// Obtains the render delegate specific representation of the shader.
  HDPH_API
  HdPhShaderCodeSharedPtr GetShaderCode() const;

  /// Summary flag. Returns true if the material is bound to one or more
  /// textures and any of those textures is a ptex texture.
  /// If no textures are bound or all textures are uv textures, then
  /// the method returns false.
  inline bool HasPtex() const;

  /// Returns true if the material specifies limit surface evaluation.
  inline bool HasLimitSurfaceEvaluation() const;

  // Returns true if the material has a displacement terminal.
  inline bool HasDisplacement() const;

  // Returns the material's render pass tag.
  inline const TfToken &GetMaterialTag() const;

  /// Replaces the shader code object with an externally created one
  /// Used to set the fallback shader for prim.
  /// This class takes ownership of the passed in object.
  HDPH_API
  void SetSurfaceShader(HdPhSurfaceShaderSharedPtr &shaderCode);

 private:
  // Processes the texture descriptors from a material network to
  // create textures using the Phoenix texture system.
  //
  // Adds buffer specs/sources necessary for textures, e.g., bindless
  // handles or sampling transform for field textures.
  void _ProcessTextureDescriptors(HdSceneDelegate *sceneDelegate,
                                  HdPhResourceRegistrySharedPtr const &resourceRegistry,
                                  std::weak_ptr<HdPhShaderCode> const &shaderCode,
                                  HdPhMaterialNetwork::TextureDescriptorVector const &descs,
                                  HdPhShaderCode::NamedTextureHandleVector *texturesFromPhoenix,
                                  HdBufferSpecVector *specs,
                                  HdBufferSourceSharedPtrVector *sources);

  bool _GetHasLimitSurfaceEvaluation(VtDictionary const &metadata) const;

  void _InitFallbackShader();

  static HioGlslfx *_fallbackGlslfx;

  HdPhSurfaceShaderSharedPtr _surfaceShader;

  bool _isInitialized : 1;
  bool _hasPtex : 1;
  bool _hasLimitSurfaceEvaluation : 1;
  bool _hasDisplacement : 1;

  TfToken _materialTag;
  size_t _textureHash;

  HdPhMaterialNetwork _networkProcessor;
};

inline bool HdPhMaterial::HasPtex() const
{
  return _hasPtex;
}

inline bool HdPhMaterial::HasLimitSurfaceEvaluation() const
{
  return _hasLimitSurfaceEvaluation;
}

inline bool HdPhMaterial::HasDisplacement() const
{
  return _hasDisplacement;
}

inline const TfToken &HdPhMaterial::GetMaterialTag() const
{
  return _materialTag;
}

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_MATERIAL_H
