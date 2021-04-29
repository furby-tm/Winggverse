#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/topology.h"
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
#ifndef FORGE_USD_USD_SKEL_TOPOLOGY_H
#define FORGE_USD_USD_SKEL_TOPOLOGY_H

/// \file usdSkel/topology.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"

#include "forge/base/tf/span.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/types.h"


FORGE_NAMESPACE_BEGIN


/// \class UsdSkelTopology
///
/// Object holding information describing skeleton topology.
/// This provides the hierarchical information needed to reason about joint
/// relationships in a manner suitable to computations.
class UsdSkelTopology
{
public:
    /// Construct an empty topology.
    UsdSkelTopology() = default;

    /// Construct a skel topology from \p paths, an array holding ordered joint
    /// paths as tokens.
    /// Internally, each token must be converted to an SdfPath. If SdfPath
    /// objects are already accessible, it is more efficient to use the
    /// construct taking an SdfPath array.
    USDSKEL_API
    UsdSkelTopology(TfSpan<const TfToken> paths);

    /// Construct a skel topology from \p paths, an array of joint paths.
    USDSKEL_API
    UsdSkelTopology(TfSpan<const SdfPath> paths);

    /// Construct a skel topology from an array of parent indices.
    /// For each joint, this provides the parent index of that
    /// joint, or -1 if none.
    USDSKEL_API
    UsdSkelTopology(const VtIntArray& parentIndices);

    /// Validate the topology.
    /// If validation is unsuccessful, a reason
    /// why will be written to \p reason, if provided.
    USDSKEL_API
    bool Validate(std::string* reason=nullptr) const;

    const VtIntArray& GetParentIndices() const { return _parentIndices; }

    size_t GetNumJoints() const { return size(); }

    size_t size() const { return _parentIndices.size(); }

    /// Returns the parent joint of the \p index'th joint,
    /// Returns -1 for joints with no parent (roots).
    inline int GetParent(size_t index) const;

    /// Returns true if the \p index'th joint is a root joint.
    bool IsRoot(size_t index) const { return GetParent(index) < 0; }

    bool operator==(const UsdSkelTopology& o) const;

    bool operator!=(const UsdSkelTopology& o) const {
        return !(*this == o);
    }

private:
    VtIntArray _parentIndices;
};


int
UsdSkelTopology::GetParent(size_t index) const
{
    TF_DEV_AXIOM(index < _parentIndices.size());
    return _parentIndices[index];
}


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_SKEL_TOPOLOGY_H
