#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pySingleton.h"
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
#ifndef FORGE_BASE_TF_PY_SINGLETON_H
#define FORGE_BASE_TF_PY_SINGLETON_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyPtrHelpers.h"
#include "forge/base/tf/pyUtils.h"

#include "forge/base/tf/singleton.h"
#include "forge/base/tf/weakPtr.h"

#include <boost/mpl/vector/vector10.hpp>

#include <boost/python/class.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/def_visitor.hpp>
#include <boost/python/raw_function.hpp>

#include <functional>
#include <string>

FORGE_NAMESPACE_BEGIN

namespace Tf_PySingleton {

namespace bp = boost::python;

TF_API
bp::object _DummyInit(bp::tuple const & /* args */,
                      bp::dict const & /* kw */);

template <class T>
TfWeakPtr<T> GetWeakPtr(T &t) {
    return TfCreateWeakPtr(&t);
}

template <class T>
TfWeakPtr<T> GetWeakPtr(T const &t) {
    // cast away constness for python...
    return TfConst_cast<TfWeakPtr<T> >(TfCreateWeakPtr(&t));
}

template <class T>
TfWeakPtr<T> GetWeakPtr(TfWeakPtr<T> const &t) {
    return t;
}

template <typename PtrType>
PtrType _GetSingletonWeakPtr(bp::object const & /* classObj */) {
    typedef typename PtrType::DataType Singleton;
    return GetWeakPtr(Singleton::GetInstance());
}

TF_API
std::string _Repr(bp::object const &self, std::string const &prefix);

struct Visitor : bp::def_visitor<Visitor> {
    explicit Visitor(std::string const &reprPrefix = std::string()) :
        _reprPrefix(reprPrefix) {}

    friend class bp::def_visitor_access;
    template <typename CLS>
    void visit(CLS &c) const {
        typedef typename CLS::metadata::held_type PtrType;

        // Singleton implies WeakPtr.
        c.def(TfPyWeakPtr());

        // Wrap __new__ to return a weak pointer to the singleton instance.
        c.def("__new__", _GetSingletonWeakPtr<PtrType>).staticmethod("__new__");
        // Make __init__ do nothing.
        c.def("__init__", bp::raw_function(_DummyInit));

        // If they supplied a repr prefix, provide a repr implementation.
        if (!_reprPrefix.empty())
            c.def("__repr__",
                  make_function(std::bind(
                                    _Repr, std::placeholders::_1, _reprPrefix),
                                bp::default_call_policies(),
                                boost::mpl::vector2<std::string,
                                                    bp::object const &>()));
    }
private:
    std::string _reprPrefix;
};

}

TF_API
Tf_PySingleton::Visitor TfPySingleton();
TF_API
Tf_PySingleton::Visitor TfPySingleton(std::string const &reprPrefix);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_SINGLETON_H
