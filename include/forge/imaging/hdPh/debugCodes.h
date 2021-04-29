#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/debugCodes.h"
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

#ifndef FORGE_IMAGING_HD_PH_DEBUG_CODES_H
#define FORGE_IMAGING_HD_PH_DEBUG_CODES_H

#include "forge/base/tf/debug.h"
#include "forge/forge.h"
#include "forge/imaging/hd/version.h"

FORGE_NAMESPACE_BEGIN

TF_DEBUG_CODES(HDPH_DRAW_BATCH,
               HDPH_FORCE_DRAW_BATCH_REBUILD,
               HDPH_DRAW_ITEM_GATHER,
               HDPH_DISABLE_FRUSTUM_CULLING,
               HDPH_DISABLE_MULTITHREADED_CULLING,
               HDPH_DUMP_GLSLFX_CONFIG,
               HDPH_DUMP_FAILING_SHADER_SOURCE,
               HDPH_DUMP_FAILING_SHADER_SOURCEFILE,
               HDPH_DUMP_SHADER_SOURCE,
               HDPH_DUMP_SHADER_SOURCEFILE,
               HDPH_MATERIAL_ADDED,
               HDPH_MATERIAL_REMOVED);

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_DEBUG_CODES_H
