#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hio/fieldTextureData.h"
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

#ifndef FORGE_IMAGING_HIO_FIELD_TEXTURE_DATA_H
#define FORGE_IMAGING_HIO_FIELD_TEXTURE_DATA_H

/// \file hio/fieldTextureData.h

#include "forge/forge.h"
#include "forge/imaging/hio/api.h"
#include "forge/imaging/hio/image.h"

#include "forge/base/gf/bbox3d.h"

#include "forge/base/tf/type.h"

#include <memory>
#include <string>

FORGE_NAMESPACE_BEGIN

using HioFieldTextureDataSharedPtr = std::shared_ptr<class HioFieldTextureData>;

/// \class HioFieldTextureData
///
/// An interface class for reading volume files having a
/// transformation.
///
class HioFieldTextureData
{
public:
    HIO_API
    HioFieldTextureData();

    HIO_API
    virtual ~HioFieldTextureData();

    /// Load Volume Field Data
    ///
    /// fieldName corresponds to the gridName in an OpenVDB file or
    /// to the layer/attribute name in a Field3D file.
    /// fieldIndex corresponds to the partition index
    /// fieldPurpose corresponds to the partition name/grouping
    ///
    /// Returns nullptr and posts an error if the specified data cannot be
    /// loaded.
    ///
    HIO_API
    static HioFieldTextureDataSharedPtr New(
        std::string const & filePath,
        std::string const & fieldName,
        int fieldIndex,
        std::string const & fieldPurpose,
        size_t targetMemory);

    /// Bounding box describing how 3d texture maps into
    /// world space.
    ///
    virtual const GfBBox3d &GetBoundingBox() const = 0;

    virtual int ResizedWidth() const = 0;

    virtual int ResizedHeight() const = 0;

    virtual int ResizedDepth() const = 0;

    virtual HioFormat GetFormat() const = 0;

    virtual bool Read() = 0;

    virtual bool HasRawBuffer() const = 0;

    virtual unsigned char const * GetRawBuffer() const = 0;

private:
    // Disallow copies
    HioFieldTextureData(const HioFieldTextureData&) = delete;
    HioFieldTextureData& operator=(const HioFieldTextureData&) = delete;

};

/// \class HioFieldTextureDataFactoryBase
///
/// A base class to make HioFieldTextureData objects, implemented by plugins.
///
class HIO_API HioFieldTextureDataFactoryBase : public TfType::FactoryBase
{
protected:
    friend class HioFieldTextureData;

    virtual HioFieldTextureDataSharedPtr _New(
        std::string const & filePath,
        std::string const & fieldName,
        int fieldIndex,
        std::string const & fieldPurpose,
        size_t targetMemory) const = 0;
};


FORGE_NAMESPACE_END

#endif /* FORGE_IMAGING_HIO_FIELD_TEXTURE_DATA_H */
