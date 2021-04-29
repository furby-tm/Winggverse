#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/debugCodes.h"
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
#ifndef FORGE_IMAGING_GLF_DEBUG_CODES_H
#define FORGE_IMAGING_GLF_DEBUG_CODES_H

/// \file glf/debugCodes.h

#include "forge/forge.h"
#include "forge/base/tf/debug.h"

FORGE_NAMESPACE_BEGIN


TF_DEBUG_CODES(

    GLF_DEBUG_CONTEXT_CAPS,
    GLF_DEBUG_ERROR_STACKTRACE,
    GLF_DEBUG_SHADOW_TEXTURES,
    GLF_DEBUG_DUMP_SHADOW_TEXTURES,
    GLF_DEBUG_POST_SURFACE_LIGHTING

);


FORGE_NAMESPACE_END

#endif
