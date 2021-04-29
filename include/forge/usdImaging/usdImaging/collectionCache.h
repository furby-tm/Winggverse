#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/collectionCache.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_COLLECTION_CACHE_H
#define FORGE_USD_IMAGING_USD_IMAGING_COLLECTION_CACHE_H

/// \file usdImaging/collectionCache.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usd/usd/collectionAPI.h"

#include <boost/noncopyable.hpp>

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_unordered_map.h>
# include <tbb/concurrent_queue.h>
#endif /* Q_MOC_RUN */

#include <unordered_map>

FORGE_NAMESPACE_BEGIN

/// \class UsdImaging_CollectionCache
///
/// UsdImaging_CollectionCache provides a cache of Usd collections
/// discovered in the scene.  It associates the collection paths
/// (UsdCollectionAPI::GetCollectionPath) with the computed
/// membership query (UsdCollectionAPI::ComputeMembershipQuery).
///
/// For efficiency, it groups collections into equivalence
/// classes based on the computed query.  Collections that yield
/// equivalent queries are merged.  Each unique query is assigned
/// an identifier token.
///
/// This cache is used to track the collections used for linking
/// UsdLux lights/shadows/filters to geometry.
///
/// As an optimization, the query that includes everything is
/// treated as a special case and given the empty id, TfToken().
///
class UsdImaging_CollectionCache : boost::noncopyable {
public:
    /// Query is the MembershipQuery computed from a collection's state.
    typedef UsdCollectionAPI::MembershipQuery Query;

    /// Computes the membership query from the current state of the
    /// given collection, and establishes a cache entry.  If a
    /// prior entry existed for the collection at this path,
    /// it is removed first.
    TfToken UpdateCollection(UsdCollectionAPI const& collection);

    /// Remove any cached entry for the given collection.
    /// Does nothing if no cache entry exists.
    void RemoveCollection(UsdCollectionAPI const& collection);

    /// Return the cached entry for the given collection.
    TfToken
    GetIdForCollection(UsdCollectionAPI const& collection);

    /// Return a list of identifiers of all collections that contain
    // the given path.
    VtArray<TfToken>
    ComputeCollectionsContainingPath(SdfPath const& path) const;

private:
    // The cache boils down to tracking the correspondence of
    // collection paths, their computed queries, and the id
    // assigned to each unique query:
    //
    // CollectionPath <=> MembershipQuery <=> AssignedId
    //
    // In this scheme, the assigned id provides a compact but
    // potentially human-meaningful reference to the query,
    // which we can pass to the renderer.
    //
    std::unordered_map<Query, TfToken, Query::Hash> _idForQuery;
    std::unordered_map<TfToken, Query, TfToken::HashFunctor> _queryForId;
    std::unordered_map<SdfPath, TfToken, SdfPath::Hash> _idForPath;
    std::unordered_map<Query, SdfPathSet, Query::Hash> _pathsForQuery;

    std::mutex _mutex;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_COLLECTION_CACHE_H
