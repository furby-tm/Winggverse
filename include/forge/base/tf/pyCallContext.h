#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyCallContext.h"
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
#ifndef FORGE_BASE_TF_PY_CALL_CONTEXT_H
#define FORGE_BASE_TF_PY_CALL_CONTEXT_H

#include "forge/base/tf/callContext.h"

FORGE_NAMESPACE_BEGIN

TF_API TfCallContext
Tf_PythonCallContext(char const *fileName,
                     char const *moduleName,
                     char const *functionName,
                     size_t line);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_CALL_CONTEXT_H
