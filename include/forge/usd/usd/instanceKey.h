#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/instanceKey.h"
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
#ifndef FORGE_USD_USD_INSTANCE_KEY_H
#define FORGE_USD_USD_INSTANCE_KEY_H

#include "forge/forge.h"
#include "forge/usd/usd/clipSetDefinition.h"
#include "forge/usd/usd/primData.h"
#include "forge/usd/usd/stageLoadRules.h"
#include "forge/usd/usd/stagePopulationMask.h"

#include "forge/usd/pcp/instanceKey.h"

#include <string>
#include <vector>
#include <iosfwd>

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex;

/// \class Usd_InstanceKey
///
/// Instancing key for prims. Instanceable prims that share the same
/// instance key are guaranteed to have the same opinions for name children
/// and properties and thus can share the same prototype.
///
class Usd_InstanceKey
{
public:
    Usd_InstanceKey();

    /// Create an instance key for the given instanceable prim index.
    explicit Usd_InstanceKey(const PcpPrimIndex& instance,
                             const UsdStagePopulationMask *popMask,
                             const UsdStageLoadRules &loadRules);

    /// Comparison operators.
    bool operator==(const Usd_InstanceKey& rhs) const;
    inline bool operator!=(const Usd_InstanceKey& rhs) const {
        return !(*this == rhs);
    }

private:
    friend size_t hash_value(const Usd_InstanceKey& key);

    friend std::ostream &
    operator<<(std::ostream &os, const Usd_InstanceKey &key);

    size_t _ComputeHash() const;

    PcpInstanceKey _pcpInstanceKey;
    std::vector<Usd_ClipSetDefinition> _clipDefs;
    UsdStagePopulationMask _mask;
    UsdStageLoadRules _loadRules;
    size_t _hash;
};

/// Return the hash code for \p key.
inline size_t
hash_value(const Usd_InstanceKey &key) {
    return key._hash;
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_INSTANCE_KEY_H
