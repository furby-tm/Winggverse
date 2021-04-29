#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/symbols.h"
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
#ifndef FORGE_BASE_ARCH_SYMBOLS_H
#define FORGE_BASE_ARCH_SYMBOLS_H

/// \file arch/symbols.h
/// \ingroup group_arch_Diagnostics
/// Architecture-specific symbol lookup routines.

#include "forge/forge.h"
#include "forge/base/arch/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN

/// Returns information about the address \p address in the running program.
///
/// Returns \c false if no information can be found, otherwise returns \c true
/// and modifies the other arguments: \p objectPath is set to the absolute path
/// to the executable or library the address is found in, \p baseAddress is the
/// address where that object is loaded, \p symbolName is the symbolic name of
/// the thing containing the address, and \p symbolAddress is the starting
/// address of that thing.  If no thing is found to contain the address then
/// \p symbolName is cleared and \p symbolAddress is set to \c NULL. Any of
/// the arguments except \p address can be \c NULL if the result isn't needed.
/// This will return \c false if \c NULL is passed to \p address.
///
/// \ingroup group_arch_Diagnostics
ARCH_API
bool ArchGetAddressInfo(void* address,
                        std::string* objectPath, void** baseAddress,
                        std::string* symbolName, void** symbolAddress);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_ARCH_SYMBOLS_H
