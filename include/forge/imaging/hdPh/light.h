#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/light.h"
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
#ifndef FORGE_IMAGING_HD_PH_LIGHT_H
#define FORGE_IMAGING_HD_PH_LIGHT_H

#include "forge/forge.h"
#include "forge/imaging/hd/light.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/glf/simpleLight.h"

#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPhLight
///
/// A light model for use in Phoenix.
/// Note: This class simply stores the light parameters and relies on an
/// external task (HdxSimpleLightTask) to upload them to the GPU.
///
class HdPhLight final : public HdLight {
 public:
  HDPH_API
  HdPhLight(SdfPath const &id, TfToken const &lightType);
  HDPH_API
  ~HdPhLight() override;

  /// Synchronizes state from the delegate to this object.
  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  /// Finalizes object resources. This function might not delete resources,
  /// but it should deal with resource ownership so that the sprim is
  /// deletable.
  HDPH_API
  void Finalize(HdRenderParam *renderParam) override;

  /// Accessor for tasks to get the parameters cached in this object.
  HDPH_API
  VtValue Get(TfToken const &token) const;

  /// Returns the minimal set of dirty bits to place in the
  /// change tracker for use in the first sync of this prim.
  /// Typically this would be all dirty bits.
  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

 private:
  // Converts area lights (sphere lights and distant lights) into
  // glfSimpleLights and inserts them in the dictionary so
  // SimpleLightTask can use them later on as if they were regular lights.
  GlfSimpleLight _ApproximateAreaLight(SdfPath const &id, HdSceneDelegate *sceneDelegate);

  // Collects data such as the environment map texture path for a
  // dome light. The lighting shader is responsible for pre-calculating
  // the different textures needed for IBL.
  GlfSimpleLight _PrepareDomeLight(SdfPath const &id, HdSceneDelegate *sceneDelegate);

 private:
  // Stores the internal light type of this light.
  TfToken _lightType;

  // Cached states.
  TfHashMap<TfToken, VtValue, TfToken::HashFunctor> _params;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_LIGHT_H
