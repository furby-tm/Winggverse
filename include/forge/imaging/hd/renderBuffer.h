#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/renderBuffer.h"
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
#ifndef FORGE_IMAGING_HD_RENDER_BUFFER_H
#define FORGE_IMAGING_HD_RENDER_BUFFER_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/bprim.h"
#include "forge/imaging/hd/types.h"
#include "forge/imaging/hd/enums.h"

#include "forge/base/gf/vec2i.h"

FORGE_NAMESPACE_BEGIN




/// \class HdRenderBuffer
///
/// A render buffer is a handle to a data resource that can be rendered into,
/// such as a 2d image for a draw target or auxiliary rendering output.
///
/// The render buffer can be used as an indexed prim, in which case it
/// communicates with the scene delegate to get buffer properties, or it can
/// be created out of band and supplied directly with allocation parameters.
///
/// Render buffers can be targeted by render passes.  They also contain
/// mapping functionality for reading and writing buffer data.
class HdRenderBuffer : public HdBprim {
public:
    // change tracking for HdRenderBuffer
    enum DirtyBits : HdDirtyBits {
        Clean               = 0,
        DirtyDescription    = 1 << 0,
        AllDirty            = (DirtyDescription)
    };

    HD_API
    HdRenderBuffer(SdfPath const& id);
    HD_API
    virtual ~HdRenderBuffer();

    // ---------------------------------------------------------------------- //
    /// \name Prim API
    // ---------------------------------------------------------------------- //

    /// Get initial invalidation state.
    HD_API
    virtual HdDirtyBits GetInitialDirtyBitsMask() const override;

    /// Get allocation information from the scene delegate.
    HD_API
    virtual void Sync(HdSceneDelegate *sceneDelegate,
                      HdRenderParam *renderParam,
                      HdDirtyBits *dirtyBits) override;

    /// Deallocate before deletion.
    HD_API
    virtual void Finalize(HdRenderParam *renderParam) override;

    // ---------------------------------------------------------------------- //
    /// \name Renderbuffer API
    // ---------------------------------------------------------------------- //

    /// Allocate a buffer.  Can be called from Sync(), or directly.
    /// If the buffer has already been allocated, calling Allocate() again
    /// will destroy the old buffer and allocate a new one.
    ///
    /// A negative dimension or invalid format will cause an allocation error.
    /// If the requested buffer can't be allocated, the function will return
    /// false.
    virtual bool Allocate(GfVec3i const& dimensions,
                          HdFormat format,
                          bool multiSampled) = 0;

    /// Get the buffer's width.
    virtual unsigned int GetWidth() const = 0;
    /// Get the buffer's height.
    virtual unsigned int GetHeight() const = 0;
    /// Get the buffer's depth.
    virtual unsigned int GetDepth() const = 0;
    /// Get the buffer's per-pixel format.
    virtual HdFormat GetFormat() const = 0;
    /// Get whether the buffer is multisampled.
    virtual bool IsMultiSampled() const = 0;

    /// Map the buffer for reading.
    virtual void* Map() = 0;
    /// Unmap the buffer. It is no longer safe to read from the buffer.
    virtual void Unmap() = 0;
    /// Return whether the buffer is currently mapped by anybody.
    virtual bool IsMapped() const = 0;

    /// Resolve the buffer so that reads reflect the latest writes.
    ///
    /// Some buffer implementations may defer final processing of writes until
    /// a buffer is read, for efficiency; examples include OpenGL MSAA or
    /// multi-sampled raytraced buffers.
    virtual void Resolve() = 0;

    /// Return whether the buffer is converged (whether the renderer is
    /// still adding samples or not).
    virtual bool IsConverged() const = 0;

    /// This optional API returns a (type-erased) resource that backs this
    /// render buffer. For example, a render buffer implementation may allocate
    /// a gpu texture that holds the data of the buffer. This function allows
    /// other parts of Hydra, such as a HdTask to get access to this resource.
    virtual VtValue GetResource(bool multiSampled) const {return VtValue();}

protected:
    /// Deallocate the buffer, freeing any owned resources.
    virtual void _Deallocate() = 0;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_RENDER_BUFFER_H