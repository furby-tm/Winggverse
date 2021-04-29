#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/skelDefinition.h"
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
#ifndef FORGE_USD_USD_SKEL_SKEL_DEFINITION_H
#define FORGE_USD_USD_SKEL_SKEL_DEFINITION_H

/// \file usdSkel/definition.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/matrix4f.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/hashmap.h"
#include "forge/base/tf/refBase.h"
#include "forge/base/tf/weakBase.h"

#include "forge/usd/usdSkel/skeleton.h"
#include "forge/usd/usdSkel/topology.h"

#include <atomic>
#include <mutex>


FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_AND_REF_PTRS(UsdSkel_SkelDefinition);


/// \class UsdSkel_SkelDefinition
///
/// Structure storing the core definition of a Skeleton.
/// A definition is a simple cache of the *validated* structure
/// of a skeleton, including its topology, bind pose and rest pose.
/// Skeleton definitions are meant to shared across instances.
class UsdSkel_SkelDefinition : public TfRefBase, public TfWeakBase
{
public:
    virtual ~UsdSkel_SkelDefinition() {}

    /// Create a definition from a skeleton.
    /// Returns an empty pointer if \p skel or its structure is invalid.
    static UsdSkel_SkelDefinitionRefPtr New(const UsdSkelSkeleton& skel);

    explicit operator bool() const {
        return static_cast<bool>(_skel);
    }

    const UsdSkelSkeleton& GetSkeleton() const { return _skel; }

    const VtTokenArray&    GetJointOrder() const { return _jointOrder; }

    const UsdSkelTopology& GetTopology() const { return _topology; }

    /// Returns rest pose joint transforms in joint-local space.
    template <typename Matrix4>
    bool GetJointLocalRestTransforms(VtArray<Matrix4>* xforms);

    /// Returns rest pose joint transforms in skel space.
    template <typename Matrix4>
    bool GetJointSkelRestTransforms(VtArray<Matrix4>* xforms);

    /// Returns bind pose joint transforms in world space.
    template <typename Matrix4>
    bool GetJointWorldBindTransforms(VtArray<Matrix4>* xforms);

    /// Returns the inverse of the world-space joint bind transforms.
    template <typename Matrix4>
    bool GetJointWorldInverseBindTransforms(VtArray<Matrix4>* xforms);

    /// Returns the inverse of the local-space rest transforms.
    template <typename Matrix4>
    bool GetJointLocalInverseRestTransforms(VtArray<Matrix4>* xforms);

    /// See UsdSkel_SkeletonQuery::HasBindPose()
    bool HasBindPose ();

    /// See UsdSkel_SkeletonQuery::HasRestPose()
    bool HasRestPose ();

private:
    UsdSkel_SkelDefinition();

    bool _Init(const UsdSkelSkeleton& skel);

    template <int ComputeFlag, typename Matrix4>
    bool _GetJointSkelRestTransforms(VtArray<Matrix4>* xforms);

    template <int ComputeFlag, typename Matrix4>
    bool _GetJointWorldInverseBindTransforms(VtArray<Matrix4>* xforms);

    template <int ComputeFlag, typename Matrix4>
    bool _GetJointLocalInverseRestTransforms(VtArray<Matrix4>* xforms);

    template <int ComputeFlag, typename Matrix4>
    bool _ComputeJointSkelRestTransforms();

    template <int ComputeFlag, typename Matrix4>
    bool _ComputeJointWorldInverseBindTransforms();

    template <int ComputeFlag, typename Matrix4>
    bool _ComputeJointLocalInverseRestTransforms();

    /// Helper for managing a set of cached transforms
    /// with both float and double precision.
    struct _XformHolder {
        template <typename Matrix4>
        VtArray<Matrix4>& Get();

        template <typename Matrix4>
        const VtArray<Matrix4>& Get() const;

        VtMatrix4dArray xforms4d;
        VtMatrix4fArray xforms4f;
    };

private:
    UsdSkelSkeleton _skel;
    VtTokenArray    _jointOrder;
    UsdSkelTopology _topology;
    VtMatrix4dArray _jointLocalRestXforms;
    VtMatrix4dArray _jointWorldBindXforms;
    // Properties computed (and cached) on-demand.
    // Different forms of transforms are cached because different
    // consumption tasks generally require different transforms.
    // They are cached on the definition in order to provide cache
    // sharing across instanced skeletons.
    _XformHolder _jointSkelRestXforms;
    _XformHolder _jointWorldInverseBindXforms;
    _XformHolder _jointLocalInverseRestXforms;

    std::atomic<int> _flags;
    std::mutex _mutex;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SKEL_SKEL_DEFINITION_H
