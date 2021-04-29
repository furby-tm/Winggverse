#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/subLayerListEditor.h"
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
#ifndef FORGE_USD_SDF_SUB_LAYER_LIST_EDITOR_H
#define FORGE_USD_SDF_SUB_LAYER_LIST_EDITOR_H

/// \file sdf/subLayerListEditor.h

#include "forge/forge.h"
#include "forge/usd/sdf/vectorListEditor.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/proxyPolicies.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// \class Sdf_SubLayerListEditor
///
/// List editor implementation for sublayer path lists.
///
class Sdf_SubLayerListEditor
    : public Sdf_VectorListEditor<SdfSubLayerTypePolicy>
{
public:
    Sdf_SubLayerListEditor(const SdfLayerHandle& owner);

    virtual ~Sdf_SubLayerListEditor();

private:
    typedef Sdf_VectorListEditor<SdfSubLayerTypePolicy> Parent;

    virtual void _OnEdit(
        SdfListOpType op,
        const std::vector<std::string>& oldValues,
        const std::vector<std::string>& newValues) const;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_SUB_LAYER_LIST_EDITOR_H
