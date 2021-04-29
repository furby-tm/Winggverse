#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/key.h"
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

#ifndef FORGE_BASE_TRACE_KEY_H
#define FORGE_BASE_TRACE_KEY_H

#include "forge/forge.h"
#include "forge/base/trace/staticKeyData.h"


FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceKey
///
/// A wrapper around a TraceStaticKeyData pointer that is stored in TraceEvent
/// instances.
///
class TraceKey {
public:
    /// Constructor.
    constexpr TraceKey(const TraceStaticKeyData& data) : _ptr(&data) {}

    /// Equality comparison.
    bool operator == (const TraceKey& other) const {
        if (_ptr == other._ptr) {
            return true;
        } else {
            return *_ptr == *other._ptr;
        }
    }

    /// Hash function.
    size_t Hash() const {
        return reinterpret_cast<size_t>(_ptr)/sizeof(TraceStaticKeyData);
    }

    /// A Hash functor which may be used to store keys in a TfHashMap.
    struct HashFunctor {
        size_t operator()(const TraceKey& key) const {
            return key.Hash();
        }
    };

private:
    const TraceStaticKeyData* _ptr;

    // TraceCollection converts TraceKeys to TfTokens for visitors.
    friend class TraceCollection;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_KEY_H
