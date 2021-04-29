#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/texture.h"
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
#ifndef FORGE_IMAGING_HGI_GL_TEXTURE_H
#define FORGE_IMAGING_HGI_GL_TEXTURE_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgi/texture.h"


FORGE_NAMESPACE_BEGIN

/// \class HgiGLTexture
///
/// Represents a OpenGL GPU texture resource.
///
class HgiGLTexture final : public HgiTexture
{
public:
    HGIGL_API
    ~HgiGLTexture() override;

    HGIGL_API
    size_t GetByteSizeOfResource() const override;

    HGIGL_API
    uint64_t GetRawResource() const override;

    /// Returns the OpenGL id / name of the texture.
    uint32_t GetTextureId() const {return _textureId;}

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLTexture(HgiTextureDesc const & desc);

    HGIGL_API
    HgiGLTexture(HgiTextureViewDesc const & desc);

private:
    HgiGLTexture() = delete;
    HgiGLTexture & operator=(const HgiGLTexture&) = delete;
    HgiGLTexture(const HgiGLTexture&) = delete;

    uint32_t _textureId;
};


FORGE_NAMESPACE_END

#endif
