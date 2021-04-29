#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/refBase.h"
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
#ifndef FORGE_BASE_TF_REF_BASE_H
#define FORGE_BASE_TF_REF_BASE_H

/// \file tf/refBase.h
/// \ingroup group_tf_Memory

#include "forge/forge.h"

#include "forge/base/tf/refCount.h"
#include "forge/base/tf/api.h"

FORGE_NAMESPACE_BEGIN

template <class T> class TfRefPtr;
template <class T> class TfWeakPtr;

/// \class TfRefBase
/// \ingroup group_tf_Memory
///
/// Enable a concrete base class for use with \c TfRefPtr.
///
/// You should be familiar with the \c TfRefPtr type before reading further.
///
/// A class (but not an interface class) is enabled for reference
/// counting via the \c TfRefPtr type by publicly deriving from \c
/// TfRefBase.
///
/// For example,
/// \code
///     #include "forge/base/tf/refPtr.h"
///
///     class Simple : public TfRefBase {
///     public:
///         TfRefPtr<Simple> New() {
///             return TfCreateRefPtr(new Simple);
///         }
///     private:
///         Simple();
///     };
/// \endcode
///
/// The class \c Simple can now only be manipulated in terms of
/// a \c TfRefPtr<Simple>.
///
/// To disable the cost of the "unique changed" system, derive
/// from TfSimpleRefBase instead.
///
class TfRefBase {
public:

    typedef void (*UniqueChangedFuncPtr)(TfRefBase const *, bool);
    struct UniqueChangedListener {
        void (*lock)();
        UniqueChangedFuncPtr func;
        void (*unlock)();
    };

    TfRefBase() : _shouldInvokeUniqueChangedListener(false) { }

    /// Return the current reference count of this object.
    size_t GetCurrentCount() const {
        return GetRefCount().Get();
    }

    /// Return true if only one \c TfRefPtr points to this object.
    bool IsUnique() const {
        return GetRefCount().Get() == 1;
    }

    const TfRefCount& GetRefCount() const {
        return _refCount;
    }

    void SetShouldInvokeUniqueChangedListener(bool shouldCall) {
        _shouldInvokeUniqueChangedListener = shouldCall;
    }

    TF_API static void SetUniqueChangedListener(UniqueChangedListener listener);

protected:
    /*
     * Prohibit deletion through a TfRefBase pointer.
     */
    TF_API virtual ~TfRefBase();

private:
    TfRefCount _refCount;
    bool _shouldInvokeUniqueChangedListener;

    static UniqueChangedListener _uniqueChangedListener;
    template <typename T> friend class TfRefPtr;
    friend struct Tf_RefPtr_UniqueChangedCounter;
    friend struct Tf_RefPtr_Counter;

    template <typename T> friend TfRefPtr<T>
    TfCreateRefPtrFromProtectedWeakPtr(TfWeakPtr<T> const &);
};

/// \class TfSimpleRefBase
/// \ingroup group_tf_Memory
///
/// Enable a concrete base class for use with \c TfRefPtr that inhibits the
/// "unique changed" facility of TfRefPtr.
///
/// Derive from this class if you don't plan on wrapping your
/// reference-counted object via boost::python.
///
class TfSimpleRefBase : public TfRefBase {
public:
    TF_API virtual ~TfSimpleRefBase();
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_REF_BASE_H
