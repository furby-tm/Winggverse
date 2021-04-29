#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ndr/filesystemDiscoveryHelpers.h"
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

#ifndef FORGE_USD_NDR_FILESYSTEM_DISCOVERY_HELPERS_H
#define FORGE_USD_NDR_FILESYSTEM_DISCOVERY_HELPERS_H

/// \file ndr/filesystemDiscoveryHelpers.h

#include "forge/forge.h"
#include "forge/usd/ndr/api.h"
#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/nodeDiscoveryResult.h"

FORGE_NAMESPACE_BEGIN

class NdrDiscoveryPluginContext;

/// \file filesystemDiscoveryHelpers.h
///
/// Provides utilities that the default filesystem discovery plugin uses. If
/// a custom filesystem discovery plugin is needed, these can be used to fill
/// in a large chunk of the functionality.
///

/// Walks the specified search paths, optionally following symlinks. Paths
/// are walked recursively, and each directory has `FsHelpersExamineFiles()`
/// called on it. Only files that match one of the provided extensions (case
/// insensitive) are candidates for being turned into `NdrDiscoveryResult`s.
/// Returns a vector of discovery results that have been found while walking
/// the search paths.  In each result the name and identifier will be the
/// same, the version will be invalid and default, and the family will
/// be empty.  The caller is expected to adjust these as appropriate.  A
/// naive client with no versions and no family will work correctly.
NDR_API
NdrNodeDiscoveryResultVec
NdrFsHelpersDiscoverNodes(
    const NdrStringVec& searchPaths,
    const NdrStringVec& allowedExtensions,
    bool followSymlinks = true,
    const NdrDiscoveryPluginContext* context = nullptr
);

FORGE_NAMESPACE_END

#endif // FORGE_USD_NDR_FILESYSTEM_DISCOVERY_HELPERS_H
