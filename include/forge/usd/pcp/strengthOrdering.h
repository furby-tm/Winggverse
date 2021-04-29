#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/strengthOrdering.h"
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
#ifndef FORGE_USD_PCP_STRENGTH_ORDERING_H
#define FORGE_USD_PCP_STRENGTH_ORDERING_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"

FORGE_NAMESPACE_BEGIN

class PcpNodeRef;

/// Compares the strength of nodes \p a and \p b. These nodes must be siblings;
/// it is a coding error if \p a and \p b do not have the same parent node.
///
/// Returns -1 if a is stronger than b,
///          0 if a is equivalent to b,
///          1 if a is weaker than b
PCP_API
int
PcpCompareSiblingNodeStrength(const PcpNodeRef& a, const PcpNodeRef& b);

/// Compares the strength of nodes \p a and \p b. These nodes must be part
/// of the same graph; it is a coding error if \p a and \p b do not have the
/// same root node.
///
/// Returns -1 if a is stronger than b,
///          0 if a is equivalent to b,
///          1 if a is weaker than b
PCP_API
int
PcpCompareNodeStrength(const PcpNodeRef& a, const PcpNodeRef& b);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_STRENGTH_ORDERING_H
