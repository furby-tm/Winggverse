#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/threads.h"
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
#ifndef FORGE_BASE_ARCH_THREADS_H
#define FORGE_BASE_ARCH_THREADS_H

/// \file arch/threads.h
/// \ingroup group_arch_Multithreading
/// Architecture-specific thread function calls.

#include "forge/forge.h"
#include "forge/base/arch/api.h"

#include <thread>

FORGE_NAMESPACE_BEGIN

/// Return true if the calling thread is the main thread, false otherwise.
/// \ingroup group_arch_Multithreading
ARCH_API bool ArchIsMainThread();

/// Return the std::thread_id for the thread arch considers to be the "main"
/// thread.
ARCH_API std::thread::id ArchGetMainThreadId();

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_THREADS_H
