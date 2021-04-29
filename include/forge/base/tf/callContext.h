#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/callContext.h"
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
#ifndef FORGE_BASE_TF_CALL_CONTEXT_H
#define FORGE_BASE_TF_CALL_CONTEXT_H

/// \file tf/callContext.h
/// Functions for recording call locations.
///
/// Many macros want to record the location in which they are invoked.  In
/// fact, this is the most useful feature that function-like macros have over
/// regular functions.  This code provides a standard way to collect and pass
/// that contextual information around.  There are two parts.  First is a
/// small structure which holds the contextual information.  Next is a macro
/// which will produce a temporary structure containing the local contextual
/// information. The intended usage is in a macro.

#include "forge/forge.h"
#include "forge/base/tf/api.h"
#include "forge/base/arch/functionLite.h"

#include <stddef.h>

FORGE_NAMESPACE_BEGIN

/// \hideinitializer
#define TF_CALL_CONTEXT \
TfCallContext(__ARCH_FILE__, __ARCH_FUNCTION__, __LINE__, __ARCH_PRETTY_FUNCTION__)

class TfCallContext
{
public:
    constexpr TfCallContext()
        : _file(nullptr)
        , _function(nullptr)
        , _line(0)
        , _prettyFunction(nullptr)
        , _hidden(false) {}

    constexpr TfCallContext(char const *file,
                            char const *function,
                            size_t line,
                            char const *prettyFunction) :
        _file(file),
        _function(function),
        _line(line),
        _prettyFunction(prettyFunction),
        _hidden(false)
    {
    }

    char const *GetFile() const {
        return _file;
    }

    char const *GetFunction() const {
        return _function;
    }

    size_t GetLine() const {
        return _line;
    }

    char const *GetPrettyFunction() const {
        return _prettyFunction;
    }

    TfCallContext const& Hide() const {
        _hidden = true;
        return *this;
    }

    bool IsHidden() const {
        return _hidden;
    }

    explicit operator bool() const { return _file && _function; }

  private:

    char const *_file;
    char const *_function;
    size_t _line;
    char const *_prettyFunction;
    mutable bool _hidden;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_CALL_CONTEXT_H
