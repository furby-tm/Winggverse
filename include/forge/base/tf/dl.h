#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/dl.h"
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
#ifndef FORGE_BASE_TF_DL_H
#define FORGE_BASE_TF_DL_H

/// \file tf/dl.h
/// \ingroup group_tf_SystemsExt
/// Interface for opening code libraries.

#include "forge/forge.h"
#include "forge/base/tf/api.h"
#include "forge/base/arch/library.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// \addtogroup group_tf_SystemsExt
///@{

/// Open a dynamic library and notify \c lib/tf that a new module has been
/// loaded.
///
/// This is a wrapper around ArchLibraryOpen() in the sense that this function
/// calls \c ArchLibraryOpen(\p filename, \p flag) but it will additionally
/// load script bindings if scripting is initialized and loading is requested.
///
/// If \p error is not \c NULL it will be set to a system reported error
/// if opening the library failed, otherwise it will be cleared.
///
/// If you set TF_DLOPEN in the TF_DEBUG environment variable then debug
/// output will be reported on each invocation of this function.
///
/// This returns an opaque handle to the opened library or \c NULL on
/// failure.
TF_API
void* TfDlopen(const std::string &filename,
               int flag,
               std::string *error = NULL,
               bool loadScriptBindings = true);

/// Close a dynamic library.
TF_API
int TfDlclose(void* handle);

/// \private
TF_API
bool Tf_DlOpenIsActive();
/// \private
TF_API
bool Tf_DlCloseIsActive();

///@}

FORGE_NAMESPACE_END

#endif
