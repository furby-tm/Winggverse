#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/scopeDescriptionPrivate.h"
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
#ifndef FORGE_BASE_TF_SCOPE_DESCRIPTION_PRIVATE_H
#define FORGE_BASE_TF_SCOPE_DESCRIPTION_PRIVATE_H

#include "forge/forge.h"

FORGE_NAMESPACE_BEGIN

// Helper class for getting the TfScopeDescription stacks as human readable text
// for crash reporting.
class Tf_ScopeDescriptionStackReportLock
{
    Tf_ScopeDescriptionStackReportLock(
        Tf_ScopeDescriptionStackReportLock const &) = delete;
    Tf_ScopeDescriptionStackReportLock &operator=(
        Tf_ScopeDescriptionStackReportLock const &) = delete;
public:
    // Lock and compute the report message.
    Tf_ScopeDescriptionStackReportLock();

    // Unlock.
    ~Tf_ScopeDescriptionStackReportLock();

    // Get the report message.  This could be nullptr if it was impossible to
    // obtain the report.
    char const *GetMessage() const { return _msg; }

private:
    char const *_msg;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_SCOPE_DESCRIPTION_PRIVATE_H
