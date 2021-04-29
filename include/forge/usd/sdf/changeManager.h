#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/changeManager.h"
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
#ifndef FORGE_USD_SDF_CHANGE_MANAGER_H
#define FORGE_USD_SDF_CHANGE_MANAGER_H

/// \file sdf/changeManager.h

#include "forge/forge.h"
#include "forge/usd/sdf/changeList.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/spec.h"
#include "forge/base/tf/singleton.h"

#include <boost/noncopyable.hpp>

#if !defined(Q_MOC_RUN)
# include <tbb/enumerable_thread_specific.h>
#endif /* Q_MOC_RUN */

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

class SdfSpec;

/// \class Sdf_ChangeManager
///
/// Pathway for invalidation and change notification emitted by Sdf.
///
/// Since Sdf is the base representation in our system, and doesn't have
/// many derived computations, this primarily just queues up invalidation
/// notifications directly.
///
/// For now this class uses TfNotices to represent invalidations.
///
class Sdf_ChangeManager : boost::noncopyable {
public:
    SDF_API
    static Sdf_ChangeManager& Get() {
        return TfSingleton<Sdf_ChangeManager>::GetInstance();
    }

    // Queue notifications.
    void DidReplaceLayerContent(const SdfLayerHandle &layer);
    void DidReloadLayerContent(const SdfLayerHandle &layer);
    void DidChangeLayerIdentifier(const SdfLayerHandle &layer,
                                  const std::string &oldIdentifier);
    void DidChangeLayerResolvedPath(const SdfLayerHandle &layer);
    void DidChangeField(const SdfLayerHandle &layer,
                        const SdfPath & path, const TfToken &field,
                        const VtValue & oldValue, const VtValue & newValue );
    void DidChangeAttributeTimeSamples(const SdfLayerHandle &layer,
                                       const SdfPath &attrPath);

    // Spec changes.
    void DidMoveSpec(const SdfLayerHandle &layer,
                     const SdfPath & oldPath, const SdfPath & newPath);
    void DidAddSpec(const SdfLayerHandle &layer, const SdfPath &path,
                    bool inert);
    void DidRemoveSpec(const SdfLayerHandle &layer, const SdfPath &path,
                       bool inert);
    void RemoveSpecIfInert(const SdfSpec&);

    // Open/close change blocks. SdfChangeBlock provides stack-based management
    // of change blocks and should be preferred over this API.
    SDF_API
    void OpenChangeBlock();
    SDF_API
    void CloseChangeBlock();

private:
    Sdf_ChangeManager();
    ~Sdf_ChangeManager();

    void _SendNoticesForChangeList( const SdfLayerHandle & layer,
                                    const SdfChangeList & changeList );
    void _SendNotices();

    void _ProcessRemoveIfInert();

    SdfChangeList &_GetListFor(SdfLayerChangeListVec &changeList,
                               SdfLayerHandle const &layer);

private:
    struct _Data {
        _Data();
        SdfLayerChangeListVec changes;
        int changeBlockDepth;
        std::vector<SdfSpec> removeIfInert;
    };

    tbb::enumerable_thread_specific<_Data> _data;

    friend class TfSingleton<Sdf_ChangeManager>;
};

SDF_API_TEMPLATE_CLASS(TfSingleton<Sdf_ChangeManager>);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_CHANGE_MANAGER_H
