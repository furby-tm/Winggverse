#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/resourceRegistry.h"
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
#ifndef FORGE_IMAGING_HD_RESOURCE_REGISTRY_H
#define FORGE_IMAGING_HD_RESOURCE_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"

#include "forge/imaging/hd/perfLog.h"

#include "forge/imaging/hf/perfLog.h"

#include "forge/base/tf/singleton.h"
#include "forge/base/tf/token.h"
#include "forge/base/vt/dictionary.h"

#include <memory>

FORGE_NAMESPACE_BEGIN


using HdResourceRegistrySharedPtr = std::shared_ptr<class HdResourceRegistry>;

/// \class HdResourceRegistry
///
/// A central registry for resources.
///
class HdResourceRegistry  {
public:
    HF_MALLOC_TAG_NEW("new HdResourceRegistry");

    HD_API
    HdResourceRegistry();

    HD_API
    virtual ~HdResourceRegistry();

    /// Commits all in-flight source data.
    HD_API
    void Commit();

    /// cleanup all buffers and remove if empty
    HD_API
    void GarbageCollect();

    /// Globally unique id for texture, see HdRenderIndex::GetTextureKey() for
    /// details.
    typedef size_t TextureKey;

    /// Invalidate any shaders registered with this registry.
    HD_API
    virtual void InvalidateShaderRegistry();

    /// Generic method to inform RenderDelegate a resource needs to be reloaded.
    /// This method can be used by the application to inform the renderDelegate
    /// that a resource, which may not have any prim representation in Hydra,
    /// needs to be reloaded. For example a texture found in a material network.
    /// The `path` can be absolute or relative. It should usually match the
    /// path found for textures during HdMaterial::Sync.
    HD_API
    virtual void ReloadResource(
        TfToken const& resourceType,
        std::string const& path);

    /// Returns a report of resource allocation by role in bytes and
    /// a summary total allocation of GPU memory in bytes for this registry.
    HD_API
    virtual VtDictionary GetResourceAllocation() const;

protected:
    /// A hook for derived registries to perform additional resource commits.
    HD_API
    virtual void _Commit();

    /// Hooks for derived registries to perform additional GC when
    /// GarbageCollect() is invoked.
    HD_API
    virtual void _GarbageCollect();

private:
    // Not copyable
    HdResourceRegistry(const HdResourceRegistry&) = delete;
    HdResourceRegistry& operator=(const HdResourceRegistry&) = delete;
};

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_RESOURCE_REGISTRY_H
