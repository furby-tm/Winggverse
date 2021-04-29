#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImagingGL/rendererSettings.h"
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

/// \file usdImagingGL/renderSettings.h

#ifndef FORGE_USD_IMAGING_USD_IMAGING_GL_RENDERER_SETTINGS_H
#define FORGE_USD_IMAGING_USD_IMAGING_GL_RENDERER_SETTINGS_H

#include "forge/forge.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

struct UsdImagingGLRendererSetting {
    enum Type {
        TYPE_FLAG,
        TYPE_INT,
        TYPE_FLOAT,
        TYPE_STRING
    };
    std::string name;
    TfToken key;
    Type type;
    VtValue defValue;
};

typedef std::vector<UsdImagingGLRendererSetting>
    UsdImagingGLRendererSettingsList;

FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_GL_RENDERER_SETTINGS_H
