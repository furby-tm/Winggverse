#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdviewq/utils.h"
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
#ifndef FORGE_USD_IMAGING_USDVIEWQ_UTILS_H
#define FORGE_USD_IMAGING_USDVIEWQ_UTILS_H

#include "forge/forge.h"
#include "forge/usdImaging/usdviewq/api.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/timeCode.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


class UsdStage;

/// \class UsdviewqUtils
///
/// Performance enhancing utilities for usdview.
///
class UsdviewqUtils {
public:

    struct PrimInfo {
        PrimInfo(const UsdPrim &prim, const UsdTimeCode time);

        bool hasCompositionArcs;
        bool isActive;
        bool isImageable;
        bool isDefined;
        bool isAbstract;
        bool isInPrototype;
        bool isInstance;
        bool supportsDrawMode;
        bool isVisibilityInherited;
        bool visVaries;
        std::string name;
        std::string typeName;
    };

    /// For the given \p stage and \p schemaType, return all active, defined
    /// prims that either match the schemaType exactly or are a descendant type.
    //
    //      Furthermore, this method is not intended to be used publically,
    //      ultimately Usd will have better core support for fast prim
    //      filtering by typeName.
    USDVIEWQ_API
    static
    std::vector<UsdPrim> _GetAllPrimsOfType(UsdStagePtr const &stage,
                                            TfType const& schemaType);

    /// Fetch prim-related data in batch to to speed up Qt treeview item
    /// population.  Takes a time argument so that we can evaluate the prim's
    /// visibiity if it is imageable.
    USDVIEWQ_API
    static UsdviewqUtils::PrimInfo GetPrimInfo(const UsdPrim &prim,
                                               const UsdTimeCode time);
};


FORGE_NAMESPACE_END

#endif //FORGE_USD_IMAGING_USDVIEWQ_UTILS_H
