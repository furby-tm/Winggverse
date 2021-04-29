#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/sampler.h"
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
#ifndef FORGE_IMAGING_HGIGL_SAMPLER_H
#define FORGE_IMAGING_HGIGL_SAMPLER_H

#include "forge/imaging/hgi/sampler.h"

#include "forge/imaging/hgiGL/api.h"


FORGE_NAMESPACE_BEGIN


///
/// \class HgiGLSampler
///
/// OpenGL implementation of HgiSampler
///
class HgiGLSampler final : public HgiSampler
{
public:
    HGIGL_API
    ~HgiGLSampler() override;

    HGIGL_API
    uint64_t GetRawResource() const override;

    /// Returns the gl resource id of the sampler.
    HGIGL_API
    uint32_t GetSamplerId() const;

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLSampler(HgiSamplerDesc const& desc);

private:
    HgiGLSampler() = delete;
    HgiGLSampler & operator=(const HgiGLSampler&) = delete;
    HgiGLSampler(const HgiGLSampler&) = delete;

private:
    uint32_t _samplerId;
};


FORGE_NAMESPACE_END

#endif