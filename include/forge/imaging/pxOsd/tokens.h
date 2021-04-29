#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/pxOsd/tokens.h"
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
#ifndef FORGE_IMAGING_PX_OSD_TOKENS_H
#define FORGE_IMAGING_PX_OSD_TOKENS_H

/// \file pxOsd/tokens.h

#include "forge/forge.h"
#include "forge/imaging/pxOsd/api.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN


#define PXOSD_OPENSUBDIV_TOKENS  \
    (all)                        \
    (none)                       \
    (cornersOnly)                \
    (cornersPlus1)               \
    (cornersPlus2)               \
    (boundaries)                 \
    (bilinear)                   \
    (catmullClark)               \
    (loop)                       \
    (edgeOnly)                   \
    (edgeAndCorner)              \
    (uniform)                    \
    (chaikin)                    \
    (leftHanded)                 \
    (rightHanded)                \
    (smooth)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(PxOsdOpenSubdivTokens, PXOSD_API, PXOSD_OPENSUBDIV_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif // PXOSD_REFINER_FACTORY_H
