#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/textureIdentifier.h"
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
#ifndef FORGE_IMAGING_HD_PH_TEXTURE_IDENTIFIER_H
#define FORGE_IMAGING_HD_PH_TEXTURE_IDENTIFIER_H

#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/base/tf/token.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhSubtextureIdentifier;

///
/// \class HdPhTextureIdentifier
///
/// Class to identify a texture file or a texture within the texture file
/// (e.g., a frame in a movie).
///
/// The class has value semantics and uses HdPhSubtextureIdentifier in a
/// polymorphic way.
///
class HdPhTextureIdentifier final {
 public:
  using ID = size_t;

  HdPhTextureIdentifier();

  /// C'tor for files that can contain only one texture.
  ///
  explicit HdPhTextureIdentifier(const TfToken &filePath);

  /// C'tor for files that can contain more than one texture (e.g.,
  /// frames in a movie, grids in a VDB file).
  ///
  HdPhTextureIdentifier(const TfToken &filePath,
                        std::unique_ptr<const HdPhSubtextureIdentifier> &&subtextureId);

  HdPhTextureIdentifier(const HdPhTextureIdentifier &textureId);

  HdPhTextureIdentifier &operator=(HdPhTextureIdentifier &&textureId);

  HdPhTextureIdentifier &operator=(const HdPhTextureIdentifier &textureId);

  ~HdPhTextureIdentifier();

  /// Get file path of texture file.
  ///
  const TfToken &GetFilePath() const
  {
    return _filePath;
  }

  /// Get additional information identifying a texture in a file that
  /// can contain more than one texture (e.g., a frame in a movie or
  /// a grid in a VDB file).
  ///
  /// nullptr for files (e.g., png) that can contain only one texture.
  ///
  const HdPhSubtextureIdentifier *GetSubtextureIdentifier() const
  {
    return _subtextureId.get();
  }

  bool operator==(const HdPhTextureIdentifier &other) const;
  bool operator!=(const HdPhTextureIdentifier &other) const;

 private:
  TfToken _filePath;
  std::unique_ptr<const HdPhSubtextureIdentifier> _subtextureId;
};

size_t hash_value(const HdPhTextureIdentifier &);

FORGE_NAMESPACE_END

#endif
