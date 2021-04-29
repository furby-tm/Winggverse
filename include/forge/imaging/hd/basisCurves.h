#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/basisCurves.h"
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
#ifndef FORGE_IMAGING_HD_BASIS_CURVES_H
#define FORGE_IMAGING_HD_BASIS_CURVES_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/rprim.h"

FORGE_NAMESPACE_BEGIN

#define HD_BASISCURVES_REPR_DESC_TOKENS \
    (surfaceShader)                     \
    (hullColor)                         \
    (pointColor)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdBasisCurvesReprDescTokens, HD_API, HD_BASISCURVES_REPR_DESC_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \class HdBasisCurvesReprDesc
///
/// Descriptor to configure a drawItem for a repr.
///
struct HdBasisCurvesReprDesc {
    HdBasisCurvesReprDesc(
        HdBasisCurvesGeomStyle geomStyle = HdBasisCurvesGeomStyleInvalid,
        TfToken shadingTerminal = HdBasisCurvesReprDescTokens->surfaceShader)
        : geomStyle(geomStyle),
          shadingTerminal(shadingTerminal)
        {}

    bool IsEmpty() const {
        return geomStyle == HdBasisCurvesGeomStyleInvalid;
    }

    HdBasisCurvesGeomStyle geomStyle;
    /// Specifies how the fragment color should be computed from primvar;
    /// this can be used to render heatmap highlighting etc.
    TfToken         shadingTerminal;
};

/// Hydra Schema for a collection of curves using a particular basis.
///
class HdBasisCurves : public HdRprim {
public:
    HD_API
    virtual ~HdBasisCurves();

    ///
    /// Topology
    ///
    inline HdBasisCurvesTopology  GetBasisCurvesTopology(HdSceneDelegate* delegate) const;
    inline HdDisplayStyle         GetDisplayStyle(HdSceneDelegate* delegate)        const;

    HD_API
    TfTokenVector const & GetBuiltinPrimvarNames() const override;

    /// Configure geometric style of drawItems for \p reprName
    HD_API
    static void ConfigureRepr(TfToken const &reprName,
                              HdBasisCurvesReprDesc desc);

    /// Returns whether refinement is always on or not.
    HD_API
    static bool IsEnabledForceRefinedCurves();

protected:
    HD_API
    HdBasisCurves(SdfPath const& id);

    typedef _ReprDescConfigs<HdBasisCurvesReprDesc> _BasisCurvesReprConfig;

    HD_API
    static _BasisCurvesReprConfig::DescArray
        _GetReprDesc(TfToken const &reprName);

private:
    // Class can not be default constructed or copied.
    HdBasisCurves()                                  = delete;
    HdBasisCurves(const HdBasisCurves &)             = delete;
    HdBasisCurves &operator =(const HdBasisCurves &) = delete;

    static _BasisCurvesReprConfig _reprDescConfig;
};

inline HdBasisCurvesTopology
HdBasisCurves::GetBasisCurvesTopology(HdSceneDelegate* delegate) const
{
    return delegate->GetBasisCurvesTopology(GetId());
}

inline HdDisplayStyle
HdBasisCurves::GetDisplayStyle(HdSceneDelegate* delegate) const
{
    return delegate->GetDisplayStyle(GetId());
}


FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_BASIS_CURVES_H
