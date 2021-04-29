#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/lightAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_LIGHT_ADAPTER_H
#define FORGE_USD_IMAGING_USD_IMAGING_LIGHT_ADAPTER_H

/// \file usdImaging/lightAdapter.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/primAdapter.h"

FORGE_NAMESPACE_BEGIN


class UsdPrim;

/// \class UsdImagingLightAdapter
///
/// Base class for all lights.
///
class UsdImagingLightAdapter : public UsdImagingPrimAdapter {
public:
    typedef UsdImagingPrimAdapter BaseAdapter;

    USDIMAGING_API
    static bool IsEnabledSceneLights();

    UsdImagingLightAdapter()
        : UsdImagingPrimAdapter()
    {}

    USDIMAGING_API
    ~UsdImagingLightAdapter() override;

    USDIMAGING_API
    SdfPath Populate(UsdPrim const& prim,
                     UsdImagingIndexProxy* index,
                     UsdImagingInstancerContext const* instancerContext = NULL) override;

    USDIMAGING_API
    bool IsSupported(UsdImagingIndexProxy const* index) const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    /// Thread Safe.
    USDIMAGING_API
    void TrackVariability(UsdPrim const& prim,
                          SdfPath const& cachePath,
                          HdDirtyBits* timeVaryingBits,
                          UsdImagingInstancerContext const*
                              instancerContext = NULL) const override;


    /// Thread Safe.
    USDIMAGING_API
    void UpdateForTime(UsdPrim const& prim,
                       SdfPath const& cachePath,
                       UsdTimeCode time,
                       HdDirtyBits requestedBits,
                       UsdImagingInstancerContext const*
                           instancerContext = NULL) const override;

    // ---------------------------------------------------------------------- //
    /// \name Change Processing
    // ---------------------------------------------------------------------- //

    /// Returns a bit mask of attributes to be udpated, or
    /// HdChangeTracker::AllDirty if the entire prim must be resynchronized.
    USDIMAGING_API
    HdDirtyBits ProcessPropertyChange(UsdPrim const& prim,
                                      SdfPath const& cachePath,
                                      TfToken const& propertyName) override;

    USDIMAGING_API
    void MarkDirty(UsdPrim const& prim,
                   SdfPath const& cachePath,
                   HdDirtyBits dirty,
                   UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    void MarkTransformDirty(UsdPrim const& prim,
                            SdfPath const& cachePath,
                            UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    void MarkVisibilityDirty(UsdPrim const& prim,
                             SdfPath const& cachePath,
                             UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    void MarkLightParamsDirty(UsdPrim const& prim,
                              SdfPath const& cachePath,
                              UsdImagingIndexProxy* index) override;

    // ---------------------------------------------------------------------- //
    /// \name Utilities
    // ---------------------------------------------------------------------- //

    USDIMAGING_API
    VtValue GetMaterialResource(UsdPrim const &prim,
                                SdfPath const& cachePath,
                                UsdTimeCode time) const override;

protected:
    void _RemovePrim(SdfPath const& cachePath,
                     UsdImagingIndexProxy* index) override;

};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_LIGHT_ADAPTER_H
