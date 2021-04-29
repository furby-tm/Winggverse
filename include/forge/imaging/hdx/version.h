#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/version.h"
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
#ifndef FORGE_IMAGING_HDX_VERSION_H
#define FORGE_IMAGING_HDX_VERSION_H

// 1  -> 2 : split HdxRenderSetupTask out of HdxRenderTask
// 2  -> 3 : move simpleLightingShader to Hdx.
// 3  -> 4 : move camera and light to Hdx.
// 4  -> 5 : move drawTarget to Hdx.
// 5  -> 6 : change HdxShadowMatrixComputation signature.
// 6  -> 7 : make HdxShadowMatrixComputationSharedPtr std::shared_ptr instead of boost::shared_ptr
// 7  -> 8 : added another HdxShadowMatrixComputation signature.
#define HDX_API_VERSION  8

#endif // FORGE_IMAGING_HDX_VERSION_H
