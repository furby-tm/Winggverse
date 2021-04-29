#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/conversions.h"
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
#ifndef FORGE_IMAGING_HGI_GL_CONVERSIONS_H
#define FORGE_IMAGING_HGI_GL_CONVERSIONS_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/garch/glApi.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/types.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

///
/// \class HgiGLConversions
///
/// Converts from Hgi types to GL types.
///
class HgiGLConversions final
{
public:
    HGIGL_API
    static void GetFormat(
        HgiFormat inFormat,
        GLenum *outFormat,
        GLenum *outType,
        GLenum *outInternalFormat = nullptr);

    HGIGL_API
    static GLenum GetFormatType(HgiFormat inFormat);

    HGIGL_API
    static std::vector<GLenum> GetShaderStages(HgiShaderStage ss);

    HGIGL_API
    static GLenum GetCullMode(HgiCullMode cm);

    HGIGL_API
    static GLenum GetPolygonMode(HgiPolygonMode pm);

    HGIGL_API
    static GLenum GetBlendFactor(HgiBlendFactor bf);

    HGIGL_API
    static GLenum GetBlendEquation(HgiBlendOp bo);

    HGIGL_API
    static GLenum GetDepthCompareFunction(HgiCompareFunction cf);

    HGIGL_API
    static GLenum GetTextureType(HgiTextureType tt);

    HGIGL_API
    static GLenum GetSamplerAddressMode(HgiSamplerAddressMode am);

    HGIGL_API
    static GLenum GetMagFilter(HgiSamplerFilter mf);

    HGIGL_API
    static GLenum GetMinFilter(
        HgiSamplerFilter minFilter,
        HgiMipFilter mipFilter);

    HGIGL_API
    static GLenum GetComponentSwizzle(HgiComponentSwizzle);

    HGIGL_API
    static GLenum GetPrimitiveType(HgiPrimitiveType pt);
};


FORGE_NAMESPACE_END

#endif
