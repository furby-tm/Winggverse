#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/pyListEditorProxy.h"
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
#ifndef FORGE_USD_SDF_PY_LIST_EDITOR_PROXY_H
#define FORGE_USD_SDF_PY_LIST_EDITOR_PROXY_H

/// \file sdf/pyListEditorProxy.h

#include "forge/forge.h"
#include "forge/usd/sdf/listEditorProxy.h"
#include "forge/usd/sdf/listOp.h"
#include "forge/usd/sdf/pyListProxy.h"

#include "forge/base/arch/demangle.h"
#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/pyCall.h"
#include "forge/base/tf/pyResultConversions.h"
#include "forge/base/tf/pyLock.h"
#include "forge/base/tf/pyUtils.h"
#include "forge/base/tf/stringUtils.h"
#include <boost/python.hpp>

FORGE_NAMESPACE_BEGIN

class Sdf_PyListEditorUtils {
public:
    template <class T, class V>
    class ApplyHelper {
    public:
        ApplyHelper(const T& owner, const boost::python::object& callback) :
            _owner(owner),
            _callback(callback)
        {
            // Do nothing
        }

        boost::optional<V> operator()(SdfListOpType op, const V& value)
        {
            using namespace boost::python;

            TfPyLock pyLock;
            object result = _callback(_owner, value, op);
            if (! TfPyIsNone(result)) {
                extract<V> e(result);
                if (e.check()) {
                    return boost::optional<V>(e());
                }
                else {
                    TF_CODING_ERROR("ApplyEditsToList callback has "
                                    "incorrect return type.");
                }
            }
            return boost::optional<V>();
        }

    private:
        const T& _owner;
        TfPyCall<boost::python::object> _callback;
    };

    template <class V>
    class ModifyHelper {
    public:
        ModifyHelper(const boost::python::object& callback) :
            _callback(callback)
        {
            // Do nothing
        }

        boost::optional<V> operator()(const V& value)
        {
            using namespace boost::python;

            TfPyLock pyLock;
            object result = _callback(value);
            if (! TfPyIsNone(result)) {
                extract<V> e(result);
                if (e.check()) {
                    return boost::optional<V>(e());
                }
                else {
                    TF_CODING_ERROR("ModifyItemEdits callback has "
                                    "incorrect return type.");
                }
            }
            return boost::optional<V>();
        }

    private:
        TfPyCall<boost::python::object> _callback;
    };
};

template <class T>
class SdfPyWrapListEditorProxy {
public:
    typedef T Type;
    typedef typename Type::TypePolicy TypePolicy;
    typedef typename Type::value_type value_type;
    typedef typename Type::value_vector_type value_vector_type;
    typedef typename Type::ApplyCallback ApplyCallback;
    typedef typename Type::ModifyCallback ModifyCallback;
    typedef SdfPyWrapListEditorProxy<Type> This;
    typedef SdfListProxy<TypePolicy> ListProxy;

    SdfPyWrapListEditorProxy()
    {
        TfPyWrapOnce<Type>(&This::_Wrap);
        SdfPyWrapListProxy<ListProxy>();
    }

private:
    static void _Wrap()
    {
        using namespace boost::python;

        class_<Type>(_GetName().c_str(), no_init)
            .def("__str__", &This::_GetStr)
            .add_property("isExpired", &Type::IsExpired)
            .add_property("explicitItems",
                &Type::GetExplicitItems,
                &This::_SetExplicitProxy)
            .add_property("addedItems",
                &Type::GetAddedItems,
                &This::_SetAddedProxy)
            .add_property("prependedItems",
                &Type::GetPrependedItems,
                &This::_SetPrependedProxy)
            .add_property("appendedItems",
                &Type::GetAppendedItems,
                &This::_SetAppendedProxy)
            .add_property("deletedItems",
                &Type::GetDeletedItems,
                &This::_SetDeletedProxy)
            .add_property("orderedItems",
                &Type::GetOrderedItems,
                &This::_SetOrderedProxy)
            .def("GetAddedOrExplicitItems", &Type::GetAddedOrExplicitItems,
                return_value_policy<TfPySequenceToTuple>())
            .add_property("isExplicit", &Type::IsExplicit)
            .add_property("isOrderedOnly", &Type::IsOrderedOnly)
            .def("ApplyEditsToList",
                &This::_ApplyEditsToList,
                return_value_policy<TfPySequenceToList>())
            .def("ApplyEditsToList",
                &This::_ApplyEditsToList2,
                return_value_policy<TfPySequenceToList>())

            .def("CopyItems", &Type::CopyItems)
            .def("ClearEdits", &Type::ClearEdits)
            .def("ClearEditsAndMakeExplicit", &Type::ClearEditsAndMakeExplicit)
            .def("ContainsItemEdit", &Type::ContainsItemEdit,
                 (arg("item"), arg("onlyAddOrExplicit")=false))
            .def("RemoveItemEdits", &Type::RemoveItemEdits)
            .def("ReplaceItemEdits", &Type::ReplaceItemEdits)
            .def("ModifyItemEdits", &This::_ModifyEdits)

            // New API (see bug 8710)
            .def("Add", &Type::Add)
            .def("Prepend", &Type::Prepend)
            .def("Append", &Type::Append)
            .def("Remove", &Type::Remove)
            .def("Erase", &Type::Erase)
            ;
    }

    static std::string _GetName()
    {
        std::string name = "ListEditorProxy_" +
                           ArchGetDemangled<TypePolicy>();
        name = TfStringReplace(name, " ", "_");
        name = TfStringReplace(name, ",", "_");
        name = TfStringReplace(name, "::", "_");
        name = TfStringReplace(name, "<", "_");
        name = TfStringReplace(name, ">", "_");
        return name;
    }

    static std::string _GetStr(const Type& x)
    {
        return x._listEditor ?
            boost::lexical_cast<std::string>(*x._listEditor) : std::string();
    }

    static void _SetExplicitProxy(Type& x, const value_vector_type& v)
    {
        x.GetExplicitItems() = v;
    }

    static void _SetAddedProxy(Type& x, const value_vector_type& v)
    {
        x.GetAddedItems() = v;
    }

    static void _SetPrependedProxy(Type& x, const value_vector_type& v)
    {
        x.GetPrependedItems() = v;
    }

    static void _SetAppendedProxy(Type& x, const value_vector_type& v)
    {
        x.GetAppendedItems() = v;
    }

    static void _SetDeletedProxy(Type& x, const value_vector_type& v)
    {
        x.GetDeletedItems() = v;
    }

    static void _SetOrderedProxy(Type& x, const value_vector_type& v)
    {
        x.GetOrderedItems() = v;
    }

    static value_vector_type _ApplyEditsToList(const Type& x,
                                               const value_vector_type& v)
    {
        value_vector_type tmp = v;
        x.ApplyEditsToList(&tmp);
        return tmp;
    }

    static value_vector_type _ApplyEditsToList2(const Type& x,
                                                const value_vector_type& v,
                                                const boost::python::object& cb)
    {
        value_vector_type tmp = v;
        x.ApplyEditsToList(&tmp,
            Sdf_PyListEditorUtils::ApplyHelper<Type, value_type>(x, cb));
        return tmp;
    }

    static void _ModifyEdits(Type& x, const boost::python::object& cb)
    {
        x.ModifyItemEdits(Sdf_PyListEditorUtils::ModifyHelper<value_type>(cb));
    }
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PY_LIST_EDITOR_PROXY_H
