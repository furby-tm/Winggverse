#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/info.h"
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
#ifndef FORGE_IMAGING_GLF_INFO_H
#define FORGE_IMAGING_GLF_INFO_H

/// \file glf/info.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN


/// Tests for GL extension support.
///
/// Returns \c true if each extension name listed in \a extensions
/// is supported by the current GL context.
GLF_API
bool GlfHasExtensions(std::string const & extensions);

FORGE_NAMESPACE_END

#endif
