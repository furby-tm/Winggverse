#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyPolymorphic.h"
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
#ifndef FORGE_BASE_TF_PY_POLYMORPHIC_H
#define FORGE_BASE_TF_PY_POLYMORPHIC_H

/// \file tf/pyPolymorphic.h

#include "forge/forge.h"

#include "forge/base/tf/pyOverride.h"

#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/pyCall.h"
#include "forge/base/tf/pyLock.h"
#include "forge/base/tf/type.h"

#include <boost/python/object/class_detail.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/type_traits.hpp>
#include <boost/python/has_back_reference.hpp>

#include <functional>
#include <type_traits>

// TODO: All this stuff with holding onto the class needs to go away.

FORGE_NAMESPACE_BEGIN

template <typename Derived>
struct TfPyPolymorphic :
    public TfType::PyPolymorphicBase,
    public boost::python::wrapper<Derived>
{
    typedef TfPyPolymorphic<Derived> This;
    typedef TfPyOverride Override;

    Override GetOverride(char const *func) const {
        TfPyLock pyLock;

        using namespace boost::python;

        // don't use boost::python::wrapper::get_override(), as it can return
        // the wrong result. instead, implement our own version which does
        // better

        PyObject * m_self = detail::wrapper_base_::get_owner(*this);
        if (m_self) {

            // using pythons mro, get the attribute string that represents
            // the named function. this will return something valid if it exists
            // in this or any ancestor class
            if (handle<> m = handle<>(
                    allow_null(
                        PyObject_GetAttrString(
                            m_self, const_cast<char*>(func))))
            )
            {
                // now get the typehandle to the class. we will use this to
                // determine if this method exists on the derived class
                type_handle typeHandle =
                    objects::registered_class_object(
                        typeid(Derived));
                PyTypeObject* class_object = typeHandle.get();

                PyObject* func_object = 0;

                if (
                    PyMethod_Check(m.get())
                    && ((PyMethodObject*)m.get())->im_self == m_self
                    && class_object->tp_dict != 0
                )
                {
                    // look for the method on the class object.
                    handle<> borrowed_f(
                        allow_null(
                            PyObject_GetAttrString(
                                (PyObject *)class_object,
                                const_cast<char*>(func))));

                    // Don't leave an exception if there's no base class method
                    PyErr_Clear();

                    // do the appropriate conversion, if possible
                    if (borrowed_f && PyMethod_Check(borrowed_f.get())) {
                        func_object =
                            ((PyMethodObject*)borrowed_f.get())->im_func;
                    }
                }

                // now, func_object is either NULL, or pointing at the method
                // on the class or one of it's ancestors. m is holding the
                // actual method that pythons mro would find. if that thing
                // is not the same, it must be an override
                if (func_object != ((PyMethodObject*)m.get())->im_func)
                    return Override(m);
            }
        }
        PyErr_Clear();  // Don't leave an exception if there's no override.

        return Override(handle<>(detail::none()));
    }

    Override GetPureOverride(char const *func) const {
        TfPyLock pyLock;
        Override ret = GetOverride(func);
        if (!ret) {
            // Raise a *python* exception when no virtual is found.  This is
            // because a subsequent attempt to call ret will result in a python
            // exception, but a far less useful one.  If we were to simply make
            // a TfError here, it would be trumped by that python exception.
            PyErr_SetString(PyExc_AttributeError, TfStringPrintf
                            ("Pure virtual method '%s' called -- "
                             "must provide a python implementation.",
                             func).c_str());
            TfPyConvertPythonExceptionToTfErrors();
        }
        return ret;
    }

    template <typename Ret>
    TfPyCall<Ret> CallPureVirtual(char const *func) const {
        TfPyLock lock;
        return TfPyCall<Ret>(GetPureOverride(func));
    }

    template <class Ret, class Cls, typename... Arg>
    std::function<Ret (Arg...)>
    CallVirtual(
        char const *fname,
        Ret (Cls::*defaultImpl)(Arg...));

    template <class Ret, class Cls, typename... Arg>
    std::function<Ret (Arg...)>
    CallVirtual(
        char const *fname,
        Ret (Cls::*defaultImpl)(Arg...) const) const;

protected:
    virtual ~TfPyPolymorphic();

private:

    // Helper to bind a pointer-to-member-function and a pointer to an
    // instance.
    template <class Ret, class Cls, typename... Args>
    struct _BindMemFn
    {
        using MemFn = typename std::conditional<
            std::is_const<Cls>::value,
            Ret (Cls::*)(Args...) const, Ret (Cls::*)(Args...)>::type;

        _BindMemFn(MemFn memFn, Cls *obj)
            : _memFn(memFn)
            , _obj(obj)
        {}

        Ret
        operator()(Args... args) const
        {
            return (_obj->*_memFn)(args...);
        }

    private:
        MemFn _memFn;
        Cls *_obj;
    };
};

template <typename Derived>
TfPyPolymorphic<Derived>::~TfPyPolymorphic()
{
}

template <typename Derived>
template <class Ret, class Cls, typename... Args>
inline
std::function<Ret (Args...)>
TfPyPolymorphic<Derived>::CallVirtual(
    char const *fname,
    Ret (Cls::*defaultImpl)(Args...))
{
    static_assert(std::is_base_of<This, Cls>::value,
                  "This must be a base of Cls.");
    TfPyLock lock;
    if (Override o = GetOverride(fname))
        return std::function<Ret (Args...)>(TfPyCall<Ret>(o));
    return _BindMemFn<Ret, Cls, Args...>(
        defaultImpl, static_cast<Cls *>(this));
}

template <typename Derived>
template <class Ret, class Cls, typename... Args>
inline
std::function<Ret (Args...)>
TfPyPolymorphic<Derived>::CallVirtual(
    char const *fname,
    Ret (Cls::*defaultImpl)(Args...) const) const
{
    static_assert(std::is_base_of<This, Cls>::value,
                  "This must be a base of Cls.");
    TfPyLock lock;
    if (Override o = GetOverride(fname))
        return std::function<Ret (Args...)>(TfPyCall<Ret>(o));
    return _BindMemFn<Ret, Cls const, Args...>(
        defaultImpl, static_cast<Cls const *>(this));
}

FORGE_NAMESPACE_END

// Specialize has_back_reference<> so that boost.python will pass
// PyObject* as the 1st argument to TfPyPolymorphic's ctor.
namespace boost { namespace python {
    template <typename T>
    struct has_back_reference< FORGE_NS::TfPyPolymorphic<T> >
        : mpl::true_ {};
}} // end namespace boost

FORGE_NAMESPACE_BEGIN

// Base case for internal Tf_PyMemberFunctionPointerUpcast.
template <typename Base, typename Fn>
struct Tf_PyMemberFunctionPointerUpcast;

template <typename Base, typename Derived,
          typename Ret, typename... Args>
struct Tf_PyMemberFunctionPointerUpcast< Base, Ret (Derived::*)(Args...) >
{
    typedef Ret (Base::*Type)(Args...);
};

template <typename Base, typename Derived,
          typename Ret, typename... Args>
struct Tf_PyMemberFunctionPointerUpcast< Base, Ret (Derived::*)(Args...) const >
{
    typedef Ret (Base::*Type)(Args...) const;
};

template <typename Base, typename Fn>
typename Tf_PyMemberFunctionPointerUpcast<Base, Fn>::Type
TfPyProtectedVirtual( Fn fn )
{
    typedef typename Tf_PyMemberFunctionPointerUpcast<Base, Fn>::Type Ret;

    return static_cast<Ret>(fn);
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_POLYMORPHIC_H
