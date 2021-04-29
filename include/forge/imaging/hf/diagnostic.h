#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hf/diagnostic.h"
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
#ifndef FORGE_IMAGING_HF_DIAGNOSTIC_H
#define FORGE_IMAGING_HF_DIAGNOSTIC_H

#include "forge/forge.h"
#include "forge/base/tf/diagnostic.h"
#include "forge/base/tf/stringUtils.h"

FORGE_NAMESPACE_BEGIN


///
/// Issues a warning with a message.  This differs from just calling TF_WARN
/// in that it tags the warning as actually needing to be a validation error,
/// and a place holder for when we develop a true validation system where we
/// can plumb this information back to the application.
///
#define HF_VALIDATION_WARN(id, ...) \
    TF_WARN("Invalid Hydra prim '%s': %s", \
            id.GetText(), \
            TfStringPrintf(__VA_ARGS__).c_str())


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HF_DIAGNOSTIC_H
