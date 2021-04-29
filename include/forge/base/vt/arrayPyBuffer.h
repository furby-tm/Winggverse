#line 1 "C:/Users/tyler/dev/WINGG/forge/base/vt/arrayPyBuffer.h"
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
#ifndef FORGE_BASE_VT_ARRAY_PY_BUFFER_H
#define FORGE_BASE_VT_ARRAY_PY_BUFFER_H

#include "forge/forge.h"
#include "forge/base/vt/api.h"
#include "forge/base/vt/array.h"
#include "forge/base/tf/pyObjWrapper.h"

#include <boost/optional.hpp>

FORGE_NAMESPACE_BEGIN

/// Convert \p obj which should support the python buffer protocol (e.g. a
/// numpy array) to a VtArray if possible and return it.  Return empty
/// optional if \p obj does not support the buffer protocol or does not have
/// compatible type and dimensions.  If \p err is supplied, set it to an
/// explanatory message in case of conversion failure.  This function may be
/// invoked for VtArray<T> where T is one of VT_ARRAY_PYBUFFER_TYPES.
template <class T>
boost::optional<VtArray<T> >
VtArrayFromPyBuffer(TfPyObjWrapper const &obj, std::string *err=nullptr);

/// The set of types for which it's valid to call VtArrayFromPyBuffer().
#define VT_ARRAY_PYBUFFER_TYPES                 \
    VT_BUILTIN_NUMERIC_VALUE_TYPES              \
    VT_VEC_VALUE_TYPES                          \
    VT_MATRIX_VALUE_TYPES                       \
    VT_GFRANGE_VALUE_TYPES                      \
    ((GfRect2i, Rect2i))                        \
    ((GfQuath, Quath))                          \
    ((GfQuatf, Quatf))                          \
    ((GfQuatd, Quatd))


FORGE_NAMESPACE_END

#endif // FORGE_BASE_VT_ARRAY_PY_BUFFER_H
