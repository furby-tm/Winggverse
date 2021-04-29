#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/simpleShadowArray.h"
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
#ifndef FORGE_IMAGING_GLF_SIMPLE_SHADOW_ARRAY_H
#define FORGE_IMAGING_GLF_SIMPLE_SHADOW_ARRAY_H

/// \file glf/simpleShadowArray.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec4d.h"
#include "forge/imaging/garch/glApi.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


class GlfSimpleShadowArray : public TfRefBase,
                             public TfWeakBase
{
public:
    GLF_API
    GlfSimpleShadowArray();
    GLF_API
    ~GlfSimpleShadowArray() override;

    // Disallow copies
    GlfSimpleShadowArray(const GlfSimpleShadowArray&) = delete;
    GlfSimpleShadowArray& operator=(const GlfSimpleShadowArray&) = delete;

    // Driven by the env var GLF_ENABLE_BINDLESS_SHADOW_TEXTURE, this returns
    // whether bindless shadow maps are enabled, which in turn dictates the API
    // to use. See below.
    GLF_API static
    bool GetBindlessShadowMapsEnabled();

    ///  Bindful API:

    // Set the 2D size of the shadow map texture array.
    GLF_API
    void SetSize(GfVec2i const & size);

    // Set the depth of the shadow map texture array, which corresponds to the
    // number of shadow maps necessary. Each shadow casting light uses one
    // shadow map.
    GLF_API
    void SetNumLayers(size_t numLayers);

    // Returns the GL texture id of the texture array.
    GLF_API
    GLuint GetShadowMapTexture() const;

    // Returns the GL sampler id of the sampler object used to read the raw
    // depth values.
    GLF_API
    GLuint GetShadowMapDepthSampler() const;

    // Returns the GL sampler id of the sampler object used for depth comparison
    GLF_API
    GLuint GetShadowMapCompareSampler() const;

    /// Bindless API:

    // Set the resolutions of all the shadow maps necessary. The number of
    // resolutions corresponds to the number of shadow map textures necessary,
    // which is currently one per shadow casting light.
    GLF_API
    void SetShadowMapResolutions(std::vector<GfVec2i> const& resolutions);

    // Returns a vector of the 64bit bindless handles corresponding to the
    // bindless shadow map textures.
    GLF_API
    std::vector<uint64_t> const& GetBindlessShadowMapHandles() const;

    /// Common API (for shadow map generation)

    // Returns the number of shadow map generation passes required, which is
    // currently one per shadow map (corresponding to a shadow casting light).
    GLF_API
    size_t GetNumShadowMapPasses() const;

    // Returns the shadow map resolution for a given pass. For bindful shadows,
    // this returns a single size for all passes, while for bindless, it returns
    // the resolution of the corresponding shadow map,
    GLF_API
    GfVec2i GetShadowMapSize(size_t pass) const;

    // Get/Set the view (world to shadow camera) transform to use for a given
    // shadow map generation pass.
    GLF_API
    GfMatrix4d GetViewMatrix(size_t index) const;
    GLF_API
    void SetViewMatrix(size_t index, GfMatrix4d const & matrix);

    // Get/Set the projection transform to use for a given shadow map generation
    // pass.
    GLF_API
    GfMatrix4d GetProjectionMatrix(size_t index) const;
    GLF_API
    void SetProjectionMatrix(size_t index, GfMatrix4d const & matrix);

    GLF_API
    GfMatrix4d GetWorldToShadowMatrix(size_t index) const;

    // Bind necessary resources for a given shadow map generation pass.
    GLF_API
    void BeginCapture(size_t index, bool clear);

    // Unbind necssary resources after a shadow map gneration pass.
    GLF_API
    void EndCapture(size_t index);

private:
    void _AllocResources();
    void _AllocBindfulTextures();
    void _AllocBindlessTextures();
    void _FreeResources();
    void _FreeBindfulTextures();
    void _FreeBindlessTextures();
    bool _ShadowMapExists() const;
    void _BindFramebuffer(size_t index);
    void _UnbindFramebuffer();

private:
    // bindful state
    GfVec2i _size;
    size_t _numLayers;
    GLuint _bindfulTexture;
    GLuint _shadowDepthSampler;

    // bindless state
    std::vector<GfVec2i> _resolutions;
    std::vector<GLuint> _bindlessTextures;
    std::vector<uint64_t> _bindlessTextureHandles;

    // common state
    std::vector<GfMatrix4d> _viewMatrix;
    std::vector<GfMatrix4d> _projectionMatrix;

    GLuint _framebuffer;

    GLuint _shadowCompareSampler;

    GLuint _unbindRestoreDrawFramebuffer;
    GLuint _unbindRestoreReadFramebuffer;

    GLint  _unbindRestoreViewport[4];
};


FORGE_NAMESPACE_END

#endif
