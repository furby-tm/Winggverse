#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/gprimAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_GPRIM_ADAPTER_H
#define FORGE_USD_IMAGING_USD_IMAGING_GPRIM_ADAPTER_H

/// \file usdImaging/gprimAdapter.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/primAdapter.h"

#include "forge/usd/usdGeom/xformCache.h"

FORGE_NAMESPACE_BEGIN


class UsdGeomGprim;

/// \class UsdImagingGprimAdapter
///
/// Delegate support for UsdGeomGrims.
///
/// This adapter is provided as a base class for all adapters that want basic
/// Gprim data support, such as visibility, doubleSided, extent, displayColor,
/// displayOpacity, purpose, and transform.
///
class UsdImagingGprimAdapter : public UsdImagingPrimAdapter
{
public:
    using BaseAdapter = UsdImagingPrimAdapter;

    UsdImagingGprimAdapter()
        : UsdImagingPrimAdapter()
    {}

    USDIMAGING_API
    ~UsdImagingGprimAdapter() override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    /// Thread Safe.
    USDIMAGING_API
    void TrackVariability(UsdPrim const& prim,
                          SdfPath const& cachePath,
                          HdDirtyBits* timeVaryingBits,
                          UsdImagingInstancerContext const*
                              instancerContext = nullptr) const override;

    /// Thread Safe.
    USDIMAGING_API
    void UpdateForTime(UsdPrim const& prim,
                       SdfPath const& cachePath,
                       UsdTimeCode time,
                       HdDirtyBits requestedBits,
                       UsdImagingInstancerContext const*
                           instancerContext = nullptr) const override;

    // ---------------------------------------------------------------------- //
    /// \name Change Processing
    // ---------------------------------------------------------------------- //

    USDIMAGING_API
    virtual HdDirtyBits ProcessPropertyChange(UsdPrim const& prim,
                                              SdfPath const& cachePath,
                                              TfToken const& property) override;

    USDIMAGING_API
    virtual void MarkDirty(UsdPrim const& prim,
                           SdfPath const& cachePath,
                           HdDirtyBits dirty,
                           UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkRefineLevelDirty(UsdPrim const& prim,
                                      SdfPath const& cachePath,
                                      UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkReprDirty(UsdPrim const& prim,
                               SdfPath const& cachePath,
                               UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkCullStyleDirty(UsdPrim const& prim,
                                    SdfPath const& cachePath,
                                    UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkRenderTagDirty(UsdPrim const& prim,
                                    SdfPath const& cachePath,
                                    UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkTransformDirty(UsdPrim const& prim,
                                    SdfPath const& cachePath,
                                    UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkVisibilityDirty(UsdPrim const& prim,
                                     SdfPath const& cachePath,
                                     UsdImagingIndexProxy* index) override;

    USDIMAGING_API
    virtual void MarkMaterialDirty(UsdPrim const& prim,
                                   SdfPath const& cachePath,
                                   UsdImagingIndexProxy* index) override;

    // ---------------------------------------------------------------------- //
    /// \name Utility methods
    // ---------------------------------------------------------------------- //
    /// Give derived classes an opportunity to override how we get points for
    /// a prim. This is useful for implicit primitives.
    USDIMAGING_API
    virtual VtValue GetPoints(UsdPrim const& prim,
                              UsdTimeCode time) const;

    /// Returns color, Usd interpolation token, and optionally color indices for
    /// a given prim, taking into account surface shader colors and explicitly
    /// authored color on the prim. If indices is not nullptr and the color
    /// value has indices, color will be set to the unflattened color value and
    /// indices set to the color value's indices.
    USDIMAGING_API
    static bool GetColor(UsdPrim const& prim,
                         UsdTimeCode time,
                         TfToken *interpolation,
                         VtValue *color,
                         VtIntArray *indices);

    /// Returns opacity, Usd interpolation token, and optionally opacity indices
    /// for a given prim, taking into account surface shader opacity and
    /// explicitly authored opacity on the prim. If indices is not nullptr and
    /// the opacity value has indices, opacity will be set to the unflattened
    /// opacity value and indices set to the opacity value's indices.
    USDIMAGING_API
    static bool GetOpacity(UsdPrim const& prim,
                           UsdTimeCode time,
                           TfToken *interpolation,
                           VtValue *opacity,
                           VtIntArray *indices);

    // Helper function: add a given type of rprim, potentially with instancer
    // name mangling, and add any bound shader.
    USDIMAGING_API
    SdfPath _AddRprim(TfToken const& primType,
                      UsdPrim const& usdPrim,
                      UsdImagingIndexProxy* index,
                      SdfPath const& materialUsdPath,
                      UsdImagingInstancerContext const* instancerContext);

    // Helper function: map USD path to UsdImaging cache path,
    // applying any name-encoding required by the instancerContext.
    USDIMAGING_API
    static SdfPath _ResolveCachePath(SdfPath const& usdPath,
            UsdImagingInstancerContext const* instancerContext);

    /// Reads the extent from the given prim. If the extent is not authored,
    /// an empty GfRange3d is returned, the extent will not be computed.
    USDIMAGING_API
    GfRange3d GetExtent(UsdPrim const& prim,
                        SdfPath const& cachePath,
                        UsdTimeCode time) const override;

    /// Reads double-sided from the given prim. If not authored, returns false
    USDIMAGING_API
    bool GetDoubleSided(UsdPrim const& prim,
                        SdfPath const& cachePath,
                        UsdTimeCode time) const override;

    USDIMAGING_API
    SdfPath GetMaterialId(UsdPrim const& prim,
                          SdfPath const& cachePath,
                          UsdTimeCode time) const override;
    /// Gets the value of the parameter named key for the given prim (which
    /// has the given cache path) and given time. If outIndices is not nullptr
    /// and the value has indices, it will return the unflattened value and set
    /// outIndices to the value's associated indices.
    USDIMAGING_API
    VtValue Get(UsdPrim const& prim,
                SdfPath const& cachePath,
                TfToken const& key,
                UsdTimeCode time,
                VtIntArray *outIndices) const override;

protected:

    USDIMAGING_API
    virtual void _RemovePrim(SdfPath const& cachePath,
                             UsdImagingIndexProxy* index) override;

    // Give derived classes an opportunity to block GprimAdapter processing
    // of certain primvars.
    USDIMAGING_API
    virtual bool _IsBuiltinPrimvar(TfToken const& primvarName) const;

    // Utility for derived classes to try to find an inherited primvar.
    USDIMAGING_API
    UsdGeomPrimvar _GetInheritedPrimvar(UsdPrim const& prim,
                                        TfToken const& primvarName) const;

};


FORGE_NAMESPACE_END

#endif //FORGE_USD_IMAGING_USD_IMAGING_GPRIM_ADAPTER_H
