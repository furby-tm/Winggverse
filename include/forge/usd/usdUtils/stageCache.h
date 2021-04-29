#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUtils/stageCache.h"
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
#ifndef FORGE_USD_USD_UTILS_STAGE_CACHE_H
#define FORGE_USD_USD_UTILS_STAGE_CACHE_H

/// \file usdUtils/stageCache.h
/// A simple interface for handling a singleton usd stage cache.

#include "forge/forge.h"
#include "forge/usd/usdUtils/api.h"
#include "forge/usd/usd/stageCache.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/token.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_AND_REF_PTRS(SdfLayer);

/// \class UsdUtilsStageCache
///
/// The UsdUtilsStageCache class provides a simple interface for handling a
/// singleton usd stage cache for use by all USD clients. This way code from
/// any location can make use of the same cache to maximize stage reuse.
///
class UsdUtilsStageCache {
public:

    /// Returns the singleton stage cache.
    USDUTILS_API
    static UsdStageCache &Get();

    /// Given variant selections as a vector of pairs (vector in case order
    /// matters to the client), constructs a session layer with overs on the
    /// given root modelName with the variant selections, or returns a cached
    /// session layer with those opinions.
    USDUTILS_API
    static SdfLayerRefPtr GetSessionLayerForVariantSelections(
        const TfToken& modelName,
        const std::vector<std::pair<std::string, std::string> > &variantSelections);
};


FORGE_NAMESPACE_END

#endif /* FORGE_USD_USD_UTILS_STAGE_CACHE_H */
