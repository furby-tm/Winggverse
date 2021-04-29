#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/aov.h"
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
#ifndef FORGE_IMAGING_HD_AOV_H
#define FORGE_IMAGING_HD_AOV_H

#include "forge/forge.h"

#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/types.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/gf/vec3i.h"
#include "forge/base/tf/hashmap.h"
#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

typedef TfHashMap<TfToken, VtValue, TfToken::HashFunctor> HdAovSettingsMap;

/// \class HdAovDescriptor
///
/// A bundle of state describing an AOV ("Arbitrary Output Variable") display
/// channel. Note that in hydra API, this data is split between
/// HdRenderPassAovBinding and HdRenderBufferDescriptor. This class is
/// provided for use in higher level application-facing API.
struct HdAovDescriptor
{
    HdAovDescriptor()
        : format(HdFormatInvalid), multiSampled(false)
        , clearValue(), aovSettings() {}
    HdAovDescriptor(HdFormat f, bool ms, VtValue const& c)
        : format(f), multiSampled(ms), clearValue(c), aovSettings() {}

    // ----------------------------------------------------------------
    // Render buffer parameters
    // ----------------------------------------------------------------

    /// The AOV output format. See also HdRenderBufferDescriptor#format.
    HdFormat format;

    /// Whether the render buffer should be multisampled.
    /// See also HdRenderBufferDescriptor#multiSampled.
    bool multiSampled;

    // ----------------------------------------------------------------
    // Renderpass binding parameters.
    // ----------------------------------------------------------------

    /// The clear value to apply to the render buffer before rendering.
    /// The type of "clearValue" should match the provided format.
    /// If clearValue is empty, no clear will be performed.
    /// See also HdRenderPassAovBinding#clearValue.
    VtValue clearValue;

    /// Extra settings for AOV rendering, such as pixel filtering options.
    /// See also HdRenderPassAovBinding#aovSettings.
    HdAovSettingsMap aovSettings;
};
typedef std::vector<HdAovDescriptor> HdAovDescriptorList;

/// \struct HdRenderBufferDescriptor
///
/// Describes the allocation structure of a render buffer bprim.
struct HdRenderBufferDescriptor {
    /// The width, height, and depth of the allocated render buffer.
    GfVec3i dimensions;

    /// The data format of the render buffer. See also HdAovDescriptor#format.
    HdFormat format;

    /// Whether the render buffer should be multisampled. See also
    /// HdAovDescriptor#multiSampled.
    bool multiSampled;

    bool operator==(HdRenderBufferDescriptor const& rhs) const {
        return dimensions == rhs.dimensions &&
               format == rhs.format && multiSampled == rhs.multiSampled;
    }
    bool operator!=(HdRenderBufferDescriptor const& rhs) const {
        return !(*this == rhs);
    }
};

/// \class HdRenderPassAovBinding
///
/// A renderpass AOV represents a binding of some output of the
/// rendering process to an output buffer.

class HdRenderBuffer;

struct HdRenderPassAovBinding {

    HdRenderPassAovBinding()
        : renderBuffer(nullptr) {}

    /// The identifier of the renderer output to be consumed. This should take
    /// a value from HdAovTokens.
    /// XXX: Depth aov bindings are identified by the "depth" suffix.
    /// See HdAovHasDepthSemantic().
    TfToken aovName;

    /// The render buffer to be bound to the above terminal output.
    ///
    /// From the app or scene, this can be specified as either a pointer or
    /// a path to a renderbuffer in the render index. If both are specified,
    /// the pointer is used preferentially.
    ///
    /// Note: hydra never takes ownership of the renderBuffer, but assumes it
    /// will be alive until the end of the renderpass, or whenever the buffer
    /// is marked converged, whichever is later.
    HdRenderBuffer* renderBuffer;

    /// The render buffer to be bound to the above terminal output.
    SdfPath renderBufferId;

    /// The clear value to apply to the bound render buffer, before rendering.
    /// The type of "clearValue" should match the type of the bound buffer.
    /// If clearValue is empty, it indicates no clear should be performed.
    /// See also HdAovDescriptor#clearValue.
    VtValue clearValue;

    /// Extra settings for AOV rendering, such as pixel filtering options.
    /// See also HdAovDescriptor#aovSettings.
    HdAovSettingsMap aovSettings;
};

typedef std::vector<HdRenderPassAovBinding> HdRenderPassAovBindingVector;

// VtValue requirements for HdRenderPassAovBinding
HD_API
std::ostream& operator<<(std::ostream& out,
    const HdRenderPassAovBinding& desc);
HD_API
bool operator==(const HdRenderPassAovBinding& lhs,
    const HdRenderPassAovBinding& rhs);
HD_API
bool operator!=(const HdRenderPassAovBinding& lhs,
    const HdRenderPassAovBinding& rhs);

HD_API
size_t hash_value(const HdRenderPassAovBinding &b);

/// Returns true if the aov is used as a depth binding based on its name.
HD_API
bool HdAovHasDepthSemantic(TfToken const& aovName);

/// \class HdParsedAovToken
///
/// Represents an AOV token which has been parsed to extract the prefix
/// (in the case of "primvars:"/"lpe:"/etc.).
struct HdParsedAovToken {
    HD_API
    HdParsedAovToken();
    HD_API
    HdParsedAovToken(TfToken const& aovName);

    TfToken name;
    bool isPrimvar : 1;
    bool isLpe : 1;
    bool isShader : 1;
};
typedef std::vector<HdParsedAovToken> HdParsedAovTokenVector;

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_AOV_H
