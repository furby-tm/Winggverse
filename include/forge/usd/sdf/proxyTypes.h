#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/proxyTypes.h"
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
#ifndef FORGE_USD_SDF_PROXY_TYPES_H
#define FORGE_USD_SDF_PROXY_TYPES_H

#include "forge/forge.h"
#include "forge/usd/sdf/childrenProxy.h"
#include "forge/usd/sdf/childrenView.h"
#include "forge/usd/sdf/childrenPolicies.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/listEditorProxy.h"
#include "forge/usd/sdf/listProxy.h"
#include "forge/usd/sdf/mapEditProxy.h"
#include "forge/usd/sdf/proxyPolicies.h"

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfSpec);

typedef SdfListProxy<SdfNameTokenKeyPolicy> SdfNameOrderProxy;
typedef SdfListProxy<SdfSubLayerTypePolicy> SdfSubLayerProxy;
typedef SdfListEditorProxy<SdfNameKeyPolicy> SdfNameEditorProxy;
typedef SdfListEditorProxy<SdfPathKeyPolicy> SdfPathEditorProxy;
typedef SdfListEditorProxy<SdfPayloadTypePolicy> SdfPayloadEditorProxy;
typedef SdfListEditorProxy<SdfReferenceTypePolicy> SdfReferenceEditorProxy;

typedef SdfChildrenView<Sdf_AttributeChildPolicy,
            SdfAttributeViewPredicate> SdfAttributeSpecView;
typedef SdfChildrenView<Sdf_PrimChildPolicy> SdfPrimSpecView;
typedef SdfChildrenView<Sdf_PropertyChildPolicy> SdfPropertySpecView;
typedef SdfChildrenView<Sdf_AttributeChildPolicy > SdfRelationalAttributeSpecView;
typedef SdfChildrenView<Sdf_RelationshipChildPolicy, SdfRelationshipViewPredicate>
            SdfRelationshipSpecView;
typedef SdfChildrenView<Sdf_VariantChildPolicy> SdfVariantView;
typedef SdfChildrenView<Sdf_VariantSetChildPolicy> SdfVariantSetView;
typedef SdfChildrenProxy<SdfVariantSetView> SdfVariantSetsProxy;

typedef SdfNameOrderProxy SdfNameChildrenOrderProxy;
typedef SdfNameOrderProxy SdfPropertyOrderProxy;
typedef SdfPathEditorProxy SdfConnectionsProxy;
typedef SdfPathEditorProxy SdfInheritsProxy;
typedef SdfPathEditorProxy SdfSpecializesProxy;
typedef SdfPathEditorProxy SdfTargetsProxy;
typedef SdfPayloadEditorProxy SdfPayloadsProxy;
typedef SdfReferenceEditorProxy SdfReferencesProxy;
typedef SdfNameEditorProxy SdfVariantSetNamesProxy;

typedef SdfMapEditProxy<VtDictionary> SdfDictionaryProxy;
typedef SdfMapEditProxy<SdfVariantSelectionMap> SdfVariantSelectionProxy;
typedef SdfMapEditProxy<SdfRelocatesMap,
                        SdfRelocatesMapProxyValuePolicy> SdfRelocatesMapProxy;

/// Returns a path list editor proxy for the path list op in the given
/// \p pathField on \p spec.  If the value doesn't exist or \p spec is
/// invalid then this returns an invalid list editor.
SdfPathEditorProxy
SdfGetPathEditorProxy(
    const SdfSpecHandle& spec, const TfToken& pathField);

/// Returns a reference list editor proxy for the references list op in the
/// given \p referenceField on \p spec. If the value doesn't exist or the object
/// is invalid then this returns an invalid list editor.
SdfReferenceEditorProxy
SdfGetReferenceEditorProxy(
    const SdfSpecHandle& spec, const TfToken& referenceField);

/// Returns a payload list editor proxy for the payloads list op in the given
/// \p payloadField on \p spec.  If the value doesn't exist or the object is
/// invalid then this returns an invalid list editor.
SdfPayloadEditorProxy
SdfGetPayloadEditorProxy(
    const SdfSpecHandle& spec, const TfToken& payloadField);

/// Returns a name order list proxy for the ordering specified in the given
/// \p orderField on \p spec.  If the value doesn't exist or the object is
/// invalid then this returns an invalid list editor.
SdfNameOrderProxy
SdfGetNameOrderProxy(
    const SdfSpecHandle& spec, const TfToken& orderField);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_PROXY_TYPES_H
