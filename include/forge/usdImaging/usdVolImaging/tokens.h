#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdVolImaging/tokens.h"
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
#ifndef FORGE_USD_IMAGING_USD_VOL_IMAGING_TOKENS_H
#define FORGE_USD_IMAGING_USD_VOL_IMAGING_TOKENS_H

#include "forge/forge.h"
#include "forge/usdImaging/usdVolImaging/api.h"
#include "forge/base/tf/staticTokens.h"

FORGE_NAMESPACE_BEGIN

#define USDVOLIMAGING_TOKENS \
    (field3dAsset)           \
    (openvdbAsset)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdVolImagingTokens, USDVOLIMAGING_API, USDVOLIMAGING_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_VOL_IMAGING_TOKENS_H
