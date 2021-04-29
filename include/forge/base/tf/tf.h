#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/tf.h"
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
#ifndef FORGE_BASE_TF_TF_H
#define FORGE_BASE_TF_TF_H

/// \file tf/tf.h
/// A file containing basic constants and definitions.

#if defined(__cplusplus) || defined(doxygen)

#include "forge/forge.h"

#include "forge/base/arch/buildMode.h"
#include "forge/base/arch/math.h"
#include "forge/base/arch/inttypes.h"

#include <math.h>
#include <utility>

FORGE_NAMESPACE_BEGIN

// This constant will only be defined if not defined already. This is because
// many files need a higher limit and define this constant themselves before
// including anything else.

#ifndef TF_MAX_ARITY
#  define TF_MAX_ARITY 7
#endif // TF_MAX_ARITY


/// This value may be used by functions that return a \c size_t to indicate
/// that a special or error condition has occurred.
/// \ingroup group_tf_TfError
#define TF_BAD_SIZE_T SIZE_MAX

/// \addtogroup group_tf_BasicMath
///@{

/// Returns the absolute value of the given \c int value.
inline int TfAbs(int v) {
    return (v < 0 ? -v : v);
}

/// Returns the absolute value of the given \c double value.
inline double TfAbs(double v) {
    return fabs(v);
}

/// Returns the smaller of the two given \c  values.
template <class T>
inline T TfMin(const T& v1, const T& v2) {
    return (v1 < v2 ? v1 : v2);
}

/// Returns the larger of the two given \c  values.
template <class T>
inline T TfMax(const T& v1, const T& v2) {
    return (v1 > v2 ? v1 : v2);
}

///@}

/// \struct TfDeleter
/// Function object for deleting any pointer.
///
/// An STL collection of pointers does not automatically delete each
/// pointer when the collection itself is destroyed. Instead of writing
/// \code
///    for (list<Otter*>::iterator i = otters.begin(); i != otters.end(); ++i)
///         delete *i;
/// \endcode
/// you can use \c TfDeleter and simply write
/// \code
/// #include <algorithm>
///
///    for_each(otters.begin(), otters.end(), TfDeleter());
/// \endcode
///
/// \note \c TfDeleter calls the non-array version of \c delete.
/// Don't use \c TfDeleter if you allocated your space using \c new[]
/// (and consider using a \c vector<> in place of a built-in array).
/// Also, note that you need to put parenthesis after \c TfDeleter
/// in the call to \c for_each().
///
/// Finally, \c TfDeleter also works for map-like collections.
/// Note that this works as follows: if \c TfDeleter is handed
/// a datatype of type \c std::pair<T1,T2*>, then the second element
/// of the pair is deleted, but the first (whether or not it is a pointer)
/// is left alone.  In other words, if you give \c TfDeleter() a pair of
/// pointers, it only deletes the second, but never the first.  This is the
/// desired behavior for maps.
///
/// \ingroup group_tf_Stl
struct TfDeleter {
    template <class T>
    void operator() (T* t) const {
        delete t;
    }

    template <class T1, class T2>
    void operator() (std::pair<T1, T2*> p) const {
        delete p.second;
    }
};

/*
 * The compile-time constants are not part of doxygen; if you know they're here,
 * fine, but they should be used rarely, so we don't go out of our way to
 * advertise them.
 *
 * Here's the idea: you may have an axiom or conditional check which is just too
 * expensive to make part of a release build. Compilers these days will optimize
 * away expressions they can evaluate at compile-time.  So you can do
 *
 *     if (TF_DEV_BUILD)
 *         TF_AXIOM(expensiveConditional);
 *
 * to get a condition axiom.  You can even write
 *
 *     TF_AXIOM(!TF_DEV_BUILD || expensiveConditional);
 *
 * What you CANNOT do is write
 *      #if defined(TF_DEV_BUILD)
 * or
 *      #if TF_DEV_BUILD == 0
 *
 * The former compiles but always yields true; the latter doesn't compile.
 * In other words, you can change the flow of control using these constructs,
 * but we deliberately are prohibiting things like
 *
 * struct Bar {
 * #if ...
 *     int _onlyNeededForChecks;
 * #endif
 * };
 *
 * or creating functions which only show up in some builds.
 */

#define TF_DEV_BUILD ARCH_DEV_BUILD

FORGE_NAMESPACE_END

#endif // defined(__cplusplus)

/// Stops compiler from producing unused argument or variable warnings.
/// This is useful mainly in C, because in C++ you can just leave
/// the variable unnamed.  However, there are situations where this
/// can be useful even in C++, such as
/// \code
/// void
/// MyClass::Method( int foo )
/// {
/// #if defined(__APPLE__)
///     TF_UNUSED( foo );
///     // do something that doesn't need foo...
/// #else
///     // do something that needs foo
/// #endif
/// }
/// \endcode
///
/// \ingroup group_tf_TfCompilerAids
#define TF_UNUSED(x)    (void) x

#endif // TF_H