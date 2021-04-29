#line 1 "C:/Users/tyler/dev/WINGG/forge/base/js/utils.h"
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
#ifndef FORGE_BASE_JS_UTILS_H
#define FORGE_BASE_JS_UTILS_H

/// \file js/utils.h

#include "forge/forge.h"
#include "forge/base/js/api.h"
#include "forge/base/js/value.h"

#include <boost/none.hpp>
#include <boost/optional.hpp>
#include <string>

FORGE_NAMESPACE_BEGIN

typedef boost::optional<JsValue> JsOptionalValue;

/// Returns the value associated with \p key in the given \p object. If no
/// such key exists, and the supplied default is not supplied, this method
/// returns an uninitialized optional JsValue. Otherwise, the \p
/// defaultValue is returned.
JS_API
JsOptionalValue JsFindValue(
    const JsObject& object,
    const std::string& key,
    const JsOptionalValue& defaultValue = boost::none);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_JS_UTILS_H
