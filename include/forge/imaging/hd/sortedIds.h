#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/sortedIds.h"
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
#ifndef FORGE_IMAGING_HD_SORTED_IDS_H
#define FORGE_IMAGING_HD_SORTED_IDS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"

#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

///
/// Manages a container of Hydra Ids in a sorted order.
///
/// For performance reasons, sorting of the list is deferred
/// due to inserting a large number of items at once.
///
/// The class chooses the type of sort based on how many unsorted items
/// there are in the list.
///
class Hd_SortedIds {
public:
    HD_API
    Hd_SortedIds();

    HD_API
    ~Hd_SortedIds() = default;

    HD_API
    Hd_SortedIds(Hd_SortedIds &&other);

    /// Sorts the ids if needed and returns the sorted list of ids.
    HD_API
    const SdfPathVector &GetIds();

    /// Add a new id to the collection
    HD_API
    void Insert(const SdfPath &id);

    /// Remove an id from the collection.
    HD_API
    void Remove(const SdfPath &id);

    /// Remove a range of id from the collection.
    /// Range defined by position index in sorted list.
    /// end is inclusive.
    HD_API
    void RemoveRange(size_t start, size_t end);

    /// Removes all ids from the collection.
    HD_API
    void Clear();

private:
    SdfPathVector           _ids;
    size_t                  _sortedCount;
    ptrdiff_t               _afterLastDeletePoint;

    void _InsertSort();
    void _FullSort();
    void _Sort();

    Hd_SortedIds(const Hd_SortedIds &) = delete;
    Hd_SortedIds &operator =(const Hd_SortedIds &) = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_SORTED_IDS_H
