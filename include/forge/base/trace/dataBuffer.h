#line 1 "C:/Users/tyler/dev/WINGG/forge/base/trace/dataBuffer.h"
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

#ifndef FORGE_BASE_TRACE_DATA_BUFFER_H
#define FORGE_BASE_TRACE_DATA_BUFFER_H

#include "forge/forge.h"

#include "forge/base/trace/api.h"

#include "forge/base/arch/hints.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <deque>
#include <memory>
#include <type_traits>

FORGE_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
/// \class TraceDataBuffer
///
/// This class stores copies of data that are associated with TraceEvent
/// instances.
/// Data stored in the buffer must be copy constructible and trivially
/// destructible.
///
class TraceDataBuffer {
public:
    constexpr static size_t DefaultAllocSize = 1024;

    /// Constructor. The buffer will make allocations of \p allocSize.
    ///
    TraceDataBuffer(size_t allocSize = DefaultAllocSize) : _alloc(allocSize) {}

    /// Makes a copy of \p value and returns a pointer to it.
    ///
    template <typename T>
    const T* StoreData(const T& value)
    {
        static_assert(std::is_copy_constructible<T>::value,
            "Must by copy constructible");
        static_assert(std::is_trivially_destructible<T>::value,
            "No destructors will be called");
        return new(_alloc.Allocate(alignof(T), sizeof(T))) T(value);
    }

    /// Makes a copy of \p str and returns a pointer to it.
    /// Specialization for c strings.
    const char* StoreData(const char* str) {
        const size_t strLen = std::strlen(str) + 1;
        void* mem = _alloc.Allocate(alignof(char), strLen);
        char* cstr = reinterpret_cast<char*>(mem);
        std::memcpy(cstr, str, strLen);
        return cstr;
    }

private:
    // Simple Allocator that only supports allocations, but not frees.
    // Allocated memory is tied to the lifetime of the allocator object.
    class Allocator {
    public:
        Allocator(size_t blockSize)
            : _desiredBlockSize(blockSize) {}
        Allocator(Allocator&&) = default;
        Allocator& operator=(Allocator&&) = default;

        Allocator(const Allocator&) = delete;
        Allocator& operator=(const Allocator&) = delete;

        void* Allocate(const size_t align, const size_t size) {
            Byte* alignedNext = AlignPointer(_next, align);
            Byte* end = alignedNext + size;
            if (ARCH_UNLIKELY(end > _blockEnd)) {
                AllocateBlock(align, size);
                alignedNext = AlignPointer(_next, align);
                end = _next + size;
            }
            _next = end;
            return alignedNext;
        }

    private:
        using Byte = std::uint8_t;

        static Byte* AlignPointer(Byte* ptr, const size_t align) {
            const size_t alignMask = align - 1;
            return reinterpret_cast<Byte*>(
                reinterpret_cast<uintptr_t>(ptr + alignMask) & ~alignMask);
        }

        TRACE_API void AllocateBlock(const size_t align, const size_t desiredSize);

        Byte* _blockEnd = nullptr;
        Byte* _next = nullptr;
        using BlockPtr = std::unique_ptr<Byte[]>;
        std::deque<BlockPtr> _blocks;
        size_t _desiredBlockSize;
    };

    Allocator _alloc;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TRACE_DATA_BUFFER_H