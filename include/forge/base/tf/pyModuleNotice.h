#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/pyModuleNotice.h"
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
#ifndef FORGE_BASE_TF_PY_MODULE_NOTICE_H
#define FORGE_BASE_TF_PY_MODULE_NOTICE_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/notice.h"

#include <string>

FORGE_NAMESPACE_BEGIN

/// \class TfPyModuleWasLoaded
///
/// A \a TfNotice that is sent when a script module is loaded.  Since many
/// modules may be loaded at once, listeners are encouraged to defer work
/// triggered by this notice to the end of an application iteration.  This, of
/// course, is good practice in general.
///
class TfPyModuleWasLoaded : public TfNotice {
public:
    explicit TfPyModuleWasLoaded(std::string const &name) : _name(name) {}

    TF_API
    virtual ~TfPyModuleWasLoaded();

    /// Return the name of the module that was loaded.
    std::string const &GetName() { return _name; }

private:
    std::string _name;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_PY_MODULE_NOTICE_H
