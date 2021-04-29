#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/resolveInfo.h"
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
#ifndef FORGE_USD_USD_RESOLVE_INFO_H
#define FORGE_USD_USD_RESOLVE_INFO_H

/// \file usd/resolveInfo.h

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/sdf/layerOffset.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/pcp/node.h"

#include "forge/base/tf/declarePtrs.h"

#include <limits>

FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_PTRS(PcpLayerStack);

/// \enum UsdResolveInfoSource
///
/// Describes the various sources of attribute values.
///
/// For more details, see \ref Usd_ValueResolution.
///
enum UsdResolveInfoSource
{
    UsdResolveInfoSourceNone,            ///< No value

    UsdResolveInfoSourceFallback,        ///< Built-in fallback value
    UsdResolveInfoSourceDefault,         ///< Attribute default value
    UsdResolveInfoSourceTimeSamples,     ///< Attribute time samples
    UsdResolveInfoSourceValueClips,      ///< Value clips
};

/// \class UsdResolveInfo
///
/// Container for information about the source of an attribute's value, i.e.
/// the 'resolved' location of the attribute.
///
/// For more details, see \ref Usd_ValueResolution.
///
class UsdResolveInfo
{
public:
    UsdResolveInfo()
        : _source(UsdResolveInfoSourceNone)
        , _layerIndex(std::numeric_limits<size_t>::max())
        , _valueIsBlocked(false)
    {
    }

    /// Return the source of the associated attribute's value.
    UsdResolveInfoSource GetSource() const {
        return _source;
    }

    /// Return true if this UsdResolveInfo represents an attribute that has an
    /// authored value opinion.  This will return `true` if there is *any*
    /// authored value opinion, including a \ref Usd_AttributeBlocking "block"
    ///
    /// This is equivalent to `HasAuthoredValue() || ValueIsBlocked()`
    bool HasAuthoredValueOpinion() const {
        return
            _source == UsdResolveInfoSourceDefault ||
            _source == UsdResolveInfoSourceTimeSamples ||
            _source == UsdResolveInfoSourceValueClips ||
            _valueIsBlocked;
    }

    /// Return true if this UsdResolveInfo represents an attribute that has an
    /// authored value that is not \ref Usd_AttributeBlocking "blocked"
    bool HasAuthoredValue() const {
        return
            _source == UsdResolveInfoSourceDefault ||
            _source == UsdResolveInfoSourceTimeSamples ||
            _source == UsdResolveInfoSourceValueClips;
    }

    /// Return the node within the containing PcpPrimIndex that provided
    /// the resolved value opinion.
    PcpNodeRef GetNode() const {
        return _node;
    }

    /// Return true if this UsdResolveInfo represents an attribute whose
    /// value is blocked.
    ///
    /// \see UsdAttribute::Block()
    bool ValueIsBlocked() const {
        return _valueIsBlocked;
    }

private:
    /// The source of the associated attribute's value.
    UsdResolveInfoSource _source;

    /// The LayerStack that provides the strongest value opinion.
    ///
    /// If \p source is either \p UsdResolveInfoSourceDefault
    /// or \p UsdResolveInfoTimeSamples, the source will be a layer
    /// in this LayerStack (\sa layerIndex).
    ///
    /// If \p source is UsdResolveInfoSourceValueClips, the source clips
    /// will have been introduced in this LayerStack.
    ///
    /// Otherwise, this LayerStack will be invalid.
    PcpLayerStackPtr _layerStack;

    /// The path to the prim that owns the attribute to query in
    /// \p layerStack to retrieve the strongest value opinion.
    ///
    /// If \p source is either \p UsdResolveInfoSourceDefault or
    /// \p UsdResolveInfoTimeSamples, this is the path to the prim
    /// specs in \p layerStack that own the attribute spec containing
    /// strongest value opinion.
    ///
    /// If \p source is UsdResolveInfoSourceValueClips, this is the
    /// path to the prim that should be used to query clips for attribute
    /// values.
    SdfPath _primPathInLayerStack;

    /// The index of the layer in \p layerStack that provides the
    /// strongest time sample or default opinion.
    ///
    /// This is valid only if \p source is either
    /// \p UsdResolveInfoSourceDefault or \p UsdResolveInfoTimeSamples.
    size_t _layerIndex;

    /// If \p source is \p UsdResolveInfoTimeSamples, the time
    /// offset that maps time in the strongest resolved layer
    /// to the stage.
    /// If no offset applies, this will be the identity offset.
    SdfLayerOffset _layerToStageOffset;

    /// If \p source is \p UsdResolveInfoSourceNone or
    /// \p UsdResolveInfoSourceFallback, this indicates whether or not
    /// this due to the value being blocked.
    bool _valueIsBlocked;

    /// The node within the containing PcpPrimIndex that provided
    /// the strongest value opinion.
    PcpNodeRef _node;

    friend class UsdAttribute;
    friend class UsdStage;
    friend class UsdStage_ResolveInfoAccess;
    friend class UsdAttributeQuery;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_RESOLVE_INFO_H
