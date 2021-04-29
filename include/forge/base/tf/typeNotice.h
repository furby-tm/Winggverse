#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/typeNotice.h"
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
#ifndef FORGE_BASE_TF_TYPE_NOTICE_H
#define FORGE_BASE_TF_TYPE_NOTICE_H

#include "forge/forge.h"

#include "forge/base/tf/notice.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

/// \class TfTypeWasDeclaredNotice
///
/// TfNotice sent after a TfType is declared.
class TfTypeWasDeclaredNotice : public TfNotice
{
public:
    TfTypeWasDeclaredNotice( TfType t );
    virtual ~TfTypeWasDeclaredNotice();

    /// Get the newly declared TfType.
    TfType GetType() const { return _type; }

private:
    TfType _type;
};

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_TYPE_NOTICE_H
