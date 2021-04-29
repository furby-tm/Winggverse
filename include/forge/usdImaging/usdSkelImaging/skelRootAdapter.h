#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdSkelImaging/skelRootAdapter.h"
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
#ifndef FORGE_USD_IMAGING_USD_SKEL_IMAGING_SKEL_ROOT_ADAPTER_H
#define FORGE_USD_IMAGING_USD_SKEL_IMAGING_SKEL_ROOT_ADAPTER_H

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/primAdapter.h"
#include "forge/usdImaging/usdSkelImaging/api.h"

FORGE_NAMESPACE_BEGIN

/// \class UsdImagingSkelRootAdapter
///
/// The SkelRoot adapter exists for two reasons:
/// (a) Registering the SkeletonAdapter to handle processing of any skinned
///     prim under a SkelRoot prim.
///     The UsdSkel schema requires that ANY skinned prim lives under a
///     SkelRoot.
/// (b) Getting the skeleton that deforms each skinned prim, which is stored
///     in the SkeletonAdapter (the latter is stateful).
/// Both of these happen during Populate(..)
///
class UsdSkelImagingSkelRootAdapter : public UsdImagingPrimAdapter {
public:
    using BaseAdapter = UsdImagingPrimAdapter;

    UsdSkelImagingSkelRootAdapter()
        : BaseAdapter()
    {}

    USDSKELIMAGING_API
    virtual ~UsdSkelImagingSkelRootAdapter();

    // ---------------------------------------------------------------------- //
    /// \name Initialization
    // ---------------------------------------------------------------------- //
    USDSKELIMAGING_API
    SdfPath
    Populate(const UsdPrim& prim,
             UsdImagingIndexProxy* index,
             const UsdImagingInstancerContext*
                 instancerContext=nullptr) override;

    USDSKELIMAGING_API
    bool CanPopulateUsdInstance() const override { return true; }

    bool ShouldIgnoreNativeInstanceSubtrees() const override;

    // ---------------------------------------------------------------------- //
    /// \name Parallel Setup and Resolve
    // ---------------------------------------------------------------------- //

    /// Thread Safe.
    USDSKELIMAGING_API
    void TrackVariability(const UsdPrim& prim,
                          const SdfPath& cachePath,
                          HdDirtyBits* timeVaryingBits,
                          const UsdImagingInstancerContext*
                             instancerContext = nullptr) const override;

    /// Thread Safe.
    USDSKELIMAGING_API
    void UpdateForTime(const UsdPrim& prim,
                       const SdfPath& cachePath,
                       UsdTimeCode time,
                       HdDirtyBits requestedBits,
                       const UsdImagingInstancerContext*
                           instancerContext=nullptr) const override;

    // ---------------------------------------------------------------------- //
    /// \name Change Processing
    // ---------------------------------------------------------------------- //

    USDSKELIMAGING_API
    HdDirtyBits ProcessPropertyChange(const UsdPrim& prim,
                                      const SdfPath& cachePath,
                                      const TfToken& propertyName) override;

    USDSKELIMAGING_API
    void MarkDirty(const UsdPrim& prim,
                   const SdfPath& cachePath,
                   HdDirtyBits dirty,
                   UsdImagingIndexProxy* index) override;

protected:
    USDSKELIMAGING_API
    void _RemovePrim(const SdfPath& cachePath,
                     UsdImagingIndexProxy* index) override;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_SKEL_IMAGING_SKEL_ROOT_ADAPTER_H
