#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/types.h"
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
#ifndef FORGE_IMAGING_HDX_TYPES_H
#define FORGE_IMAGING_HDX_TYPES_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"
#include "forge/imaging/hdx/version.h"
#include "forge/imaging/hgi/types.h"
#include "forge/imaging/hio/types.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/dictionary.h"

FORGE_NAMESPACE_BEGIN


// Struct used to send shader inputs from Presto and send them to Hydra
struct HdxShaderInputs {
    VtDictionary parameters;
    VtDictionary textures;
    VtDictionary textureFallbackValues;
    TfTokenVector attributes;
    VtDictionary metaData;
};

HDX_API
bool operator==(const HdxShaderInputs& lhs, const HdxShaderInputs& rhs);
HDX_API
bool operator!=(const HdxShaderInputs& lhs, const HdxShaderInputs& rhs);
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxShaderInputs& pv);

/// Returns the HioFormat for the given HgiFormat
HDX_API
HioFormat HdxGetHioFormat(HgiFormat hgiFormat);

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HDX_TYPES_H
