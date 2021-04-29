#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/instancerContext.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_INSTANCER_CONTEXT_H
#define FORGE_USD_IMAGING_USD_IMAGING_INSTANCER_CONTEXT_H

/// \file usdImaging/instancerContext.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN


using UsdImagingPrimAdapterSharedPtr =
    std::shared_ptr<class UsdImagingPrimAdapter>;

/// \class UsdImagingInstancerContext
///
/// Object used by instancer prim adapters to pass along context
/// about the instancer and instance prim to prototype prim adapters.
///
class UsdImagingInstancerContext
{
public:
    /// The cachePath of the instancer.
    SdfPath instancerCachePath;

    /// The name of the child prim, typically used for prototypes.
    TfToken childName;

    /// The USD path to the material bound to the instance prim
    /// being processed.
    SdfPath instancerMaterialUsdPath;

    /// The draw mode bound to the instance prim being processed.
    TfToken instanceDrawMode;

    // The inheritable purpose bound to the instance prim being processed. If
    // the instance prim can provide this, prototypes without an explicit or
    // inherited purpose will inherit this purpose from the instance.
    TfToken instanceInheritablePurpose;

    /// The instancer's prim Adapter. Useful when an adapter is needed, but the
    /// default adapter may be overridden for the sake of instancing.
    UsdImagingPrimAdapterSharedPtr instancerAdapter;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_INSTANCER_CONTEXT_H
