#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/texture.h"
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
#ifndef FORGE_IMAGING_HD_TEXTURE_H
#define FORGE_IMAGING_HD_TEXTURE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bprim.h"

#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN


///
/// Represents a Texture Buffer Prim.
///
class HdTexture : public HdBprim {
public:
    // change tracking for HdTexture
    enum DirtyBits : HdDirtyBits {
        Clean                 = 0,
        DirtyParams           = 1 << 0,
        DirtyTexture          = 1 << 1,
        AllDirty              = (DirtyParams
                                |DirtyTexture)
    };

    HD_API
    HdTexture(SdfPath const & id);
    HD_API
    virtual ~HdTexture();
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_TEXTURE_H
