#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hf/pluginBase.h"
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
#ifndef FORGE_IMAGING_HF_PLUGIN_BASE_H
#define FORGE_IMAGING_HF_PLUGIN_BASE_H

#include "forge/forge.h"
#include "forge/imaging/hf/api.h"

FORGE_NAMESPACE_BEGIN

///
/// \class HfPluginBase
///
/// Base class for all hydra plugin classes. This class provides no
/// functionality other than to serve as a polymorphic type for the
/// plugin registry.
///
class HfPluginBase
{
public:
    HF_API
    virtual ~HfPluginBase();  // = default: See workaround in cpp file

protected:
    // Pure virtual class, must be derived
    HF_API
    HfPluginBase() = default;

private:
    ///
    /// This class is not intended to be copied.
    ///
    HfPluginBase(const HfPluginBase &)            = delete;
    HfPluginBase &operator=(const HfPluginBase &) = delete;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HF_PLUGIN_BASE_H
