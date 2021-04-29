#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/instanceKey.h"
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
#ifndef FORGE_USD_PCP_INSTANCE_KEY_H
#define FORGE_USD_PCP_INSTANCE_KEY_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/mapExpression.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/pcp/site.h"
#include "forge/usd/pcp/types.h"

#include "forge/usd/sdf/layerOffset.h"

#include <boost/functional/hash.hpp>

#include <string>
#include <utility>
#include <vector>

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex;

/// \class PcpInstanceKey
///
/// A PcpInstanceKey identifies instanceable prim indexes that share the
/// same set of opinions. Instanceable prim indexes with equal instance
/// keys are guaranteed to have the same opinions for name children and
/// properties beneath those name children. They are NOT guaranteed to have
/// the same opinions for direct properties of the prim indexes themselves.
///
class PcpInstanceKey
{
public:
    PCP_API
    PcpInstanceKey();

    /// Create an instance key for the given prim index.
    PCP_API
    explicit PcpInstanceKey(const PcpPrimIndex& primIndex);

    /// Comparison operators
    PCP_API
    bool operator==(const PcpInstanceKey& rhs) const;
    PCP_API
    bool operator!=(const PcpInstanceKey& rhs) const;

    /// Returns hash value for this instance key.
    friend size_t hash_value(const PcpInstanceKey& key)
    {
        return key._hash;
    }

    /// \struct Hash
    ///
    /// Hash functor.
    ///
    struct Hash {
        inline size_t operator()(const PcpInstanceKey& key) const
        {
            return key._hash;
        }
    };

    /// Returns string representation of this instance key
    /// for debugging purposes.
    PCP_API
    std::string GetString() const;

private:
    struct _Collector;

    struct _Arc
    {
        explicit _Arc(const PcpNodeRef& node)
            : _arcType(node.GetArcType())
            , _sourceSite(node.GetSite())
            , _timeOffset(node.GetMapToRoot().GetTimeOffset())
        {
        }

        bool operator==(const _Arc& rhs) const
        {
            return _arcType == rhs._arcType    &&
                _sourceSite == rhs._sourceSite &&
                _timeOffset == rhs._timeOffset;
        }

        size_t GetHash() const
        {
            size_t hash = _arcType;
            boost::hash_combine(hash, _sourceSite);
            boost::hash_combine(hash, _timeOffset.GetHash());
            return hash;
        }

        PcpArcType _arcType;
        PcpSite _sourceSite;
        SdfLayerOffset _timeOffset;
    };
    std::vector<_Arc> _arcs;

    typedef std::pair<std::string, std::string> _VariantSelection;
    std::vector<_VariantSelection> _variantSelection;

    size_t _hash;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_INSTANCE_KEY_H
