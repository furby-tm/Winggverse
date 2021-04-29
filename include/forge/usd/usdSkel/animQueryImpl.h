#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/animQueryImpl.h"
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
#ifndef FORGE_USD_USD_SKEL_ANIM_QUERY_IMPL_H
#define FORGE_USD_USD_SKEL_ANIM_QUERY_IMPL_H

/// \file UsdSkel_AnimQueryImpl

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refBase.h"
#include "forge/base/vt/types.h"

#include "forge/usd/usdGeom/xformable.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/types.h"


FORGE_NAMESPACE_BEGIN


class UsdAttribute;
class UsdPrim;
class UsdTimeCode;


TF_DECLARE_REF_PTRS(UsdSkel_AnimQueryImpl);


/// \class UsdSkel_AnimQueryImpl
///
/// Internal implementation of anim animation query.
/// Subclassing of animation queries is supported out of an expectation
/// that additional core animation prim types may be added in the future.
class UsdSkel_AnimQueryImpl : public TfRefBase
{
public:
    /// Create an anim query for \p prim, if the prim is a valid type.
    static UsdSkel_AnimQueryImplRefPtr New(const UsdPrim& prim);

    virtual ~UsdSkel_AnimQueryImpl() {}

    virtual UsdPrim GetPrim() const = 0;

    virtual bool ComputeJointLocalTransforms(VtMatrix4dArray* xforms,
                                             UsdTimeCode time) const = 0;

    virtual bool ComputeJointLocalTransforms(VtMatrix4fArray* xforms,
                                             UsdTimeCode time) const = 0;

    virtual bool ComputeJointLocalTransformComponents(
                     VtVec3fArray* translations,
                     VtQuatfArray* rotations,
                     VtVec3hArray* scales,
                     UsdTimeCode time) const = 0;

    virtual bool
    GetJointTransformTimeSamples(const GfInterval& interval,
                                 std::vector<double>* times) const = 0;

    virtual bool
    GetJointTransformAttributes(std::vector<UsdAttribute>* attrs) const = 0;

    virtual bool JointTransformsMightBeTimeVarying() const = 0;

    virtual bool
    ComputeBlendShapeWeights(VtFloatArray* weights,
                             UsdTimeCode time=UsdTimeCode::Default()) const = 0;

    virtual bool
    GetBlendShapeWeightTimeSamples(const GfInterval& interval,
                                   std::vector<double>* times) const = 0;

    virtual bool
    GetBlendShapeWeightAttributes(std::vector<UsdAttribute>* attrs) const = 0;

    virtual bool
    BlendShapeWeightsMightBeTimeVarying() const = 0;

    const VtTokenArray& GetJointOrder() const { return _jointOrder; }

    const VtTokenArray& GetBlendShapeOrder() const { return _blendShapeOrder; }

protected:
    VtTokenArray _jointOrder, _blendShapeOrder;
};


FORGE_NAMESPACE_END

#endif // USDSKEL_ANIMQUERY_IMPL
