#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/cache.h"
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
#ifndef FORGE_USD_USD_SKEL_CACHE_H
#define FORGE_USD_USD_SKEL_CACHE_H

/// \file usdSkel/cache.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"

#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/primFlags.h"

#include "forge/usd/usdSkel/animQuery.h"
#include "forge/usd/usdSkel/binding.h"

#include <memory>


FORGE_NAMESPACE_BEGIN


class UsdSkelRoot;
class UsdSkelAnimation;
class UsdSkelSkeleton;
class UsdSkelSkeletonQuery;
class UsdSkelSkinningQuery;

TF_DECLARE_REF_PTRS(UsdSkelBinding);


/// Thread-safe cache for accessing query objects for evaluating skeletal data.
///
/// This provides caching of major structural components, such as skeletal
/// topology. In a streaming context, this cache is intended to persist.
class UsdSkelCache
{
public:
    USDSKEL_API
    UsdSkelCache();

    USDSKEL_API
    void Clear();

    /// Populate the cache for the skeletal data beneath prim \p root,
    /// as traversed using \p predicate.
    ///
    /// Population resolves inherited skel bindings set using the
    /// UsdSkelBindingAPI, making resolved bindings available through
    /// GetSkinningQuery(), ComputeSkelBdining() and ComputeSkelBindings().
    USDSKEL_API
    bool Populate(const UsdSkelRoot& root,
                  Usd_PrimFlagsPredicate predicate) const;

    /// Get a skel query for computing properties of \p skel.
    ///
    /// This does not require Populate() to be called on the cache.
    USDSKEL_API
    UsdSkelSkeletonQuery GetSkelQuery(const UsdSkelSkeleton& skel) const;

    /// Get an anim query corresponding to \p anim.
    ///
    /// This does not require Populate() to be called on the cache.
    USDSKEL_API
    UsdSkelAnimQuery GetAnimQuery(const UsdSkelAnimation& anim) const;

    /// \overload
    /// \deprecated
    USDSKEL_API
    UsdSkelAnimQuery GetAnimQuery(const UsdPrim& prim) const;

    /// Get a skinning query at \p prim.
    ///
    /// Skinning queries are defined at any skinnable prims (I.e., boundable
    /// prims with fully defined joint influences).
    ///
    /// The caller must first Populate() the cache with the skel root containing
    /// \p prim, with a predicate that will visit \p prim, in order for a
    /// skinning query to be discoverable.
    USDSKEL_API
    UsdSkelSkinningQuery GetSkinningQuery(const UsdPrim& prim) const;

    /// Compute the set of skeleton bindings beneath \p skelRoot,
    /// as discovered through a traversal using \p predicate.
    ///
    /// Skinnable prims are only discoverable by this method if Populate()
    /// has already been called for \p skelRoot, with an equivalent predicate.
    USDSKEL_API
    bool ComputeSkelBindings(const UsdSkelRoot& skelRoot,
                             std::vector<UsdSkelBinding>* bindings,
                             Usd_PrimFlagsPredicate predicate) const;

    /// Compute the bindings corresponding to a single skeleton, bound beneath
    /// \p skelRoot, as discovered through a traversal using \p predicate.
    ///
    /// Skinnable prims are only discoverable by this method if Populate()
    /// has already been called for \p skelRoot, with an equivalent predicate.
    USDSKEL_API
    bool ComputeSkelBinding(const UsdSkelRoot& skelRoot,
                            const UsdSkelSkeleton& skel,
                            UsdSkelBinding* binding,
                            Usd_PrimFlagsPredicate predicate) const;

private:
    std::shared_ptr<class UsdSkel_CacheImpl> _impl;

    friend class UsdSkelAnimQuery;
    friend class UsdSkelSkeletonQuery;
};

FORGE_NAMESPACE_END

#endif // USDSKEL_EVALCACHE_H
