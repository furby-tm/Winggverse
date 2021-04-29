#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/atomicRenameUtil.h"
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
#include "forge/forge.h"

#include <string>

FORGE_NAMESPACE_BEGIN

// Atomically rename \p srcFileName over \p dstFileName, assuming they are
// sibling files on the same filesystem.  Set \p error and return false in case
// of an error, otherwise return true.
bool
Tf_AtomicRenameFileOver(std::string const &srcFileName,
                        std::string const &dstFileName,
                        std::string *error);

// Attempt to create a temporary sibling file of \p fileName.  If succesful
// return the realpath of \p fileName in \p realFileName, the created temporary
// file name in \p tempFileName, and its open file descriptor.  In case of an
// error, set \p error and return -1.
int
Tf_CreateSiblingTempFile(std::string fileName,
                         std::string *realFileName,
                         std::string *tempFileName,
                         std::string *error);

FORGE_NAMESPACE_END
