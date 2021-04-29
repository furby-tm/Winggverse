#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/field.h"
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
#ifndef FORGE_IMAGING_HD_PH_FIELD_H
#define FORGE_IMAGING_HD_PH_FIELD_H

#include "forge/forge.h"
#include "forge/imaging/hd/field.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hdPh/textureIdentifier.h"

FORGE_NAMESPACE_BEGIN

///
/// Represents a Field Buffer Prim.
///
class HdPhField : public HdField {
 public:
  /// For now, only fieldType HdPhTokens->openvdbAsset is supported.
  HDPH_API
  HdPhField(SdfPath const &id, TfToken const &fieldType);
  HDPH_API
  ~HdPhField() override;

  /// Loads field as 3d texture to generate GetFieldResource.
  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  /// Initialized by Sync.
  HDPH_API
  HdPhTextureIdentifier const &GetTextureIdentifier() const
  {
    return _textureId;
  }

  /// Get memory request for this field
  size_t GetTextureMemory() const
  {
    return _textureMemory;
  }

  /// Bprim types handled by this class
  HDPH_API
  static const TfTokenVector &GetSupportedBprimTypes();

  /// Can bprim type be handled by this class
  HDPH_API
  static bool IsSupportedBprimType(const TfToken &bprimType);

 private:
  const TfToken _fieldType;

  HdPhTextureIdentifier _textureId;
  size_t _textureMemory;

  bool _isInitialized : 1;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_FIELD_H
