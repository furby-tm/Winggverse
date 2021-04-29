#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/statistics.h"
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
#ifndef FORGE_USD_PCP_STATISTICS_H
#define FORGE_USD_PCP_STATISTICS_H

#include "forge/forge.h"

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

class PcpCache;
class PcpPrimIndex;

/// Accumulate and print statistics about the contents of \p cache to
/// \p out.
void
Pcp_PrintCacheStatistics(
    const PcpCache* cache, std::ostream& out);

/// Accumulate and print statistics about the contents of \p primIndex to
/// \p out.
void
Pcp_PrintPrimIndexStatistics(
    const PcpPrimIndex& primIndex, std::ostream& out);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_STATISTICS_H
