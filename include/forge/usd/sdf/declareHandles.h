#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/declareHandles.h"
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
#ifndef FORGE_USD_SDF_DECLARE_HANDLES_H
#define FORGE_USD_SDF_DECLARE_HANDLES_H

/// \file sdf/declareHandles.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/base/arch/demangle.h"
#include "forge/base/arch/hints.h"
#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/weakPtrFacade.h"
#include "forge/base/tf/declarePtrs.h"

#include <set>
#include <typeinfo>
#include <type_traits>
#include <vector>
#include <boost/intrusive_ptr.hpp>
#include <boost/operators.hpp>

FORGE_NAMESPACE_BEGIN

class SdfLayer;
class SdfSpec;
template <class T> class TfRefPtr;
class Sdf_Identity;

// Sdf_Identities are held via intrusive_ptr so that we can carefully
// manage the ref-count to avoid race conditions -- see
// Sdf_IdentityRegistry::Identify().
typedef boost::intrusive_ptr<Sdf_Identity> Sdf_IdentityRefPtr;

/// \class SdfHandle
///
/// SdfHandle is a smart ptr that calls IsDormant() on the pointed-to
/// object as an extra expiration check so that dormant objects appear to
/// be expired.
///
template <class T>
class SdfHandle : private boost::totally_ordered<SdfHandle<T> > {
public:
    typedef SdfHandle<T> This;
    typedef T SpecType;

    typedef typename std::remove_const<SpecType>::type NonConstSpecType;
    typedef SdfHandle<NonConstSpecType> NonConstThis;

    SdfHandle() { }
    SdfHandle(TfNullPtrType) { }
    explicit SdfHandle(const Sdf_IdentityRefPtr& id) : _spec(id) { }
    SdfHandle(const SpecType& spec) : _spec(spec) { }

    template <class U>
    SdfHandle(const SdfHandle<U>& x) : _spec(x._spec) { }

    This& operator=(const This& x)
    {
        const_cast<NonConstSpecType&>(_spec) = x._spec;
        return *this;
    }

    template <class U>
    This& operator=(const SdfHandle<U>& x)
    {
        const_cast<NonConstSpecType&>(_spec) = x._spec;
        return *this;
    }

    /// Dereference.  Raises a fatal error if the object is invalid or
    /// dormant.
    SpecType* operator->() const
    {
        if (ARCH_UNLIKELY(_spec.IsDormant())) {
            TF_FATAL_ERROR("Dereferenced an invalid %s",
                           ArchGetDemangled(typeid(SpecType)).c_str());
            return 0;
        }
        return const_cast<SpecType*>(&_spec);
    }

    const SpecType & GetSpec() const
    {
        return _spec;
    }

    void Reset()
    {
        const_cast<SpecType&>(_spec) = SpecType();
    }

#if !defined(doxygen)
    typedef SpecType This::*UnspecifiedBoolType;
#endif

    /// Returns \c true in a boolean context if the object is valid,
    /// \c false otherwise.
    operator UnspecifiedBoolType() const
    {
        return _spec.IsDormant() ? 0 : &This::_spec;
    }
    /// Returns \c false in a boolean context if the object is valid,
    /// \c true otherwise.
    bool operator!() const
    {
        return _spec.IsDormant();
    }

    /// Compares handles for equality.
    template <class U>
    bool operator==(const SdfHandle<U>& other) const
    {
        return _spec == other._spec;
    }

    /// Arranges handles in an arbitrary strict weak ordering.  Note that
    /// this ordering is stable across path changes.
    template <class U>
    bool operator<(const SdfHandle<U>& other) const
    {
        return _spec < other._spec;
    }

    /// Hash.
    friend size_t hash_value(const This &x) {
        return hash_value(x._spec);
    }

private:
    friend
    inline SpecType *get_pointer(const SdfHandle &x) {
        return ARCH_UNLIKELY(x._spec.IsDormant()) ?
            nullptr : const_cast<SpecType*>(&x._spec);
    }

    SpecType _spec;

    template <class U> friend class SdfHandle;
};

FORGE_NAMESPACE_END

namespace boost {

using FORGE_NS::get_pointer;

}

FORGE_NAMESPACE_BEGIN

template <class T>
struct SdfHandleTo {
    typedef SdfHandle<T> Handle;
    typedef SdfHandle<const T> ConstHandle;
    typedef std::vector<Handle> Vector;
    typedef std::vector<ConstHandle> ConstVector;
};

template <>
struct SdfHandleTo<SdfLayer> {
    typedef TfWeakPtr<SdfLayer> Handle;
    typedef TfWeakPtr<const SdfLayer> ConstHandle;
    typedef std::vector<Handle> Vector;
    typedef std::vector<ConstHandle> ConstVector;
};

template <typename T>
typename SdfHandleTo<T>::Handle
SdfCreateHandle(T *p)
{
    return typename SdfHandleTo<T>::Handle(p ? *p : T());
}

template <>
SDF_API SdfHandleTo<SdfLayer>::Handle
SdfCreateHandle(SdfLayer *p);

template <typename T>
typename SdfHandleTo<T>::Handle
SdfCreateNonConstHandle(T const *p)
{
    return SdfCreateHandle(const_cast<T *>(p));
}

struct Sdf_CastAccess {
    template<class DST, class SRC>
    static DST CastSpec(const SRC& spec) {
        return DST(spec);
    }
};

SDF_API bool
Sdf_CanCastToType(
    const SdfSpec& srcSpec, const std::type_info& destType);

SDF_API bool
Sdf_CanCastToTypeCheckSchema(
    const SdfSpec& srcSpec, const std::type_info& destType);

template <class DST, class SRC>
struct Sdf_SpecTypesAreDirectlyRelated
    : std::integral_constant<bool,
        std::is_base_of<DST, SRC>::value ||
        std::is_base_of<SRC, DST>::value>
{ };

/// Convert SdfHandle<SRC> \p x to an SdfHandle<DST>. This function
/// behaves similar to a dynamic_cast. If class DST cannot represent
/// the spec pointed to be \p x, or if the classes DST and SRC are
/// not directly related to each other in the C++ type hierarchy,
/// the conversion fails and an invalid handle is returned.
///
/// XXX: The second condition in the above statement is currently untrue.
///      This function will allow casting between spec classes even if
///      they are not directly related. Doing so could lead to schema
///      mismatches and other buggy behavior.
template <typename DST, typename SRC>
inline
SdfHandle<typename DST::SpecType>
TfDynamic_cast(const SdfHandle<SRC>& x)
{
    typedef typename DST::SpecType Spec;
    typedef SdfHandle<Spec> Handle;

    if (Sdf_CanCastToType(x.GetSpec(), typeid(Spec))) {
        return Handle(Sdf_CastAccess::CastSpec<Spec,SRC>(x.GetSpec()));
    }

    return Handle();
}

template <typename DST, typename SRC>
inline
SdfHandle<typename DST::SpecType>
TfSafeDynamic_cast(const SdfHandle<SRC>& x)
{
    return TfDynamic_cast(x);
}

/// Convert SdfHandle<SRC> \p x to an SdfHandle<DST>. This function
/// behaves similar to a static_cast. No runtime checks are performed
/// to ensure the conversion is valid; it is up to the consumer to
/// ensure this.
template <typename DST, typename SRC>
inline
SdfHandle<typename DST::SpecType>
TfStatic_cast(const SdfHandle<SRC>& x)
{
    typedef typename DST::SpecType Spec;
    typedef SdfHandle<Spec> Handle;
    static_assert(Sdf_SpecTypesAreDirectlyRelated<Spec, SRC>::value,
                  "Spec and SRC must be directly related.");

    return Handle(Sdf_CastAccess::CastSpec<Spec,SRC>(x.GetSpec()));
}

template <typename T>
inline
SdfHandle<typename T::SpecType>
TfConst_cast(const SdfHandle<const typename T::SpecType>& x)
{
    return TfStatic_cast<T>(x);
}

/// Convert SdfHandle<SRC> \p x to an SdfHandle<DST>. This function is
/// similar to TfDynamic_cast, but it allows the SRC and DST spec to be
/// indirectly related, so long as the schema associated with the DST
/// spec type is a subclass of the schema associated with \p x.
template <typename DST, typename SRC>
inline
SdfHandle<typename DST::SpecType>
SdfSpecDynamic_cast(const SdfHandle<SRC>& x)
{
    typedef typename DST::SpecType Spec;
    typedef SdfHandle<Spec> Handle;

    if (Sdf_CanCastToTypeCheckSchema(x.GetSpec(), typeid(Spec))) {
        return Handle(Sdf_CastAccess::CastSpec<Spec,SRC>(x.GetSpec()));
    }

    return Handle();
}

/// Convert SdfHandle<SRC> \p x to an SdfHandle<DST>. This function is
/// similar to TfStatic_cast, but it allows the SRC and DST spec to be
/// indirectly related.
template <typename DST, typename SRC>
inline
SdfHandle<typename DST::SpecType>
SdfSpecStatic_cast(const SdfHandle<SRC>& x)
{
    typedef typename DST::SpecType Spec;
    typedef SdfHandle<Spec> Handle;
    return Handle(Sdf_CastAccess::CastSpec<Spec,SRC>(x.GetSpec()));
}

/// Convert SRC_SPEC to a DST_SPEC.
template <typename DST_SPEC, typename SRC_SPEC>
inline
DST_SPEC
SdfSpecStatic_cast(const SRC_SPEC& x)
{
    return Sdf_CastAccess::CastSpec<DST_SPEC,SRC_SPEC>(x);
}

typedef TfRefPtr<SdfLayer> SdfLayerRefPtr;
typedef std::vector<TfRefPtr<SdfLayer> > SdfLayerRefPtrVector;
typedef std::set<SdfHandleTo<SdfLayer>::Handle> SdfLayerHandleSet;

#define SDF_DECLARE_HANDLES(cls)                                         \
    typedef SdfHandleTo<class cls>::Handle cls##Handle;                  \
    typedef SdfHandleTo<class cls>::ConstHandle cls##ConstHandle;        \
    typedef SdfHandleTo<class cls>::Vector cls##HandleVector;            \
    typedef SdfHandleTo<class cls>::ConstVector cls##ConstHandleVector

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_DECLARE_HANDLES_H
