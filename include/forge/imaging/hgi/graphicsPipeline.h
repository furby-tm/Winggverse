#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgi/graphicsPipeline.h"
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
#ifndef FORGE_IMAGING_HGI_GRAPHICS_PIPELINE_H
#define FORGE_IMAGING_HGI_GRAPHICS_PIPELINE_H

#include "forge/forge.h"
#include "forge/imaging/hgi/api.h"
#include "forge/imaging/hgi/attachmentDesc.h"
#include "forge/imaging/hgi/enums.h"
#include "forge/imaging/hgi/handle.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgi/shaderProgram.h"
#include "forge/imaging/hgi/types.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \struct HgiVertexAttributeDesc
///
/// Describes one attribute of a vertex.
///
/// <ul>
/// <li>format:
///   Format of the vertex attribute.</li>
/// <li>offset:
///    The byte offset of the attribute in vertex buffer</li>
/// <li>shaderBindLocation:
///    The location of the attribute in the shader. layout(location = X)</li>
/// </ul>
///
struct HgiVertexAttributeDesc
{
    HGI_API
    HgiVertexAttributeDesc();

    HgiFormat format;
    uint32_t offset;
    uint32_t shaderBindLocation;
};
using HgiVertexAttributeDescVector = std::vector<HgiVertexAttributeDesc>;

HGI_API
bool operator==(
    const HgiVertexAttributeDesc& lhs,
    const HgiVertexAttributeDesc& rhs);

HGI_API
inline bool operator!=(
    const HgiVertexAttributeDesc& lhs,
    const HgiVertexAttributeDesc& rhs);


/// \struct HgiVertexBufferDesc
///
/// Describes the attributes of a vertex buffer.
///
/// <ul>
/// <li>bindingIndex:
///    Binding location for this vertex buffer.</li>
/// <li>vertexAttributes:
///   List of vertex attributes (in vertex buffer).</li>
/// <li>vertexStride:
///   The byte size of a vertex (distance between two vertices).</li>
/// </ul>
///
struct HgiVertexBufferDesc
{
    HGI_API
    HgiVertexBufferDesc();

    uint32_t bindingIndex;
    HgiVertexAttributeDescVector vertexAttributes;
    uint32_t vertexStride;
};
using HgiVertexBufferDescVector = std::vector<HgiVertexBufferDesc>;

HGI_API
bool operator==(
    const HgiVertexBufferDesc& lhs,
    const HgiVertexBufferDesc& rhs);

HGI_API
inline bool operator!=(
    const HgiVertexBufferDesc& lhs,
    const HgiVertexBufferDesc& rhs);


/// \struct HgiMultiSampleState
///
/// Properties to configure multi sampling.
///
/// <ul>
/// <li>alphaToCoverageEnable:
///   Fragment's color.a determines coverage (screen door transparency).</li>
/// <li>sampleCount:
///   The number of samples for each fragment. Must match attachments</li>
/// </ul>
///
struct HgiMultiSampleState
{
    HGI_API
    HgiMultiSampleState();

    bool alphaToCoverageEnable;
    HgiSampleCount sampleCount;
};

HGI_API
bool operator==(
    const HgiMultiSampleState& lhs,
    const HgiMultiSampleState& rhs);

HGI_API
bool operator!=(
    const HgiMultiSampleState& lhs,
    const HgiMultiSampleState& rhs);


/// \struct HgiRasterizationState
///
/// Properties to configure multi sampling.
///
/// <ul>
/// <li>polygonMode:
///   Determines the rasterization draw mode of primitve (triangles).</li>
/// <li>lineWidth:
///   The width of lines when polygonMode is set to line drawing.</li>
/// <li>cullMode:
///   Determines the culling rules for primitives (triangles).</li>
/// <li>winding:
///   The rule that determines what makes a front-facing primitive.</li>
/// <li>rasterizationEnabled:
///   When false all primitives are discarded before rasterization stage.</li>
/// </ul>
///
struct HgiRasterizationState
{
    HGI_API
    HgiRasterizationState();

    HgiPolygonMode polygonMode;
    float lineWidth;
    HgiCullMode cullMode;
    HgiWinding winding;
    bool rasterizerEnabled;
};

HGI_API
bool operator==(
    const HgiRasterizationState& lhs,
    const HgiRasterizationState& rhs);

HGI_API
bool operator!=(
    const HgiRasterizationState& lhs,
    const HgiRasterizationState& rhs);

/// \struct HgiDepthStencilState
///
/// Properties to configure depth and stencil test.
///
/// <ul>
/// <li>depthTestEnabled:
///   When enabled uses `depthCompareFn` to test if a fragment passes the
///   depth test. Note that depth writes are automatically disabled when
///   depthTestEnabled is false.</li>
/// <li>depthWriteEnabled:
///   When enabled uses `depthCompareFn` to test if a fragment passes the
///   depth test. Note that depth writes are automatically disabled when
///   depthTestEnabled is false.</li>
/// <li>stencilTestEnabled:
///   Enables the stencil test.</li>
/// </ul>
///
struct HgiDepthStencilState
{
    HGI_API
    HgiDepthStencilState();

    bool depthTestEnabled;
    bool depthWriteEnabled;
    HgiCompareFunction depthCompareFn;
    bool stencilTestEnabled;
};

HGI_API
bool operator==(
    const HgiDepthStencilState& lhs,
    const HgiDepthStencilState& rhs);

HGI_API
bool operator!=(
    const HgiDepthStencilState& lhs,
    const HgiDepthStencilState& rhs);

/// \struct HgiGraphicsShaderConstantsDesc
///
/// A small, but fast buffer of uniform data for shaders.
///
/// <ul>
/// <li>byteSize:
///    Size of the constants in bytes. (max 256 bytes)</li>
/// <li>stageUsage:
///    What shader stage(s) the constants will be used in.</li>
/// </ul>
///
struct HgiGraphicsShaderConstantsDesc {
    HGI_API
    HgiGraphicsShaderConstantsDesc();

    uint32_t byteSize;
    HgiShaderStage stageUsage;
};

HGI_API
bool operator==(
    const HgiGraphicsShaderConstantsDesc& lhs,
    const HgiGraphicsShaderConstantsDesc& rhs);

HGI_API
bool operator!=(
    const HgiGraphicsShaderConstantsDesc& lhs,
    const HgiGraphicsShaderConstantsDesc& rhs);

/// \struct HgiGraphicsPipelineDesc
///
/// Describes the properties needed to create a GPU pipeline.
///
/// <ul>
/// <li>primitiveType:
///   Describes the stream of vertices (primitive topology).</li>
/// <li>shaderProgram:
///   Shader functions/stages used in this pipeline.</li>
/// <li>depthState:
///   Describes depth state for a pipeline.</li>
/// <li>multiSampleState:
///   Various settings to control multi-sampling.</li>
/// <li>rasterizationState:
///   Various settings to control rasterization.</li>
/// <li>vertexBuffers:
///   Description of the vertex buffers (per-vertex attributes).
///   The actual VBOs are bound via GraphicsCmds.</li>
/// <li>colorAttachmentDescs:
///   Describes each of the color attachments.</li>
/// <li>colorResolveAttachmentDescs:
///   Describes each of the color resolve attachments (optional).</li>
/// <li>depthAttachmentDesc:
///   Describes the depth attachment (optional)
///   Use HgiFormatInvalid to indicate no depth attachment.</li>
/// <li>depthResolveAttachmentDesc:
///   Describes the depth resolve attachment (optional).
///   Use HgiFormatInvalid to indicate no depth resolve attachment.</li>
/// <li>shaderConstantsDesc:
///   Describes the shader uniforms.</li>
/// </ul>
///
struct HgiGraphicsPipelineDesc
{
    HGI_API
    HgiGraphicsPipelineDesc();

    std::string debugName;
    HgiPrimitiveType primitiveType;
    HgiShaderProgramHandle shaderProgram;
    HgiDepthStencilState depthState;
    HgiMultiSampleState multiSampleState;
    HgiRasterizationState rasterizationState;
    HgiVertexBufferDescVector vertexBuffers;
    HgiAttachmentDescVector colorAttachmentDescs;
    HgiAttachmentDescVector colorResolveAttachmentDescs;
    HgiAttachmentDesc depthAttachmentDesc;
    HgiAttachmentDesc depthResolveAttachmentDesc;
    HgiGraphicsShaderConstantsDesc shaderConstantsDesc;
};

HGI_API
bool operator==(
    const HgiGraphicsPipelineDesc& lhs,
    const HgiGraphicsPipelineDesc& rhs);

HGI_API
bool operator!=(
    const HgiGraphicsPipelineDesc& lhs,
    const HgiGraphicsPipelineDesc& rhs);


///
/// \class HgiGraphicsPipeline
///
/// Represents a graphics platform independent GPU graphics pipeline
/// resource.
///
/// Base class for Hgi pipelines.
/// To the client (HdPh) pipeline resources are referred to via
/// opaque, stateless handles (HgiPipelineHandle).
///
class HgiGraphicsPipeline
{
public:
    HGI_API
    virtual ~HgiGraphicsPipeline();

    /// The descriptor describes the object.
    HGI_API
    HgiGraphicsPipelineDesc const& GetDescriptor() const;

protected:
    HGI_API
    HgiGraphicsPipeline(HgiGraphicsPipelineDesc const& desc);

    HgiGraphicsPipelineDesc _descriptor;

private:
    HgiGraphicsPipeline() = delete;
    HgiGraphicsPipeline & operator=(const HgiGraphicsPipeline&) = delete;
    HgiGraphicsPipeline(const HgiGraphicsPipeline&) = delete;
};

using HgiGraphicsPipelineHandle = HgiHandle<HgiGraphicsPipeline>;
using HgiGraphicsPipelineHandleVector = std::vector<HgiGraphicsPipelineHandle>;


FORGE_NAMESPACE_END

#endif
