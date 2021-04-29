#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/regex.h"
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
#ifndef FORGE_BASE_ARCH_REGEX_H
#define FORGE_BASE_ARCH_REGEX_H

#include "forge/forge.h"
#include "forge/base/arch/api.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

class ArchRegex {
public:
    static constexpr unsigned int CASE_INSENSITIVE = 1u;
    static constexpr unsigned int GLOB             = 2u;

    /// Create an empty regex.
    ARCH_API ArchRegex();
    ARCH_API ArchRegex(const std::string& pattern, unsigned int flags = 0);
    ArchRegex(const ArchRegex&) = delete;
    ARCH_API ArchRegex(ArchRegex&&) noexcept;
    ArchRegex& operator=(const ArchRegex&) = delete;
    ARCH_API ArchRegex& operator=(ArchRegex&&) noexcept;
    ARCH_API ~ArchRegex();

    /// Returns \c true if the regex is valid.
    ARCH_API explicit operator bool() const;

    /// Returns the reason the regex is invalid or the empty string if
    /// it's valid.
    ARCH_API std::string GetError() const;

    /// Returns the flags used to construct the regex.
    ARCH_API unsigned int GetFlags() const;

    /// Returns \c true if the regex matches \p query anywhere, otherwise
    /// returns \c false.
    ARCH_API bool Match(const std::string& query) const;

private:
    class _Impl;
    unsigned int _flags = 0;
    std::string _error;
    std::unique_ptr<_Impl> _impl;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_REGEX_H
