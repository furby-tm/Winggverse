#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/site.h"
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
#ifndef FORGE_USD_SDF_SITE_H
#define FORGE_USD_SDF_SITE_H

#include "forge/forge.h"
#include "forge/usd/sdf/layer.h"
#include "forge/usd/sdf/path.h"

#include <set>
#include <vector>
#include <boost/operators.hpp>

FORGE_NAMESPACE_BEGIN

/// \class SdfSite
///
/// An SdfSite is a simple representation of a location in a layer where
/// opinions may possibly be found. It is simply a pair of layer and path
/// within that layer.
///
class SdfSite
    : public boost::totally_ordered<SdfSite>
{
public:
    SdfSite() { }
    SdfSite(const SdfLayerHandle& layer_, const SdfPath& path_)
        : layer(layer_)
        , path(path_)
    { }

    bool operator==(const SdfSite& other) const
    {
        return layer == other.layer && path == other.path;
    }

    bool operator<(const SdfSite& other) const
    {
        return layer < other.layer ||
               (!(other.layer < layer) && path < other.path);
    }

    /// Explicit bool conversion operator. A site object converts to \c true iff
    /// both the layer and path fields are filled with valid values, \c false
    /// otherwise.
    /// This does NOT imply that there are opinions in the layer at that path.
    explicit operator bool() const
    {
        return layer && !path.IsEmpty();
    }

public:
    SdfLayerHandle layer;
    SdfPath path;
};

typedef std::set<SdfSite> SdfSiteSet;
typedef std::vector<SdfSite> SdfSiteVector;

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_SITE_H
