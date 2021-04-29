#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/drawTarget.h"
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
#ifndef FORGE_IMAGING_HD_PH_DRAW_TARGET_H
#define FORGE_IMAGING_HD_PH_DRAW_TARGET_H

#include "forge/forge.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hd/sprim.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/drawTargetRenderPassState.h"

#include "forge/base/tf/staticTokens.h"
#include "forge/usd/sdf/path.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

#define HDPH_DRAW_TARGET_TOKENS \
  (camera)(collection)(drawTargetSet)(enable)(resolution)(aovBindings)(depthPriority)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdPhDrawTargetTokens, HDPH_API, HDPH_DRAW_TARGET_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

class HdCamera;
class HdRenderIndex;
using HdPhDrawTargetPtrVector = std::vector<class HdPhDrawTarget *>;

/// \class HdPhDrawTarget
///
/// Represents an render to texture render pass.
///
/// \note This is a temporary API to aid transition to Phoenix, and is subject
/// to major changes.
///
class HdPhDrawTarget : public HdSprim {
 public:
  HDPH_API
  HdPhDrawTarget(SdfPath const &id);
  HDPH_API
  ~HdPhDrawTarget() override;

  /// Dirty bits for the HdPhDrawTarget object
  ///
  /// When GetUsePhoenixTextureSystem() is true, "Legacy" dirty
  /// bits are ignored.
  ///
  enum DirtyBits : HdDirtyBits {
    Clean = 0,
    DirtyDTEnable = 1 << 0,
    DirtyDTCamera = 1 << 1,
    DirtyDTResolution = 1 << 2,
    DirtyDTAovBindings = 1 << 4,
    DirtyDTDepthPriority = 1 << 6,
    DirtyDTCollection = 1 << 7,
    AllDirty = (DirtyDTEnable | DirtyDTCamera | DirtyDTResolution | DirtyDTAovBindings |
                DirtyDTDepthPriority | DirtyDTCollection)
  };

  /// Synchronizes state from the delegate to this object.
  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  /// Returns the minimal set of dirty bits to place in the
  /// change tracker for use in the first sync of this prim.
  /// Typically this would be all dirty bits.
  HDPH_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  // ---------------------------------------------------------------------- //
  /// \name Draw Target API
  // ---------------------------------------------------------------------- //
  bool IsEnabled() const
  {
    return _enabled;
  }
  const HdPhDrawTargetRenderPassState *GetDrawTargetRenderPassState() const
  {
    return &_drawTargetRenderPassState;
  }

  /// Returns collection of rprims the draw target draws.
  HDPH_API
  HdRprimCollection const &GetCollection() const
  {
    return _collection;
  }

  /// returns all HdPhDrawTargets in the render index
  HDPH_API
  static void GetDrawTargets(HdRenderIndex *renderIndex, HdPhDrawTargetPtrVector *drawTargets);

  /// Resolution.
  ///
  /// Set during sync.
  ///
  const GfVec2i &GetResolution() const
  {
    return _resolution;
  }

 private:
  bool _enabled;
  GfVec2i _resolution;
  HdRprimCollection _collection;

  HdPhDrawTargetRenderPassState _drawTargetRenderPassState;

  // No copy
  HdPhDrawTarget() = delete;
  HdPhDrawTarget(const HdPhDrawTarget &) = delete;
  HdPhDrawTarget &operator=(const HdPhDrawTarget &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DRAW_TARGET_H
