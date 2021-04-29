#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/field.h"
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
#ifndef FORGE_IMAGING_HD_FIELD_H
#define FORGE_IMAGING_HD_FIELD_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/bprim.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

#define HD_FIELD_TOKENS                                    \
    (filePath)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdFieldTokens, HD_API, HD_FIELD_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

class HdSceneDelegate;
typedef std::vector<class HdField const *> HdFieldPtrConstVector;

/// \class HdField
///
/// Hydra schema for a USD field primitive. Acts like a texture, combined
/// with other fields to make up a renderable volume.
///
class HdField : public HdBprim {
public:
    HD_API
    HdField(SdfPath const & id);
    HD_API
    virtual ~HdField();

    // Change tracking for HdField
    enum DirtyBits : HdDirtyBits {
        Clean                 = 0,
        DirtyTransform        = 1 << 0,
        DirtyParams           = 1 << 1,
        AllDirty              = (DirtyTransform
                                 |DirtyParams)
    };
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_FIELD_H
