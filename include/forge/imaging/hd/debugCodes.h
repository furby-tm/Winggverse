#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/debugCodes.h"
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
#ifndef FORGE_IMAGING_HD_DEBUG_CODES_H
#define FORGE_IMAGING_HD_DEBUG_CODES_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/base/tf/debug.h"

FORGE_NAMESPACE_BEGIN


TF_DEBUG_CODES(
    HD_BPRIM_ADDED,
    HD_BPRIM_REMOVED,
    HD_BUFFER_ARRAY_INFO,
    HD_BUFFER_ARRAY_RANGE_CLEANED,
    HD_CACHE_HITS,
    HD_CACHE_MISSES,
    HD_COUNTER_CHANGED,
    HD_DIRTY_ALL_COLLECTIONS,
    HD_DIRTY_LIST,
    HD_DISABLE_MULTITHREADED_RPRIM_SYNC,
    HD_DRAWITEMS_CULLED,
    HD_ENGINE_PHASE_INFO,
    HD_EXT_COMPUTATION_ADDED,
    HD_EXT_COMPUTATION_REMOVED,
    HD_EXT_COMPUTATION_UPDATED,
    HD_EXT_COMPUTATION_EXECUTION,
    HD_FREEZE_CULL_FRUSTUM,
    HD_INSTANCER_ADDED,
    HD_INSTANCER_CLEANED,
    HD_INSTANCER_REMOVED,
    HD_INSTANCER_UPDATED,
    HD_MDI,
    HD_RENDER_SETTINGS,
    HD_RPRIM_ADDED,
    HD_RPRIM_CLEANED,
    HD_RPRIM_REMOVED,
    HD_RPRIM_UPDATED,
    HD_SAFE_MODE,
    HD_SELECTION_UPDATE,
    HD_SHARED_EXT_COMPUTATION_DATA,
    HD_SPRIM_ADDED,
    HD_SPRIM_REMOVED,
    HD_TASK_ADDED,
    HD_TASK_REMOVED,
    HD_VARYING_STATE
);


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_DEBUG_CODES_H
