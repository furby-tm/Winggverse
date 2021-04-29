#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyExceptionState.h"
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

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyLock.h"
#include "forge/base/tf/errorMark.h"

#include <boost/python/handle.hpp>

FORGE_NAMESPACE_BEGIN

struct TfPyExceptionState {
    TfPyExceptionState(boost::python::handle<> const &type,
                        boost::python::handle<> const &value,
                        boost::python::handle<> const &trace) :
            _type(type), _value(value), _trace(trace) {}
    boost::python::handle<> const &GetType() const { return _type; }
    boost::python::handle<> const &GetValue() const { return _value; }
    boost::python::handle<> const &GetTrace() const { return _trace; }
    void Release() {
        _type.release();
        _value.release();
        _trace.release();
    }
    TF_API
    std::string GetExceptionString() const;
    private:
        boost::python::handle<> _type, _value, _trace;
};

FORGE_NAMESPACE_END
