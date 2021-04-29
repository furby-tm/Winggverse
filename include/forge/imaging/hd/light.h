#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/light.h"
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
#ifndef FORGE_IMAGING_HD_LIGHT_H
#define FORGE_IMAGING_HD_LIGHT_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/sprim.h"

#include "forge/base/tf/staticTokens.h"
#include "forge/base/vt/dictionary.h"
#include "forge/base/vt/value.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

#define HD_LIGHT_TOKENS                                     \
    (angle)                                                 \
    (color)                                                 \
    (colorTemperature)                                      \
    (enableColorTemperature)                                \
    (exposure)                                              \
    (height)                                                \
    (intensity)                                             \
    (radius)                                                \
    (length)                                                \
    ((textureFile, "texture:file"))                         \
    ((textureFormat, "texture:format"))                     \
    (width)                                                 \
    (diffuse)                                               \
    (specular)                                              \
    (normalize)                                             \
    ((shapingFocus, "shaping:focus"))                       \
    ((shapingFocusTint, "shaping:focusTint"))               \
    ((shapingConeAngle, "shaping:cone:angle"))              \
    ((shapingConeSoftness, "shaping:cone:softness"))        \
    ((shapingIesFile, "shaping:ies:file"))                  \
    ((shapingIesAngleScale, "shaping:ies:angleScale"))      \
    ((shapingIesNormalize, "shaping:ies:normalize"))        \
    ((shadowEnable, "shadow:enable"))                       \
    ((shadowColor, "shadow:color"))                         \
    ((shadowDistance, "shadow:distance"))                   \
    ((shadowFalloff, "shadow:falloff"))                     \
    ((shadowFalloffGamma, "shadow:falloffGamma"))           \
                                                            \
    (params)                                                \
    (shadowCollection)                                      \
    (shadowParams)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdLightTokens, HD_API, HD_LIGHT_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

class HdSceneDelegate;
typedef std::vector<class HdLight const *> HdLightPtrConstVector;

/// \class HdLight
///
/// A light model, used in conjunction with HdRenderPass.
///
class HdLight : public HdSprim {
public:
    HD_API
    HdLight(SdfPath const & id);
    HD_API
    virtual ~HdLight();

    // Change tracking for HdLight
    enum DirtyBits : HdDirtyBits {
        Clean                 = 0,
        DirtyTransform        = 1 << 0,
        DirtyParams           = 1 << 1,
        DirtyShadowParams     = 1 << 2,
        DirtyCollection       = 1 << 3,
        DirtyResource         = 1 << 4,
        AllDirty              = (DirtyTransform
                                 |DirtyParams
                                 |DirtyShadowParams
                                 |DirtyCollection
                                 |DirtyResource)
    };
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_LIGHT_H
