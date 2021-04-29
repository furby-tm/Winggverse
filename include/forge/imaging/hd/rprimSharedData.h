#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/rprimSharedData.h"
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
#ifndef FORGE_IMAGING_HD_RPRIM_SHARED_DATA_H
#define FORGE_IMAGING_HD_RPRIM_SHARED_DATA_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bufferArrayRange.h"
#include "forge/imaging/hd/tokens.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/gf/bbox3d.h"

FORGE_NAMESPACE_BEGIN


// HdRprimSharedData is an assortment of data being shared across HdReprs,
// owned by HdRprim. HdDrawItem holds a const pointer to HdRprimSharedData.
//
// HdRprim
//   |
//   +--HdRepr(s)
//   |    |
//   |    +--HdDrawItem(s)-----.
//   |                         |
//   +--HdRprimSharedData  <---'
//

struct HdRprimSharedData {
    HdRprimSharedData(int barContainerSize)
        : barContainer(barContainerSize)
        , bounds()
        , instancerLevels(0)
        , visible(true)
        , rprimID()
        , materialTag(HdMaterialTagTokens->defaultMaterialTag)
    { }

    HdRprimSharedData(int barContainerSize,
                      bool visible)
        : barContainer(barContainerSize)
        , bounds()
        , instancerLevels(0)
        , visible(visible)
        , rprimID()
        , materialTag(HdMaterialTagTokens->defaultMaterialTag)
    { }

    // BufferArrayRange array
    HdBufferArrayRangeContainer barContainer;

    // Used for CPU frustum culling.
    GfBBox3d bounds;

    // The number of levels of instancing applied to this rprim.
    int instancerLevels;

    // Used for authored/delegate visibility.
    bool visible;

    // The owning Rprim's identifier.
    SdfPath rprimID;

    // Used to organize drawItems into collections based on material properties.
    TfToken materialTag;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_RPRIM_SHARED_DATA_H
