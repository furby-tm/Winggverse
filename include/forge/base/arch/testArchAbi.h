#line 1 "C:/Users/tyler/dev/WINGG/forge/base/arch/testArchAbi.h"
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
#include "forge/base/arch/api.h"

FORGE_NAMESPACE_BEGIN

struct ArchAbiBase1 {
    void* dummy;
};

struct ArchAbiBase2 {
    virtual ~ArchAbiBase2() { }
    virtual const char* name() const = 0;
};

template <class T>
struct ArchAbiDerived : public ArchAbiBase1, public ArchAbiBase2 {
    virtual ~ArchAbiDerived() { }
    virtual const char* name() const { return "ArchAbiDerived"; }
};

FORGE_NAMESPACE_END
