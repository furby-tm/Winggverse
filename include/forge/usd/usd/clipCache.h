#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/clipCache.h"
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
#ifndef FORGE_USD_USD_CLIP_CACHE_H
#define FORGE_USD_USD_CLIP_CACHE_H

#include "forge/forge.h"

#include "forge/usd/usd/clip.h"
#include "forge/usd/usd/clipSet.h"
#include "forge/usd/sdf/pathTable.h"

#include <mutex>
#include <vector>

FORGE_NAMESPACE_BEGIN

class PcpPrimIndex;

/// \class Usd_ClipCache
///
/// Private helper object for computing and caching clip information for
/// a prim on a UsdStage.
///
class Usd_ClipCache
{
    Usd_ClipCache(Usd_ClipCache const &) = delete;
    Usd_ClipCache &operator=(Usd_ClipCache const &) = delete;
public:
    Usd_ClipCache();
    ~Usd_ClipCache();

    /// \struct ConcurrentPopulationContext
    ///
    /// Structure for enabling cache population via concurrent calls to
    /// PopulateClipsForPrim.  Protects member data reads/writes with a mutex
    /// during its lifetime.
    /// \sa PopulateClipsForPrim.
    struct ConcurrentPopulationContext
    {
        explicit ConcurrentPopulationContext(Usd_ClipCache &cache);
        ~ConcurrentPopulationContext();
        Usd_ClipCache &_cache;
        std::mutex _mutex;
    };

    /// Populate the cache with clips for \p prim. Returns true if clips
    /// that may contribute opinions to attributes on \p prim are found,
    /// false otherwise.
    ///
    /// This function assumes that clips for ancestors of \p prim have
    /// already been populated.
    bool PopulateClipsForPrim(
        const SdfPath& path, const PcpPrimIndex& primIndex);

    /// Get all the layers that have been opened because we needed to extract
    /// data from their corresponding clips.  USD tries to be as lazy as
    /// possible about opening clip layers to avoid unnecessary latency and
    /// memory bloat; however, once a layer is open, it will generally be
    /// kept open for the life of the stage.
    SdfLayerHandleSet GetUsedLayers() const;

    /// Reload all clip layers that have been opened. Generated clip manifests
    /// will also be regenerated.
    void Reload();

    /// Get all clips that may contribute opinions to attributes on the
    /// prim at \p path, including clips that were authored on ancestral prims.
    ///
    /// The returned vector contains all clips that affect the prim at \p path
    /// in strength order. Each individual list of value clips will be ordered
    /// by start time.
    const std::vector<Usd_ClipSetRefPtr>&
    GetClipsForPrim(const SdfPath& path) const;

    /// \struct Lifeboat
    ///
    /// Structure for keeping invalidated clip data alive.
    /// \sa InvalidateClipsForPrim.
    ///
    struct Lifeboat
    {
        explicit Lifeboat(Usd_ClipCache& cache);
        ~Lifeboat();
        Usd_ClipCache& _cache;

        class Data;
        std::unique_ptr<Data> _data;
    };

    /// Invalidates the clip cache for prims at and below \p path.
    /// A Lifeboat object must be active for this cache before calling
    /// this function. This potentially allows the underlying clip layers
    /// to be reused if the clip cache is repopulated while the lifeboat
    /// is still active.
    ///
    /// NOTE: This function must not be invoked concurrently with any other
    /// function on this object.
    void InvalidateClipsForPrim(const SdfPath& path);

private:
    void _ComputeClipsFromPrimIndex(
        const SdfPath& usdPrimPath,
        const PcpPrimIndex& primIndex,
        std::vector<Usd_ClipSetRefPtr>* clips) const;

    inline const std::vector<Usd_ClipSetRefPtr>&
    _GetClipsForPrim_NoLock(const SdfPath& path) const;

    // Map from prim path to all clips that apply to that prim, including
    // ancestral clips. This map is sparse; only prims where clips are
    // authored will have entries.
    typedef SdfPathTable<std::vector<Usd_ClipSetRefPtr> >_ClipTable;
    _ClipTable _table;

    ConcurrentPopulationContext *_concurrentPopulationContext;
    Lifeboat *_lifeboat;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_CLIP_CACHE_H
