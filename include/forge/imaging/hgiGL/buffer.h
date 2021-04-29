#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/buffer.h"
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
#ifndef FORGE_IMAGING_HGI_GL_BUFFER_H
#define FORGE_IMAGING_HGI_GL_BUFFER_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/imaging/hgi/buffer.h"


FORGE_NAMESPACE_BEGIN

/// \class HgiGLBuffer
///
/// Represents an OpenGL GPU buffer resource.
///
class HgiGLBuffer final : public HgiBuffer
{
public:
    HGIGL_API
    ~HgiGLBuffer() override;

    HGIGL_API
    size_t GetByteSizeOfResource() const override;

    HGIGL_API
    uint64_t GetRawResource() const override;

    HGIGL_API
    void* GetCPUStagingAddress() override;

    uint32_t GetBufferId() const {return _bufferId;}

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLBuffer(HgiBufferDesc const & desc);

private:
    HgiGLBuffer() = delete;
    HgiGLBuffer & operator=(const HgiGLBuffer&) = delete;
    HgiGLBuffer(const HgiGLBuffer&) = delete;

    uint32_t _bufferId;
    void* _mapped;
    void* _cpuStaging;
};


FORGE_NAMESPACE_END

#endif
