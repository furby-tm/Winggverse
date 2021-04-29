#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/debugNotice.h"
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
#ifndef FORGE_BASE_TF_DEBUG_NOTICE_H
#define FORGE_BASE_TF_DEBUG_NOTICE_H

/// \file tf/debugNotice.h

#include "forge/forge.h"
#include "forge/base/tf/notice.h"

FORGE_NAMESPACE_BEGIN

/// \class TfDebugSymbolsChangedNotice
///
/// Sent when the list of available debug symbol names has changed.
class TfDebugSymbolsChangedNotice : public TfNotice
{
public:
    TfDebugSymbolsChangedNotice() {}
    virtual ~TfDebugSymbolsChangedNotice();
};

/// \class TfDebugSymbolEnableChangedNotice
///
/// Sent when a debug symbol has been enabled or disabled.
class TfDebugSymbolEnableChangedNotice : public TfNotice
{
public:
    TfDebugSymbolEnableChangedNotice() {}
    virtual ~TfDebugSymbolEnableChangedNotice();
};

FORGE_NAMESPACE_END

#endif
