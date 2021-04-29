#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ar/asset.h"
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
#ifndef FORGE_USD_AR_ASSET_H
#define FORGE_USD_AR_ASSET_H

/// \file ar/asset.h

#include "forge/forge.h"
#include "forge/usd/ar/api.h"

#include <cstdio>
#include <memory>
#include <utility>

FORGE_NAMESPACE_BEGIN

/// \class ArAsset
///
/// Interface for accessing the contents of an asset.
///
/// \see ArResolver::OpenAsset for how to retrieve instances of this object.
class ArAsset {
public:
    AR_API
    virtual ~ArAsset();

    ArAsset(const ArAsset&) = delete;

    ArAsset& operator=(const ArAsset&) = delete;

    /// Returns size of the asset.
    AR_API
    virtual size_t GetSize() = 0;

    /// Returns a pointer to a buffer with the contents of the asset,
    /// with size given by GetSize(). Returns an invalid std::shared_ptr
    /// if the contents could not be retrieved.
    ///
    /// The data in the returned buffer must remain valid while there are
    /// outstanding copies of the returned std::shared_ptr. Note that the
    /// deleter stored in the std::shared_ptr may contain additional data
    /// needed to maintain the buffer's validity.
    AR_API
    virtual std::shared_ptr<const char> GetBuffer() = 0;

    /// Read \p count bytes at \p offset from the beginning of the asset
    /// into \p buffer. Returns number of bytes read, or 0 on error.
    ///
    /// Implementers should range-check calls and return zero for out-of-bounds
    /// reads.
    AR_API
    virtual size_t Read(void* buffer, size_t count, size_t offset) = 0;

    /// Returns a read-only FILE* handle and offset for this asset if
    /// available, or (nullptr, 0) otherwise.
    ///
    /// The returned handle must remain valid for the lifetime of this
    /// ArAsset object. The returned offset is the offset from the beginning
    /// of the FILE* where the asset's contents begins.
    ///
    /// This function is marked unsafe because the handle may wind up
    /// being used in multiple threads depending on the underlying
    /// resolver implementation. For instance, a resolver may cache
    /// and return ArAsset objects with the same FILE* to multiple
    /// threads.
    ///
    /// Clients MUST NOT use this handle with functions that cannot be
    /// called concurrently on the same file descriptor, e.g. read,
    /// fread, fseek, etc. See ArchPRead for a function that can be used
    /// to read data from this handle safely.
    AR_API
    virtual std::pair<FILE*, size_t> GetFileUnsafe() = 0;

protected:
    AR_API
    ArAsset();
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_AR_ASSET_H
