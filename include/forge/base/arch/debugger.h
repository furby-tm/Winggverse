#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/debugger.h"
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
#ifndef FORGE_BASE_ARCH_DEBUGGER_H
#define FORGE_BASE_ARCH_DEBUGGER_H

/// \file arch/debugger.h
/// Routines for interacting with a debugger.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include "forge/base/arch/attributes.h"

FORGE_NAMESPACE_BEGIN

/// Stop in a debugger.
///
/// This function will do one of the following:  start a debugger
/// attached to this process stopped on this function;  stop in an
/// already attached debugger;  stop and wait for a debugger to
/// attach, or nothing.
///
/// On Linux this will start a debugger using \c ArchDebuggerAttach()
/// if no debugger is attached.  If a debugger is (or was) attached it
/// will stop on this function due to \c SIGTRAP.  Alternatively, users
/// can configure the debugger to not stop on \c SIGTRAP and instead
/// break on \c ArchDebuggerTrap().
///
/// If a debugger is not attached, \c ArchDebuggerAttach() does not
/// attach one, and \c ArchDebuggerWait() has been most recently
/// called with \c true then this will wait for a debugger to attach,
/// otherwise it does nothing and the process does not stop.  The user
/// can continue the process from the debugger simply by issuing the
/// continue command.  The user can also continue the process from an
/// attached terminal by putting the process into the foreground or
/// background.
///
ARCH_API
void ArchDebuggerTrap() ARCH_NOINLINE;

/// Cause debug traps to wait for the debugger or not.
///
/// When \p wait is \c true the next call to \c ArchDebuggerTrap()
/// will cause the process to wait for a signal.  The user can attach
/// a debugger to continue the process.  The process will not wait
/// again until another call to this function with \p wait \c true.
///
ARCH_API
void ArchDebuggerWait(bool wait);

/// Attach a debugger.
///
/// Attaches the debugger by running the contents of the enviroment variable
/// ARCH_DEBUGGER using /bin/sh.  Any '%p' in the contents of this variable
/// will be replaced with the process id of the process launching the debugger.
/// Any '%e' will be replaced with the path to the executable for the process.
///
/// Returns true if ARCH_DEBUGGER is set and the debugger was successfully
/// launched, otherwise returns false.
ARCH_API
bool ArchDebuggerAttach() ARCH_NOINLINE;

/// Test if a debugger is attached
///
/// Attempts to detect if a debugger is currently attached to the process.
ARCH_API
bool ArchDebuggerIsAttached() ARCH_NOINLINE;

/// Abort.  This will try to avoid the JIT debugger if any if ARCH_AVOID_JIT
/// is in the environment and the debugger isn't already attached.  In that
/// case it will _exit(134).  If \p logging is \c false then this will
/// attempt to bypass any crash logging.
[[noreturn]]
ARCH_API
void ArchAbort(bool logging = true);

/// Stop in the debugger.
///
/// This macro expands to \c ArchDebuggerTrap() and, if necessary and
/// possible, code to prevent optimization so the caller appears in the
/// debugger's stack trace.  The calling functions should also use the
/// \c ARCH_NOINLINE function attribute.
#if defined(ARCH_COMPILER_GCC) || defined(ARCH_COMPILER_CLANG)
#define ARCH_DEBUGGER_TRAP do { ArchDebuggerTrap(); asm(""); } while (0)
#else
#define ARCH_DEBUGGER_TRAP do { ArchDebuggerTrap(); } while (0)
#endif

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_DEBUGGER_H
