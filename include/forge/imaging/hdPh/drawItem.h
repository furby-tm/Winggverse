#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/drawItem.h"
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
#ifndef FORGE_IMAGING_HD_PH_DRAW_ITEM_H
#define FORGE_IMAGING_HD_PH_DRAW_ITEM_H

#include "forge/forge.h"
#include "forge/imaging/hd/drawItem.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

using HdPh_GeometricShaderSharedPtr = std::shared_ptr<class HdPh_GeometricShader>;
using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;

class HdPhDrawItem : public HdDrawItem {
 public:
  HF_MALLOC_TAG_NEW("new HdPhDrawItem");

  HDPH_API
  HdPhDrawItem(HdRprimSharedData const *sharedData);

  HDPH_API
  ~HdPhDrawItem() override;

  void SetGeometricShader(HdPh_GeometricShaderSharedPtr const &shader)
  {
    _geometricShader = shader;
  }

  HdPh_GeometricShaderSharedPtr const &GetGeometricShader() const
  {
    return _geometricShader;
  }

  HdPhShaderCodeSharedPtr const &GetMaterialShader() const
  {
    return _materialShader;
  }

  void SetMaterialShader(HdPhShaderCodeSharedPtr const &shader)
  {
    _materialShader = shader;
  }

 protected:
  size_t _GetBufferArraysHash() const override;
  size_t _GetElementOffsetsHash() const override;

 private:
  HdPh_GeometricShaderSharedPtr _geometricShader;
  HdPhShaderCodeSharedPtr _materialShader;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DRAW_ITEM_H
