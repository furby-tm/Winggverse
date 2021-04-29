#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/cleanupTracker.h"
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
#ifndef FORGE_USD_SDF_CLEANUP_TRACKER_H
#define FORGE_USD_SDF_CLEANUP_TRACKER_H

/// \file sdf/cleanupTracker.h

#include "forge/forge.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/spec.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfSpec);

#include <vector>

/// \class Sdf_CleanupTracker
///
/// A singleton that tracks specs edited within an Sdf_CleanupEnabler scope.
///
/// When the last Sdf_CleanupEnabler goes out of scope, the specs are removed
/// from the layer if they are inert.
///
class Sdf_CleanupTracker : public TfWeakBase
{
public:

    /// Retrieves singleton instance.
    static Sdf_CleanupTracker &GetInstance();

    /// Adds the spec to the vector of tracked specs if there is at least one
    /// Sdf_CleanupEnabler on the stack.
    void AddSpecIfTracking(SdfSpecHandle const &spec);

    /// Return the authoring monitor identified by the index
    void CleanupSpecs();

private:

    Sdf_CleanupTracker();
    ~Sdf_CleanupTracker();

    std::vector<SdfSpecHandle> _specs;

    friend class TfSingleton<Sdf_CleanupTracker>;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_CLEANUP_TRACKER_H
