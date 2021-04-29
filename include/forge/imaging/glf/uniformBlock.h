#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/uniformBlock.h"
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
#ifndef FORGE_IMAGING_GLF_UNIFORM_BLOCK_H
#define FORGE_IMAGING_GLF_UNIFORM_BLOCK_H

/// \file glf/uniformBlock.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/imaging/garch/glApi.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refBase.h"
#include "forge/base/tf/weakBase.h"
#include <string>

FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_AND_REF_PTRS(GlfUniformBlock);
TF_DECLARE_WEAK_PTRS(GlfBindingMap);

/// \class GlfUniformBlock
///
/// Manages a GL uniform buffer object.
///
class GlfUniformBlock : public TfRefBase, public TfWeakBase {
public:

    /// Returns a new instance.
    GLF_API
    static GlfUniformBlockRefPtr New(char const *label = nullptr);

    GLF_API
    virtual ~GlfUniformBlock();

    /// Binds the uniform buffer using a bindingMap and identifier.
    GLF_API
    void Bind(GlfBindingMapPtr const & bindingMap,
              std::string const & identifier);

    /// Updates the content of the uniform buffer. If the size
    /// is different, the buffer will be reallocated.
    GLF_API
    void Update(const void *data, int size);

protected:
    GLF_API
    GlfUniformBlock(char const *label);

private:
    GLuint _buffer;
    int _size;
    std::string _debugLabel;
};


FORGE_NAMESPACE_END

#endif
