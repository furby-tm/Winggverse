#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/stringHash.h"
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

#ifndef FORGE_BASE_TRACE_STRING_HASH_H
#define FORGE_BASE_TRACE_STRING_HASH_H

#include "forge/forge.h"

#include <cstdint>

FORGE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
///
/// \class TraceStringHash
///
/// This class provides a function to compute compile time hashes for string
/// literals.
///
class TraceStringHash {
  public:

    /// Computes a compile time hash of \p str.
    template <int N>
    static constexpr std::uint32_t Hash(const char (&str)[N]) {
        return djb2HashStr<N-1>(str);
    }

  private:
    // Recursive function computing the xor variant of the djb2 hash
    // function.
    template <int N>
    static constexpr std::uint32_t djb2HashStr(const char* str) {
        return (djb2HashStr<N-1>(str) * 33) ^ str[N-1];
    }
};

// Template recursion base case.
template <>
constexpr std::uint32_t TraceStringHash::djb2HashStr<0>(const char* str) {
    return 5381;
}

FORGE_NAMESPACE_END

#endif //FORGE_BASE_TRACE_STRING_HASH_H