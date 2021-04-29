#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/connectionListEditor.h"
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
#ifndef FORGE_USD_SDF_CONNECTION_LIST_EDITOR_H
#define FORGE_USD_SDF_CONNECTION_LIST_EDITOR_H

#include "forge/forge.h"
#include "forge/usd/sdf/listOpListEditor.h"
#include "forge/usd/sdf/childrenPolicies.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/proxyPolicies.h"
#include "forge/usd/sdf/types.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfSpec);
class TfToken;

/// \class Sdf_ConnectionListEditor
///
/// List editor implementation that ensures that the appropriate target
/// specs are created or destroyed when connection/relationship targets are
/// added to the underlying list operation.
///
template <class ConnectionChildPolicy>
class Sdf_ConnectionListEditor
    : public Sdf_ListOpListEditor<SdfPathKeyPolicy>
{
protected:
    virtual ~Sdf_ConnectionListEditor();

    Sdf_ConnectionListEditor(
        const SdfSpecHandle& connectionOwner,
        const TfToken& connectionListField,
        const SdfPathKeyPolicy& typePolicy = SdfPathKeyPolicy());

    void _OnEditShared(SdfListOpType op,
        SdfSpecType specType,
        const std::vector<SdfPath>& oldItems,
        const std::vector<SdfPath>& newItems) const;

private:
    typedef Sdf_ListOpListEditor<SdfPathKeyPolicy> Parent;
};

/// \class Sdf_AttributeConnectionListEditor
///
/// List editor implementation for attribute connections.
///
class Sdf_AttributeConnectionListEditor
    : public Sdf_ConnectionListEditor<Sdf_AttributeConnectionChildPolicy>
{
public:
    virtual ~Sdf_AttributeConnectionListEditor();

    Sdf_AttributeConnectionListEditor(
        const SdfSpecHandle& owner,
        const SdfPathKeyPolicy& typePolicy = SdfPathKeyPolicy());

    virtual void _OnEdit(SdfListOpType op,
        const std::vector<SdfPath>& oldItems,
        const std::vector<SdfPath>& newItems) const;
private:
    typedef Sdf_ConnectionListEditor<Sdf_AttributeConnectionChildPolicy> Parent;
};

/// \class Sdf_RelationshipTargetListEditor
///
/// List editor implementation for attribute connections.
///
class Sdf_RelationshipTargetListEditor
    : public Sdf_ConnectionListEditor<Sdf_RelationshipTargetChildPolicy>
{
public:
    virtual ~Sdf_RelationshipTargetListEditor();

    Sdf_RelationshipTargetListEditor(
        const SdfSpecHandle& owner,
        const SdfPathKeyPolicy& typePolicy = SdfPathKeyPolicy());

    virtual void _OnEdit(SdfListOpType op,
        const std::vector<SdfPath>& oldItems,
        const std::vector<SdfPath>& newItems) const;
private:
    typedef Sdf_ConnectionListEditor<Sdf_RelationshipTargetChildPolicy> Parent;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_CONNECTION_LIST_EDITOR_H
