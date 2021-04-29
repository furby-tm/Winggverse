#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/notice.h"
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
#ifndef FORGE_BASE_PLUG_NOTICE_H
#define FORGE_BASE_PLUG_NOTICE_H

#include "forge/forge.h"
#include "forge/base/plug/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/notice.h"

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_PTRS(PlugPlugin);

/// \class PlugNotice
/// Notifications sent by the Plug library.
class PlugNotice
{
public:
    /// Base class for all Plug notices.
    class Base : public TfNotice
    {
    public:
        PLUG_API virtual ~Base();
    };

    /// Notice sent after new plugins have been registered with the Plug
    /// registry.
    class DidRegisterPlugins : public Base
    {
    public:
        explicit DidRegisterPlugins(const PlugPluginPtrVector& newPlugins);
        PLUG_API virtual ~DidRegisterPlugins();

        const PlugPluginPtrVector& GetNewPlugins() const
        { return _plugins; }

    private:
        PlugPluginPtrVector _plugins;
    };

private:
    PlugNotice();
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_NOTICE_H
