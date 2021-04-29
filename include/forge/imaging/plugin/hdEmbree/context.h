#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hdEmbree/context.h"
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
#ifndef FORGE_IMAGING_PLUGIN_HD_EMBREE_CONTEXT_H
#define FORGE_IMAGING_PLUGIN_HD_EMBREE_CONTEXT_H

#include "forge/forge.h"

#include "forge/imaging/plugin/hdEmbree/sampler.h"

#include "forge/base/gf/matrix4f.h"
#include "forge/base/vt/array.h"

#include <embree3/rtcore.h>

FORGE_NAMESPACE_BEGIN

class HdRprim;

/// \class HdEmbreePrototypeContext
///
/// A small bit of state attached to each bit of prototype geometry in embree,
/// for the benefit of HdEmbreeRenderer::_TraceRay.
///
struct HdEmbreePrototypeContext
{
    /// A pointer back to the owning HdEmbree rprim.
    HdRprim *rprim;
    /// A name-indexed map of primvar samplers.
    TfHashMap<TfToken, HdEmbreePrimvarSampler*, TfToken::HashFunctor>
        primvarMap;
    /// A copy of the primitive params for this rprim.
    VtIntArray primitiveParams;
};

///
/// \class HdEmbreeInstanceContext
///
/// A small bit of state attached to each bit of instanced geometry in embree,
/// for the benefit of HdEmbreeRenderer::_TraceRay.
///
struct HdEmbreeInstanceContext
{
    /// The object-to-world transform, for transforming normals to worldspace.
    GfMatrix4f objectToWorldMatrix;
    /// The scene the prototype geometry lives in, for passing to
    /// rtcInterpolate.
    RTCScene rootScene;
    /// The instance id of this instance.
    int32_t instanceId;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_PLUGIN_HD_EMBREE_CONTEXT_H
