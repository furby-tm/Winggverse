#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/selectionTracker.h"
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
#ifndef FORGE_IMAGING_HDX_SELECTION_TRACKER_H
#define FORGE_IMAGING_HDX_SELECTION_TRACKER_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hd/selection.h"
#include "forge/base/vt/array.h"
#include <vector>
#include <memory>

FORGE_NAMESPACE_BEGIN


class HdRenderIndex;

using HdxSelectionTrackerSharedPtr =
    std::shared_ptr<class HdxSelectionTracker>;

/// ----------------------------------------------------------------------------
/// Selection highlighting in Hydra:
///
/// Hydra Stream (*) supports selection highlighting of:
/// (a) a set of rprims, wherein each rprim is entirely highlighted
/// (b) a set of instances of an rprim, wherein each instance is highlighted
/// (c) a set of subprimitives of an rprim, wherein each subprim is highlighted.
/// Subprimitives support is limited to elements (faces of meshes, or
/// individual curves of basis curves), edges of meshes/curves,
///  and points of meshes.
///
/// * While the goal is have an architecture that is extensible by rendering
/// backends, the current implementation is heavily influenced by the Stream(GL)
/// backend.
///
/// Background:
/// The current selection implementation is, in a sense, global in nature.
/// If there are no selected objects, we do not bind any selection-related
/// resources, nor does the shader execute any selection-related operations.
///
/// If there are one or more selected objects, we *don't* choose to have them
/// in a separate 'selection' collection.
/// Instead, we stick by AZDO principles and avoid command buffer changes as
/// a result of selection updates (which would involve removal of draw items
/// corresponding to the selected objects from each render pass' command buffer
/// and building the selection pass' command buffer).
/// We build an integer buffer encoding of the selected items, for use in the
/// fragment shader, that allows us to perform a small number of lookups to
/// quickly tell us if a fragment needs to be highlighted.
///
/// Conceptually, the implementation is split into:
/// (a) HdSelection : Client facing API that builds a collection of selected
/// items. This is agnostic of the rendering backend.
/// (b) HdxSelectionTracker: Base class that observes (a) and encodes it as
/// needed by (c). This may be specialized to be backend specific.
/// (c) HdxSelectionTask : A scene task that, currently, only syncs resources
/// related to selection highlighting. Currently, this is tied to Stream.
/// (d) HdxRenderSetupTask : A scene task that sets up the render pass shader
/// to use the selection highlighting mixin in the render pass(es) of
/// HdxRenderTask. This is relevant only to Stream.
///
/// ----------------------------------------------------------------------------


/// \class HdxSelectionTracker
///
/// HdxSelectionTracker takes HdSelection and generates a GPU buffer to be used
/// \class HdxSelectionTracker
///
/// HdxSelectionTracker is a base class for observing selection state and
/// providing selection highlighting details to interested clients.
///
/// Applications may use HdxSelectionTracker as-is, or extend it as needed.
///
/// HdxSelectionTask takes HdxSelectionTracker as a task parameter, and uploads
/// the selection buffer encoding to the GPU.
///
class HdxSelectionTracker
{
public:
    HDX_API
    HdxSelectionTracker();
    virtual ~HdxSelectionTracker();

    /// Optional override to update the HdSelection during
    /// HdxSelectionTask::Sync.
    HDX_API
    virtual void UpdateSelection(HdRenderIndex *index);

    /// Encodes the selection state (HdxSelection) as an integer array. This is
    /// uploaded to the GPU and decoded in the fragment shader to provide
    /// selection highlighting behavior. See HdxSelectionTask.
    /// Returns true if offsets has anything selected.
    /// \p enableSelection is a global on/off switch for selection; if it's
    /// false, nothing will be encoded.
    HDX_API
    virtual bool GetSelectionOffsetBuffer(HdRenderIndex const *index,
                                          bool enableSelection,
                                          VtIntArray *offsets) const;

    HDX_API
    virtual VtVec4fArray GetSelectedPointColors() const;

    /// Returns a monotonically increasing version number, which increments
    /// whenever the result of GetBuffers has changed. Note that this number may
    /// overflow and become negative, thus clients should use a not-equal
    /// comparison.
    HDX_API
    int GetVersion() const;

    /// The collection of selected objects is expected to be created externally
    /// and set via SetSelection.
    HDX_API
    void SetSelection(HdSelectionSharedPtr const &selection) {
        _selection = selection;
        _IncrementVersion();
    }

    /// XXX: Rename to GetSelection
    HDX_API
    HdSelectionSharedPtr const &GetSelectionMap() const {
        return _selection;
    }

protected:
    /// Increments the internal selection state version, used for invalidation
    /// via GetVersion().
    HDX_API
    void _IncrementVersion();

    HDX_API
    virtual bool _GetSelectionOffsets(HdSelection::HighlightMode const& mode,
                                      HdRenderIndex const* index,
                                      size_t modeOffset,
                                      std::vector<int>* offsets) const;

private:
    int _version;
    HdSelectionSharedPtr _selection;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_SELECTION_TRACKER_H
