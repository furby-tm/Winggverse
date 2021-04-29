#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/detachedTask.h"
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
#ifndef FORGE_BASE_WORK_DETACHED_TASK_H
#define FORGE_BASE_WORK_DETACHED_TASK_H

/// \file work/detachedTask.h

#include "forge/forge.h"
#include "forge/base/tf/errorMark.h"
#include "forge/base/work/api.h"

#if !defined(Q_MOC_RUN)
# include <tbb/task_group.h>
#endif /* Q_MOC_RUN */

#include <type_traits>
#include <utility>

FORGE_NAMESPACE_BEGIN

template <class Fn>
struct Work_DetachedInvoker : public tbb::task_group {

    explicit Work_DetachedInvoker(Fn &&fn)
        : _fn(std::move(fn)) {}

    explicit Work_DetachedInvoker(Fn const &fn)
        : _fn(fn) {}

    virtual void execute() {
        TfErrorMark m;
        _fn();
        m.Clear();
    }

private:
    Fn _fn;
};

WORK_API tbb::task_group_context &Work_GetDetachedTaskGroupContext();

/// Invoke \p fn asynchronously, discard any errors it produces, and provide
/// no way to wait for it to complete.
template <class Fn>
void WorkRunDetachedTask(Fn &&fn)
{
    // using FnType = typename Fn::type;
    tbb::task_group tg;
    tg.run([&] {
        *new Work_DetachedInvoker<Fn>(std::forward<Fn>(fn));
    });
}

FORGE_NAMESPACE_END

#endif // FORGE_BASE_WORK_DETACHED_TASK_H
