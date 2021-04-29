#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/staticKeyData.h"
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

#ifndef FORGE_BASE_TRACE_STATIC_KEY_DATA_H
#define FORGE_BASE_TRACE_STATIC_KEY_DATA_H

#include "forge/forge.h"
#include "forge/base/trace/api.h"

#include <cstddef>
#include <string>

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
///
/// \class TraceStaticKeyData
///
/// This class holds data necessary to create keys for TraceEvent instances.
/// This class is meant to be used as constexpr static data.
///
class TraceStaticKeyData {
public:
    /// \class StringLiteral
    ///
    /// This is a helper class for the constructors of TraceStaticKeyData.
    ///
    class StringLiteral {
    public:
        /// Constructor from string literals.
        template <size_t N>
        constexpr StringLiteral(const char(&s)[N]) : str(s) {}

        /// Default Constructor.
        constexpr StringLiteral() : str(nullptr) {}

    private:
        const char* str;

        friend class TraceStaticKeyData;
    };

    /// Constructor for a \p name.
    constexpr TraceStaticKeyData(const StringLiteral name)
        : _name(name.str) {}

    /// Constructor for a function (\p func, \p prettyFunc) and optional
    /// scope \p name.
    constexpr TraceStaticKeyData(
        const StringLiteral func,
        const StringLiteral prettyFunc,
        const StringLiteral name = StringLiteral())
        : _funcName(func.str)
        , _prettyFuncName(prettyFunc.str)
        , _name(name.str) {}

    /// Equality comparison.  Inequality is also defined.
    TRACE_API
    bool operator == (const TraceStaticKeyData& other) const;

    bool operator != (const TraceStaticKeyData& other) const {
        return !(*this == other);
    }

    /// Returns the string representation of the key data.
    TRACE_API
    std::string GetString() const;

private:
    TraceStaticKeyData() {}

    const char* _funcName = nullptr;
    const char* _prettyFuncName = nullptr;
    const char* _name = nullptr;

    friend class TraceDynamicKey;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_STATIC_KEY_DATA_H
