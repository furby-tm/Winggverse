#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/anyUniquePtr.h"
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
#ifndef FORGE_BASE_TF_ANY_UNIQUE_PTR_H
#define FORGE_BASE_TF_ANY_UNIQUE_PTR_H

#include "forge/forge.h"
#include "forge/base/tf/api.h"

#include <type_traits>

FORGE_NAMESPACE_BEGIN

/// A simple type-erased container that provides only destruction, moves and
/// immutable, untyped access to the held value.
///
/// There are a couple of facilities that provide fallback or default values
/// in error cases.  TfAnyUniquePtr exists to hold these oft-instantiated but
/// rarely accessed values.  As such, its design prioritizes compile-time
/// overhead over runtime performance and avoids clever metaprogramming.
/// Please resist the urge to add functionality to this class (e.g. small
/// object optimization, boost::python interoperability.)
class TfAnyUniquePtr
{
public:
    template <typename T>
    static TfAnyUniquePtr New() {
        static_assert(!std::is_array<T>::value, "Array types not supported");
        return TfAnyUniquePtr(new T());
    }

    template <typename T>
    static TfAnyUniquePtr New(T const &v) {
        static_assert(!std::is_array<T>::value, "Array types not supported");
        return TfAnyUniquePtr(new T(v));
    }

    TfAnyUniquePtr(TfAnyUniquePtr &&other)
        : _ptr(other._ptr)
        , _delete(other._delete)
    {
        other._ptr = nullptr;
        // We don't set other._delete to nullptr here on purpose.  Invoking
        // delete on a null pointer is not an error so if we can ensure that
        // _delete is never null we can call it unconditionally.
    }

    TfAnyUniquePtr& operator=(TfAnyUniquePtr &&other) {
        if (this != &other) {
            _delete(_ptr);
            _ptr = other._ptr;
            _delete = other._delete;
            other._ptr = nullptr;
        }
        return *this;
    }

    TfAnyUniquePtr(TfAnyUniquePtr const&) = delete;
    TfAnyUniquePtr& operator=(TfAnyUniquePtr const&) = delete;

    ~TfAnyUniquePtr() {
        _delete(_ptr);
    }

    /// Return a pointer to the owned object.
    void const *Get() const {
        return _ptr;
    }

private:
    template <typename T>
    explicit TfAnyUniquePtr(T const *ptr)
        : _ptr(ptr)
        , _delete(&_Delete<T>)
    {}

    template <typename T>
    static void _Delete(void const *ptr) {
        delete static_cast<T const *>(ptr);
    }

private:
    void const *_ptr;
    void (*_delete)(void const *);
};

FORGE_NAMESPACE_END

#endif
