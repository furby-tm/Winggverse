#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/layerHints.h"
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
#ifndef FORGE_USD_SDF_LAYER_HINTS_H
#define FORGE_USD_SDF_LAYER_HINTS_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

/// Contains hints about layer contents that may be used to accelerate certain
/// composition operations.
class SdfLayerHints
{
public:
    /// Default constructed hints provide the most conservative set of values
    /// such that consumers of the hints will act correctly if not optimally.
    SdfLayerHints() = default;

    /// Construct hints with specific values.  Using this constructor requires
    /// that all hint fields be specified.
    explicit SdfLayerHints(bool mightHaveRelocates)
        : mightHaveRelocates(mightHaveRelocates)
    {}

    /// If this field is false, the layer does not contain relocates.  If
    /// true, relocates may be present but are not guaranteed to exist.
    bool mightHaveRelocates = true;
};

FORGE_NAMESPACE_END

#endif
