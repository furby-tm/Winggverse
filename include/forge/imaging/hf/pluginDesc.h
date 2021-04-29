#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hf/pluginDesc.h"
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
#ifndef FORGE_IMAGING_HF_PLUGIN_DESC_H
#define FORGE_IMAGING_HF_PLUGIN_DESC_H

#include "forge/forge.h"
#include "forge/base/tf/token.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


///
/// Common structure used to report registered plugins in one of the plugin
/// registries.  The id token is used for internal api communication
/// about the name of the plugin.
/// displayName is a human readable name given to the plugin intended
/// to be used in menus.
/// priority is used to provide an ordering of plugins.  The plugin
/// with the highest priority is determined to be the default (unless
/// overridden by the application).  In the event of a tie
/// the string version of id is used to sort alphabetically ('a' has priority
/// over 'b').
///
struct HfPluginDesc {
    TfToken     id;
    std::string displayName;
    int         priority;
};

typedef std::vector<HfPluginDesc> HfPluginDescVector;


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HF_PLUGIN_DESC_H
