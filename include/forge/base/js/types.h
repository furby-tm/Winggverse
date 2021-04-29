#line 1 "C:/Users/tyler/dev/WINGG/forge/base/js/types.h"
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
#ifndef FORGE_BASE_JS_TYPES_H
#define FORGE_BASE_JS_TYPES_H

/// \file js/types.h

#include "forge/forge.h"

#include <map>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class JsValue;
typedef std::map<std::string, JsValue> JsObject;
typedef std::vector<JsValue> JsArray;

FORGE_NAMESPACE_END

#endif // FORGE_BASE_JS_TYPES_H
