#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/drawItem.h"
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
#ifndef FORGE_IMAGING_HD_DRAW_ITEM_H
#define FORGE_IMAGING_HD_DRAW_ITEM_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/drawingCoord.h"
#include "forge/imaging/hd/rprimSharedData.h"

#include "forge/imaging/hf/perfLog.h"

#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/bbox3d.h"
#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec4f.h"

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

/// \class HdDrawItem
///
/// A draw item is a light-weight representation of an HdRprim's resources and
/// material to be used for rendering. The visual representation (HdRepr) of an
/// HdRprim might require multiple draw items.
///
/// HdDrawItem(s) are created by the HdRprim (HdMesh, HdBasisCurve, ..) for each
/// HdRepr. The relevant compositional hierarchy is:
///
///  HdRprim
///  |
///  +--HdRepr(s)
///       |
///       +--HdDrawItem(s)
///
///  HdDrawItem(s) are consumed by HdRenderPass for its HdRprimCollection via
///  HdRenderIndex::GetDrawItems.
///
/// \note
/// Rendering backends may choose to specialize this class.
///
class HdDrawItem {
public:
    HF_MALLOC_TAG_NEW("new HdDrawItem");

    HD_API
    HdDrawItem(HdRprimSharedData const *sharedData);
    HD_API
    virtual ~HdDrawItem();

    HD_API
    SdfPath const &GetRprimID() const { return _sharedData->rprimID; }

    HD_API
    GfBBox3d const & GetBounds() const { return _sharedData->bounds; }

    HD_API
    GfRange3d const& GetExtent() const {
        return _sharedData->bounds.GetRange();
    }

    HD_API
    GfMatrix4d const& GetMatrix() const {
        return _sharedData->bounds.GetMatrix();
    }

    /// Returns a BufferRange of constant-Primvar.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetConstantPrimvarRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetConstantPrimvarIndex());
    }

    /// Returns the number of nested levels of instance primvars.
    HD_API
    int GetInstancePrimvarNumLevels() const {
        TF_VERIFY(_sharedData->instancerLevels != -1);
        return _sharedData->instancerLevels;
    }

    /// Returns a BufferRange of instance-Primvars at \p level
    /// the level is assigned to nested instancers in a bottom-up manner.
    ///
    /// example: (numLevels = 2)
    ///
    ///     instancerA         (level = 1)
    ///       |
    ///       +-- instancerB   (level = 0)
    ///             |
    ///             +-- mesh_prototype
    ///
    HD_API
    HdBufferArrayRangeSharedPtr const &GetInstancePrimvarRange(int level) const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetInstancePrimvarIndex(level));
    }

    /// Returns a BufferRange of instance-index indirection.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetInstanceIndexRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetInstanceIndexIndex());
    }

    /// Returns a BufferRange of element-Primvars.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetElementPrimvarRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetElementPrimvarIndex());
    }

    /// Returns a BufferArrayRange of topology.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetTopologyRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetTopologyIndex());
    }

    HD_API
    HdBufferArrayRangeSharedPtr const &GetTopologyVisibilityRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetTopologyVisibilityIndex());
    }

    /// Returns a BufferArrayRange of vertex-primvars.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetVertexPrimvarRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetVertexPrimvarIndex());
    }

    /// Returns a BufferArrayRange of varying primvars.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetVaryingPrimvarRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetVaryingPrimvarIndex());
    }


    /// Returns a BufferArrayRange of face-varying primvars.
    HD_API
    HdBufferArrayRangeSharedPtr const &GetFaceVaryingPrimvarRange() const {
        return _sharedData->barContainer.Get(
            _drawingCoord.GetFaceVaryingPrimvarIndex());
    }

    HD_API
    HdDrawingCoord *GetDrawingCoord() {
        return &_drawingCoord;
    }

    /// Returns the authored visibility, expressed by the delegate.
    HD_API
    bool GetVisible() const { return _sharedData->visible; }

    HD_API
    TfToken const& GetMaterialTag() const {
        return _sharedData->materialTag;
    }

    /// Returns true if the drawItem has instancer.
    HD_API
    bool HasInstancer() const {
        TF_VERIFY(_sharedData->instancerLevels != -1);
        return (_sharedData->instancerLevels > 0);
    }

    /// Returns the hash of the versions of underlying buffers. When the
    /// hash changes, it means the drawing coord might have been reassigned,
    /// so any drawing coord caching buffer (e.g. indirect dispatch buffer)
    /// has to be rebuilt at the moment.
    /// Note that this value is a hash, not sequential.
    HD_API
    size_t GetBufferArraysHash() const;

    /// Returns the hash of the element offsets of the underlying BARs.
    /// When the hash changes, it means that any drawing coord caching
    /// buffer (e.g. the indirect dispatch buffer) has to be rebuilt.
    /// Note that this value is a hash, not sequential.
    HD_API
    size_t GetElementOffsetsHash() const;

    /// Tests the intersection with the view projection matrix.
    /// Returns true if this drawItem is in the frustum.
    ///
    /// XXX: Currently if this drawitem uses HW instancing, always returns true.
    HD_API
    bool IntersectsViewVolume(GfMatrix4d const &viewProjMatrix) const;

    HD_API
    friend std::ostream &operator <<(std::ostream &out,
                                     const HdDrawItem& self);

protected:
    // TfHash support.
    template <class HashState>
    friend void TfHashAppend(HashState &h, HdDrawItem const &di);

    /// Returns the shared data
    HD_API
    HdRprimSharedData const *_GetSharedData() const {
        return _sharedData;
    }

    /// Allows derived classes to return a hash of the versions of buffers
    /// they manage.
    /// Called by GetBufferArraysHash.
    HD_API
    virtual size_t _GetBufferArraysHash() const;

    /// Allows derived classes to return a hash of the element offsets of
    /// the underlying BARs they manage.
    /// Called by GetBufferArraysHash.
    HD_API
    virtual size_t _GetElementOffsetsHash() const;

private:
    // configuration of how to bundle the drawing coordinate for this draw item
    // out of BARs in sharedData
    HdDrawingCoord _drawingCoord;

    // pointer to shared data across reprs, owned by rprim:
    //    bufferArrayRanges, bounds, visibility
    HdRprimSharedData const *_sharedData;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_DRAW_ITEM_H
