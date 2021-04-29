#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/resolverContext_v1.h"
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
#ifndef INCLUDE_AR_RESOLVER_CONTEXT
#error This file should not be included directly. Include resolverContext.h instead
#endif

#ifndef FORGE_USD_AR_RESOLVER_CONTEXT_V1_H
#define FORGE_USD_AR_RESOLVER_CONTEXT_V1_H

/// \file ar/resolverContext_v1.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"
#include "forge/base/tf/safeTypeCompare.h"

#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

FORGE_NAMESPACE_BEGIN

/// \class ArIsContextObject
///
/// Metafunction to determine whether the templated object type is a
/// valid context object.
///
template <class T>
struct ArIsContextObject
{
    static const bool value = false;
};

/// Default implementation for providing debug info on the contained context.
template <class Context>
std::string ArGetDebugString(const Context& context);

/// \class ArResolverContext
///
/// An asset resolver context allows clients to provide additional data
/// to the resolver for use during resolution. Clients may provide this
/// data via a context object of their own (subject to restrictions below).
/// An ArResolverContext is simply a wrapper around this object that
/// allows it to be treated as a single type.
///
/// A client-defined context object must provide the following:
///   - Default and copy constructors
///   - operator<
///   - operator==
///   - An overload for size_t hash_value(const T&)
///
/// Note that the user may define a free function:
///
/// std::string ArGetDebugString(const Context& ctx);
/// (Where Context is the type of the user's path resolver context.)
///
/// This is optional; a default generic implementation has been predefined.
/// This function should return a string representation of the context
/// to be utilized for debugging purposes(such as in TF_DEBUG statements).
///
/// The ArIsContextObject template must also be specialized for this
/// object to declare that it can be used as a context object. This is to
/// avoid accidental use of an unexpected object as a context object.
/// The AR_DECLARE_RESOLVER_CONTEXT macro can be used to do this
/// as a convenience.
///
/// \sa AR_DECLARE_RESOLVER_CONTEXT
/// \sa ArResolver::BindContext
/// \sa ArResolver::UnbindContext
/// \sa ArResolverContextBinder
class ArResolverContext
{
public:
    /// Construct an empty asset resolver context.
    ArResolverContext()
    {
    }

    /// Construct a resolver context using the context object \p context.
    /// See class documentation for requirements.
    template <class Context,
              typename std::enable_if<ArIsContextObject<Context>::value>
                  ::type* = nullptr>
    ArResolverContext(const Context& context)
        : _context(new _Typed<Context>(context))
    {
    }

    /// Returns whether this context object is empty.
    bool IsEmpty() const
    {
        return !_context;
    }

    /// Return pointer to the context object held in this asset resolver
    /// context if the context is holding an object of the requested type,
    /// NULL otherwise.
    template <class Context>
    const Context* Get() const
    {
        return _context && _context->IsHolding(typeid(Context)) ?
            &_GetTyped<Context>(*_context)._context : NULL;
    }

    /// Returns a debug string representing the contained context
    std::string GetDebugString() const
    {
        return _context ? _context->GetDebugString() : std::string();
    }

    /// \name Operators
    /// @{
    bool operator==(const ArResolverContext& rhs) const
    {
        if (_context && rhs._context) {
            return (_context->IsHolding(rhs._context->GetTypeid())
                    && _context->Equals(*rhs._context));
        }
        return (!_context && !rhs._context);
    }

    bool operator!=(const ArResolverContext& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const ArResolverContext& rhs) const
    {
        if (_context && rhs._context) {
            if (_context->IsHolding(rhs._context->GetTypeid())) {
                return _context->LessThan(*rhs._context);
            }
            return (std::string(_context->GetTypeid().name()) <
                    std::string(rhs._context->GetTypeid().name()));
        }
        else if (_context && !rhs._context) {
            return false;
        }
        else if (!_context && rhs._context) {
            return true;
        }
        return false;
    }

    /// @}

    /// Returns hash value for this asset resolver context.
    friend size_t hash_value(const ArResolverContext& context)
    {
        return context._context ? context._context->Hash() : 0;
    }

private:
    // Type-erased storage for context objects.
    struct _Untyped;
    template <class Context> struct _Typed;

    template <class Context>
    static const _Typed<Context>& _GetTyped(const _Untyped& untyped)
    {
        return static_cast<const _Typed<Context>&>(untyped);
    }

    struct _Untyped
    {
        AR_API
        virtual ~_Untyped();

        bool IsHolding(const std::type_info& ti) const
        {
            return TfSafeTypeCompare(ti, GetTypeid());
        }

        virtual const std::type_info& GetTypeid() const = 0;
        virtual bool LessThan(const _Untyped& rhs) const = 0;
        virtual bool Equals(const _Untyped& rhs) const = 0;
        virtual size_t Hash() const = 0;
        virtual std::string GetDebugString() const = 0;
    };

    template <class Context>
    struct _Typed : public _Untyped
    {
        virtual ~_Typed() { }

        _Typed(const Context& context) : _context(context)
        {
        }

        virtual const std::type_info& GetTypeid() const
        {
            return typeid(Context);
        }

        virtual bool LessThan(const _Untyped& rhs) const
        {
            return _context < _GetTyped<Context>(rhs)._context;
        }

        virtual bool Equals(const _Untyped& rhs) const
        {
            return _context == _GetTyped<Context>(rhs)._context;
        }

        virtual size_t Hash() const
        {
            return hash_value(_context);
        }

        virtual std::string GetDebugString() const
        {
            return ArGetDebugString(_context);
        }

        Context _context;
    };

    std::shared_ptr<_Untyped> _context;
};


// Default implementation for streaming out held contexts.
AR_API
std::string Ar_GetDebugString(const std::type_info&, void const*);

template <class Context>
std::string ArGetDebugString(const Context& context)
{
    return Ar_GetDebugString(typeid(Context),
                             static_cast<void const*>(&context));
}

FORGE_NAMESPACE_END

#endif