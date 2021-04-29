#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/cleanupEnabler.h"
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
#ifndef FORGE_USD_SDF_CLEANUP_ENABLER_H
#define FORGE_USD_SDF_CLEANUP_ENABLER_H

/// \file sdf/cleanupEnabler.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/base/tf/stacked.h"

FORGE_NAMESPACE_BEGIN

/// \class SdfCleanupEnabler
///
/// An RAII class which, when an instance is alive, enables scheduling of
/// automatic cleanup of SdfLayers.
///
/// Any affected specs which no longer contribute to the scene will be removed
/// when the last SdfCleanupEnabler instance goes out of scope. Note that for
/// this purpose, SdfPropertySpecs are removed if they have only required fields
/// (see SdfPropertySpecs::HasOnlyRequiredFields), but only if the property spec
/// itself was affected by an edit that left it with only required fields. This
/// will have the effect of uninstantiating on-demand attributes. For example,
/// if its parent prim was affected by an edit that left it otherwise inert, it
/// will not be removed if it contains an SdfPropertySpec with only required
/// fields, but if the property spec itself is edited leaving it with only
/// required fields, it will be removed, potentially uninstantiating it if it's
/// an on-demand property.
///
/// SdfCleanupEnablers are accessible in both C++ and Python.
///
/// /// SdfCleanupEnabler can be used in the following manner:
/// \code
/// {
///     SdfCleanupEnabler enabler;
///
///     // Perform any action that might otherwise leave inert specs around,
///     // such as removing info from properties or prims, or removing name
///     // children. i.e:
///     primSpec->ClearInfo(SdfFieldKeys->Default);
///
///     // When enabler goes out of scope on the next line, primSpec will
///     // be removed if it has been left as an empty over.
/// }
/// \endcode
///
TF_DEFINE_STACKED(SdfCleanupEnabler, false, SDF_API)
{
public:

    SDF_API SdfCleanupEnabler();

    SDF_API ~SdfCleanupEnabler();

    /// Returns whether cleanup is currently being scheduled.
    SDF_API static bool IsCleanupEnabled();
};

FORGE_NAMESPACE_END

#endif  // #ifndef FORGE_USD_SDF_CLEANUP_ENABLER_H
