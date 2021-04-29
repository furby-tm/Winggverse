#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/siteUtils.h"
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
#ifndef FORGE_USD_SDF_SITE_UTILS_H
#define FORGE_USD_SDF_SITE_UTILS_H

/// \file sdf/siteUtils.h
///
/// Convenience API for working with SdfSite.
///
/// These functions simply forward to the indicated functions on SdfLayer.

#include "forge/forge.h"
#include "forge/usd/sdf/site.h"
#include "forge/usd/sdf/layer.h"
#include "forge/usd/sdf/primSpec.h"
#include "forge/usd/sdf/propertySpec.h"
#include "forge/usd/sdf/spec.h"

FORGE_NAMESPACE_BEGIN

inline
SdfSpecHandle
SdfGetObjectAtPath(const SdfSite& site)
{
    return site.layer->GetObjectAtPath(site.path);
}

inline
SdfPrimSpecHandle
SdfGetPrimAtPath(const SdfSite& site)
{
    return site.layer->GetPrimAtPath(site.path);
}

inline
SdfPropertySpecHandle
SdfGetPropertyAtPath(const SdfSite& site)
{
    return site.layer->GetPropertyAtPath(site.path);
}

inline
bool
SdfHasField(const SdfSite& site, const TfToken& field)
{
    return site.layer->HasField(site.path, field);
}

template <class T>
inline bool
SdfHasField(const SdfSite& site, const TfToken& field, T* value)
{
    return site.layer->HasField(site.path, field, value);
}

inline
const VtValue
SdfGetField(const SdfSite& site, const TfToken& field)
{
    return site.layer->GetField(site.path, field);
}

template <class T>
inline
T
SdfGetFieldAs(const SdfSite& site, const TfToken& field,
              const T& defaultValue = T())
{
    return site.layer->GetFieldAs<T>(site.path, field, defaultValue);
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_SITE_UTILS_H
