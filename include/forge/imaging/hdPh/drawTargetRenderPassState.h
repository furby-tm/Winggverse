#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/drawTargetRenderPassState.h"
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
#ifndef FORGE_IMAGING_HD_PH_DRAW_TARGET_RENDER_PASS_STATE_H
#define FORGE_IMAGING_HD_PH_DRAW_TARGET_RENDER_PASS_STATE_H

#include "forge/forge.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

class VtValue;
using HdRenderPassAovBindingVector = std::vector<struct HdRenderPassAovBinding>;

/// \class HdPhDrawTargetRenderPassState
///
/// Represents common non-gl context specific render pass state for a draw
/// target.
///
/// \note This is a temporary API to aid transition to Phoenix, and is subject
/// to major changes.  It is likely this functionality will be absorbed into
/// the base class.
///
class HdPhDrawTargetRenderPassState final {
 public:
  HDPH_API
  HdPhDrawTargetRenderPassState();
  HDPH_API
  ~HdPhDrawTargetRenderPassState();  // final no need to be virtual

  const HdRenderPassAovBindingVector &GetAovBindings() const
  {
    return _aovBindings;
  }

  HDPH_API
  void SetAovBindings(const HdRenderPassAovBindingVector &aovBindings);

  /// Sets the priority of values in the depth buffer.
  /// i.e. should pixels closer or further from the camera win.
  HDPH_API
  void SetDepthPriority(HdDepthPriority priority);

  /// Set the path to the camera to use to draw this render path from.
  HDPH_API
  void SetCamera(const SdfPath &cameraId);

  HDPH_API
  void SetRprimCollection(HdRprimCollection const &col);

  HdDepthPriority GetDepthPriority() const
  {
    return _depthPriority;
  }

  /// Returns the path to the camera to render from.
  const SdfPath &GetCamera() const
  {
    return _cameraId;
  }

  /// Returns an increasing version number for when the collection object
  /// is changed.
  /// Note: This tracks the actual object and not the contents of the
  /// collection.
  unsigned int GetRprimCollectionVersion() const
  {
    return _rprimCollectionVersion;
  }

  /// Returns the collection associated with this draw target.
  const HdRprimCollection &GetRprimCollection() const
  {
    return _rprimCollection;
  }

 private:
  HdRenderPassAovBindingVector _aovBindings;
  HdDepthPriority _depthPriority;

  SdfPath _cameraId;

  HdRprimCollection _rprimCollection;
  unsigned int _rprimCollectionVersion;

  HdPhDrawTargetRenderPassState(const HdPhDrawTargetRenderPassState &) = delete;
  HdPhDrawTargetRenderPassState &operator=(const HdPhDrawTargetRenderPassState &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DRAW_TARGET_RENDER_PASS_STATE_H
