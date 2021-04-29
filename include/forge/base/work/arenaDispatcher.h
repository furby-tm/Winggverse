#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/arenaDispatcher.h"
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
#ifndef FORGE_BASE_WORK_ARENA_DISPATCHER_H
#define FORGE_BASE_WORK_ARENA_DISPATCHER_H

/// \file work/arenaDispatcher.h

#include "forge/forge.h"
#include "forge/base/work/dispatcher.h"
#include "forge/base/work/threadLimits.h"
#include "forge/base/work/api.h"

#if !defined(Q_MOC_RUN)
# include <tbb/task_arena.h>
#endif /* Q_MOC_RUN */

#include <functional>
#include <type_traits>
#include <utility>

FORGE_NAMESPACE_BEGIN

/// \class WorkArenaDispatcher
///
/// This is a specialization of the WorkDispatcher that uses an isolated arena
/// to Run() all its tasks in. The WorkArenaDispatcher is useful where it must
/// be guaranteed that a specific set of tasks shall not be stolen by any
/// other dispatcher, or where stealing from other dispatchers could cause
/// lock dependencies that may lead to deadlocks. Note that a regular
/// WorkDispatcher can provide better throughput, and should thus be the
/// preferred over the WorkArenaDispatcher.
///
/// The interface of the WorkArenaDispatcher, and thread-safety notes about its
/// API are identical to those of the WorkDispatcher.
///
class WorkArenaDispatcher
{
public:
    /// Constructs a new dispatcher. The internal arena will mirror the
    /// global concurrency limit setting.
    WorkArenaDispatcher() : _arena(_GetArena()) {}

    /// Wait() for any pending tasks to complete, then destroy the dispatcher.
    WORK_API ~WorkArenaDispatcher();

    WorkArenaDispatcher(WorkArenaDispatcher const &) = delete;
    WorkArenaDispatcher &operator=(WorkArenaDispatcher const &) = delete;

#ifdef doxygen

    /// Add work for the dispatcher to run.
    ///
    /// Before a call to Wait() is made it is safe for any client to invoke
    /// Run().  Once Wait() is invoked, it is \b only safe to invoke Run() from
    /// within the execution of tasks already added via Run().
    ///
    /// This function does not block.  The added work may be not yet started,
    /// may be started but not completed, or may be completed upon return.  No
    /// guarantee is made.
    template <class Callable, class A1, class A2, ... class AN>
    void Run(Callable &&c, A1 &&a1, A2 &&a2, ... AN &&aN);

#else // doxygen

    template <class Callable, class ... Args>
    inline void Run(Callable &&c, Args&&... args) {
        _arena->execute(
            _MakeRunner(&_dispatcher,
                        std::bind(std::forward<Callable>(c),
                                  std::forward<Args>(args)...)));
    }

#endif // doxygen

    /// Block until the work started by Run() completes.
    WORK_API void Wait();

    /// Cancel remaining work and return immediately.
    ///
    /// This call does not block.  Call Wait() after Cancel() to wait for
    /// pending tasks to complete.
    WORK_API void Cancel();

private:
    WORK_API tbb::task_arena *_GetArena() const;

    template <class Fn>
    struct _Runner {
        _Runner(WorkDispatcher *wd, Fn &&fn) : _wd(wd), _fn(std::move(fn)) {}
        _Runner(WorkDispatcher *wd, Fn const &fn) : _wd(wd), _fn(fn) {}
        void operator()() { _wd->Run(std::move(_fn)); }
        void operator()() const { _wd->Run(std::move(_fn)); }
    private:
        WorkDispatcher *_wd;
        mutable Fn _fn;
    };

    template <class Fn>
    _Runner<typename Fn>
    _MakeRunner(WorkDispatcher *wd, Fn &&fn) {
        return _Runner<typename Fn>(
            wd, std::forward<Fn>(fn));
    }

    // The task arena.
    tbb::task_arena *_arena;

    // The dispatcher.
    WorkDispatcher _dispatcher;
};

///////////////////////////////////////////////////////////////////////////////

FORGE_NAMESPACE_END

#endif // FORGE_BASE_WORK_ARENA_DISPATCHER_H
