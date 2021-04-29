#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyObjWrapper.h"
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
#ifndef FORGE_BASE_TF_PY_OBJ_WRAPPER_H
#define FORGE_BASE_TF_PY_OBJ_WRAPPER_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"

#include <boost/functional/hash.hpp>
#include <boost/python/object_fwd.hpp>
#include <boost/python/object_operators.hpp>

#include <iosfwd>
#include <memory>

FORGE_NAMESPACE_BEGIN

/// \class TfPyObjWrapper
///
/// Boost Python object wrapper.
///
/// Provides a wrapper around boost::python::object that works correctly for the
/// following basic operations regardless of the GIL state: default construction,
/// copy construction, assignment, (in)equality comparison, hash_value(), and
/// destruction.
///
/// None of those work correctly in the presence of an unlocked GIL for
/// boost::python::object.  This class only actually acquires the GIL for default
/// construction, destruction and for some (in)equality comparisons.  The other
/// operations do not require taking the GIL.
///
/// This is primarily useful in cases where a boost::python::object might be
/// destroyed without a locked GIL by a client blind to that fact.  This occurs
/// when a registry, for example, holds type-erased objects.  If one
/// of the type-erased objects in the registry happens to hold a
/// boost::python::object, that type-erased object must be destroyed while the
/// GIL is held but it's unreasonable to require that the registry know that.
/// This class helps solve that problem.
///
/// This class also provides many of the operators that boost::python::object
/// provides, by virtue of deriving from boost::python::api::object_operators<T>.
/// However it is important to note that callers must ensure the GIL is held
/// before using these operators!
class TfPyObjWrapper
    : public boost::python::api::object_operators<TfPyObjWrapper>
{
    typedef boost::python::object object;

public:

    /// Default construct a TfPyObjWrapper holding a reference to python None.
    /// The GIL need not be held by the caller.
    TF_API TfPyObjWrapper();

    /// Construct a TfPyObjectWrapper wrapping \a obj.
    /// The GIL must be held by the caller.  Note, allowing the implicit
    /// conversion is intended here.
    TF_API TfPyObjWrapper(object obj);

    /// Underlying object access.
    /// This method returns a reference, so technically, the GIL need not be
    /// held to call this.  However, the caller is strongly advised to ensure
    /// the GIL is held, since assigning this object to another or otherwise
    /// operating on the returned object requires it.
    object const &Get() const {
        return *_objectPtr;
    }

    /// Underlying PyObject* access.
    /// This method returns a pointer, so technically, the GIL need not be
    /// held to call this. However, the caller is strongly advised to ensure
    /// the GIL is held, since assigning this object to another or otherwise
    /// operating on the returned object requires it.  The returned PyObject *
    /// is a "borrowed reference", meaning that the underlying object's
    /// reference count has not been incremented on behalf of the caller.
    TF_API PyObject *ptr() const;

    /// Produce a hash code for this object.
    /// Note that this does not attempt to hash the underlying python object,
    /// it returns a hash code that's suitable for hash-table lookup of
    /// TfPyObjWrapper instances, and does not require taking the python lock.
    friend inline size_t hash_value(TfPyObjWrapper const &o) {
        return (size_t) o.ptr();
    }

    /// Equality.
    /// Returns true if \a other refers to the same python object.
    TF_API bool operator==(TfPyObjWrapper const &other) const;

    /// Inequality.
    /// Returns false if \a other refers to the same python object.
    TF_API bool operator!=(TfPyObjWrapper const &other) const;

private:

    // Befriend object_operators to allow it access to implicit conversion to
    // boost::python::object.
    friend class boost::python::api::object_operators<TfPyObjWrapper>;
    operator object const &() const {
        return Get();
    }

    // Store a shared_ptr to a python object.
    std::shared_ptr<object> _objectPtr;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_OBJ_WRAPPER_H
