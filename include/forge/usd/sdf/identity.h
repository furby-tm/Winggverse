#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/identity.h"
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
#ifndef FORGE_USD_SDF_IDENTITY_H
#define FORGE_USD_SDF_IDENTITY_H

#include "forge/forge.h"
#include "forge/base/tf/hashmap.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/path.h"

#include <boost/intrusive_ptr.hpp>
#include <boost/noncopyable.hpp>

#if !defined(Q_MOC_RUN)
# include <tbb/spin_mutex.h>
#endif /* Q_MOC_RUN */

FORGE_NAMESPACE_BEGIN

class Sdf_IdentityRegistry;
SDF_DECLARE_HANDLES(SdfLayer);

/// \class Sdf_Identity
///
/// Identifies the logical object behind an SdfSpec.
///
/// This is simply the layer the spec belongs to and the path to the spec.
///
class Sdf_Identity : public boost::noncopyable {
public:
    /// Returns the layer that this identity refers to.
    SDF_API
    const SdfLayerHandle &GetLayer() const;

    /// Returns the path that this identity refers to.
    const SdfPath &GetPath() const {
        return _path;
    }

private:
    // Ref-counting ops manage _refCount.
    friend void intrusive_ptr_add_ref(Sdf_Identity*);
    friend void intrusive_ptr_release(Sdf_Identity*);

    friend class Sdf_IdentityRegistry;

    SDF_API
    Sdf_Identity(Sdf_IdentityRegistry *registry, const SdfPath &path);
    SDF_API
    ~Sdf_Identity();

    void _Forget();

    mutable std::atomic_int _refCount;
    Sdf_IdentityRegistry *_registry;
    SdfPath _path;
};

// Specialize boost::intrusive_ptr operations.
inline void intrusive_ptr_add_ref(FORGE_NS::Sdf_Identity* p) {
    ++p->_refCount;
}
inline void intrusive_ptr_release(FORGE_NS::Sdf_Identity* p) {
    if (--p->_refCount == 0) {
        delete p;
    }
}

class Sdf_IdentityRegistry : public boost::noncopyable {
public:
    Sdf_IdentityRegistry(const SdfLayerHandle &layer);
    ~Sdf_IdentityRegistry();

    /// Returns the layer that owns this registry.
    const SdfLayerHandle &GetLayer() const {
        return _layer;
    }

    /// Return the identity associated with \a path, issuing a new
    /// one if necessary. The registry will track the identity
    /// and update it if the logical object it represents moves
    /// in namespace.
    Sdf_IdentityRefPtr Identify(const SdfPath &path);

    /// Update identity in response to a namespace edit.
    void MoveIdentity(const SdfPath &oldPath, const SdfPath &newPath);

private:
    // When an identity expires, it will remove itself from the registry.
    friend class Sdf_Identity;

    // Remove the identity mapping for \a path to \a id from the registry.
    // This is only called by Sdf_Identity's destructor.
    void _Remove(const SdfPath &path, Sdf_Identity *id);

    /// The layer that owns this registry, and on behalf of which
    /// this registry tracks identities.
    const SdfLayerHandle _layer;

    /// The identities being managed by this registry
    typedef TfHashMap<SdfPath, Sdf_Identity*, SdfPath::Hash> _IdMap;
    _IdMap _ids;

    /// Cache the last fetched identity, it's commonly re-fetched.
    Sdf_IdentityRefPtr _lastId;

    // This mutex synchronizes access to _ids.
    tbb::spin_mutex _idsMutex;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_IDENTITY_H
