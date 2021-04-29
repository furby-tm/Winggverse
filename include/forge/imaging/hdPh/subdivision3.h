#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/subdivision3.h"
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
#ifndef FORGE_IMAGING_HD_PH_SUBDIVISION3_H
#define FORGE_IMAGING_HD_PH_SUBDIVISION3_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"

FORGE_NAMESPACE_BEGIN

class HdPh_Subdivision;

class HdPh_Osd3Factory {
 public:
  static HdPh_Subdivision *CreateSubdivision();
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_SUBDIVISION3_H
