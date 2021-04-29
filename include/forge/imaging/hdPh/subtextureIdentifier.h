#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/subtextureIdentifier.h"
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
#ifndef FORGE_IMAGING_HD_PH_SUBTEXTURE_IDENTIFIER_H
#define FORGE_IMAGING_HD_PH_SUBTEXTURE_IDENTIFIER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/tf/token.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhDynamicUvTextureImplementation;

///
/// \class HdPhSubtextureIdentifier
///
/// Base class for additional information to identify a texture in a
/// file that can contain several textures (e.g., frames in a movie or
/// grids in an OpenVDB file).
///
class HdPhSubtextureIdentifier {
 public:
  using ID = size_t;

  HDPH_API
  virtual std::unique_ptr<HdPhSubtextureIdentifier> Clone() const = 0;

  HDPH_API
  virtual ~HdPhSubtextureIdentifier();

 protected:
  HDPH_API
  friend size_t hash_value(const HdPhSubtextureIdentifier &subId);

  virtual ID _Hash() const = 0;
};

HDPH_API
size_t hash_value(const HdPhSubtextureIdentifier &subId);

///
/// \class HdPhFieldBaseSubtextureIdentifier
///
/// Base class for information identifying a grid in a volume field
/// file. Parallels FieldBase in usdVol.
///
class HdPhFieldBaseSubtextureIdentifier : public HdPhSubtextureIdentifier {
 public:
  /// Get field name.
  ///
  HDPH_API
  TfToken const &GetFieldName() const
  {
    return _fieldName;
  }

  /// Get field index.
  ///
  HDPH_API
  int GetFieldIndex() const
  {
    return _fieldIndex;
  }

  HDPH_API
  ~HdPhFieldBaseSubtextureIdentifier() override = 0;

 protected:
  HDPH_API
  HdPhFieldBaseSubtextureIdentifier(TfToken const &fieldName, int fieldIndex);

  HDPH_API
  ID _Hash() const override;

 private:
  TfToken _fieldName;
  int _fieldIndex;
};

///
/// \class HdPhAssetUvSubtextureIdentifier
///
/// Specifies whether a UV texture should be loaded flipped vertically, whether
/// it should be loaded with pre-multiplied alpha values, and the color space
/// in which the texture is encoded.
///
/// The former functionality allows the texture system to support both the
/// legacy HwUvTexture_1 (flipVertically = true) and UsdUvTexture
/// (flipVertically = false) which have opposite conventions for the
/// vertical orientation.
///
class HdPhAssetUvSubtextureIdentifier final : public HdPhSubtextureIdentifier {
 public:
  /// C'tor takes bool whether flipping vertically, whether to pre-multiply
  /// by alpha, and the texture's source color space
  HDPH_API
  explicit HdPhAssetUvSubtextureIdentifier(bool flipVertically,
                                           bool premultiplyAlpha,
                                           const TfToken &sourceColorSpace);

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  HDPH_API
  bool GetFlipVertically() const
  {
    return _flipVertically;
  }

  HDPH_API
  bool GetPremultiplyAlpha() const
  {
    return _premultiplyAlpha;
  }

  HDPH_API
  TfToken GetSourceColorSpace() const
  {
    return _sourceColorSpace;
  }

  HDPH_API
  ~HdPhAssetUvSubtextureIdentifier() override;

 protected:
  HDPH_API
  ID _Hash() const override;

 private:
  bool _flipVertically;
  bool _premultiplyAlpha;
  TfToken _sourceColorSpace;
};

///
/// \class HdPhDynamicUvSubtextureIdentifier
///
/// Used as a tag that the Phoenix texture system returns a
/// HdPhDynamicUvTextureObject that is populated by a client rather
/// than by the Phoenix texture system.
///
/// Clients can subclass this class and provide their own
/// HdPhDynamicUvTextureImplementation to create UV texture with custom
/// load and commit behavior.
///
/// testHdPhDynamicUvTexture.cpp is an example of how custom load and
/// commit behavior can be implemented.
///
/// AOV's are another example. In presto, these are baked by
/// HdPhDynamicUvTextureObject's. In this case, the
/// HdPhDynamicUvTextureObject's do not provide custom load or commit
/// behavior (null-ptr returned by GetTextureImplementation). Instead,
/// GPU memory is allocated by explicitly calling
/// HdPhDynamicUvTextureObject::CreateTexture in
/// HdPhRenderBuffer::Sync/Allocate and the texture is filled by using
/// it as render target in various render passes.
///
class HdPhDynamicUvSubtextureIdentifier : public HdPhSubtextureIdentifier {
 public:
  HDPH_API
  HdPhDynamicUvSubtextureIdentifier();

  HDPH_API
  ~HdPhDynamicUvSubtextureIdentifier() override;

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  /// Textures can return their own HdPhDynamicUvTextureImplementation
  /// to customize the load and commit behavior.
  HDPH_API
  virtual HdPhDynamicUvTextureImplementation *GetTextureImplementation() const;

 protected:
  HDPH_API
  ID _Hash() const override;
};

///
/// \class HdPhPtexSubtextureIdentifier
///
/// Specifies whether a Ptex texture should be loaded with pre-multiplied alpha
/// values.
///
class HdPhPtexSubtextureIdentifier final : public HdPhSubtextureIdentifier {
 public:
  /// C'tor takes bool whether to pre-multiply by alpha
  HDPH_API
  explicit HdPhPtexSubtextureIdentifier(bool premultiplyAlpha);

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  HDPH_API
  bool GetPremultiplyAlpha() const
  {
    return _premultiplyAlpha;
  }

  HDPH_API
  ~HdPhPtexSubtextureIdentifier() override;

 protected:
  HDPH_API
  ID _Hash() const override;

 private:
  bool _premultiplyAlpha;
};

///
/// \class HdPhUdimSubtextureIdentifier
///
/// Specifies whether a Udim texture should be loaded with pre-multiplied alpha
/// values and the color space in which the texture is encoded.
///
class HdPhUdimSubtextureIdentifier final : public HdPhSubtextureIdentifier {
 public:
  /// C'tor takes bool whether to pre-multiply by alpha and the texture's
  /// source color space
  HDPH_API
  explicit HdPhUdimSubtextureIdentifier(bool premultiplyAlpha, const TfToken &sourceColorSpace);

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  HDPH_API
  bool GetPremultiplyAlpha() const
  {
    return _premultiplyAlpha;
  }

  HDPH_API
  TfToken GetSourceColorSpace() const
  {
    return _sourceColorSpace;
  }

  HDPH_API
  ~HdPhUdimSubtextureIdentifier() override;

 protected:
  HDPH_API
  ID _Hash() const override;

 private:
  bool _premultiplyAlpha;
  TfToken _sourceColorSpace;
};

FORGE_NAMESPACE_END

#endif
