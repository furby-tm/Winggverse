#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/volumeAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_VOLUME_ADAPTER_H
#define FORGE_USD_IMAGING_USD_IMAGING_VOLUME_ADAPTER_H

/// \file usdImaging/volumeAdapter.h

#include "forge/forge.h"
#include "forge/usd/usdVol/volume.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/primAdapter.h"
#include "forge/usdImaging/usdImaging/gprimAdapter.h"

FORGE_NAMESPACE_BEGIN

/// \class UsdImagingVolumeAdapter
///
/// Delegate support for UsdVolVolume.
///
class UsdImagingVolumeAdapter : public UsdImagingGprimAdapter {
public:
    typedef UsdImagingGprimAdapter BaseAdapter;

    UsdImagingVolumeAdapter()
        : UsdImagingGprimAdapter()
    {}
    virtual ~UsdImagingVolumeAdapter();

    virtual SdfPath Populate(UsdPrim const& prim,
                     UsdImagingIndexProxy* index,
                     UsdImagingInstancerContext const*
                     instancerContext = NULL) override;

    virtual bool IsSupported(UsdImagingIndexProxy const* index) const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //
    /// Thread Safe.
    virtual void TrackVariability(UsdPrim const& prim,
                                  SdfPath const& cachePath,
                                  HdDirtyBits* timeVaryingBits,
                                  UsdImagingInstancerContext const*
                                      instancerContext = NULL) const override;

    /// Thread Safe.
    virtual void UpdateForTime(UsdPrim const& prim,
                               SdfPath const& cachePath,
                               UsdTimeCode time,
                               HdDirtyBits requestedBits,
                               UsdImagingInstancerContext const*
                                   instancerContext = NULL) const override;

    virtual HdVolumeFieldDescriptorVector
    GetVolumeFieldDescriptors(UsdPrim const& usdPrim, SdfPath const &id,
                              UsdTimeCode time) const override;

private:
    bool _GatherVolumeData(UsdPrim const& prim,
                           UsdVolVolume::FieldMap *fieldMap) const;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_VOLUME_ADAPTER_H
