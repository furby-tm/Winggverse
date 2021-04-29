#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/scopedStateHolder.h"
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
#ifndef FORGE_IMAGING_HGIGL_STATE_H
#define FORGE_IMAGING_HGIGL_STATE_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"


FORGE_NAMESPACE_BEGIN


/// \class HgiGLScopedStateHolder
///
/// OpenGL state guard object.
///
/// We've historically allowed applications to change global OpenGL.
/// Consecutive code then relies on certain global state having been set.
/// This results in difficult to manage and inefficient OpenGL code.
///
/// For Hgi transition, we defensively capture state in this object and restore
/// it to the previous state to keep our applications function as before.
/// The end goal is to not need this object at all and make sure all opengl
/// state is only changed via HgiPipeline objects.
///
class HgiGL_ScopedStateHolder final
{
public:
    HGIGL_API
    HgiGL_ScopedStateHolder();

    HGIGL_API
    ~HgiGL_ScopedStateHolder();

private:
    HgiGL_ScopedStateHolder& operator=(const HgiGL_ScopedStateHolder&) = delete;
    HgiGL_ScopedStateHolder(const HgiGL_ScopedStateHolder&) = delete;

    int32_t _restoreDrawFramebuffer;
    int32_t _restoreReadFramebuffer;
    int32_t _restoreRenderBuffer;
    int32_t _restoreVao;
    bool _restoreDepthTest;
    bool _restoreDepthWriteMask;
    int32_t _restoreStencilWriteMask;
    int32_t _restoreDepthFunc;
    int32_t _restoreViewport[4];
    bool _restoreblendEnabled;
    int32_t _restoreColorOp;
    int32_t _restoreAlphaOp;
    int32_t _restoreColorSrcFnOp;
    int32_t _restoreAlphaSrcFnOp;
    int32_t _restoreColorDstFnOp;
    int32_t _restoreAlphaDstFnOp;
    bool _restoreAlphaToCoverage;
    bool _restoreSampleAlphaToOne;
    float _lineWidth;
    bool _cullFace;
    int32_t _cullMode;
    int32_t _frontFace;
    bool _rasterizerDiscard;
    bool _restoreFramebufferSRGB;
};


FORGE_NAMESPACE_END

#endif
