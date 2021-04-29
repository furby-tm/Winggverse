#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/wrapTypeHelpers.h"
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
#ifndef FORGE_BASE_TF_WRAP_TYPE_HELPERS_H
#define FORGE_BASE_TF_WRAP_TYPE_HELPERS_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/pyObjWrapper.h"
#include "forge/base/tf/type.h"
#include <boost/python/class.hpp>
#include <boost/python/def_visitor.hpp>

FORGE_NAMESPACE_BEGIN

// Private implementation namespace; public types are exposed below.
namespace TfType_WrapHelpers {

    using namespace boost::python;

    struct _PythonClass : def_visitor<_PythonClass>
    {
        friend class def_visitor_access;

    private:
        template <class CLS, class T>
        void _Visit(CLS &c, T *) const {
            if (TfType t = TfType::Find<T>())
                t.DefinePythonClass(c);
        }

    public:
        template <class CLS>
        void visit(CLS &c) const {
            // Use function template resolution to wrap the type
            // appropriately depending on whether it is a polymorphic
            // wrapper<> type.
            typedef typename CLS::wrapped_type Type;
            _Visit(c, detail::unwrap_wrapper((Type*)0));
        }
    };

} // namespace TfType_WrapHelpers


/// \struct TfTypePythonClass
/// A boost.python visitor that associates the Python class object created by
/// the wrapping with the TfType of the C++ type being wrapped.
///
/// Example use:
/// \code
/// class_<Foo, ...>("Foo", ...)
///     .def( TfTypePythonClass() )
/// \endcode
///
struct TfTypePythonClass : public TfType_WrapHelpers::_PythonClass {};

/// A helper for wrapping C++ types.
/// This method defines a TfType for the given python class object, and also
/// recursively defines TfTypes for all the Python bases if necessary.
TF_API TfType TfType_DefinePythonTypeAndBases( const boost::python::object & classObj );

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_WRAP_TYPE_HELPERS_H
