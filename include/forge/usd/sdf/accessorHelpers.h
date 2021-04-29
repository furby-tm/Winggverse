#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/accessorHelpers.h"
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
#ifndef FORGE_USD_SDF_ACCESSOR_HELPERS_H
#define FORGE_USD_SDF_ACCESSOR_HELPERS_H

/// \file sdf/accessorHelpers.h

#include "forge/forge.h"
#include "forge/usd/sdf/schema.h"
#include "forge/usd/sdf/spec.h"
#include "forge/usd/sdf/types.h"

// This file defines macros intended to reduce the amount of boilerplate code
// associated with adding new metadata to SdfSpec subclasses.  There's still a
// lot of files to touch, but these at least reduce the copy/paste/edit load.
//
// Prior to using these macros in the SdfSpec implementation file, define the
// following symbols:
//
// #define SDF_ACCESSOR_CLASS                    SdfSomeSpec
// #define SDF_ACCESSOR_READ_PREDICATE(key_)     _CanRead(key_)
// #define SDF_ACCESSOR_WRITE_PREDICATE(key_)    _CanWrite(key_)
//
// ...where _CanRead and _CanWrite are member functions of the specified class,
// with the signature 'bool _fn_(const TfToken&)'.  If either accessor predicate
// is unnecessary, #define the corresponding symbol to 'SDF_NO_PREDICATE'.
//
// Also, please observe good form and #undef the symbols after instancing the
// accessor macros.

FORGE_NAMESPACE_BEGIN

// "Helper" macros
#define _GET_KEY_(key_)     key_
#define SDF_NO_PREDICATE    true

#define _GET_WITH_FALLBACK(key_, heldType_)                                    \
    {                                                                          \
        typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;               \
        const VtValue& value = _Helper::GetField(this, key_);                  \
        if (value.IsEmpty() || !value.IsHolding<heldType_>()) {                \
            const SdfSchemaBase& schema = _Helper::GetSchema(this);            \
            return schema.GetFallback(_GET_KEY_(key_)).Get<heldType_>();       \
        }                                                                      \
        else {                                                                 \
            return value.Get<heldType_>();                                     \
        }                                                                      \
    }

// Accessor methods for "simple type" values: Get, Is, Set, Has, Clear
// Usually the client will utilize one of the combination macros (below).

#define SDF_DEFINE_GET(name_, key_, heldType_)                                 \
heldType_                                                                      \
SDF_ACCESSOR_CLASS::Get ## name_() const                                       \
{                                                                              \
    if (SDF_ACCESSOR_READ_PREDICATE(_GET_KEY_(key_))) {                        \
        /* Empty clause needed to prevent compiler complaints */               \
    }                                                                          \
                                                                               \
    _GET_WITH_FALLBACK(key_, heldType_);                                       \
}

#define SDF_DEFINE_IS(name_, key_)                                             \
bool                                                                           \
SDF_ACCESSOR_CLASS::Is ## name_() const                                        \
{                                                                              \
    if (!SDF_ACCESSOR_READ_PREDICATE(_GET_KEY_(key_))) {                       \
        return false;                                                          \
    }                                                                          \
                                                                               \
    _GET_WITH_FALLBACK(key_, bool);                                            \
}

#define SDF_DEFINE_SET(name_, key_, argType_)                                  \
void                                                                           \
SDF_ACCESSOR_CLASS::Set ## name_(argType_ value)                               \
{                                                                              \
    if (SDF_ACCESSOR_WRITE_PREDICATE(_GET_KEY_(key_))) {                       \
        typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;               \
        _Helper::SetField(this, _GET_KEY_(key_), value);                       \
    }                                                                          \
}

#define SDF_DEFINE_HAS(name_, key_)                                            \
bool                                                                           \
SDF_ACCESSOR_CLASS::Has ## name_() const                                       \
{                                                                              \
    typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;                   \
    return SDF_ACCESSOR_READ_PREDICATE(_GET_KEY_(key_)) ?                      \
        _Helper::HasField(this, _GET_KEY_(key_)) : false;                      \
}

#define SDF_DEFINE_CLEAR(name_, key_)                                          \
void                                                                           \
SDF_ACCESSOR_CLASS::Clear ## name_()                                           \
{                                                                              \
    typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;                   \
    if (SDF_ACCESSOR_WRITE_PREDICATE(_GET_KEY_(key_))) {                       \
        _Helper::ClearField(this, _GET_KEY_(key_));                            \
    }                                                                          \
}

// Accessor methods similar to the above, but intended for private use in
// the SdSpec classes.

#define SDF_DEFINE_GET_PRIVATE(name_, key_, heldType_)                         \
heldType_                                                                      \
SDF_ACCESSOR_CLASS::_Get ## name_() const                                      \
{                                                                              \
    if (SDF_ACCESSOR_READ_PREDICATE(_GET_KEY_(key_))) {                        \
        /* Empty clause needed to prevent compiler complaints */               \
    }                                                                          \
                                                                               \
    _GET_WITH_FALLBACK(key_, heldType_);                                       \
}

// Accessor methods for VtDictionary types, utilizing SdDictionaryProxy for the
// 'Get' accessors.  Due to unusual naming in the original SdSpec API, these
// macros accept/require explicit accessor method names.  Dammit.
#define SDF_DEFINE_DICTIONARY_GET(name_, key_)                                 \
SdfDictionaryProxy                                                             \
SDF_ACCESSOR_CLASS::name_() const                                              \
{                                                                              \
    typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;                   \
    return SDF_ACCESSOR_READ_PREDICATE(_GET_KEY_(key_)) ?                      \
        SdfDictionaryProxy(_Helper::GetSpecHandle(this), _GET_KEY_(key_)) :    \
        SdfDictionaryProxy();                                                  \
}

#define SDF_DEFINE_DICTIONARY_SET(name_, key_)                                 \
void                                                                           \
SDF_ACCESSOR_CLASS::name_(                                                     \
    const std::string& name,                                                   \
    const VtValue& value)                                                      \
{                                                                              \
    typedef Sdf_AccessorHelpers<SDF_ACCESSOR_CLASS> _Helper;                   \
    if (SDF_ACCESSOR_WRITE_PREDICATE(_GET_KEY_(key_))) {                       \
        SdfDictionaryProxy proxy(                                              \
            _Helper::GetSpecHandle(this), _GET_KEY_(key_));                    \
        if (value.IsEmpty()) {                                                 \
            proxy.erase(name);                                                 \
        }                                                                      \
        else {                                                                 \
            proxy[name] = value;                                               \
        }                                                                      \
    }                                                                          \
}

// Convenience macros to provide common combinations of value accessors

#define SDF_DEFINE_TYPED_GET_SET(name_, key_, getType_, setType_)              \
SDF_DEFINE_GET(name_, key_, getType_)                                          \
SDF_DEFINE_SET(name_, key_, setType_)

#define SDF_DEFINE_TYPED_GET_SET_HAS_CLEAR(name_, key_, getType_, setType_)    \
SDF_DEFINE_TYPED_GET_SET(name_, key_, getType_, setType_)                      \
SDF_DEFINE_HAS(name_, key_)                                                    \
SDF_DEFINE_CLEAR(name_, key_)

#define SDF_DEFINE_GET_SET(name_, key_, type_)                                 \
SDF_DEFINE_TYPED_GET_SET(name_, key_, type_,                                   \
                         boost::call_traits<type_>::param_type)

#define SDF_DEFINE_GET_SET_HAS_CLEAR(name_, key_, type_)                       \
SDF_DEFINE_TYPED_GET_SET_HAS_CLEAR(name_, key_, type_,                         \
                                   boost::call_traits<type_>::param_type)

#define SDF_DEFINE_IS_SET(name_, key_)                                         \
SDF_DEFINE_IS(name_, key_)                                                     \
SDF_DEFINE_SET(name_, key_, bool)

#define SDF_DEFINE_DICTIONARY_GET_SET(getName_, setName_, key_)                \
SDF_DEFINE_DICTIONARY_GET(getName_, key_)                                      \
SDF_DEFINE_DICTIONARY_SET(setName_, key_)

// Implementation details
// The helper macros above can be used in the implementation of a spec
// class or a spec API class (see declareSpec.h for details). Both cases
// access data in a different way -- spec classes can query their data
// members directly, while spec API classes need to query their associated
// spec. These templates capture those differences.

template <class T,
          bool IsForSpec = boost::is_base_of<SdfSpec, T>::value>
struct Sdf_AccessorHelpers;

template <class T>
struct Sdf_AccessorHelpers<T, true>
{
    static const SdfSchemaBase& GetSchema(const T* spec)
    { return spec->GetSchema(); }

    static VtValue GetField(const T* spec, const TfToken& key)
    { return spec->GetField(key); }

    template <class V>
    static bool SetField(T* spec, const TfToken& key, const V& value)
    { return spec->SetField(key, value); }

    static bool HasField(const T* spec, const TfToken& key)
    { return spec->HasField(key); }

    static void ClearField(T* spec, const TfToken& key)
    { spec->ClearField(key); }

    static SdfSpecHandle GetSpecHandle(const T* spec)
    { return SdfCreateNonConstHandle(spec); }
};

template <class T>
struct Sdf_AccessorHelpers<T, false>
{
    static const SdfSchemaBase& GetSchema(const T* spec)
    { return spec->_GetSpec().GetSchema(); }

    static VtValue GetField(const T* spec, const TfToken& key)
    { return spec->_GetSpec().GetField(key); }

    template <class V>
    static bool SetField(T* spec, const TfToken& key, const V& value)
    { return spec->_GetSpec().SetField(key, value); }

    static bool HasField(const T* spec, const TfToken& key)
    { return spec->_GetSpec().HasField(key); }

    static void ClearField(T* spec, const TfToken& key)
    { spec->_GetSpec().ClearField(key); }

    static SdfSpecHandle GetSpecHandle(const T* spec)
    { return SdfCreateNonConstHandle(&(spec->_GetSpec())); }
};

FORGE_NAMESPACE_END

#endif  // #ifndef FORGE_USD_SDF_ACCESSOR_HELPERS_H