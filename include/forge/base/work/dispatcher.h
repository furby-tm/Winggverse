#line 1 "C:/Users/tyler/dev/WINGG/forge/base/work/dispatcher.h"
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

#ifndef FORGE_BASE_WORK_DISPATCHER_H
#define FORGE_BASE_WORK_DISPATCHER_H

/// \file work/dispatcher.h

#include "forge/forge.h"
#include "forge/base/work/threadLimits.h"
#include "forge/base/work/api.h"

#include "forge/base/tf/errorMark.h"
#include "forge/base/tf/errorTransport.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_vector.h>
# include <tbb/task_group.h>
#endif /* Q_MOC_RUN */

#include <functional>
#include <type_traits>
#include <utility>

FORGE_NAMESPACE_BEGIN

/// \class WorkDispatcher
///
/// A work dispatcher runs concurrent tasks.  The dispatcher supports adding
/// new tasks from within running tasks.  This suits problems that exhibit
/// hierarchical structured parallelism: tasks that discover additional tasks
/// during their execution.
///
/// Typical use is to create a dispatcher and invoke Run() to begin doing
/// work, then Wait() for the work to complete.  Tasks may invoke Run() during
/// their execution as they discover additional tasks to perform.
///
/// For example,
///
/// \code
/// WorkDispatcher dispatcher;
/// for (i = 0; i != N; ++i) {
///     dispatcher.Run(DoSomeWork, workItem[i]);
/// }
/// dispatcher.Wait();
/// \endcode
///
/// Calls to Run() and Cancel() may be made concurrently.  However, once Wait()
/// is called, calls to Run() and Cancel() must only be made by tasks already
/// added by Run().  Additionally, Wait() must never be called by a task added by
/// Run(), since that task could never complete.
///
class WorkDispatcher
{
public:
    /// Construct a new dispatcher.
    WORK_API WorkDispatcher();

    /// Wait() for any pending tasks to complete, then destroy the dispatcher.
    WORK_API ~WorkDispatcher();

    WorkDispatcher(WorkDispatcher const &) = delete;
    WorkDispatcher &operator=(WorkDispatcher const &) = delete;

#ifdef doxygen

    /// Add work for the dispatcher to run.
    ///
    /// Before a call to Wait() is made it is safe for any client to invoke
    /// Run().  Once Wait() is invoked, it is \b only safe to invoke Run() from
    /// within the execution of tasks already added via Run().
    ///
    /// This function does not block, in general.  It may block if concurrency
    /// is limited to 1.  The added work may be not yet started, may be started
    /// but not completed, or may be completed upon return.  No guarantee is
    /// made.
    template <class Callable, class A1, class A2, ... class AN>
    void Run(Callable &&c, A1 &&a1, A2 &&a2, ... AN &&aN);

#else // doxygen

    template <class Callable>
    inline void Run(Callable &&c) {
       _rootTask.run([&]{
           _MakeInvokerTask(std::forward<Callable>(c));
       });
    }

    template <class Callable, class A0, class ... Args>
    inline void Run(Callable &&c, A0 &&a0, Args&&... args) {
        Run(std::bind(std::forward<Callable>(c),
                      std::forward<A0>(a0),
                      std::forward<Args>(args)...));
    }

#endif // doxygen

    /// Block until the work started by Run() completes.
    WORK_API void Wait();

    /// Cancel remaining work and return immediately.
    ///
    /// Calling this function affects task that are being run directly
    /// by this dispatcher. If any of these tasks are using their own
    /// dispatchers to run tasks, these dispatchers will not be affected
    /// and these tasks will run to completion, unless they are also
    /// explicitly cancelled.
    ///
    /// This call does not block.  Call Wait() after Cancel() to wait for
    /// pending tasks to complete.
    WORK_API void Cancel();

private:
    typedef tbb::concurrent_vector<TfErrorTransport> _ErrorTransports;

    // Function invoker helper that wraps the invocation with an ErrorMark so we
    // can transmit errors that occur back to the thread that Wait() s for tasks
    // to complete.
    template <class Fn>
    struct _InvokerTask : public tbb::task_group {
        explicit _InvokerTask(Fn &&fn, _ErrorTransports *err)
            : task_group(),
              _fn(std::move(fn)), _errors(err) {}

        explicit _InvokerTask(Fn const &fn, _ErrorTransports *err)
            : task_group(),
              _fn(fn), _errors(err) {}

        virtual void execute() {
            TfErrorMark m;
            _fn();
            if (!m.IsClean())
                WorkDispatcher::_TransportErrors(m, _errors);
        }

      private:
        Fn _fn;
        _ErrorTransports *_errors;
    };

    // Make an _InvokerTask instance, letting the function template deduce Fn.
    template <class Fn>
    _InvokerTask<typename Fn>&
    _MakeInvokerTask(Fn &&fn) {
        return *new _InvokerTask<typename Fn>(std::forward<Fn>(fn), &_errors);
    }

    // Helper function that removes errors from \p m and stores them in a new
    // entry in \p errors.
    WORK_API static void
    _TransportErrors(const TfErrorMark &m, _ErrorTransports *errors);

    // Task group context and associated root task that allows us to cancel
    // tasks invoked directly by this dispatcher.
    tbb::task_group_context _context;
    tbb::task_group _rootTask;

    // The error transports we use to transmit errors in other threads back to
    // this thread.
    _ErrorTransports _errors;
};

///////////////////////////////////////////////////////////////////////////////

FORGE_NAMESPACE_END

#endif // FORGE_BASE_WORK_DISPATCHER_H
