#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/thisPlugin.h"
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
#ifndef FORGE_BASE_PLUG_THIS_PLUGIN_H
#define FORGE_BASE_PLUG_THIS_PLUGIN_H

#include "forge/forge.h"
#include "forge/base/plug/registry.h"
#include "forge/base/tf/preprocessorUtilsLite.h"

FORGE_NAMESPACE_BEGIN

/// Returns a plugin registered with the name of the current library (uses the
/// define for MFB_PACKAGE_NAME). Note that plugin registration occurs as a
/// side effect of using this macro, at the point in time the code at the
/// macro site is invoked.
#define PLUG_THIS_PLUGIN \
    PlugRegistry::GetInstance().GetPluginWithName(\
        TF_PP_STRINGIZE(MFB_PACKAGE_NAME))

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_THIS_PLUGIN_H
