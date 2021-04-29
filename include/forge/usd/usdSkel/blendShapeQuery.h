#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/blendShapeQuery.h"
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
#ifndef FORGE_USD_USD_SKEL_BLEND_SHAPE_QUERY_H
#define FORGE_USD_USD_SKEL_BLEND_SHAPE_QUERY_H

/// \file usdSkel/blendShapeQuery.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"
#include "forge/usd/usdSkel/blendShape.h"
#include "forge/usd/usdSkel/inbetweenShape.h"

#include "forge/base/gf/vec3f.h"
#include "forge/base/tf/span.h"
#include "forge/base/vt/array.h"


FORGE_NAMESPACE_BEGIN


class UsdSkelBindingAPI;


/// \class UsdSkelBlendShapeQuery
///
/// Helper class used to resolve blend shape weights, including
/// inbetweens.
class UsdSkelBlendShapeQuery
{
public:

    UsdSkelBlendShapeQuery() = default;

    USDSKEL_API UsdSkelBlendShapeQuery(const UsdSkelBindingAPI& binding);

    /// Return true if this query is valid.
    bool IsValid() const { return bool(_prim); }

    /// Boolean conversion operator. Equivalent to IsValid().
    explicit operator bool() const { return IsValid(); }

    /// Returns the prim the blend shapes apply to.
    const UsdPrim& GetPrim() const { return _prim; }

    /// Returns the blend shape corresponding to \p blendShapeIndex.
    USDSKEL_API UsdSkelBlendShape GetBlendShape(size_t blendShapeIndex) const;

    /// Returns the inbetween shape corresponding to sub-shape \p i, if any.
    USDSKEL_API UsdSkelInbetweenShape GetInbetween(size_t subShapeIndex) const;

    /// Returns the blend shape index corresponding to the \p i'th sub-shape.
    USDSKEL_API size_t GetBlendShapeIndex(size_t subShapeIndex) const;

    size_t GetNumBlendShapes() const { return _blendShapes.size(); }

    size_t GetNumSubShapes() const { return _subShapes.size(); }

    /// Compute an array holding the point indices of all shapes.
    /// This is indexed by the _blendShapeIndices_ returned by
    /// ComputeSubShapes().
    /// Since the _pointIndices_ property of blend shapes is optional,
    /// some of the arrays may be empty.
    USDSKEL_API std::vector<VtIntArray>
    ComputeBlendShapePointIndices() const;

    /// Compute an array holding the point offsets of all sub-shapes.
    /// This includes offsets of both primary shapes -- those stored directly
    /// on a BlendShape primitive -- as well as those of inbetween shapes.
    /// This is indexed by the _subShapeIndices_ returned by
    /// ComputeSubShapeWeights().
    USDSKEL_API std::vector<VtVec3fArray>
    ComputeSubShapePointOffsets() const;

    /// Compute an array holding the normal offsets of all sub-shapes.
    /// This includes offsets of both primary shapes -- those stored directly
    /// on a BlendShape primitive -- as well as those of inbetween shapes.
    /// This is indexed by the _subShapeIndices_ returned by
    /// ComputeSubShapeWeights().
    /// Normal offsets are optional. An empty array is stored for shapes that
    /// do not specify normal offsets.
    USDSKEL_API std::vector<VtVec3fArray>
    ComputeSubShapeNormalOffsets() const;

    /// Compute the resolved weights for all sub-shapes bound to this prim.
    /// The \p weights values are initial weight values, ordered according
    /// to the _skel:blendShapeTargets_ relationship of the prim this query
    /// is associated with. If there are any inbetween shapes, a new set
    /// of weights is computed, providing weighting of the relevant inbetweens.
    ///
    /// All computed arrays shared the same size. Elements of the same index
    /// identify which sub-shape of which blend shape a given weight value
    /// is mapped to.
    USDSKEL_API bool
    ComputeSubShapeWeights(const TfSpan<const float>& weights,
                           VtFloatArray* subShapeWeights,
                           VtUIntArray* blendShapeIndices,
                           VtUIntArray* subShapeIndices) const;


    /// Compute a flattened array of weights for all sub-shapes.
    USDSKEL_API bool
    ComputeFlattenedSubShapeWeights(const TfSpan<const float>& weights,
                                    VtFloatArray* subShapeWeights) const;

    /// Deform \p points using the resolved sub-shapes given by
    /// \p subShapeWeights, \p blendShapeIndices and \p subShapeIndices.
    /// The \p blendShapePointIndices and \p blendShapePointOffsets
    /// arrays both provide the pre-computed point offsets and indices
    /// of each sub-shape, as computed by ComputeBlendShapePointIndices()
    /// and ComputeSubShapePointOffsets().
    USDSKEL_API bool
    ComputeDeformedPoints(
        const TfSpan<const float> subShapeWeights,
        const TfSpan<const unsigned> blendShapeIndices,
        const TfSpan<const unsigned> subShapeIndices,
        const std::vector<VtIntArray>& blendShapePointIndices,
        const std::vector<VtVec3fArray>& subShapePointOffsets,
        TfSpan<GfVec3f> points) const;

    /// Deform \p normals using the resolved sub-shapes given by
    /// \p subShapeWeights, \p blendShapeIndices and \p subShapeIndices.
    /// The \p blendShapePointIndices and \p blendShapeNormalOffsets
    /// arrays both provide the pre-computed normal offsets and indices
    /// of each sub-shape, as computed by ComputeBlendShapePointIndices()
    /// and ComputeSubShapeNormalOffsets().
    /// This is equivalent to ComputeDeformedPoints(), except that the
    /// resulting points are normalized after deformation.
    USDSKEL_API bool
    ComputeDeformedNormals(
        const TfSpan<const float> subShapeWeights,
        const TfSpan<const unsigned> blendShapeIndices,
        const TfSpan<const unsigned> subShapeIndices,
        const std::vector<VtIntArray>& blendShapePointIndices,
        const std::vector<VtVec3fArray>& subShapeNormalOffsets,
        TfSpan<GfVec3f> noramls) const;

    /// Compute a packed shape table combining all sub-shapes.
    /// This is intended to help encode blend shapes in a GPU-friendly form.
    /// The resulting \p offsets array holds contiguous runs of
    /// offsets for every point. The array holds all of the offsets of
    /// every blend shape for point 0, followed by the offset of every
    /// blend shape for point 1, and so forth.
    /// Offsets are stored as a GfVec4f. The first three components of each
    /// offset holds the actual offset value, while the last value holds
    /// the sub-shape index, as a float. The sub-shape index can be used
    /// to lookup a corresponding weight value in the 'subShapeWeights'
    /// array returned by ComputeSubShapeWeights.
    USDSKEL_API bool
    ComputePackedShapeTable(VtVec4fArray* offsets,
                            VtVec2iArray* ranges) const;

    USDSKEL_API
    std::string GetDescription() const;

private:

    /// Object identifying a general subshape.
    struct _SubShape {
        _SubShape() = default;

        _SubShape(unsigned blendShapeIndex, int inbetweenIndex, float weight)
            : _blendShapeIndex(blendShapeIndex),
              _inbetweenIndex(inbetweenIndex),
              _weight(weight) {}

        unsigned GetBlendShapeIndex() const { return _blendShapeIndex; }

        int GetInbetweenIndex() const { return _inbetweenIndex; }

        bool IsInbetween() const    { return _inbetweenIndex >= 0; }
        bool IsNullShape() const    { return _weight == 0.0f; }
        bool IsPrimaryShape() const { return _weight == 1.0f; }

        float GetWeight() const { return _weight; }

    private:
        unsigned _blendShapeIndex = 0;
        int _inbetweenIndex = 0;
        float _weight = 0;
    };

    struct _SubShapeCompareByWeight {
        bool operator()(const _SubShape& lhs, const _SubShape& rhs) const
             { return lhs.GetWeight() < rhs.GetWeight(); }

        bool operator()(float lhs, const _SubShape& rhs) const
             { return lhs < rhs.GetWeight(); }
    };

    struct _BlendShape {
        UsdSkelBlendShape shape;
        size_t firstSubShape = 0;
        size_t numSubShapes = 0;
    };

    UsdPrim _prim;
    std::vector<_SubShape> _subShapes;
    std::vector<_BlendShape> _blendShapes;
    std::vector<UsdSkelInbetweenShape> _inbetweens;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SKEL_BLEND_SHAPE_QUERY_H
