#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUtils/registeredVariantSet.h"
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
#ifndef FORGE_USD_USD_UTILS_REGISTERED_VARIANT_SET_H
#define FORGE_USD_USD_UTILS_REGISTERED_VARIANT_SET_H

/// \file usdUtils/registeredVariantSet.h

#include "forge/forge.h"
#include "forge/usd/usdUtils/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN


/// \class UsdUtilsRegisteredVariantSet
///
/// Class that holds information about variantSets that are registered with
/// the pipeline.
///
/// Registered variantSets are known variantSets in a pipeline that may need to
/// be reasoned about by apps during import/export.
///
/// \sa UsdUtilsGetRegisteredVariantSets
struct UsdUtilsRegisteredVariantSet
{
public:
    /// The name of the variantSet.
    const std::string name;

    /// This specifies how the variantSet should be treated during export.
    ///
    /// Note, in the plugInfo.json, the values for these enum's are
    /// lowerCamelCase.
    enum class SelectionExportPolicy {
        /// Never
        ///
        /// This variantSet selection is meant to remain entirely within an
        /// application.  This typically represents a "session" variantSelection
        /// that should not be transmitted down the pipeline.
        Never,

        /// IfAuthored
        ///
        /// This variantSet selection should be exported if there is an authored
        /// opinion in the application.  This is only relevant if the
        /// application is able to distinguish between "default" and "set"
        /// opinions.
        IfAuthored,

        /// Authored
        ///
        /// This variantSet selection should always be exported.
        Always,
    };

    /// Specifies how to export a variant selection.
    const SelectionExportPolicy selectionExportPolicy;

    UsdUtilsRegisteredVariantSet(
            const std::string& name,
            const SelectionExportPolicy& selectionExportPolicy) :
        name(name),
        selectionExportPolicy(selectionExportPolicy)
    {
    }

    // provided so this can be stored in a std::set.
    bool operator<(const UsdUtilsRegisteredVariantSet&
            other) const {
        return this->name < other.name;
    }
};


FORGE_NAMESPACE_END

#endif /* FORGE_USD_USD_UTILS_REGISTERED_VARIANT_SET_H */
