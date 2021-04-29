#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/clipSetDefinition.h"
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
#ifndef FORGE_USD_USD_CLIP_SET_DEFINITION_H
#define FORGE_USD_USD_CLIP_SET_DEFINITION_H

#include "forge/forge.h"

#include "forge/usd/sdf/assetPath.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/vt/array.h"
#include "forge/base/gf/vec2d.h"
#include "forge/base/tf/declarePtrs.h"

#include <boost/optional.hpp>

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex;
TF_DECLARE_WEAK_PTRS(PcpLayerStack);

/// \class Usd_ClipSetDefinition
///
/// Collection of metadata from scene description and other information that
/// uniquely defines a clip set.
class Usd_ClipSetDefinition
{
public:
    Usd_ClipSetDefinition()
        : interpolateMissingClipValues(false)
        , indexOfLayerWhereAssetPathsFound(0)
    {
    }

    bool operator==(const Usd_ClipSetDefinition& rhs) const
    {
        return (clipAssetPaths == rhs.clipAssetPaths
            && clipManifestAssetPath == rhs.clipManifestAssetPath
            && clipPrimPath == rhs.clipPrimPath
            && clipActive == rhs.clipActive
            && clipTimes == rhs.clipTimes
            && interpolateMissingClipValues == rhs.interpolateMissingClipValues
            && sourceLayerStack == rhs.sourceLayerStack
            && sourcePrimPath == rhs.sourcePrimPath
            && indexOfLayerWhereAssetPathsFound
                    == rhs.indexOfLayerWhereAssetPathsFound);
    }

    bool operator!=(const Usd_ClipSetDefinition& rhs) const
    {
        return !(*this == rhs);
    }

    size_t GetHash() const
    {
        size_t hash = indexOfLayerWhereAssetPathsFound;
        boost::hash_combine(hash, sourceLayerStack);
        boost::hash_combine(hash, sourcePrimPath);

        if (clipAssetPaths) {
            for (const auto& assetPath : *clipAssetPaths) {
                boost::hash_combine(hash, assetPath.GetHash());
            }
        }
        if (clipManifestAssetPath) {
            boost::hash_combine(hash, clipManifestAssetPath->GetHash());
        }
        if (clipPrimPath) {
            boost::hash_combine(hash, *clipPrimPath);
        }
        if (clipActive) {
            for (const auto& active : *clipActive) {
                boost::hash_combine(hash, active[0]);
                boost::hash_combine(hash, active[1]);
            }
        }
        if (clipTimes) {
            for (const auto& time : *clipTimes) {
                boost::hash_combine(hash, time[0]);
                boost::hash_combine(hash, time[1]);
            }
        }
        if (interpolateMissingClipValues) {
            boost::hash_combine(hash, *interpolateMissingClipValues);
        }

        return hash;
    }

    boost::optional<VtArray<SdfAssetPath> > clipAssetPaths;
    boost::optional<SdfAssetPath> clipManifestAssetPath;
    boost::optional<std::string> clipPrimPath;
    boost::optional<VtVec2dArray> clipActive;
    boost::optional<VtVec2dArray> clipTimes;
    boost::optional<bool> interpolateMissingClipValues;

    PcpLayerStackPtr sourceLayerStack;
    SdfPath sourcePrimPath;
    size_t indexOfLayerWhereAssetPathsFound;
};

/// Computes clip set definitions for the given \p primIndex and returns
/// them in \p clipSetDefinitions. The clip sets in this vector are sorted in
/// strength order. If \p clipSetNames is provided it will contain the name
/// for each clip set in the corresponding position in \p clipSetDefinitions.
void
Usd_ComputeClipSetDefinitionsForPrimIndex(
    const PcpPrimIndex& primIndex,
    std::vector<Usd_ClipSetDefinition>* clipSetDefinitions,
    std::vector<std::string>* clipSetNames = nullptr);

FORGE_NAMESPACE_END

#endif
