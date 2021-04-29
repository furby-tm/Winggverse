#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/expiryNotifier.h"
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
#ifndef FORGE_BASE_TF_EXPIRY_NOTIFIER_H
#define FORGE_BASE_TF_EXPIRY_NOTIFIER_H

/// \file tf/expiryNotifier.h

#include "forge/forge.h"
#include "forge/base/arch/hints.h"
#include "forge/base/tf/api.h"

FORGE_NAMESPACE_BEGIN

/// \class Tf_ExpiryNotifier
///
/// Set the extra notifier function.
///
/// Objects derived from \c TfWeakBase can request that extra notification be
/// performed when they expire.  Objects that do not request extra
/// notification do not suffer any performance penalty when they expire, while
/// objects that request the notification will have the extra notifier
/// function run on them, with the address returned by \c
/// TfWeakPtr::GetUniqueIdentifier() passed to the notifier function.
///
/// An object requests extra notification be performed by calling \c
/// wp.RequestExtraNotification() where \c wp is a \c TfWeakPtr pointing to
/// the object in question.
///
/// This functions sets the extra notifier function to \p func.  At present,
/// this notifier is intended to be used only by the scripting system to
/// inform the system that a particular object has expired and scripting
/// resources devoted to that object can be discarded.  Accordingly, if
/// \p func is non-NULL and a previous non-NULL notifier function has been
/// set, a fatal error is issued.
class Tf_ExpiryNotifier {
public:
    TF_API static void Invoke(void const *p);
    TF_API static void SetNotifier(void (*func)(void const *));

    TF_API static void Invoke2(void const *p);
    TF_API static void SetNotifier2(void (*func)(void const *));
private:

    static void (*_func)(void const *);
    static void (*_func2)(void const *);
};

FORGE_NAMESPACE_END

#endif
