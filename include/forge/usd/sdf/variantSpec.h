#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/variantSpec.h"
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
#ifndef FORGE_USD_SDF_VARIANT_SPEC_H
#define FORGE_USD_SDF_VARIANT_SPEC_H

/// \file sdf/variantSpec.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareSpec.h"
#include "forge/usd/sdf/proxyTypes.h"
#include "forge/usd/sdf/spec.h"
#include <string>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);
SDF_DECLARE_HANDLES(SdfPrimSpec);
SDF_DECLARE_HANDLES(SdfVariantSpec);
SDF_DECLARE_HANDLES(SdfVariantSetSpec);

class SdfPath;

/// \class SdfVariantSpec
///
/// Represents a single variant in a variant set.
///
/// A variant contains a prim.  This prim is the root prim of the variant.
///
/// SdfVariantSpecs are value objects.  This means they are immutable
/// once created and they are passed by copy-in APIs.  To change a variant
/// spec, you make a new one and replace the existing one.
///
class SdfVariantSpec : public SdfSpec
{
    SDF_DECLARE_SPEC(SdfVariantSpec, SdfSpec);

public:
    ///
    /// \name Spec construction
    /// @{

    /// Constructs a new instance.
    SDF_API
    static SdfVariantSpecHandle New(const SdfVariantSetSpecHandle& owner,
                                    const std::string& name);

    /// @}

    /// \name Name
    /// @{

    /// Returns the name of this variant.
    SDF_API
    std::string GetName() const;

    /// Returns the name of this variant.
    SDF_API
    TfToken GetNameToken() const;

    /// @}
    /// \name Namespace hierarchy
    /// @{

    /// Return the SdfVariantSetSpec that owns this variant.
    SDF_API
    SdfVariantSetSpecHandle GetOwner() const;

    /// Get the prim spec owned by this variant.
    SDF_API
    SdfPrimSpecHandle GetPrimSpec() const;

    /// Returns the nested variant sets.
    ///
    /// The result maps variant set names to variant sets.  Variant sets
    /// may be removed through the proxy.
    SDF_API
    SdfVariantSetsProxy GetVariantSets() const;

    /// Returns list of variant names for the given variant set.
    SDF_API
    std::vector<std::string> GetVariantNames(const std::string& name) const;

    /// @}
};

/// Convenience function to create a variant spec for a given variant set and
/// a prim at the given path with.
///
/// The function creates the prim spec if it doesn't exist already and any
/// necessary parent prims, in the given layer.
///
/// It adds the variant set to the variant set list if it doesn't already exist.
///
/// It creates a variant spec with the given name under the specified variant
/// set if it doesn't already exist.
SDF_API SdfVariantSpecHandle SdfCreateVariantInLayer(
    const SdfLayerHandle &layer,
    const SdfPath &primPath,
    const std::string &variantSetName,
    const std::string &variantName );

FORGE_NAMESPACE_END

#endif /* SDF_VARIANT_SPEC_H */
