#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/dynamicKey.h"
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

#ifndef FORGE_BASE_TRACE_DYNAMIC_KEY_H
#define FORGE_BASE_TRACE_DYNAMIC_KEY_H

#include "forge/forge.h"
#include "forge/base/trace/staticKeyData.h"
#include "forge/base/tf/token.h"

FORGE_NAMESPACE_BEGIN

////////////////////////////////////////////////////////////////////////////////
/// \class TraceDynamicKey
///
/// This class stores data used to create dynamic keys which can be referenced
/// in TraceEvent instances.
///
/// Is a key is known at compile time, it is preferable to use
/// a static constexpr TraceStaticKeyData instance instead.
class TraceDynamicKey {
public:
    /// Constructor for TfToken.
    TraceDynamicKey(TfToken name) : _key(std::move(name)) {
        _data._name = _key.GetText();
    }

    /// Constructor for string.
    TraceDynamicKey(const std::string& name) : _key(name) {
        _data._name = _key.GetText();
    }

    /// Constructor for C string.
    TraceDynamicKey(const char* name) : _key(name) {
        _data._name = _key.GetText();
    }

    /// Equality operator.
    bool operator == (const TraceDynamicKey& other) const {
        return _key == other._key;
    }

    /// Return a cached hash code for this key.
    size_t Hash() const {
        return _key.Hash();
    }

    /// A Hash functor which uses the cached hash which may be used to store
    /// keys in a TfHashMap.
    struct HashFunctor {
        size_t operator()(const TraceDynamicKey& key) const {
            return key.Hash();
        }
    };

    /// Returns a reference to TraceStaticKeyData.
    const TraceStaticKeyData& GetData() const { return _data; }

private:
    TraceStaticKeyData _data;
    TfToken _key;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_DYNAMIC_KEY_H