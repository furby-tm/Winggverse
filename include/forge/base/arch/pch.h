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
// WARNING: THIS FILE IS GENERATED.  DO NOT EDIT.
//

#include "forge/forge.h"
#include "forge/base/arch/defines.h"
#if defined(ARCH_OS_DARWIN)
#include <crt_externs.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <glob.h>
#include <limits.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach-o/swap.h>
#include <mach/mach_time.h>
#endif
#if defined(ARCH_OS_LINUX)
#include <csignal>
#include <dlfcn.h>
#include <glob.h>
#include <limits.h>
#include <sys/param.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <sys/statfs.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <ucontext.h>
#include <unistd.h>
#include <unwind.h>
#include <x86intrin.h>
#endif
#if defined(ARCH_OS_WINDOWS)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <DbgHelp.h>
#include <Memoryapi.h>
#include <Psapi.h>
#include <WinIoCtl.h>
#include <Winsock2.h>
#include <chrono>
#include <direct.h>
#include <intrin.h>
#include <io.h>
#include <process.h>
#endif
#include <algorithm>
#include <atomic>
#include <cctype>
#include <cerrno>
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <functional>
#include <inttypes.h>
#include <iosfwd>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <regex>
#include <set>
#include <signal.h>
#include <sstream>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <time.h>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>
