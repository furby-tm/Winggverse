#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/refCount.h"
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
#ifndef FORGE_BASE_TF_REF_COUNT_H
#define FORGE_BASE_TF_REF_COUNT_H

/// \file tf/refCount.h
/// \ingroup group_tf_Memory

#include "forge/forge.h"

#include "forge/base/arch/inttypes.h"
#include "forge/base/tf/api.h"
#include <atomic>

FORGE_NAMESPACE_BEGIN

template <typename T> class TfRefPtr;

/// \class TfRefCount
/// \ingroup group_tf_Memory
///
/// Reference counter class
///
/// This class is intended to be embedded in other classes, for use as
/// a reference counter.  Unless you need to provide extraordinary
/// customization, you should forgo direct use of this class and instead
/// make use of the base class \c TfRefBase.
///
/// Initialization of a reference counter is somewhat counterintuitive.
/// Consider an object T with a reference counter R.  When T is
/// initialized, R should be initialized to one, even if T is
/// copy-constructed.  This implies that \e all constructors of \c
/// TfRefCount set the counter to one, even the copy constructor.
///
/// Conversely, if T is assigned to, the reference counter R in T should not
/// change.  This implies that the assignment operator for \c TfRefCount
/// does not change the counter's value.
///
/// Finally, for thread-safety, the counter should be atomic.
///
/// This class was written primarily for use in classes whose access is
/// encapsulated by means of the \c TfRefPtr interface; such classes require
/// reference counting semantics as described above.  Note that
/// the behavior of a \c TfRefCount in a class T is invariant with respect
/// to T's copy constructors and assignment operators.
///
/// Again, please do not directly embed a \c TfRefCount in a structure
/// unless the functionality of \c TfRefBase is insufficient for your needs.
///
class TfRefCount {
public:
    /// Initialize counter to one.
    TfRefCount() : _counter(1) {
    }

    /// Initialize counter to one.
    ///
    /// Even if you copy from a reference counter, you want the
    /// newly constructed counter to start at one.
    TfRefCount(const TfRefCount&) : _counter(1) {
    }

    /// Returns counter's value.
    int Get() const {
        return _counter;
    }

    /// Assignment to a reference counter has no effect.
    const TfRefCount& operator=(const TfRefCount&) const {
        return *this;
    }
private:
    /// Decrements counter by \c 1, returning true if the result is 0.
    bool _DecrementAndTestIfZero() const {
        return (--_counter == 0);
    }

    /// Adds \c amount to the count, returning the prior value.
    int _FetchAndAdd(int amount) const {
        return _counter.fetch_add(amount);
    }

private:
    mutable std::atomic<int> _counter;
    template <typename T> friend class TfRefPtr;
    friend struct Tf_RefPtr_UniqueChangedCounter;
    friend struct Tf_RefPtr_Counter;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_REF_COUNT_H
