#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/cacheImpl.h"
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
#ifndef FORGE_USD_USD_SKEL_CACHE_IMPL_H
#define FORGE_USD_USD_SKEL_CACHE_IMPL_H

/// \file usdSkel/cacheImpl.h"

#include "forge/usd/usd/attribute.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/relationship.h"

#include "forge/usd/usdSkel/animMapper.h"
#include "forge/usd/usdSkel/animQueryImpl.h"
#include "forge/usd/usdSkel/animQuery.h"
#include "forge/usd/usdSkel/skeleton.h"
#include "forge/usd/usdSkel/skelDefinition.h"
#include "forge/usd/usdSkel/skeletonQuery.h"
#include "forge/usd/usdSkel/skinningQuery.h"

#include <boost/optional.hpp>

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_hash_map.h>
# include <tbb/queuing_rw_mutex.h>
#endif /* Q_MOC_RUN */

#include <unordered_map>


FORGE_NAMESPACE_BEGIN


class UsdGeomXformCache;
class UsdSkelRoot;


struct UsdSkel_HashPrim {
    inline size_t operator()(const UsdPrim& prim) const {
        return hash_value(prim);
    }

    static bool equal(const UsdPrim& a, const UsdPrim& b) {
        return a == b;
    }

    static size_t hash(const UsdPrim& prim) {
        return hash_value(prim);
    }
};


/// Internal cache implementation.
class UsdSkel_CacheImpl
{
public:
    using RWMutex = tbb::queuing_rw_mutex;

    struct _SkinningQueryKey {
        UsdAttribute jointIndicesAttr;
        UsdAttribute jointWeightsAttr;
        UsdAttribute geomBindTransformAttr;
        UsdAttribute jointsAttr;
        UsdAttribute blendShapesAttr;
        UsdRelationship blendShapeTargetsRel;
        UsdPrim skel;
    };

    /// Scope for performing read-only operations on the cache.
    /// Any thread-safe operations should be called here.
    struct ReadScope {
        ReadScope(UsdSkel_CacheImpl* cache);

        // Getters for properties with a direct prim association.
        // These are produced on-demand rather than through Populate().

        UsdSkelAnimQuery
        FindOrCreateAnimQuery(const UsdPrim& prim);

        UsdSkel_SkelDefinitionRefPtr
        FindOrCreateSkelDefinition(const UsdPrim& prim);

        UsdSkelSkeletonQuery
        FindOrCreateSkelQuery(const UsdPrim& prim);

        /// Method for populating the cache with cache properties, for
        /// the set of properties that depend on inherited state.
        ///
        /// Returns true if any skinnable prims were populated.
        bool Populate(const UsdSkelRoot& root,
                      Usd_PrimFlagsPredicate predicate);

        // Getters for properties added to the cache through Populate().

        UsdSkelSkinningQuery
        GetSkinningQuery(const UsdPrim& prim) const;

    private:

        UsdSkelSkinningQuery
        _FindOrCreateSkinningQuery(const UsdPrim& skinnedPrim,
                                   const _SkinningQueryKey& key);

        using _PrimToSkinMap =
            std::unordered_map<UsdPrim,_SkinningQueryKey,UsdSkel_HashPrim>;

        /// Recursively populate the cache beneath \p prim.
        /// Returns the number of skinnable prims populated beneath \p prim.
        void _RecursivePopulate(const SdfPath& rootPath,
                                const UsdPrim& prim,
                                _SkinningQueryKey key,
                                UsdSkelAnimQuery animQuery,
                                _PrimToSkinMap* skinBindingMap,
                                size_t depth=1);

    private:
        UsdSkel_CacheImpl* _cache;
        RWMutex::scoped_lock _lock;
    };

    /// Scope for performing write operations on the cache.
    /// This is used for non-threadsafe operations, like cache clearing.
    struct WriteScope {
        WriteScope(UsdSkel_CacheImpl* cache);

        void Clear();

    private:
        UsdSkel_CacheImpl* _cache;
        RWMutex::scoped_lock _lock;
    };

private:

    using _PrimToAnimMap =
        tbb::concurrent_hash_map<UsdPrim,
                                 UsdSkel_AnimQueryImplRefPtr,
                                 UsdSkel_HashPrim>;

    using _PrimToSkelDefinitionMap =
        tbb::concurrent_hash_map<UsdPrim,
                                 UsdSkel_SkelDefinitionRefPtr,
                                 UsdSkel_HashPrim>;

    using _PrimToSkelQueryMap =
        tbb::concurrent_hash_map<UsdPrim,
                                 UsdSkelSkeletonQuery,
                                 UsdSkel_HashPrim>;

    using _PrimToSkinningQueryMap =
        tbb::concurrent_hash_map<UsdPrim,
                                 UsdSkelSkinningQuery,
                                 UsdSkel_HashPrim>;

    using _RWMutex = tbb::queuing_rw_mutex;

    _PrimToAnimMap _animQueryCache;
    _PrimToSkelDefinitionMap _skelDefinitionCache;
    _PrimToSkelQueryMap _skelQueryCache;
    _PrimToSkinningQueryMap _primSkinningQueryCache;

    /// Mutex around unsafe operations (eg., clearing the maps)
    mutable _RWMutex _mutex; // XXX: Not recursive!
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SKEL_CACHE_IMPL_H
