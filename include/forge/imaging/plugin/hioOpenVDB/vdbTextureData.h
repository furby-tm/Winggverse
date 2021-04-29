#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/plugin/hioOpenVDB/vdbTextureData.h"
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
#ifndef FORGE_IMAGING_HIO_OPENVDB_TEXTURE_DATA_H
#define FORGE_IMAGING_HIO_OPENVDB_TEXTURE_DATA_H

/// \file hioOpenVDB/vdbTextureData.h

#include "forge/forge.h"
#include "forge/imaging/hio/api.h"
#include "forge/imaging/hio/fieldTextureData.h"

#include "forge/base/gf/bbox3d.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HioOpenVDB_TextureData_DenseGridHolderBase;

/// \class HioOpenVDB_TextureData
///
/// Implements HioFieldTextureData to read grid with given name from
/// OpenVDB file at given path.
///
class HioOpenVDB_TextureData final : public HioFieldTextureData
{
public:
    using Base = HioFieldTextureData;

    HioOpenVDB_TextureData(std::string const & filePath,
                           std::string const & gridName,
                           size_t targetMemory);
    ~HioOpenVDB_TextureData() override;

    const GfBBox3d &GetBoundingBox() const override;

    int ResizedWidth() const override;

    int ResizedHeight() const override;

    int ResizedDepth() const override;

    HioFormat GetFormat() const override;
    
    bool Read() override;
    
    bool HasRawBuffer() const override;

    unsigned char const * GetRawBuffer() const override;

private:
    const std::string _filePath;
    const std::string _gridName;

    const size_t _targetMemory;

    int _resizedWidth, _resizedHeight, _resizedDepth;

    HioFormat _format;

    GfBBox3d _boundingBox;

    std::unique_ptr<HioOpenVDB_TextureData_DenseGridHolderBase> _denseGrid;
};


FORGE_NAMESPACE_END

#endif /* FORGE_IMAGING_HIO_OPENVDB_TEXTURE_DATA_H */
