#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/colorChannelTask.h"
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
#ifndef HDX_COLORCHANNEL_TASK_H
#define HDX_COLORCHANNEL_TASK_H

#include "forge/forge.h"
#include "forge/usd/sdf/path.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/task.h"
#include "forge/imaging/hdx/tokens.h"
#include "forge/imaging/hgi/graphicsCmds.h"

FORGE_NAMESPACE_BEGIN

/// \class HdxColorChannelTask
///
/// A task for choosing a color channel for display.
///
class HdxColorChannelTask : public HdxTask
{
public:
    HDX_API
    HdxColorChannelTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxColorChannelTask() override;

    /// Prepare the tasks resources
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute the color channel task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

protected:
    /// Sync the render pass resources
    HDX_API
    void _Sync(HdSceneDelegate* delegate,
               HdTaskContext* ctx,
               HdDirtyBits* dirtyBits) override;

private:
    HdxColorChannelTask() = delete;
    HdxColorChannelTask(const HdxColorChannelTask &) = delete;
    HdxColorChannelTask &operator =(const HdxColorChannelTask &) = delete;

    // Utility function to update the shader uniform parameters.
    // Returns true if the values were updated. False if unchanged.
    bool _UpdateParameterBuffer(float screenSizeX, float screenSizeY);

    /// Apply the color channel filtering.
    void _ApplyColorChannel();

    // This struct must match ParameterBuffer in colorChannel.glslfx.
    // Be careful to remember the std430 rules.
    struct _ParameterBuffer
    {
        float screenSize[2];
        int channel;
        bool operator==(const _ParameterBuffer& other) const {
            return channel == other.channel &&
                   screenSize[0] == other.screenSize[0] &&
                   screenSize[1] == other.screenSize[1];
        }
    };

    std::unique_ptr<class HdxFullscreenShader> _compositor;
    _ParameterBuffer _parameterData;

    // The color channel to be rendered (see HdxColorChannelTokens for the
    // possible values).
    TfToken _channel;
};


/// \class HdxColorChannelTaskParams
///
/// ColorChannelTask parameters.
///
struct HdxColorChannelTaskParams
{
    HdxColorChannelTaskParams() {}

    // Specifies which output color channel should be drawn. Defaults to 'color'
    // (untouched RGBA).
    TfToken channel = HdxColorChannelTokens->color;
};

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxColorChannelTaskParams& pv);
HDX_API
bool operator==(const HdxColorChannelTaskParams& lhs,
                const HdxColorChannelTaskParams& rhs);
HDX_API
bool operator!=(const HdxColorChannelTaskParams& lhs,
                const HdxColorChannelTaskParams& rhs);


FORGE_NAMESPACE_END

#endif
