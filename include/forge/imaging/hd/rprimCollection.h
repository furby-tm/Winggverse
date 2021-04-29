#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/rprimCollection.h"
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
#ifndef FORGE_IMAGING_HD_RPRIM_COLLECTION_H
#define FORGE_IMAGING_HD_RPRIM_COLLECTION_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/repr.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/tf/token.h"

#include <string>

FORGE_NAMESPACE_BEGIN


/// \class HdRprimCollection
///
/// A named, semantic collection of objects.
///
/// Note that the collection object itself doesn't hold HdRprim objects, rather
/// it acts as an addressing mechanism to identify a specific group of HdRprim
/// objects that can be requested from the HdRenderIndex.
///
/// HdDirtyList provides the above algorithmic functionality, while HdRenderPass
/// uses HdRprimCollection to concisely represent the HdRprim's it operates on.
///
/// \sa
/// HdRenderPass
/// HdDirtyList
///
class HdRprimCollection {
public:
    HD_API
    HdRprimCollection();

    /// Constructs an rprim collection with \p reprSelector. \p if forcedRepr is
    /// set to true, prims authored repr will be ignored.
    /// If \p materialTag is provided, only prims who's material have
    /// a matching tag will end up in the collection. This can be used to make
    /// seperate collections for e.g. opaque vs translucent prims.
    /// An empty materialTag opts-out of using material tags entirely and will
    /// return all prims in the collection, regardless of their material tags.
    HD_API
    HdRprimCollection(TfToken const& name,
                      HdReprSelector const& reprSelector,
                      bool forcedRepr=false,
                      TfToken const& materialTag = TfToken());

    /// Constructs an rprim collection, excluding all Rprims not prefixed by \p
    /// rootPath. \p if forcedRepr is set to true, prims authored repr will be
    /// ignored.
    /// If \p materialTag is provided, only prims who's material have
    /// a matching tag will end up in the collection. This can be used to make
    /// seperate collections for e.g. opaque vs translucent prims.
    /// An empty materialTag opts-out of using material tags entirely and will
    /// return all prims in the collection, regardless of their material tags.
    HD_API
    HdRprimCollection(TfToken const& name,
                      HdReprSelector const& reprSelector,
                      SdfPath const& rootPath,
                      bool forcedRepr=false,
                      TfToken const& materialTag = TfToken());

    /// Copy constructor.
    HD_API
    HdRprimCollection(HdRprimCollection const& col);

    // Destructor.
    HD_API
    virtual ~HdRprimCollection();

    /// Constructs and returns a collection with the root and exclude paths
    /// swapped.
    HD_API
    HdRprimCollection CreateInverseCollection() const;

    /// Returns the semantic name of this collection.
    ///
    /// The semantic name represents the entire collection of prims, for
    /// example "visible", "selected", etc.
    TfToken const& GetName() const {
        return _name;
    }

    /// Sets the semantic name of this collection.
    void SetName(TfToken const& name) {
        _name = name;
    }

    /// Returns the representation name.
    ///
    /// The repr selector corresponds to specific aspects of the requested set
    /// of Rprims, for example one can request "hullAndPoints" repr which
    /// would cause both the hull and points representations of all prims named
    /// by the collection to be included.
    HdReprSelector const& GetReprSelector() const {
        return _reprSelector;
    }

    void SetReprSelector(HdReprSelector const& reprSelector) {
        _reprSelector = reprSelector;
    }

    bool IsForcedRepr() const {
        return _forcedRepr;
    }

    void SetForcedRepr(bool flag) {
        _forcedRepr = flag;
    }

    /// Returns the paths at which all Rprims must be rooted to be included in
    /// this collection. Defaults to a vector containing only
    /// SdfPath::AbsoluteRootPath().
    ///
    /// Note that this vector is always sorted.
    HD_API
    SdfPathVector const& GetRootPaths() const;

    /// Sets all root paths for this collection, replacing any existing paths
    /// that were present previously. All paths must be absolute. Duplicate
    /// paths are allowed, but may result in performance degradation.
    HD_API
    void SetRootPaths(SdfPathVector const& rootPaths);

    /// Sets the path at which all Rprims must be rooted to be included in this
    /// collection, replacing any existing root paths that were previously
    /// specified.
    HD_API
    void SetRootPath(SdfPath const& rootPath);

    /// Sets all exclude paths for this collection. All paths must be absolute.
    /// Duplicate paths are allowed, but may result in performance degradation.
    HD_API
    void SetExcludePaths(SdfPathVector const& excludePaths);

    /// Returns the excluded paths
    ///
    /// Note that this vector is always sorted.
    HD_API
    SdfPathVector const& GetExcludePaths() const;

    /// A MaterialTag can be used to ensure only prims whos material have
    /// a matching tag will end up in the collection. Different rendering
    /// backends can control what material properties are useful for splitting
    /// up collections. For example, when Stream finds the 'translucent'
    /// MaterialTag in a material it will transfer this tag onto the
    /// prim's DrawItem. This ensures that opaque and translucent prims end up
    /// in different collections so they can be rendered seperately.
    /// A path-tracer backend may find the translucent MaterialTag on a material
    /// and choose NOT to transfer the tag onto the DrawItem because the
    /// backend wants to render opaque and translucent prims in the same
    /// collection.
    HD_API
    void SetMaterialTag(TfToken const& tag);

    HD_API
    TfToken const& GetMaterialTag() const;

    HD_API
    size_t ComputeHash() const;

    struct Hash {
        size_t operator()(HdRprimCollection const& value) const {
            return value.ComputeHash();
        }
    };

    // TfHash support.
    template <class HashState>
    friend void TfHashAppend(HashState &h, HdRprimCollection const &rc) {
        h.Append(rc._name,
                 rc._reprSelector,
                 rc._forcedRepr,
                 rc._rootPaths,
                 rc._excludePaths,
                 rc._materialTag);
    }

    HD_API
    bool operator==(HdRprimCollection const & lhs) const;
    HD_API
    bool operator!=(HdRprimCollection const & lhs) const;

private:
    HD_API
    friend std::ostream & operator <<(std::ostream &out,
        HdRprimCollection const & v);

    TfToken _name;
    HdReprSelector _reprSelector;
    bool _forcedRepr;
    TfToken _materialTag;
    SdfPathVector _rootPaths;
    SdfPathVector _excludePaths;
};

// VtValue requirements
HD_API
std::ostream& operator<<(std::ostream& out, HdRprimCollection const & v);

// Overload hash_value for HdRprimCollection.  Used by things like boost::hash.
HD_API
size_t hash_value(HdRprimCollection const &col);


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_RPRIM_COLLECTION_H
