#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/sprim.h"
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
#ifndef FORGE_IMAGING_HD_SPRIM_H
#define FORGE_IMAGING_HD_SPRIM_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/types.h"

#include "forge/usd/sdf/path.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
class HdRenderParam;

/// \class HdSprim
///
/// Sprim (state prim) is a base class of managing state for non-drawable
/// scene entity (e.g. camera, light). Similar to Rprim, Sprim communicates
/// scene delegate and tracks the changes through change tracker, then updates
/// data cached in Hd (either on CPU or GPU).
///
/// Unlike Rprim, Sprim doesn't produce draw items. The data cached in HdSprim
/// may be used by HdTask or by HdShader.
///
/// The lifetime of HdSprim is owned by HdRenderIndex.
///
class HdSprim {
public:
    HD_API
    HdSprim(SdfPath const & id);
    HD_API
    virtual ~HdSprim();

    /// Returns the identifier by which this state is known. This
    /// identifier is a common associative key used by the SceneDelegate,
    /// RenderIndex, and for binding to the state (e.g. camera, light)
    SdfPath const& GetId() const { return _id; }

    /// Synchronizes state from the delegate to this object.
    /// @param[in, out]  dirtyBits: On input specifies which state is
    ///                             is dirty and can be pulled from the scene
    ///                             delegate.
    ///                             On output specifies which bits are still
    ///                             dirty and were not cleaned by the sync.
    ///
    virtual void Sync(HdSceneDelegate *sceneDelegate,
                      HdRenderParam   *renderParam,
                      HdDirtyBits     *dirtyBits) = 0;

    /// Finalizes object resources. This function might not delete resources,
    /// but it should deal with resource ownership so that the sprim is
    /// deletable.
    HD_API
    virtual void Finalize(HdRenderParam *renderParam);

    /// Returns the minimal set of dirty bits to place in the
    /// change tracker for use in the first sync of this prim.
    /// Typically this would be all dirty bits.
    virtual HdDirtyBits GetInitialDirtyBitsMask() const = 0;

private:
    SdfPath _id;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_SPRIM_H
