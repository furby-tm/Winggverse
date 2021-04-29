#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/daemon.h"
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
#ifndef FORGE_BASE_ARCH_DAEMON_H
#define FORGE_BASE_ARCH_DAEMON_H

/// \file arch/daemon.h
/// \ingroup group_arch_Multithreading
/// Create background or daemon processes.

#include "forge/forge.h"
#include "forge/base/arch/api.h"

FORGE_NAMESPACE_BEGIN

/// Close all file descriptors (with possible exceptions)
///
/// \c ArchCloseAllFiles will close all file descriptors open in the
/// current process.  Occasionally you'd like to close all files except
/// for some small subset (like 0, 1, and 2).  The \p nExcept and \p
/// exceptFds arguments can be used to provide the list of exceptions.
/// \c ArchDaemonizeProcess uses this method to close all unwanted file
/// descriptors in the daemon process.
///
/// \p nExcept should be the number of elements in the \p exceptFds array.
/// Invalid file descriptors in exceptFds are ignored.
///
/// \note Be \b very careful when using this routine.  It is intended
/// to be used after a \c fork(2) call to close \b all unwanted file
/// descriptors.  However, it does not flush stdio buffers, wait for
/// processes opened with popen, shut down the X11 display connection,
/// or anything.  It just slams closed all the file descriptors.  This
/// is appropriate following a \c fork(2) call as all these file
/// descriptors are duplicates of the ones in the parent process and
/// shutting down the X11 display connection would mess up the parent's
/// X11 display.  But you shouldn't use \c ArchCloseAllFiles unless you
/// know what you are doing.
///
/// \return -1 on error and \c errno will be set to an appropriate
/// value.  Returns 0 on success.
///
/// \ingroup group_arch_Multithreading
ARCH_API
int ArchCloseAllFiles(int nExcept, const int* exceptFds);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_DAEMON_H
