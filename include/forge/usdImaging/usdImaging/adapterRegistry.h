#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/adapterRegistry.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_ADAPTER_REGISTRY_H
#define FORGE_USD_IMAGING_USD_IMAGING_ADAPTER_REGISTRY_H

/// \file usdImaging/adapterRegistry.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/base/tf/singleton.h"
#include "forge/base/tf/staticTokens.h"
#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

#include <unordered_map>

FORGE_NAMESPACE_BEGIN


class UsdImagingPrimAdapter;
using UsdImagingPrimAdapterSharedPtr = std::shared_ptr<UsdImagingPrimAdapter>;

#define USD_IMAGING_ADAPTER_KEY_TOKENS          \
    ((instanceAdapterKey, "__instanceAdapter")) \
    ((drawModeAdapterKey, "__drawModeAdapter"))       \

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(UsdImagingAdapterKeyTokens, USDIMAGING_API, USD_IMAGING_ADAPTER_KEY_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \class UsdImagingAdapterRegistry
///
/// Registry of PrimAdapter plug-ins.
///
class UsdImagingAdapterRegistry : public TfSingleton<UsdImagingAdapterRegistry>
{
    friend class TfSingleton<UsdImagingAdapterRegistry>;
    UsdImagingAdapterRegistry();

    typedef std::unordered_map<TfToken,TfType,TfToken::HashFunctor> _TypeMap;
    _TypeMap _typeMap;

public:

    /// Returns true if external plugins are enabled.
    /// Internal plugins have isInternal=1 set in their metadata. This flag is
    /// only intended to be set for critical imaging plugins  (mesh, cube,
    /// sphere, curve, etc). This allows users to disable plugins that are
    /// crashing or executing slowly.
    ///
    /// Driven by by the USDIMAGING_ENABLE_PLUGINS environment variable.
    USDIMAGING_API
    static bool AreExternalPluginsEnabled();

    USDIMAGING_API
    static UsdImagingAdapterRegistry& GetInstance() {
        return TfSingleton<UsdImagingAdapterRegistry>::GetInstance();
    }

    /// Returns true if an adapter has been registered to handle the given
    /// \p adapterKey.
    USDIMAGING_API
    bool HasAdapter(TfToken const& adapterKey);

    /// Returns a new instance of the UsdImagingPrimAdapter that has been
    /// registered to handle the given \p adapterKey. This key is either
    /// a prim typename or a key specified in UsdImagingAdapterKeyTokens.
    /// Returns NULL if no adapter was registered for this key.
    USDIMAGING_API
    UsdImagingPrimAdapterSharedPtr ConstructAdapter(TfToken const& adapterKey);
};

USDIMAGING_API_TEMPLATE_CLASS(TfSingleton<UsdImagingAdapterRegistry>);

FORGE_NAMESPACE_END

#endif //FORGE_USD_IMAGING_USD_IMAGING_ADAPTER_REGISTRY_H
