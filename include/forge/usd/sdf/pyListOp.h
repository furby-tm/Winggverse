#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/pyListOp.h"
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
#ifndef FORGE_USD_SDF_PY_LIST_OP_H
#define FORGE_USD_SDF_PY_LIST_OP_H

#include "forge/forge.h"
#include "forge/usd/sdf/listOp.h"
#include "forge/base/arch/demangle.h"
#include "forge/base/tf/pyUtils.h"
#include "forge/base/tf/stringUtils.h"
#include <boost/python.hpp>

FORGE_NAMESPACE_BEGIN

/// \class SdfPyWrapListOp
///
/// Helper class for wrapping SdfListOp objects for Python. The template
/// parameter is the specific SdfListOp type being wrapped (e.g.,
/// SdfPathListOp)
///
template <class T>
class SdfPyWrapListOp {
public:
    typedef typename T::ItemType   ItemType;
    typedef typename T::ItemVector ItemVector;

    typedef SdfPyWrapListOp<T> This;

    SdfPyWrapListOp(const std::string& name)
    {
        TfPyWrapOnce<T>([name]() { SdfPyWrapListOp::_Wrap(name); });
    }

private:
    static ItemVector _ApplyOperations1(const T& listOp, ItemVector input) {
        ItemVector result = input;
        listOp.ApplyOperations(&result);
        return result;
    }
    static boost::python::object
    _ApplyOperations2(const T& outer, const T& inner) {
        if (boost::optional<T> r = outer.ApplyOperations(inner)) {
            return boost::python::object(*r);
        } else {
            return boost::python::object();
        }
    }

    static void _Wrap(const std::string& name)
    {
        using namespace boost::python;

        using ItemVector = typename T::ItemVector;

        class_<T>(name.c_str())
            .def("__str__", &This::_GetStr)

            .def("Create", &T::Create,
                 (arg("prependedItems") = ItemVector(),
                  arg("appendedItems") = ItemVector(),
                  arg("deletedItems") = ItemVector()))
            .staticmethod("Create")

            .def("CreateExplicit", &T::CreateExplicit,
                 (arg("explicitItems") = ItemVector()))
            .staticmethod("CreateExplicit")

            .def(self == self)
            .def(self != self)

            .def("HasItem", &T::HasItem)

            .def("Clear", &T::Clear)
            .def("ClearAndMakeExplicit", &T::ClearAndMakeExplicit)
            .def("ApplyOperations", &This::_ApplyOperations1)
            .def("ApplyOperations", &This::_ApplyOperations2)

            .add_property("explicitItems",
                make_function(&T::GetExplicitItems,
                              return_value_policy<return_by_value>()),
                &T::SetExplicitItems)
            .add_property("addedItems",
                make_function(&T::GetAddedItems,
                              return_value_policy<return_by_value>()),
                &T::SetAddedItems)
            .add_property("prependedItems",
                make_function(&T::GetPrependedItems,
                              return_value_policy<return_by_value>()),
                &T::SetPrependedItems)
            .add_property("appendedItems",
                make_function(&T::GetAppendedItems,
                              return_value_policy<return_by_value>()),
                &T::SetAppendedItems)
            .add_property("deletedItems",
                make_function(&T::GetDeletedItems,
                              return_value_policy<return_by_value>()),
                &T::SetDeletedItems)
            .add_property("orderedItems",
                make_function(&T::GetOrderedItems,
                              return_value_policy<return_by_value>()),
                &T::SetOrderedItems)
            .def("GetAddedOrExplicitItems",
                &This::_GetAddedOrExplicitItems)

            .add_property("isExplicit", &T::IsExplicit)

            ;

    }

    static std::string _GetStr(const T& listOp)
    {
        return TfStringify(listOp);
    }

    static
    ItemVector _GetAddedOrExplicitItems(const T& listOp)
    {
        ItemVector result;
        listOp.ApplyOperations(&result);
        return result;
    }

};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PY_LIST_OP_H
