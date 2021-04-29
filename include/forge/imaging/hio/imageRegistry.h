#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hio/imageRegistry.h"
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
#ifndef FORGE_IMAGING_HIO_IMAGE_REGISTRY_H
#define FORGE_IMAGING_HIO_IMAGE_REGISTRY_H

#include "forge/forge.h"
#include "forge/imaging/hio/api.h"
#include "forge/base/tf/singleton.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

using HioImageSharedPtr = std::shared_ptr<class HioImage>;

class HioRankedTypeMap;

/// \class HioImageRegistry
///
/// Manages plugin registration and loading for HioImage subclasses.
///
class HioImageRegistry : public TfSingleton<HioImageRegistry>
{
public:
    HIO_API
    static HioImageRegistry& GetInstance();

    HIO_API
    bool IsSupportedImageFile(std::string const & filename);

private:
    friend class TfSingleton<HioImageRegistry>;
    HioImageRegistry();

    friend class HioImage;

    HioImageSharedPtr _ConstructImage(std::string const & filename);

private:
    std::unique_ptr<HioRankedTypeMap> const _typeMap;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HIO_IMAGE_REGISTRY_H
