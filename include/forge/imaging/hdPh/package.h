#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/package.h"
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
#ifndef FORGE_IMAGING_HD_PH_PACKAGE_H
#define FORGE_IMAGING_HD_PH_PACKAGE_H

#include "forge/base/tf/token.h"
#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

FORGE_NAMESPACE_BEGIN

HDPH_API
TfToken HdPhPackageComputeShader();

HDPH_API
TfToken HdPhPackageDomeLightShader();

HDPH_API
TfToken HdPhPackagePtexTextureShader();

HDPH_API
TfToken HdPhPackageRenderPassShader();

HDPH_API
TfToken HdPhPackageFallbackLightingShader();

HDPH_API
TfToken HdPhPackageLightingIntegrationShader();

HDPH_API
TfToken HdPhPackageFallbackSurfaceShader();

HDPH_API
TfToken HdPhPackageFallbackVolumeShader();

HDPH_API
TfToken HdPhPackageImageShader();

HDPH_API
TfToken HdPhPackageSimpleLightingShader();

FORGE_NAMESPACE_END

#endif
