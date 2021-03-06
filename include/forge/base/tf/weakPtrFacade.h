#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/weakPtrFacade.h"
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
#ifndef FORGE_BASE_TF_WEAK_PTR_FACADE_H
#define FORGE_BASE_TF_WEAK_PTR_FACADE_H

#include "forge/forge.h"

#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/weakBase.h"

#include "forge/base/arch/demangle.h"

#include <boost/functional/hash_fwd.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

FORGE_NAMESPACE_BEGIN

template <class U> class TfRefPtr;

template <template <class> class PtrTemplate, class DataType>
class TfWeakPtrFacade;

/// \class TfWeakPtrFacadeAccess
///
/// This access class is befriended by \c TfWeakPtrFacade -derived classes to
/// grant \c TfWeakPtrFacade access to specific internal functions provided by
/// the derived classes.
class TfWeakPtrFacadeAccess {
public:
    template <template <class> class PtrTemplate, class DataType>
    friend class TfWeakPtrFacade;

    template <class Facade>
    static typename Facade::DataType *FetchPointer(Facade const &f) {
        return f._FetchPointer();
    }

    template <class Facade>
    static void const *GetUniqueIdentifier(Facade const &f) {
        return f._GetUniqueIdentifier();
    }

    template <class Facade>
    static void EnableExtraNotification(Facade const &f) {
        return f._EnableExtraNotification();
    }

    template <class Facade>
    static bool IsInvalid(Facade const &f) {
        return f._IsInvalid();
    }

private:
    TfWeakPtrFacadeAccess();
};

// Provide an overload of get_pointer for WeakPtrFacade.  Boost libraries do
// unqualified calls to get_pointer to get the underlying pointer from a smart
// pointer, expecting the right overload will be found by ADL.
template <template <class> class X, class Y>
Y *get_pointer(TfWeakPtrFacade<X, Y> const &p) {
    return TfWeakPtrFacadeAccess::FetchPointer(p);
}

FORGE_NAMESPACE_END

// Inject the global-scope operator for clients that make qualified calls to our
// previous overload in the boost namespace.
namespace boost {
    using FORGE_NS::get_pointer;
};

FORGE_NAMESPACE_BEGIN

// Common base class, used to identify subtypes in enable_if expressions.
class TfWeakPtrFacadeBase {};

template <template <class> class PtrTemplate, class Type>
class TfWeakPtrFacade : public TfWeakPtrFacadeBase {

public:

    friend class TfWeakPtrFacadeAccess;

    typedef Type DataType;
    typedef PtrTemplate<DataType> Derived;
    typedef TfWeakPtrFacadeAccess Access;

    typedef Type element_type;

    template <class Other>
    bool operator == (PtrTemplate<Other> const &p) const {
        if (false)
            return _FetchPointer() == TfWeakPtrFacadeAccess::FetchPointer(p);
        return GetUniqueIdentifier() == p.GetUniqueIdentifier();
    }

    template <class Other>
    bool operator != (PtrTemplate<Other> const &p) const {
        return !(*this == p);
    }

    template <class T>
    bool operator == (TfRefPtr<T> const &p) const {
        if (!GetUniqueIdentifier())
            return !p;
        DataType *ptr = _FetchPointer();
        return ptr && ptr == get_pointer(p);
    }

    template <class T>
    bool operator != (TfRefPtr<T> const &p) const {
        return !(*this == p);
    }

    template <class T>
    friend bool operator == (const TfRefPtr<T>& p1, Derived const &p2) {
        return p2 == p1;
    }

    template <class T>
    friend bool operator != (const TfRefPtr<T>& p1, Derived const &p2) {
        return !(p1 == p2);
    }

    template <class Other>
    bool operator < (PtrTemplate<Other> const &p) const {
        if (false)
            return _FetchPointer() < TfWeakPtrFacadeAccess::FetchPointer(p);
        return GetUniqueIdentifier() < p.GetUniqueIdentifier();
    }

    template <class Other>
    bool operator > (PtrTemplate<Other> const &p) const {
        return !(*this < p) && !(*this == p);
    }

    template <class Other>
    bool operator <= (PtrTemplate<Other> const &p) const {
        return (*this < p) || (*this == p);
    }

    template <class Other>
    bool operator >= (PtrTemplate<Other> const &p) const {
        return !(*this < p);
    }

    using UnspecifiedBoolType = DataType * (TfWeakPtrFacade::*)(void) const;

    operator UnspecifiedBoolType () const {
        return _FetchPointer() ? &TfWeakPtrFacade::_FetchPointer : nullptr;
    }

    bool operator ! () const {
        return !(bool(*this));
    }

    template <class T>
    bool PointsTo(T const &obj) const {
        return _FetchPointer() == &obj;
    }

    /// Return true if this object points to an object of type \a T.  \a T
    /// must either be the same as or a base class of \a DataType or DataType
    /// must be polymorphic.
    template <class T>
    bool PointsToA() const {
        return dynamic_cast<T *>(_FetchPointer());
    }

    bool IsInvalid() const {
        return Access::IsInvalid(_Derived());
    }

    void const *GetUniqueIdentifier() const {
        return Access::GetUniqueIdentifier(_Derived());
    }

    TfWeakBase const *GetWeakBase() const {
        return &_Derived()->__GetTfWeakBase__();
    }

    void EnableExtraNotification() const {
        Access::EnableExtraNotification(_Derived());
    }

    DataType *operator -> () const {
        DataType *ptr = _FetchPointer();
        if (ARCH_LIKELY(ptr)) {
            return ptr;
        }
        static const TfCallContext ctx(TF_CALL_CONTEXT);
        Tf_PostNullSmartPtrDereferenceFatalError(ctx, typeid(Derived));
    }

    DataType &operator * () const {
        return * operator->();
    }

    /// Reset this pointer to point at no object. Equivalent to assignment
    /// with \a TfNullPtr.
    void Reset() {
        _Derived() = TfNullPtr;
    }

private:

    friend std::type_info const &TfTypeid(Derived const &p) {
        if (ARCH_UNLIKELY(!p))
            TF_FATAL_ERROR("Called TfTypeid on invalid %s",
                           ArchGetDemangled(typeid(Derived)).c_str());
        return typeid(*get_pointer(p));
    }

    DataType *_FetchPointer() const {
        return Access::FetchPointer(_Derived());
    }

    Derived &_Derived() {
        return static_cast<Derived &>(*this);
    }

    Derived const &_Derived() const {
        return static_cast<Derived const &>(*this);
    }

};


/// \section nullptr comparisons
///@{
///
/// These are provided both to avoid ambiguous overloads due to
/// TfWeakPtrFacade::Derived comparisons with TfRefPtr and because implicitly
/// converting a nullptr to a TfWeakPtrFacade-derived type can add an unknown
/// amount of overhead.
///

template <template <class> class X, class Y>
inline bool operator== (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return !p;
}
template <template <class> class X, class Y>
inline bool operator== (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return !p;
}

template <template <class> class X, class Y>
inline bool operator!= (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return !(p == nullptr);
}
template <template <class> class X, class Y>
inline bool operator!= (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return !(nullptr == p);
}

template <template <class> class X, class Y>
inline bool operator< (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return std::less<void const *>()(p.GetUniqueIdentifier(), nullptr);
}
template <template <class> class X, class Y>
inline bool operator< (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return std::less<void const *>()(nullptr, p.GetUniqueIdentifier());
}

template <template <class> class X, class Y>
inline bool operator<= (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return !(nullptr < p);
}
template <template <class> class X, class Y>
inline bool operator<= (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return !(p < nullptr);
}

template <template <class> class X, class Y>
inline bool operator> (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return nullptr < p;
}
template <template <class> class X, class Y>
inline bool operator> (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return p < nullptr;
}

template <template <class> class X, class Y>
inline bool operator>= (TfWeakPtrFacade<X, Y> const &p, std::nullptr_t)
{
    return !(p < nullptr);
}
template <template <class> class X, class Y>
inline bool operator>= (std::nullptr_t, TfWeakPtrFacade<X, Y> const &p)
{
    return !(nullptr < p);
}

///@}

template <class ToPtr, template <class> class X, class Y>
ToPtr TfDynamic_cast(TfWeakPtrFacade<X, Y> const &p) {
    return ToPtr(dynamic_cast<typename ToPtr::DataType *>
                 (get_pointer(p)));
}

template <class ToPtr, template <class> class X, class Y>
ToPtr TfSafeDynamic_cast(TfWeakPtrFacade<X, Y> const &p) {
    return ToPtr(TfSafeDynamic_cast<typename ToPtr::DataType *>
                 (get_pointer(p)));
}

template <class ToPtr, template <class> class X, class Y>
ToPtr TfStatic_cast(TfWeakPtrFacade<X, Y> const &p) {
    return ToPtr(static_cast<typename ToPtr::DataType *>
                 (get_pointer(p)));
}

template <class ToPtr, template <class> class X, class Y>
ToPtr TfConst_cast(TfWeakPtrFacade<X, Y> const &p) {
    return ToPtr(const_cast<typename ToPtr::DataType *>
                 (get_pointer(p)));
}

//
// This is the implementation; the declaration and doxygen
// is in refPtr.h.
//
// If _remnant itself is NULL, then wp doesn't point to anything.
//

template <class T>
template <template <class> class X, class U>
inline TfRefPtr<T>::TfRefPtr(const TfWeakPtrFacade<X, U>& p,
                             typename boost::enable_if<
                                 boost::is_convertible<U*, T*>
                             >::type *dummy)
    : _refBase(get_pointer(p))
{
    _AddRef();
    Tf_RefPtrTracker_New(this, _GetObjectForTracking());
}

//
// See typeFunctions.h for documention.
//
template <template <class> class Ptr, class T>
struct TfTypeFunctions<Ptr<T>,
                       typename boost::enable_if<
                           boost::is_base_of<TfWeakPtrFacadeBase, Ptr<T> >
                           >::type>
{
    static T* GetRawPtr(const Ptr<T>& t) {
        return get_pointer(t);
    }

    static Ptr<T> ConstructFromRawPtr(T* ptr) {
        return Ptr<T>(ptr);
    }

    static bool IsNull(const Ptr<T>& t) {
        return !t;
    }

    static void Class_Object_MUST_Be_Passed_By_Address() { }
    static void Class_Object_MUST_Not_Be_Const() { }
};

template <template <class> class Ptr, class T>
struct TfTypeFunctions<Ptr<const T>,
                       typename boost::enable_if<
                           boost::is_base_of<TfWeakPtrFacadeBase, Ptr<const T> >
                           >::type>
{
    static const T* GetRawPtr(const Ptr<const T>& t) {
        return get_pointer(t);
    }

    static Ptr<const T> ConstructFromRawPtr(const T* ptr) {
        return Ptr<const T>(ptr);
    }

    static bool IsNull(const Ptr<const T>& t) {
        return !t;
    }

    static void Class_Object_MUST_Be_Passed_By_Address() { }
};

// TfHash support.
template <class HashState, template <class> class X, class T>
inline void
TfHashAppend(HashState &h, TfWeakPtrFacade<X, T> const &ptr)
{
    return h.Append(ptr.GetUniqueIdentifier());
}

// Extend boost::hash to support TfWeakPtrFacade.
template <template <class> class X, class T>
inline size_t
hash_value(TfWeakPtrFacade<X, T> const &ptr)
{
    // Make the boost::hash type depend on T so that we don't have to always
    // include boost/functional/hash.hpp in this header for the definition of
    // boost::hash.
    auto uniqueId = ptr.GetUniqueIdentifier();
    return boost::hash<decltype(uniqueId)>()(uniqueId);
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_WEAK_PTR_FACADE_H
