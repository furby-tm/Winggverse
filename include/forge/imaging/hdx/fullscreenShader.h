#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/fullscreenShader.h"
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
#ifndef FORGE_IMAGING_HDX_FULLSCREENSHADER_H
#define FORGE_IMAGING_HDX_FULLSCREENSHADER_H

#include "forge/forge.h"

#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hd/types.h"
#include "forge/base/gf/vec2i.h"
#include "forge/imaging/hgi/buffer.h"
#include "forge/imaging/hgi/graphicsPipeline.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgi/shaderProgram.h"
#include "forge/imaging/hgi/texture.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

class Hgi;

/// \class HdxFullscreenShader
///
/// This class is a utility for rendering deep raytracer or aov output
/// (color/depth) to a hgi texture. This lets callers composite results
/// into existing scenes.
///
class HdxFullscreenShader
{
public:
    /// Create a new fullscreen shader object.
    /// 'debugName' is assigned to the fullscreen pass as gpu debug group that
    /// is helpful when inspecting the frame on a gpu debugger.
    HDX_API
    HdxFullscreenShader(Hgi* hgi, std::string const& debugName);

    /// Destroy the fullscreen shader object, releasing GPU resources.
    HDX_API
    ~HdxFullscreenShader();

    /// Set the program for the class to use for its fragment shader.
    /// The vertex shader is always hdx/shaders/fullscreen.glslfx,
    /// "FullScreenVertex", which draws a full-screen triangle.
    /// The fragment shader should expect a varying called "uv", and
    /// whatever textures or uniforms have been passed in by the caller.
    ///   \param glslfx The name of the glslfx file where the fragment shader
    ///                 is located.
    ///   \param shaderName The (technique) name of the fragment shader.
    ///   \param vertDesc Describes inputs, outputs and stage of vertex shader.
    ///   \param fragDesc Describes inputs, outputs and stage of fragment shader.
    HDX_API
    void SetProgram(
        TfToken const& glslfx,
        TfToken const& shaderName,
        HgiShaderFunctionDesc &fragDesc,
        HgiShaderFunctionDesc vertDesc = GetFullScreenVertexDesc()
        );

    /// Bind a (externally managed) buffer to the shader program.
    /// This function can be used to bind buffers to a custom shader program.
    /// The lifetime of the buffer is managed by the caller. HdxFullscreenShader
    /// does not take ownership. To update values in the buffer, the client can
    /// use a blitCmds to copy new data into their buffer.
    /// If an invalid 'buffer' is passed, the binding will be cleared.
    HDX_API
    void BindBuffer(HgiBufferHandle const& buffer, uint32_t bindingIndex);

    /// Bind (externally managed) textures to the shader program.
    /// This function can be used to bind textures to a custom shader program.
    /// The lifetime of textures is managed by the caller. HdxFullscreenShader
    /// does not take ownership.
    /// If an invalid 'texture' is passed, the binding will be cleared.
    HDX_API
    void BindTextures(
        TfTokenVector const& names,
        HgiTextureHandleVector const& textures);

    /// By default HdxFullscreenShader creates a pipeline object that enables
    /// depth testing and enables depth write if there is a depth texture.
    /// This function allows you to override the depth and stencil state.
    HDX_API
    void SetDepthState(HgiDepthStencilState const& state);

    /// By default HdxFullscreenShader uses no blending (opaque).
    /// This function allows you to override blend state (e.g. alpha blending)
    HDX_API
    void SetBlendState(
        bool enableBlending,
        HgiBlendFactor srcColorBlendFactor,
        HgiBlendFactor dstColorBlendFactor,
        HgiBlendOp colorBlendOp,
        HgiBlendFactor srcAlphaBlendFactor,
        HgiBlendFactor dstAlphaBlendFactor,
        HgiBlendOp alphaBlendOp);

    /// Provide the shader constant values (uniforms).
    /// The data values are copied, so you do not have to set them
    /// each frame if they do not change in value.
    HDX_API
    void SetShaderConstants(
        uint32_t byteSize,
        const void* data);

    /// Draw the internal textures to the provided destination textures.
    /// `depth` is optional.
    HDX_API
    void Draw(HgiTextureHandle const& colorDst,
              HgiTextureHandle const& depthDst);

private:
    HdxFullscreenShader() = delete;

    using TextureMap = std::map<TfToken, HgiTextureHandle>;
    using BufferMap = std::map<uint32_t, HgiBufferHandle>;

    // Utility function to create buffer resources.
    void _CreateBufferResources();

    // Destroy shader program and the shader functions it holds.
    void _DestroyShaderProgram();

    // Utility to create resource bindings
    bool _CreateResourceBindings(TextureMap const& textures);

    // Utility to create default vertex buffer descriptor
    void _CreateVertexBufferDescriptor();

    // Utility to create a pipeline
    bool _CreatePipeline(
        HgiTextureHandle const& colorDst,
        HgiTextureHandle const& depthDst,
        bool depthWrite);

    // Utility to create a texture sampler
    bool _CreateSampler();

    // Internal draw method
    void _Draw(TextureMap const& textures,
              HgiTextureHandle const& colorDst,
              HgiTextureHandle const& depthDst,
              bool depthWrite);

    static HgiShaderFunctionDesc GetFullScreenVertexDesc();

    // Print shader compile errors.
    void _PrintCompileErrors();

    class Hgi* _hgi;

    std::string _debugName;

    TextureMap _textures;
    BufferMap _buffers;

    TfToken _glslfx;
    TfToken _shaderName;

    HgiBufferHandle _indexBuffer;
    HgiBufferHandle _vertexBuffer;
    HgiShaderProgramHandle _shaderProgram;
    HgiResourceBindingsHandle _resourceBindings;
    HgiGraphicsPipelineHandle _pipeline;
    HgiSamplerHandle _sampler;
    HgiVertexBufferDesc _vboDesc;

    HgiDepthStencilState _depthState;

    bool _blendingEnabled;
    HgiBlendFactor _srcColorBlendFactor;
    HgiBlendFactor _dstColorBlendFactor;
    HgiBlendOp _colorBlendOp;
    HgiBlendFactor _srcAlphaBlendFactor;
    HgiBlendFactor _dstAlphaBlendFactor;
    HgiBlendOp _alphaBlendOp;

    HgiAttachmentDesc _attachment0;
    HgiAttachmentDesc _depthAttachment;

    std::vector<uint8_t> _constantsData;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_FULLSCREENSHADER_H
