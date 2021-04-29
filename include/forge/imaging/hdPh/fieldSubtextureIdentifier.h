#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/fieldSubtextureIdentifier.h"
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
#ifndef FORGE_IMAGING_HD_PH_FIELD_SUBTEXTURE_IDENTIFIER_H
#define FORGE_IMAGING_HD_PH_FIELD_SUBTEXTURE_IDENTIFIER_H

#include "forge/imaging/hdPh/subtextureIdentifier.h"

FORGE_NAMESPACE_BEGIN

///
/// \class HdPhOpenVDBAssetSubtextureIdentifier
///
/// Identifies a grid in an OpenVDB file. Parallels OpenVDBAsset in usdVol.
///
class HdPhOpenVDBAssetSubtextureIdentifier final : public HdPhFieldBaseSubtextureIdentifier {
 public:
  /// C'tor
  ///
  /// fieldName corresponds to the gridName in the OpenVDB file.
  ///
  HDPH_API
  explicit HdPhOpenVDBAssetSubtextureIdentifier(TfToken const &fieldName, int fieldIndex);

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  HDPH_API
  ~HdPhOpenVDBAssetSubtextureIdentifier() override;

 protected:
  HDPH_API
  ID _Hash() const override;
};

///
/// \class HdPhField3DAssetSubtextureIdentifier
///
/// Identifies the grid in a Field3DAsset file.
/// Parallels Field3DAsset in usdVol.
///
class HdPhField3DAssetSubtextureIdentifier final : public HdPhFieldBaseSubtextureIdentifier {
 public:
  /// C'tor
  ///
  /// fieldName corresponds (e.g., density) to the
  ///             layer/attribute name in the Field3D file
  /// fieldIndex corresponds to the
  ///             partition index
  /// fieldPurpose (e.g., BigCloud) corresponds to the
  ///             partition name/grouping
  ///
  HDPH_API
  explicit HdPhField3DAssetSubtextureIdentifier(TfToken const &fieldName,
                                                int fieldIndex,
                                                TfToken const &fieldPurpose);

  HDPH_API
  std::unique_ptr<HdPhSubtextureIdentifier> Clone() const override;

  HDPH_API
  TfToken const &GetFieldPurpose() const
  {
    return _fieldPurpose;
  }

  HDPH_API
  ~HdPhField3DAssetSubtextureIdentifier() override;

 protected:
  HDPH_API
  ID _Hash() const override;

 private:
  TfToken _fieldPurpose;
};

FORGE_NAMESPACE_END

#endif
