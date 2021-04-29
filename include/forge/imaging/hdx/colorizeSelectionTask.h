#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/colorizeSelectionTask.h"
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
#ifndef FORGE_IMAGING_HDX_COLORIZE_SELECTION_TASK_H
#define FORGE_IMAGING_HDX_COLORIZE_SELECTION_TASK_H

#include "forge/forge.h"
#include "forge/base/gf/vec2f.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"

#include "forge/imaging/hgi/texture.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxColorizeSelectionTaskParams
///
/// Input parameters for HdxColorizeSelectionTask
///
struct HdxColorizeSelectionTaskParams
{
    HdxColorizeSelectionTaskParams()
        : enableSelection(false)
        , selectionColor(0)
        , locateColor(0)
        , enableOutline(false)
        , outlineRadius(5)
        , primIdBufferPath()
        , instanceIdBufferPath()
        , elementIdBufferPath()
        {}

    bool enableSelection;
    GfVec4f selectionColor;
    GfVec4f locateColor;
    bool enableOutline;
    unsigned int outlineRadius;

    SdfPath primIdBufferPath;
    SdfPath instanceIdBufferPath;
    SdfPath elementIdBufferPath;
};

/// \class HdxColorizeSelectionTask
///
/// A task for taking ID buffer data and turning it into a "selection overlay"
/// that can be composited on top of hydra's color output.
///
/// If enableOutline is true then instead of overlaying the ID buffer as is, an
/// outline with thickness of outlineRadius pixels around the areas with IDs
/// will be overlaid. Otherwise, the ID buffer will be overlaid as is.
class HdxColorizeSelectionTask : public HdxTask
{
public:
    HDX_API
    HdxColorizeSelectionTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxColorizeSelectionTask() override;

    /// Hooks for progressive rendering.
    bool IsConverged() const override;

    /// Prepare the render pass resources
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute the task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    /// Sync the render pass resources
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    // The core colorizing logic of this task: given the ID buffers and the
    // selection buffer, produce a color output at each pixel.
    void _ColorizeSelection();

    GfVec4f _GetColorForMode(int mode) const;

    // Utility function to update the shader uniform parameters.
    // Returns true if the values were updated. False if unchanged.
    bool _UpdateParameterBuffer();

    // Create a new GPU texture for the provided format and pixel data.
    // If an old texture exists it will be destroyed first.
    void _CreateTexture(
        int width,
        int height,
        HdFormat format,
        void *data);

    // This struct must match ParameterBuffer in outline.glslfx.
    // Be careful to remember the std430 rules.
    struct _ParameterBuffer
    {
        // Size of a colorIn texel - to iterate adjacent texels.
        GfVec2f texelSize;
        // Draws outline when enabled, or color overlay when disabled.
        int enableOutline = 0;
        // The outline radius (thickness).
        int radius = 5;

        bool operator==(const _ParameterBuffer& other) const {
            return texelSize == other.texelSize &&
                   enableOutline == other.enableOutline &&
                   radius == other.radius;
        }
    };

    // Incoming data
    HdxColorizeSelectionTaskParams _params;

    int _lastVersion;
    bool _hasSelection;
    VtIntArray _selectionOffsets;

    HdRenderBuffer *_primId;
    HdRenderBuffer *_instanceId;
    HdRenderBuffer *_elementId;

    uint8_t *_outputBuffer;
    size_t _outputBufferSize;
    bool _converged;

    std::unique_ptr<class HdxFullscreenShader> _compositor;

    _ParameterBuffer _parameterData;
    HgiTextureHandle _texture;
    bool _pipelineCreated;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out,
    const HdxColorizeSelectionTaskParams& pv);
HDX_API
bool operator==(const HdxColorizeSelectionTaskParams& lhs,
                const HdxColorizeSelectionTaskParams& rhs);
HDX_API
bool operator!=(const HdxColorizeSelectionTaskParams& lhs,
                const HdxColorizeSelectionTaskParams& rhs);

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_COLORIZE_SELECTION_TASK_H
