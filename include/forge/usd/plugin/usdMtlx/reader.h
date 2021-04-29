#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/plugin/usdMtlx/reader.h"
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
#ifndef FORGE_USD_PLUGIN_USD_MTLX_READER_H
#define FORGE_USD_PLUGIN_USD_MTLX_READER_H

#include "forge/forge.h"
#include "forge/usd/plugin/usdMtlx/api.h"
#include "forge/usd/sdf/path.h"
#include "forge/base/tf/declarePtrs.h"
#include <MaterialXCore/Document.h>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_PTRS(UsdStage);

/// Translate the MaterialX document in \p mtlx into the stage \p stage.
/// \p internalPath is a namespace path where converted MaterialX objects
/// will live. \p externalPath is a namespace path of a prim that will
/// have all of the look variants.  It will have references into
/// \p internalPath.  Clients are expected to reference the prim at
/// \p externalPath to apply looks.
///
/// Note that this method will traverse the materialx network following material
/// nodes, and does an early exit if no looks are defined in the mtlx document.
USDMTLX_LOCAL
void UsdMtlxRead(const MaterialX::ConstDocumentPtr& mtlx,
                 const UsdStagePtr& stage,
                 const SdfPath& internalPath = SdfPath("/MaterialX"),
                 const SdfPath& externalPath = SdfPath("/ModelRoot"));

/// Translate node graphs in the MaterialX document in \p mtlx into the
/// stage \p stage.  \p internalPath is a namespace path where converted
/// MaterialX objects will live.
///
/// Note that this method will traverse all the nodegraphs in the mtlx document.
USDMTLX_LOCAL
void UsdMtlxReadNodeGraphs(const MaterialX::ConstDocumentPtr& mtlx,
                           const UsdStagePtr& stage,
                           const SdfPath& internalPath = SdfPath("/MaterialX"));

FORGE_NAMESPACE_END

#endif // FORGE_USD_PLUGIN_USD_MTLX_READER_H
