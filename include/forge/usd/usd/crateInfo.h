#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/crateInfo.h"
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
#ifndef FORGE_USD_USD_CRATE_INFO_H
#define FORGE_USD_USD_CRATE_INFO_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/base/tf/token.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class UsdCrateInfo
///
/// A class for introspecting the underlying qualities of .usdc 'crate' files,
/// for diagnostic purposes.
///
class UsdCrateInfo
{
public:
    struct Section {
        Section() = default;
        Section(std::string const &name, int64_t start, int64_t size)
            : name(name), start(start), size(size) {}
        std::string name;
        int64_t start = -1, size = -1;
    };

    struct SummaryStats {
        size_t numSpecs = 0;
        size_t numUniquePaths = 0;
        size_t numUniqueTokens = 0;
        size_t numUniqueStrings = 0;
        size_t numUniqueFields = 0;
        size_t numUniqueFieldSets = 0;
    };

    /// Attempt to open and read \p fileName.
    USD_API
    static UsdCrateInfo Open(std::string const &fileName);

    /// Return summary statistics structure for this file.
    USD_API
    SummaryStats GetSummaryStats() const;

    /// Return the named file sections, their location and sizes in the file.
    USD_API
    std::vector<Section> GetSections() const;

    /// Return the file version.
    USD_API
    TfToken GetFileVersion() const;

    /// Return the software version.
    USD_API
    TfToken GetSoftwareVersion() const;

    /// Return true if this object refers to a valid file.
    explicit operator bool() const { return (bool)_impl; }

private:

    struct _Impl;
    std::shared_ptr<_Impl> _impl;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_CRATE_INFO_H
