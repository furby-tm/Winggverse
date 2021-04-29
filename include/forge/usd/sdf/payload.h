#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/payload.h"
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
#ifndef FORGE_USD_SDF_PAYLOAD_H
#define FORGE_USD_SDF_PAYLOAD_H

/// \file sdf/payload.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/layerOffset.h"
#include "forge/usd/sdf/path.h"

#include <boost/functional/hash.hpp>
#include <boost/operators.hpp>

#include <iosfwd>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class SdfPayload;

typedef std::vector<SdfPayload> SdfPayloadVector;

/// \class SdfPayload
///
/// Represents a payload and all its meta data.
///
/// A payload represents a prim reference to an external layer.  A payload
/// is similar to a prim reference (see SdfReference) with the major
/// difference that payloads are explicitly loaded by the user.
///
/// Unloaded payloads represent a boundary that lazy composition and
/// system behaviors will not traverse across, providing a user-visible
/// way to manage the working set of the scene.
///
class SdfPayload : boost::totally_ordered<SdfPayload> {
public:
    /// Creates a payload.
    ///
    SDF_API
    SdfPayload(
        const std::string &assetPath = std::string(),
        const SdfPath &primPath = SdfPath(),
        const SdfLayerOffset &layerOffset = SdfLayerOffset());

    /// Returns the asset path of the layer that the payload uses.
    const std::string &GetAssetPath() const {
        return _assetPath;
    }

    /// Sets a new asset path for the layer the payload uses.
    void SetAssetPath(const std::string &assetPath) {
        _assetPath = assetPath;
    }

    /// Returns the scene path of the prim for the payload.
    const SdfPath &GetPrimPath() const {
        return _primPath;
    }

    /// Sets a new prim path for the prim that the payload uses.
    void SetPrimPath(const SdfPath &primPath) {
        _primPath = primPath;
    }

    /// Returns the layer offset associated with the payload.
    const SdfLayerOffset &GetLayerOffset() const {
        return _layerOffset;
    }

    /// Sets a new layer offset.
    void SetLayerOffset(const SdfLayerOffset &layerOffset) {
        _layerOffset = layerOffset;
    }

    /// Returns whether this payload equals \a rhs.
    SDF_API bool operator==(const SdfPayload &rhs) const;

    /// Returns whether this payload is less than \a rhs.
    /// The meaning of less than is arbitrary but stable.
    SDF_API bool operator<(const SdfPayload &rhs) const;

private:
    friend inline size_t hash_value(const SdfPayload &p) {
        size_t h = 0;
        boost::hash_combine(h, p._assetPath);
        boost::hash_combine(h, p._primPath);
        boost::hash_combine(h, p._layerOffset);
        return h;
    }

    // The asset path to the external layer.
    std::string _assetPath;

    // The root prim path to the referenced prim in the external layer.
    SdfPath _primPath;

    // The layer offset to transform time.
    SdfLayerOffset _layerOffset;
};

/// Writes the string representation of \a SdfPayload to \a out.
SDF_API
std::ostream & operator<<(std::ostream &out, const SdfPayload &payload);

FORGE_NAMESPACE_END

#endif
