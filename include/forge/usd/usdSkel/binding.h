#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/binding.h"
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
#ifndef FORGE_USD_USD_SKEL_BINDING_H
#define FORGE_USD_USD_SKEL_BINDING_H

/// \file usdSkel/binding.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"

#include "forge/usd/usdSkel/skeleton.h"
#include "forge/usd/usdSkel/skinningQuery.h"

FORGE_NAMESPACE_BEGIN


/// \class UsdSkelBinding
///
/// Helper object that describes the binding of a skeleton to a set of
/// skinnable objects. The set of skinnable objects is given as
/// UsdSkelSkinningQuery prims, which can be used both to identify the
/// skinned prim as well compute skinning properties of the prim.
class UsdSkelBinding
{
public:
    UsdSkelBinding() {}

    UsdSkelBinding(const UsdSkelSkeleton& skel,
                   const VtArray<UsdSkelSkinningQuery>& skinningQueries)
        : _skel(skel), _skinningQueries(skinningQueries) {}

    /// Returns the bound skeleton.
    const UsdSkelSkeleton& GetSkeleton() const { return _skel; }

    /// Returns the set skinning targets.
    const VtArray<UsdSkelSkinningQuery>& GetSkinningTargets() const
        { return _skinningQueries; }

private:
    UsdSkelSkeleton _skel;
    VtArray<UsdSkelSkinningQuery> _skinningQueries;
};


FORGE_NAMESPACE_END

#endif // USDSKEL_SKINNING_MAP
