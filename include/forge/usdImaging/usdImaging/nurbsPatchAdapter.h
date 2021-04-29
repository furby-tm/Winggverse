#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/nurbsPatchAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_NURBS_PATCH_ADAPTER_H
#define FORGE_USD_IMAGING_USD_IMAGING_NURBS_PATCH_ADAPTER_H

/// \file usdImaging/nurbsPatchAdapter.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/primAdapter.h"
#include "forge/usdImaging/usdImaging/gprimAdapter.h"

FORGE_NAMESPACE_BEGIN


/// \class UsdImagingNurbsPatchAdapter
///
/// Delegate support for UsdGeomNurbsPatch.
///
class UsdImagingNurbsPatchAdapter : public UsdImagingGprimAdapter
{
public:
    using BaseAdapter = UsdImagingGprimAdapter;

    UsdImagingNurbsPatchAdapter()
        : UsdImagingGprimAdapter()
    {}
    USDIMAGING_API
    ~UsdImagingNurbsPatchAdapter() override;

    USDIMAGING_API
    SdfPath Populate(
        UsdPrim const& prim,
        UsdImagingIndexProxy* index,
        UsdImagingInstancerContext const* instancerContext = nullptr) override;

    USDIMAGING_API
    bool IsSupported(UsdImagingIndexProxy const* index) const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    /// Thread Safe.
    USDIMAGING_API
    void TrackVariability(
        UsdPrim const& prim,
        SdfPath const& cachePath,
        HdDirtyBits* timeVaryingBits,
        UsdImagingInstancerContext const* instancerContext = nullptr)
            const override;

    USDIMAGING_API
    HdDirtyBits ProcessPropertyChange(UsdPrim const& prim,
                                      SdfPath const& cachePath,
                                      TfToken const& propertyName) override;

    // ---------------------------------------------------------------------- //
    /// \name Data access
    // ---------------------------------------------------------------------- //

    USDIMAGING_API
    VtValue GetTopology(UsdPrim const& prim,
                        SdfPath const& cachePath,
                        UsdTimeCode time) const override;

    // Override the implemetation in GprimAdapter since we don't fetch the
    // points attribute for implicit primitives.
    USDIMAGING_API
    VtValue GetPoints(
        UsdPrim const& prim,
        UsdTimeCode time) const override;

    // Used by the legacyEngine.
    USDIMAGING_API
    static VtValue GetMeshPoints(UsdPrim const& prim,
                                 UsdTimeCode time);

    // Used by the legacyEngine.
    USDIMAGING_API
    static VtValue GetMeshTopology(UsdPrim const& prim,
                                   UsdTimeCode time);
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_NURBS_PATCH_ADAPTER_H
