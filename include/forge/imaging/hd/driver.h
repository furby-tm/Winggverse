#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/driver.h"
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
#ifndef FORGE_IMAGING_HD_DRIVER_H
#define FORGE_IMAGING_HD_DRIVER_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"

#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

/// HdDriver represents a device object, commonly a render device, that is owned
/// by the application and passed to HdRenderIndex. The RenderIndex passes it to
/// the render delegate and rendering tasks.
/// The application manages the lifetime (destruction) of HdDriver and must
/// ensure it remains valid while Hydra is running.
class HdDriver {
public:
    TfToken name;
    VtValue driver;
};

FORGE_NAMESPACE_END

#endif
