#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/tokens.h"
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
#ifndef FORGE_IMAGING_HGI_TOKENS_H
#define FORGE_IMAGING_HGI_TOKENS_H

#include "forge/forge.h"
#include "forge/base/tf/staticTokens.h"

#include "forge/imaging/hgi/api.h"

FORGE_NAMESPACE_BEGIN

#define HGI_TOKENS    \
    (taskDriver)      \
    (renderDriver)    \
    (OpenGL)          \
    (Metal)           \
    (Vulkan)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HgiTokens, HGI_API, HGI_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

FORGE_NAMESPACE_END

#endif
