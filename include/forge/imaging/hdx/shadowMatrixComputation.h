#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/shadowMatrixComputation.h"
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
#ifndef FORGE_IMAGING_HDX_SHADOW_MATRIX_COMPUTATION_H
#define FORGE_IMAGING_HDX_SHADOW_MATRIX_COMPUTATION_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/cameraUtil/conformWindow.h"
#include "forge/base/gf/matrix4d.h"

FORGE_NAMESPACE_BEGIN

class CameraUtilFraming;

// Interface class for computing the shadow matrix
// for a given viewport.
class HdxShadowMatrixComputation
{
public:
    // For legacy clients using viewport, will be removed eventually.
    virtual std::vector<GfMatrix4d> Compute(const GfVec4f &viewport, CameraUtilConformWindowPolicy policy) = 0;

    // For modern clients using camera framing API.
    virtual std::vector<GfMatrix4d> Compute(const CameraUtilFraming &framing, CameraUtilConformWindowPolicy policy) = 0;

protected:
    HdxShadowMatrixComputation()          = default;
    virtual ~HdxShadowMatrixComputation() = default;

private:
    HdxShadowMatrixComputation(const HdxShadowMatrixComputation &)             = delete;
    HdxShadowMatrixComputation &operator =(const HdxShadowMatrixComputation &) = delete;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_SHADOW_MATRIX_COMPUTATION_H
