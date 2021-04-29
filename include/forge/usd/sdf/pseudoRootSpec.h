#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/pseudoRootSpec.h"
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
#ifndef FORGE_USD_SDF_PSEUDO_ROOT_SPEC_H
#define FORGE_USD_SDF_PSEUDO_ROOT_SPEC_H

/// \file sdf/pseudoRootSpec.h

#include "forge/forge.h"
#include "forge/usd/sdf/declareSpec.h"
#include "forge/usd/sdf/primSpec.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfPseudoRootSpec);

class SdfPseudoRootSpec : public SdfPrimSpec
{
    SDF_DECLARE_SPEC(SdfPseudoRootSpec, SdfPrimSpec);
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PSEUDO_ROOT_SPEC_H
