#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/instancer.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_INSTANCER_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_INSTANCER_H

#include "forge/forge.h"

#include "forge/imaging/hd/instancer.h"
#include "forge/imaging/hd/vtBufferSource.h"

#include "forge/base/tf/hashmap.h"
#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

/// \class HdEmbreeInstancer
///
/// HdEmbree implements instancing by adding prototype geometry to the BVH
/// multiple times within HdEmbreeMesh::Sync(). The only instance-varying
/// attribute that HdEmbree supports is transform, so the natural
/// accessor to instancer data is ComputeInstanceTransforms(),
/// which returns a list of transforms to apply to the given prototype
/// (one instance per transform).
///
/// Nested instancing can be handled by recursion, and by taking the
/// cartesian product of the transform arrays at each nesting level, to
/// create a flattened transform array.
///
class HdEmbreeInstancer : public HdInstancer {
public:
    /// Constructor.
    ///   \param delegate The scene delegate backing this instancer's data.
    ///   \param id The unique id of this instancer.
    HdEmbreeInstancer(HdSceneDelegate* delegate, SdfPath const& id);

    /// Destructor.
    ~HdEmbreeInstancer();

    /// Computes all instance transforms for the provided prototype id,
    /// taking into account the scene delegate's instancerTransform and the
    /// instance primvars "instanceTransform", "translate", "rotate", "scale".
    /// Computes and flattens nested transforms, if necessary.
    ///   \param prototypeId The prototype to compute transforms for.
    ///   \return One transform per instance, to apply when drawing.
    VtMatrix4dArray ComputeInstanceTransforms(SdfPath const &prototypeId);

    /// Updates cached primvar data from the scene delegate.
    ///   \param sceneDelegate The scene delegate for this prim.
    ///   \param renderParam The hdEmbree render param.
    ///   \param dirtyBits The dirty bits for this instancer.
    void Sync(HdSceneDelegate *sceneDelegate,
              HdRenderParam   *renderParam,
              HdDirtyBits     *dirtyBits) override;

private:
    // Updates the cached primvars in _primvarMap based on scene delegate
    // data.  This is a helper function for Sync().
    void _SyncPrimvars(HdSceneDelegate *delegate, HdDirtyBits dirtyBits);

    // Map of the latest primvar data for this instancer, keyed by
    // primvar name. Primvar values are VtValue, an any-type; they are
    // interpreted at consumption time (here, in ComputeInstanceTransforms).
    TfHashMap<TfToken,
              HdVtBufferSource*,
              TfToken::HashFunctor> _primvarMap;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_PLUGIN_HD_EMBREE_INSTANCER_H
