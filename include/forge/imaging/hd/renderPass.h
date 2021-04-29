#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/renderPass.h"
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
#ifndef FORGE_IMAGING_HD_RENDER_PASS_H
#define FORGE_IMAGING_HD_RENDER_PASS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/changeTracker.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hd/task.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdRenderIndex;
class HdSceneDelegate;

using HdDirtyListSharedPtr = std::shared_ptr<class HdDirtyList>;
using HdRenderPassSharedPtr = std::shared_ptr<class HdRenderPass>;
using HdRenderPassStateSharedPtr = std::shared_ptr<class HdRenderPassState>;

/// \class HdRenderPass
///
/// An abstract class representing a single render iteration over a set of prims
/// (the HdRprimCollection), for the camera/viewport parameters in
/// HdRenderPassState.
///
/// Conceptually, a rendering task may be broken down into one or more
/// HdRenderPass(es).
///
/// An HdRenderPass has two phases, Sync() and Execute(), in line with Hydra's
/// execution phases (See HdEngine::Execute)
///
/// The base class implementation of Sync() takes care of syncing collection
/// changes with the HdRenderIndex via HdDirtyList, and allows derived classes
/// to track collection changes (via _MarkCollectionDirty) and sync additional
/// resources (via _Sync)
///
/// Renderer backends implement _Execute, wherein the HdDrawItem(s) for the
/// collection may be consumed via HdRenderIndex::GetDrawItems.
/// Typically, the HdRenderPassState argument of _Execute is made available via
/// the HdTaskContext.
///
/// \note
/// Rendering backends are expected to specialize this abstract class, and
/// return the specialized object via HdRenderDelegate::CreateRenderPass
///
class HdRenderPass
{
public:
    HD_API
    HdRenderPass(HdRenderIndex *index, HdRprimCollection const& collection);
    HD_API
    virtual ~HdRenderPass();

    /// Returns the HdRprimCollection to be drawn by this RenderPass.
    HdRprimCollection const& GetRprimCollection() const { return _collection; }

    /// Sets the HdRprimCollection, note that this may invalidate internal
    /// caches used to accelerate drawing.
    HD_API
    void SetRprimCollection(HdRprimCollection const& col);

    /// Returns the dirty list (maintained in the change tracker) for
    /// efficient traversal
    HdDirtyListSharedPtr const &GetDirtyList() const {
        return _dirtyList;
    }

    /// Return the render index
    HdRenderIndex* GetRenderIndex() const { return _renderIndex; }

    // ---------------------------------------------------------------------- //
    /// \name Synchronization
    // ---------------------------------------------------------------------- //

    /// Sync the render pass resources
    HD_API
    void Sync();

    // ---------------------------------------------------------------------- //
    /// \name Prepare
    // ---------------------------------------------------------------------- //

    /// Prepare renderpass data
    HD_API
    void Prepare(TfTokenVector const &renderTags);

    // ---------------------------------------------------------------------- //
    /// \name Execution
    // ---------------------------------------------------------------------- //

    /// Execute a subset of buckets of this renderpass.
    HD_API
    void Execute(HdRenderPassStateSharedPtr const &renderPassState,
                 TfTokenVector const &renderTags);

    // ---------------------------------------------------------------------- //
    /// \name Optional API hooks for progressive rendering
    // ---------------------------------------------------------------------- //

    virtual bool IsConverged() const { return true; }

protected:
    /// Virtual API: Execute the buckets corresponding to renderTags;
    /// renderTags.empty() implies execute everything.
    virtual void _Execute(HdRenderPassStateSharedPtr const &renderPassState,
                         TfTokenVector const &renderTags) = 0;

    /// Optional API: let derived classes mark their collection tracking as dirty.
    virtual void _MarkCollectionDirty() {}

    /// Optional API: let derived classes sync data.
    virtual void _Sync() {}

    /// Optional API: let derived classes prepare data.
    virtual void _Prepare(TfTokenVector const &renderTags) {}

private:

    // Don't allow copies
    HdRenderPass(const HdRenderPass &) = delete;
    HdRenderPass &operator=(const HdRenderPass &) = delete;

    // ---------------------------------------------------------------------- //
    // \name Change Tracking State
    // ---------------------------------------------------------------------- //
    // The renderIndex to which this renderPass belongs
    // (can't change after construction)
    HdRenderIndex * const _renderIndex;

    // cached dirty prims list
    HdDirtyListSharedPtr _dirtyList;

    // ---------------------------------------------------------------------- //
    // \name Core RenderPass State
    // ---------------------------------------------------------------------- //
    HdRprimCollection _collection;
};

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_RENDER_PASS_H
