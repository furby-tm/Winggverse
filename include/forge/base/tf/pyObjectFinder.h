#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyObjectFinder.h"
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
#ifndef FORGE_BASE_TF_PY_OBJECT_FINDER_H
#define FORGE_BASE_TF_PY_OBJECT_FINDER_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyIdentity.h"

#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>

#include <typeinfo>

FORGE_NAMESPACE_BEGIN

struct Tf_PyObjectFinderBase {
    TF_API virtual ~Tf_PyObjectFinderBase();
    virtual boost::python::object Find(void const *objPtr) const = 0;
};

template <class T, class PtrType>
struct Tf_PyObjectFinder : public Tf_PyObjectFinderBase {
    virtual ~Tf_PyObjectFinder() {}
    virtual boost::python::object Find(void const *objPtr) const {
        using namespace boost::python;
        TfPyLock lock;
        void *p = const_cast<void *>(objPtr);
        PyObject *obj = Tf_PyGetPythonIdentity(PtrType(static_cast<T *>(p)));
        return obj ? object(handle<>(obj)) : object();
    }
};

TF_API
void Tf_RegisterPythonObjectFinderInternal(std::type_info const &type,
                                           Tf_PyObjectFinderBase const *finder);

template <class T, class PtrType>
void Tf_RegisterPythonObjectFinder() {
    Tf_RegisterPythonObjectFinderInternal(typeid(T),
                                          new Tf_PyObjectFinder<T, PtrType>());
}

TF_API boost::python::object
Tf_FindPythonObject(void const *objPtr, std::type_info const &type);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_OBJECT_FINDER_H
