#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdr/declare.h"
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
#ifndef FORGE_USD_SDR_DECLARE_H
#define FORGE_USD_SDR_DECLARE_H

/// \file sdr/declare.h

#include "forge/forge.h"
#include "forge/usd/ndr/declare.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class SdrShaderNode;
class SdrShaderProperty;

/// Common typedefs that are used throughout the SDR library.

// ShaderNode
typedef SdrShaderNode* SdrShaderNodePtr;
typedef SdrShaderNode const* SdrShaderNodeConstPtr;
typedef std::unique_ptr<SdrShaderNode> SdrShaderNodeUniquePtr;
typedef std::vector<SdrShaderNodeConstPtr> SdrShaderNodePtrVec;

// ShaderProperty
typedef SdrShaderProperty* SdrShaderPropertyPtr;
typedef SdrShaderProperty const* SdrShaderPropertyConstPtr;
typedef std::unique_ptr<SdrShaderProperty> SdrShaderPropertyUniquePtr;
typedef std::unordered_map<TfToken, SdrShaderPropertyConstPtr,
                           TfToken::HashFunctor> SdrPropertyMap;

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDR_DECLARE_H
