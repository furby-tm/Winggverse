#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/points.h"
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
#ifndef FORGE_IMAGING_HD_POINTS_H
#define FORGE_IMAGING_HD_POINTS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/rprim.h"

FORGE_NAMESPACE_BEGIN

/// \class HdPointsReprDesc
///
/// Descriptor to configure a drawItem for a repr.
///
struct HdPointsReprDesc {
    HdPointsReprDesc(
        HdPointsGeomStyle geomStyle = HdPointsGeomStyleInvalid)
        : geomStyle(geomStyle)
        {}

    bool IsEmpty() const {
        return geomStyle == HdPointsGeomStyleInvalid;
    }

    HdPointsGeomStyle geomStyle;
};

/// Hydra Schema for a point cloud.
///
class HdPoints: public HdRprim {
public:
    HD_API
    virtual ~HdPoints();

    HD_API
    TfTokenVector const & GetBuiltinPrimvarNames() const override;

    /// Configure geometric style of drawItems for \p reprName
    HD_API
    static void ConfigureRepr(TfToken const &reprName,
                              const HdPointsReprDesc &desc);

protected:
    /// Constructor. instancerId, if specified, is the instancer which uses
    /// this point cloud as a prototype.
    HD_API
    HdPoints(SdfPath const& id);

    typedef _ReprDescConfigs<HdPointsReprDesc> _PointsReprConfig;

    HD_API
    static _PointsReprConfig::DescArray _GetReprDesc(TfToken const &reprName);

private:

    // Class can not be default constructed or copied.
    HdPoints()                             = delete;
    HdPoints(const HdPoints &)             = delete;
    HdPoints &operator =(const HdPoints &) = delete;

    static _PointsReprConfig _reprDescConfig;
};


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_POINTS_H
