#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/resourceBindings.h"
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
#ifndef FORGE_IMAGING_HGIGL_RESOURCEBINDINGS_H
#define FORGE_IMAGING_HGIGL_RESOURCEBINDINGS_H

#include "forge/forge.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgiGL/api.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


///
/// \class HgiGLResourceBindings
///
/// OpenGL implementation of HgiResourceBindings.
///
///
class HgiGLResourceBindings final : public HgiResourceBindings
{
public:
    HGIGL_API
    ~HgiGLResourceBindings() override;

    /// Binds the resources to GPU.
    HGIGL_API
    void BindResources();

protected:
    friend class HgiGL;

    HGIGL_API
    HgiGLResourceBindings(HgiResourceBindingsDesc const& desc);

private:
    HgiGLResourceBindings() = delete;
    HgiGLResourceBindings & operator=(const HgiGLResourceBindings&) = delete;
    HgiGLResourceBindings(const HgiGLResourceBindings&) = delete;
};


FORGE_NAMESPACE_END

#endif
