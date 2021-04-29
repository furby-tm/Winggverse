#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/utils.h"
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
#ifndef FORGE_IMAGING_GLF_UTILS_H
#define FORGE_IMAGING_GLF_UTILS_H

/// \file glf/utils.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/imaging/garch/glApi.h"
#include "forge/imaging/hio/types.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// Number of elements.
///
/// Returns the number of elements (channels) in a given GL enum format.
///
/// Supported formats are : GL_DEPTH_COMPONENT, GL_COLOR_INDEX, GL_ALPHA,
/// GL_RED, GL_LUMINANCE, GL_RG, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
GLF_API
int GlfGetNumElements(GLenum format);

/// Byte size of a GL type.
///
/// Returns the size in bytes of a given GL type.
///
/// Supported types are : GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT,
/// GL_SHORT, GL_FLOAT, GL_DOUBLE
GLF_API
int GlfGetElementSize(GLenum type);

/// HioFormat
///
/// Returns the HioFormat for the given GL format and GL type
///
/// Supported formats are : GL_DEPTH_COMPONENT, GL_COLOR_INDEX, GL_ALPHA,
/// GL_RED, GL_LUMINANCE, GL_RG, GL_LUMINANCE_ALPHA, GL_RGB, GL_RGBA
///
/// Supported types are : GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT,
/// GL_SHORT, GL_FLOAT, GL_DOUBLE
GLF_API
HioFormat GlfGetHioFormat(GLenum glFormat, GLenum glType, bool isSRGB);


/// Checks the valitidy of a GL framebuffer
///
/// True if the currently bound GL framebuffer is valid and can be bound
/// or returns the cause of the problem
GLF_API
bool GlfCheckGLFrameBufferStatus(GLuint target, std::string * reason);

FORGE_NAMESPACE_END

#endif
