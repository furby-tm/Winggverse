#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/primDataHandle.h"
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
#ifndef FORGE_USD_USD_PRIM_DATA_HANDLE_H
#define FORGE_USD_USD_PRIM_DATA_HANDLE_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include <boost/functional/hash.hpp>
#include <boost/intrusive_ptr.hpp>

FORGE_NAMESPACE_BEGIN

class SdfPath;

// To start we always validate.
#define USD_CHECK_ALL_PRIM_ACCESSES

// Forward declare boost::intrusive_ptr requirements.  Defined in primData.h.
void intrusive_ptr_add_ref(const class Usd_PrimData *prim);
void intrusive_ptr_release(const class Usd_PrimData *prim);

// Forward declarations for Usd_PrimDataHandle's use.  Defined in primData.h.
USD_API
void Usd_IssueFatalPrimAccessError(Usd_PrimData const *p);
bool Usd_IsDead(Usd_PrimData const *p);

// convenience typedefs for raw ptrs.
typedef Usd_PrimData *Usd_PrimDataPtr;
typedef const Usd_PrimData *Usd_PrimDataConstPtr;

// convenience typedefs for intrusive_ptr.
typedef boost::intrusive_ptr<Usd_PrimData> Usd_PrimDataIPtr;
typedef boost::intrusive_ptr<const Usd_PrimData> Usd_PrimDataConstIPtr;

// Private helper class that holds a reference to prim data.  UsdObject (and by
// inheritance its subclasses) hold an instance of this class.  It lets
// UsdObject detect prim expiry, and provides access to cached prim data.
class Usd_PrimDataHandle
{
public:
    // smart ptr element_type typedef.
    typedef Usd_PrimDataConstIPtr::element_type element_type;

    // Construct a null handle.
    Usd_PrimDataHandle() {}
    // Convert/construct a handle from a prim data intrusive ptr.
    Usd_PrimDataHandle(const Usd_PrimDataIPtr &primData)
        : _p(primData) {}
    // Convert/construct a handle from a prim data intrusive ptr.
    Usd_PrimDataHandle(const Usd_PrimDataConstIPtr &primData)
        : _p(primData) {}
    // Convert/construct a handle from a prim data raw ptr.
    Usd_PrimDataHandle(Usd_PrimDataPtr primData)
        : _p(Usd_PrimDataConstIPtr(primData)) {}
    // Convert/construct a handle from a prim data raw ptr.
    Usd_PrimDataHandle(Usd_PrimDataConstPtr primData)
        : _p(Usd_PrimDataConstIPtr(primData)) {}

    // Reset this handle to null.
    void reset() { _p.reset(); }

    // Swap this handle with \p other.
    void swap(Usd_PrimDataHandle &other) { _p.swap(other._p); }

    // Dereference this handle.  If USD_CHECK_ALL_PRIM_ACCESSES is defined, this
    // will issue a fatal error if the handle is invalid.
    element_type *operator->() const {
        element_type *p = _p.get();
#ifdef USD_CHECK_ALL_PRIM_ACCESSES
        if (!p || Usd_IsDead(p))
            Usd_IssueFatalPrimAccessError(p);
#endif
        return p;
    }

    // Explicit bool conversion operator. Returns \c true if this handle points
    // to a valid prim instance that is not marked dead, \c false otherwise.
    explicit operator bool() const {
        element_type *p = _p.get();
        return p && !Usd_IsDead(p);
    }

    // Return a text description of this prim data, used primarily for
    // diagnostic purposes.
    std::string GetDescription(SdfPath const &proxyPrimPath) const;

private:
    // Equality comparison.
    friend bool operator==(const Usd_PrimDataHandle &lhs,
                           const Usd_PrimDataHandle &rhs) {
        return lhs._p == rhs._p;
    }

    // Inequality comparison.
    friend bool operator!=(const Usd_PrimDataHandle &lhs,
                           const Usd_PrimDataHandle &rhs) {
        return !(lhs == rhs);
    }

    // Swap \p lhs and \p rhs.
    friend void swap(Usd_PrimDataHandle &lhs, Usd_PrimDataHandle &rhs) {
        lhs.swap(rhs);
    }

    // Provide hash_value.
    friend size_t hash_value(const Usd_PrimDataHandle &h) {
        return boost::hash_value(h._p.get());
    }

    friend element_type *get_pointer(const Usd_PrimDataHandle &h) {
        return h._p.get();
    }

    Usd_PrimDataConstIPtr _p;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_PRIM_DATA_HANDLE_H
