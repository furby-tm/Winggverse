#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/coordSys.h"
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
#ifndef FORGE_IMAGING_HD_COORD_SYS_H
#define FORGE_IMAGING_HD_COORD_SYS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/sprim.h"

#include "forge/base/vt/dictionary.h"
#include "forge/base/vt/value.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;

/// \class HdCoordSys
///
/// HdCoordSys representes a coordinate system as a Hydra state prim.
///
/// Coordinate systems may be referred to by name from a shader network.
/// Following the convention in UsdShadeCoordSysAPI, we use the Hydra
/// id to establish the name, where the id is a namespaced property
/// path of the form <tt><.../prim.coordSys:NAME></tt>.  GetName()
/// will retrieve the name.
///
/// Each rprim may have a set of bound coordinate systems, which
/// may be retrieved via the <tt>HdTokens->coordSysBindings</tt> key.
/// The returned value is of type HdIdVectorSharedPtr, a reference-
/// counted pointer to a vector of ids of coordinate systems.
/// The intention of this design is to make it efficient for scene
/// delegates to communicate to renderer delegates the common
/// mappings of bound coordinate systems across groups of rprims.
///
/// The transform value of an HdCoordSys is the matrix representation
/// of the transform from its local space to world space.  In other
/// words, it has the same interpretation as the transform for rprims.
///
class HdCoordSys : public HdSprim {
public:
    HD_API
    HdCoordSys(SdfPath const & id);
    HD_API
    virtual ~HdCoordSys();

    // Change tracking for HdCoordSys
    enum DirtyBits : HdDirtyBits {
        Clean                 = 0,
        DirtyTransform        = 1 << 0,
        AllDirty              = DirtyTransform
    };

    /// Returns the name bound to this coordinate system.
    ///
    /// There may be multiple coordinate systems with the same
    /// name, but they must associate with disjoint sets of rprims.
    TfToken GetName() const { return _name; }

private:
    TfToken _name;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_COORD_SYS_H
