#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/variantSetSpec.h"
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
#ifndef FORGE_USD_SDF_VARIANT_SET_SPEC_H
#define FORGE_USD_SDF_VARIANT_SET_SPEC_H

/// \file sdf/variantSetSpec.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareSpec.h"
#include "forge/usd/sdf/spec.h"
#include "forge/usd/sdf/proxyTypes.h"
#include "forge/usd/sdf/types.h"

#include <iosfwd>
#include <map>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class SdfVariantSetSpec
///
/// Represents a coherent set of alternate representations for part of a
/// scene.
///
/// An SdfPrimSpec object may contain one or more named SdfVariantSetSpec
/// objects that define variations on the prim.
///
/// An SdfVariantSetSpec object contains one or more named SdfVariantSpec
/// objects. It may also define the name of one of its variants to be used by
/// default.
///
/// When a prim references another prim, the referencing prim may specify
/// one of the variants from each of the variant sets of the target prim.
/// The chosen variant from each set (or the default variant from those sets
/// that the referencing prim does not explicitly specify) is composited
/// over the target prim, and then the referencing prim is composited over
/// the result.
///
class SdfVariantSetSpec : public SdfSpec
{
    SDF_DECLARE_SPEC(SdfVariantSetSpec, SdfSpec);

public:
    ///
    /// \name Spec construction
    /// @{

    /// Constructs a new instance.
    SDF_API
    static SdfVariantSetSpecHandle
    New(const SdfPrimSpecHandle& prim, const std::string& name);

    /// Constructs a new instance.
    SDF_API
    static SdfVariantSetSpecHandle
    New(const SdfVariantSpecHandle& prim, const std::string& name);

    /// @}

    /// \name Name
    /// @{

    /// Returns the name of this variant set.
    SDF_API
    std::string GetName() const;

    /// Returns the name of this variant set.
    SDF_API
    TfToken GetNameToken() const;

    /// @}
    /// \name Namespace hierarchy
    /// @{

    /// Returns the prim or variant that this variant set belongs to.
    SDF_API
    SdfSpecHandle GetOwner() const;

    /// @}
    /// \name Variants
    /// @{

    /// Returns the variants as a map.
    SDF_API
    SdfVariantView GetVariants() const;

    /// Returns the variants as a vector.
    SDF_API
    SdfVariantSpecHandleVector GetVariantList() const;

    /// Removes \p variant from the list of variants.
    ///
    /// If the variant set does not currently own \p variant, no action
    /// is taken.
    SDF_API
    void RemoveVariant(const SdfVariantSpecHandle& variant);

    /// @}
};

FORGE_NAMESPACE_END

#endif // SD_VARIANTSETSPEC_H
