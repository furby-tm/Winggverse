#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hgiGL/diagnostic.h"
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
#ifndef FORGE_IMAGING_HGI_GL_DIAGNOSTIC_H
#define FORGE_IMAGING_HGI_GL_DIAGNOSTIC_H

#include "forge/forge.h"
#include "forge/imaging/hgiGL/api.h"
#include "forge/base/arch/functionLite.h"
#include <string>

FORGE_NAMESPACE_BEGIN


/// Posts diagnostic errors for all GL errors in the current context.
/// This macro tags the diagnostic errors with the name of the calling
/// function.
#define HGIGL_POST_PENDING_GL_ERRORS() \
        HgiGLPostPendingGLErrors(__ARCH_PRETTY_FUNCTION__)

/// Returns true if GL debug is enabled
HGIGL_API
bool HgiGLDebugEnabled();

/// Posts diagnostic errors for all GL errors in the current context.
HGIGL_API
void HgiGLPostPendingGLErrors(std::string const & where = std::string());

/// Setup OpenGL 4 debug facilities
HGIGL_API
void HgiGLSetupGL4Debug();

HGIGL_API
bool HgiGLMeetsMinimumRequirements();

/// Calls glObjectLabel making sure the label is not too long.
HGIGL_API
void HgiGLObjectLabel(uint32_t identifier,
                      uint32_t name,
                      const std::string &label);

FORGE_NAMESPACE_END

#endif
