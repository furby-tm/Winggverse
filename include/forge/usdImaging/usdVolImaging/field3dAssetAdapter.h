#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdVolImaging/field3dAssetAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_VOL_IMAGING_FIELD3D_ASSET_ADAPTER_H
#define FORGE_USD_IMAGING_USD_VOL_IMAGING_FIELD3D_ASSET_ADAPTER_H

/// \file usdImaging/field3dAssetAdapter.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/fieldAdapter.h"
#include "forge/usdImaging/usdVolImaging/api.h"

FORGE_NAMESPACE_BEGIN


class UsdPrim;

/// \class UsdImagingField3DAssetAdapter
///
/// Adapter class for fields of type Field3DAsset
///
class UsdImagingField3DAssetAdapter : public UsdImagingFieldAdapter {
public:
    using BaseAdapter = UsdImagingFieldAdapter;

    UsdImagingField3DAssetAdapter()
        : UsdImagingFieldAdapter()
    {}

    USDVOLIMAGING_API
    ~UsdImagingField3DAssetAdapter() override;

    USDVOLIMAGING_API
    VtValue Get(UsdPrim const& prim,
                SdfPath const& cachePath,
                TfToken const& key,
                UsdTimeCode time,
                VtIntArray *outIndices) const override;

    USDVOLIMAGING_API
    TfToken GetPrimTypeToken() const override;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_VOL_IMAGING_FIELD3D_ASSET_ADAPTER_H
