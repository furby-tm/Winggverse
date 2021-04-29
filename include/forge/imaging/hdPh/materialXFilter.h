#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/materialXFilter.h"
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
#ifndef FORGE_IMAGING_HD_PH_MATERIALX_FILTER_H
#define FORGE_IMAGING_HD_PH_MATERIALX_FILTER_H

#include "forge/forge.h"
#include "forge/imaging/hd/material.h"
#include "forge/usd/sdf/path.h"
#include <MaterialXCore/Document.h>
#include <MaterialXFormat/Util.h>

FORGE_NAMESPACE_BEGIN

/// MaterialX Filter
/// Converting a MaterialX node to one with a generated MaterialX glslfx file
void HdPh_ApplyMaterialXFilter(HdMaterialNetwork2 *hdNetwork,
                               SdfPath const &materialPath,
                               HdMaterialNode2 const &terminalNode,
                               SdfPath const &terminalNodePath);

// Generates the glsfx source code for the given MaterialX Document
std::string HdPh_GenMaterialXShaderCode(
    MaterialX::DocumentPtr const &mxDoc,
    MaterialX::FileSearchPath const &searchPath,
    MaterialX::StringMap const &mxHdTextureMap);  // Mx-Hd texture counterparts

FORGE_NAMESPACE_END

#endif