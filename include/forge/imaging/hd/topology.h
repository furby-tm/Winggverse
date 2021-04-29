#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/topology.h"
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
#ifndef FORGE_IMAGING_HD_TOPOLOGY_H
#define FORGE_IMAGING_HD_TOPOLOGY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/base/arch/inttypes.h"

#include <ostream>

FORGE_NAMESPACE_BEGIN

class HdTopology {
public:
    typedef uint64_t ID;

    HdTopology() {};
    virtual ~HdTopology() {};

    /// Returns the hash value of this topology to be used for instancing.
    virtual ID ComputeHash() const = 0;
};

HD_API
std::ostream& operator << (std::ostream &out, HdTopology const &);


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_TOPOLOGY_H
