#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/graphicsPipeline.h"
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
#ifndef FORGE_IMAGING_HGIGL_PIPELINE_H
#define FORGE_IMAGING_HGIGL_PIPELINE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/graphicsPipeline.h"
#include "forge/imaging/hgiGL/api.h"


FORGE_NAMESPACE_BEGIN


/// \class HgiGLPipeline
///
/// OpenGL implementation of HgiGraphicsPipeline.
///
class HgiGLGraphicsPipeline final : public HgiGraphicsPipeline
{
public:
    HGIGL_API
    ~HgiGLGraphicsPipeline() override;

    /// Apply pipeline state
    HGIGL_API
    void BindPipeline();

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLGraphicsPipeline(HgiGraphicsPipelineDesc const& desc);

private:
    HgiGLGraphicsPipeline() = delete;
    HgiGLGraphicsPipeline & operator=(const HgiGLGraphicsPipeline&) = delete;
    HgiGLGraphicsPipeline(const HgiGLGraphicsPipeline&) = delete;

    uint32_t _vao;
};


FORGE_NAMESPACE_END

#endif
