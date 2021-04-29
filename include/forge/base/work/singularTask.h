#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/singularTask.h"
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
#ifndef FORGE_BASE_WORK_SINGULAR_TASK_H
#define FORGE_BASE_WORK_SINGULAR_TASK_H

/// \file work/singularTask.h

#include "forge/forge.h"

#include <atomic>
#include <functional>
#include <type_traits>

FORGE_NAMESPACE_BEGIN

class WorkDispatcher;
class WorkArenaDispatcher;

/// \class WorkSingularTask
///
/// A WorkSingularTask runs a task in a WorkDispatcher, but never concurrently
/// with itself.  That is, the function provided to the WorkSingularTask runs
/// concurrently with other tasks in the WorkDispatcher, but never with another
/// invocation of itself.
///
/// This is useful if there is single-threaded work to do that can be overlapped
/// with other parallel tasks in a dispatcher.  For example, a
/// multiple-producer, single-consumer problem can be tackled this way.  Run the
/// producer tasks as usual in a WorkDispatcher and create a WorkSingularTask
/// for the consumer.  When a producer task has generated a result to consume,
/// it invokes Wake() on the consumer task.  This ensures that the consumer runs
/// only when there are results to consume, and it lets the consumer operate
/// single-threaded.  For example, the consumer could populate stl containers
/// without locking.
///
class WorkSingularTask
{
public:

    WorkSingularTask(WorkSingularTask const &) = delete;
    WorkSingularTask &operator=(WorkSingularTask const &) = delete;

#ifdef doxygen

    /// Create a singular task to be run in \p dispatcher.  Callers must ensure
    /// that \p dispatcher lives at least as long as this WorkSingularTask.
    ///
    /// A singular task is one that will not run concurrently with itself.  See
    /// the WorkSingularTask doc for more details.
    ///
    /// After constructing a WorkSingularTask, call Wake() to ensure that the
    /// task runs at least once.
    template <class Callable, class A1, class A2, ... class AN>
    WorkSingularTask(WorkDispatcher &dispatcher,
                     Callable &&c, A1 &&a1, A2 &&a2, ... AN &&aN);

    /// \overload
    template <class Callable, class A1, class A2, ... class AN>
    WorkSingularTask(WorkArenaDispatcher &dispatcher,
                     Callable &&c, A1 &&a1, A2 &&a2, ... AN &&aN);

#else // doxygen

    template <class Callable, class... Args>
    WorkSingularTask(WorkDispatcher &d, Callable &&c, Args&&... args)
        : _waker(_MakeWaker(d, std::bind(std::forward<Callable>(c),
                                         std::forward<Args>(args)...)))
        , _count(0) {}

    template <class Callable, class... Args>
    WorkSingularTask(WorkArenaDispatcher &d, Callable &&c, Args&&... args)
        : _waker(_MakeWaker(d, std::bind(std::forward<Callable>(c),
                                         std::forward<Args>(args)...)))
        , _count(0) {}

#endif // doxygen

    /// Ensure that this task runs at least once after this call.  The task is
    /// not guaranteed to run as many times as Wake() is invoked, only that it
    /// run at least once after a call to Wake().
    inline void Wake() {
        if (++_count == 1)
            _waker(_count);
    }

private:
    template <class Dispatcher, class Fn>
    struct _Waker {
        explicit _Waker(Dispatcher &d, Fn &&fn)
            : _dispatcher(d), _fn(std::move(fn)) {}

        void operator()(std::atomic_size_t &count) const {
            _dispatcher.Run(
                [this, &count]() {
                    // We read the current refCount into oldCount, then we
                    // invoke the task function.  Finally we try to CAS the
                    // refCount to zero.  If we fail, it means some other
                    // clients have invoked Wake() in the meantime.  In that
                    // case we go again to ensure the task can do whatever it
                    // was awakened to do.  Once we successfully take the count
                    // to zero, we stop.
                    size_t old = count;
                    do { _fn(); } while (
                        !count.compare_exchange_strong(old, 0));
                });
        }
        Dispatcher &_dispatcher;
        Fn _fn;
    };

    template <class Dispatcher, class Fn>
    static std::function<void (std::atomic_size_t &)>
    _MakeWaker(Dispatcher &d, Fn &&fn) {
        return std::function<void (std::atomic_size_t &)>(
            _Waker<Dispatcher, typename std::decay<Fn>::type>(
                d, std::forward<Fn>(fn)));
    }

    std::function<void (std::atomic_size_t &)> _waker;
    std::atomic_size_t _count;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_WORK_SINGULAR_TASK_H
