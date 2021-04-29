#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/resource.h"
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
#ifndef FORGE_IMAGING_HD_RESOURCE_H
#define FORGE_IMAGING_HD_RESOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/base/tf/token.h"

#include <cstddef>
#include <memory>

FORGE_NAMESPACE_BEGIN


using HdResourceSharedPtr = std::shared_ptr<class HdResource>;

/// \class HdResource
///
/// Base class for all GPU resource objects.
///
class HdResource
{
public:
    HD_API
    HdResource(TfToken const & role);
    HD_API
    virtual ~HdResource();

    /// Returns the role of the GPU data in this resource.
    TfToken const & GetRole() const {return _role;}

    /// Returns the size of the resource allocated in the GPU
    HD_API
    size_t GetSize() const {return _size;}

protected:
    /// Stores the size of the resource allocated in the GPU
    HD_API
    void SetSize(size_t size);

private:

    // Don't allow copies.
    HdResource(const HdResource &) = delete;
    HdResource &operator=(const HdResource &) = delete;


    const TfToken _role;
    size_t _size;
};


FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_RESOURCE_H
