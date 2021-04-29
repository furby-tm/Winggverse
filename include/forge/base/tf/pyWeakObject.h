#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyWeakObject.h"
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
#ifndef FORGE_BASE_TF_PY_WEAK_OBJECT_H
#define FORGE_BASE_TF_PY_WEAK_OBJECT_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyIdentity.h"

#include "forge/base/tf/hash.h"
#include "forge/base/tf/singleton.h"
#include "forge/base/tf/weakBase.h"
#include "forge/base/tf/weakPtr.h"

#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>

#include "forge/base/tf/hashmap.h"

FORGE_NAMESPACE_BEGIN

typedef TfWeakPtr<struct Tf_PyWeakObject> Tf_PyWeakObjectPtr;

// A weak pointable weak reference to a python object.
struct Tf_PyWeakObject : public TfWeakBase
{
public:
    typedef Tf_PyWeakObject This;

    static Tf_PyWeakObjectPtr GetOrCreate(boost::python::object const &obj);
    boost::python::object GetObject() const;
    void Delete();

private:
    explicit Tf_PyWeakObject(boost::python::object const &obj);

    boost::python::handle<> _weakRef;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_WEAK_OBJECT_H
