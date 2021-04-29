#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/visualizeAovTask.h"
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
#ifndef HDX_VISUALIZE_AOV_TASK_H
#define HDX_VISUALIZE_AOV_TASK_H

#include "forge/forge.h"
#include "forge/base/gf/vec3i.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"
#include "forge/imaging/hdx/tokens.h"
#include "forge/imaging/hgi/attachmentDesc.h"
#include "forge/imaging/hgi/buffer.h"
#include "forge/imaging/hgi/graphicsPipeline.h"
#include "forge/imaging/hgi/resourceBindings.h"
#include "forge/imaging/hgi/shaderProgram.h"
#include "forge/imaging/hgi/texture.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxVisualizeAovTask
///
/// A task for visualizing non-color AOVs such as depth, normals, primId.
///
/// Different kernels are used depending on the AOV:
///     Depth: Renormalized from the range [0.0, 1.0] to [min, max] depth
///            to provide better contrast.
///     Normals: Transform each component from [-1.0, 1.0] tp [0.0, 1.0] so that
///              negative components don't appear black.
///     Ids: Integer ids are colorized by multiplying by a large prime and
///          shuffling resulting bits so that neighboring ids are easily
///          distinguishable.
///     Other Aovs: A fallback kernel that transfers the AOV contents into a
///                 float texture is used.
///
/// This task updates the 'color' entry of the task context with the colorized
/// texture contents.
///
class HdxVisualizeAovTask : public HdxTask
{
public:
    HDX_API
    HdxVisualizeAovTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxVisualizeAovTask() override;

    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    // Enumeration of visualization kernels
    enum VizKernel {
        VizKernelDepth = 0,
        VizKernelId,
        VizKernelNormal,
        VizKernelFallback,
        VizKernelNone
    };

    HdxVisualizeAovTask() = delete;
    HdxVisualizeAovTask(const HdxVisualizeAovTask &) = delete;
    HdxVisualizeAovTask &operator =(const HdxVisualizeAovTask &) = delete;

    // Returns true if the enum member was updated, indicating that the kernel
    // to be used has changed.
    bool _UpdateVizKernel(TfToken const &aovName);

    // Returns a token used in sampling the texture based on the kernel used.
    TfToken const& _GetTextureIdentifierForShader() const;

    // Returns the fragment shader mixin based on the kernel used.
    TfToken const& _GetFragmentMixin() const;

    // ------------- Hgi resource creation/deletion utilities ------------------
    // Utility function to create the GL program for color correction
    bool _CreateShaderResources(HgiTextureDesc const& inputAovTextureDesc);

    // Utility function to create buffer resources.
    bool _CreateBufferResources();

    // Utility to create resource bindings
    bool _CreateResourceBindings(HgiTextureHandle const& inputAovTexture);

    // Utility to create a pipeline
    bool _CreatePipeline(HgiTextureDesc const& outputTextureDesc);

    // Utility to create a texture sampler
    bool _CreateSampler();

    // Create texture to write the colorized results into.
    bool _CreateOutputTexture(GfVec3i const &dimensions);

    // Destroy shader program and the shader functions it holds.
    void _DestroyShaderProgram();

    // Print shader compile errors.
    void _PrintCompileErrors();
    // -------------------------------------------------------------------------
    
    // Readback the depth AOV on the CPU to update min, max values.
    void _UpdateMinMaxDepth(HgiTextureHandle const &inputAovTexture);

    // Execute the appropriate kernel and update the task context 'color' entry.
    void _ApplyVisualizationKernel(HgiTextureHandle const& outputTexture);

    // Kernel dependent resources
    HgiTextureHandle _outputTexture;
    GfVec3i _outputTextureDimensions;
    HgiAttachmentDesc _outputAttachmentDesc;
    HgiShaderProgramHandle _shaderProgram;
    HgiResourceBindingsHandle _resourceBindings;
    HgiGraphicsPipelineHandle _pipeline;

    // Kernel independent resources
    HgiBufferHandle _indexBuffer;
    HgiBufferHandle _vertexBuffer;
    HgiSamplerHandle _sampler;

    float _screenSize[2];
    float _minMaxDepth[2];
    VizKernel _vizKernel;
};


/// \class HdxVisualizeAovTaskParams
///
/// `aovName`: The name of the aov to visualize.
///
/// The Hgi texture resource backing the AOV is retreived from the task context
/// instead of fetching the render buffer prim via its render index path.
/// HdxAovInputTask is responsible for updating the task context entry for
/// the active AOV.
///
struct HdxVisualizeAovTaskParams
{
    HDX_API
    HdxVisualizeAovTaskParams();

    TfToken aovName;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxVisualizeAovTaskParams& pv);
HDX_API
bool operator==(const HdxVisualizeAovTaskParams& lhs,
                const HdxVisualizeAovTaskParams& rhs);
HDX_API
bool operator!=(const HdxVisualizeAovTaskParams& lhs,
                const HdxVisualizeAovTaskParams& rhs);

FORGE_NAMESPACE_END

#endif
