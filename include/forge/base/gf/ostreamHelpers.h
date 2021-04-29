#line 1 "C:/Users/tyler/dev/WINGG/forge/base/gf/ostreamHelpers.h"
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
#ifndef FORGE_BASE_GF_OSTREAM_HELPERS_H
#define FORGE_BASE_GF_OSTREAM_HELPERS_H

/// \file gf/ostreamHelpers.h
/// \ingroup group_gf_DebuggingOutput
///
/// Helpers for Gf stream operators.
///
/// These functions are useful to help with writing stream operators for
/// Gf types.  Please do not include this file in any header.

#include "forge/forge.h"
#include "forge/base/tf/stringUtils.h"

FORGE_NAMESPACE_BEGIN

// Make the template class general so that we can use the same class
// (Gf_OstreamHelperP) on all variables and not worry about making a mistake
template <class T>
T Gf_OstreamHelperP(T v) { return v; }

inline TfStreamFloat Gf_OstreamHelperP(float v) {
    return TfStreamFloat(v);
}
inline TfStreamDouble Gf_OstreamHelperP(double v) {
    return TfStreamDouble(v);
}

FORGE_NAMESPACE_END

#endif // GF_OSTREAM_HELPERS
