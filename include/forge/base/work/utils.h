#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/utils.h"
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
#ifndef FORGE_BASE_WORK_UTILS_H
#define FORGE_BASE_WORK_UTILS_H

///\file work/utils.h

#include "forge/forge.h"
#include "forge/base/work/api.h"
#include "forge/base/work/detachedTask.h"

#include <utility>

FORGE_NAMESPACE_BEGIN

WORK_API
bool Work_ShouldSynchronizeAsyncDestroyCalls();

template <class T>
struct Work_AsyncMoveDestroyHelper {
    void operator()() const { /* do nothing */ }
    T obj;
};

// Helper for swap-based asynchronous destruction that synthesizes move
// construction and assignment using swap.
template <class T>
struct Work_AsyncSwapDestroyHelper {
    Work_AsyncSwapDestroyHelper() = default;

    Work_AsyncSwapDestroyHelper(Work_AsyncSwapDestroyHelper const&) = delete;
    Work_AsyncSwapDestroyHelper& operator=(
        Work_AsyncSwapDestroyHelper const&) = delete;

    Work_AsyncSwapDestroyHelper(Work_AsyncSwapDestroyHelper &&other)
        : obj()
    {
        using std::swap;
        swap(obj, other.obj);
    }

    Work_AsyncSwapDestroyHelper& operator=(
        Work_AsyncSwapDestroyHelper &&other)
    {
        using std::swap;
        swap(obj, other.obj);
        return *this;
    }

    void operator()() const { /* do nothing */ }
    T obj;
};

/// Swap \p obj with a default-constructed T instance, return and arrange
/// for the swapped-out instance to be destroyed asynchronously.  This means
/// that any code that obj's destructor might invoke must be safe to run both
/// concurrently with other code and at any point in the future.  This might not
/// be true, for example, if obj's destructor might try to update some other
/// data structure that could be destroyed by the time obj's destruction occurs.
/// Be careful.
template <class T>
void WorkSwapDestroyAsync(T &obj)
{
    using std::swap;
    Work_AsyncSwapDestroyHelper<T> helper;
    swap(helper.obj, obj);
    if (!Work_ShouldSynchronizeAsyncDestroyCalls())
        WorkRunDetachedTask(std::move(helper));
}

/// Like WorkSwapDestroyAsync() but instead, move from \p obj, leaving it
/// in a moved-from state instead of a default constructed state.
template <class T>
void WorkMoveDestroyAsync(T &obj)
{
    Work_AsyncMoveDestroyHelper<T> helper { std::move(obj) };
    if (!Work_ShouldSynchronizeAsyncDestroyCalls())
        WorkRunDetachedTask(std::move(helper));
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_WORK_UTILS_H
