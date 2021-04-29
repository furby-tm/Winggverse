#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/virtualMemory.h"
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
#ifndef FORGE_BASE_ARCH_VIRTUAL_MEMORY_H
#define FORGE_BASE_ARCH_VIRTUAL_MEMORY_H

/// \file arch/virtualMemory.h
/// \ingroup group_arch_SystemFunctions
/// Architecture dependent routines for virtual memory.

#include "forge/forge.h"
#include "forge/base/arch/api.h"

#include <cstddef>

FORGE_NAMESPACE_BEGIN

/// Reserve \p numBytes bytes of virtual memory.  Call ArchCommitVirtualMemory()
/// on subranges to write to and read from the memory.  Return nullptr in case
/// of an error; check errno.
ARCH_API void *
ArchReserveVirtualMemory(size_t numBytes);

/// Make the range of \p numBytes bytes starting at \p start available for
/// reading and writing.  The range must be within one previously reserved by
/// ArchReserveVirtualMemory().  It is not an error to commit a range that was
/// previously partly or fully committed.  Return false in case of an error;
/// check errno.
ARCH_API bool
ArchCommitVirtualMemoryRange(void *start, size_t numBytes);

/// Return memory obtained with ArchReserveVirtualMemory() to the system.  The
/// \p start argument must be the value returned from a previous call to
/// ArchReserveVirtualMemory, and \p numBytes must match the argument from that
/// call.  Memory within the range may not be accessed after this call.  Return
/// false in case of an error; check errno.
ARCH_API bool
ArchFreeVirtualMemory(void *start, size_t numBytes);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_VIRTUAL_MEMORY_H
