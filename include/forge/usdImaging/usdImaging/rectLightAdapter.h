#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/rectLightAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_RECT_LIGHT_ADAPTER_H
#define FORGE_USD_IMAGING_USD_IMAGING_RECT_LIGHT_ADAPTER_H

/// \file usdImaging/rectLightAdapter.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/lightAdapter.h"

FORGE_NAMESPACE_BEGIN


class UsdPrim;

/// \class UsdImagingRectLightAdapter
///
/// Adapter class for lights of type RectLight
///
class UsdImagingRectLightAdapter : public UsdImagingLightAdapter {
public:
    typedef UsdImagingLightAdapter BaseAdapter;

    UsdImagingRectLightAdapter()
        : UsdImagingLightAdapter()
    {}

    USDIMAGING_API
    virtual ~UsdImagingRectLightAdapter();

    USDIMAGING_API
    virtual SdfPath Populate(UsdPrim const& prim,
                     UsdImagingIndexProxy* index,
                     UsdImagingInstancerContext const* instancerContext = NULL);

    USDIMAGING_API
    virtual bool IsSupported(UsdImagingIndexProxy const* index) const;

protected:
    virtual void _RemovePrim(SdfPath const& cachePath,
                             UsdImagingIndexProxy* index) final;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_RECT_LIGHT_ADAPTER_H
