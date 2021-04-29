#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/relationshipSpec.h"
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
#ifndef FORGE_USD_SDF_RELATIONSHIP_SPEC_H
#define FORGE_USD_SDF_RELATIONSHIP_SPEC_H

/// \file sdf/relationshipSpec.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareSpec.h"
#include "forge/usd/sdf/propertySpec.h"
#include "forge/usd/sdf/types.h"

FORGE_NAMESPACE_BEGIN

/// \class SdfRelationshipSpec
///
/// A property that contains a reference to one or more SdfPrimSpec instances.
///
/// A relationship may refer to one or more target prims or attributes.
/// All targets of a single relationship are considered to be playing the same
/// role. Note that \c role does not imply that the target prims or attributes
/// are of the same \c type.
///
/// Relationships may be annotated with relational attributes.
/// Relational attributes are named SdfAttributeSpec objects containing
/// values that describe the relationship.  For example, point weights are
/// commonly expressed as relational attributes.
///
class SdfRelationshipSpec : public SdfPropertySpec
{
    SDF_DECLARE_SPEC(SdfRelationshipSpec, SdfPropertySpec);

public:
    typedef SdfRelationshipSpec This;
    typedef SdfPropertySpec Parent;

    ///
    /// \name Spec creation
    /// @{

    /// Creates a new prim relationship instance.
    ///
    /// Creates and returns a new relationship for the given prim.
    /// The \p owner will own the newly created relationship.
    SDF_API
    static SdfRelationshipSpecHandle
    New(const SdfPrimSpecHandle& owner,
        const std::string& name,
        bool custom = true,
        SdfVariability variability = SdfVariabilityUniform);

    /// @}

    /// \name Relationship targets
    /// @{

    /// Returns the relationship's target path list editor.
    ///
    /// The list of the target paths for this relationship may be modified
    /// through the proxy.
    SDF_API
    SdfTargetsProxy GetTargetPathList() const;

    /// Returns true if the relationship has any target paths.
    SDF_API
    bool HasTargetPathList() const;

    /// Clears the list of target paths on this relationship.
    SDF_API
    void ClearTargetPathList() const;

    /// Updates the specified target path.
    ///
    /// Replaces the path given by \p oldPath with the one specified by
    /// \p newPath.  Relational attributes are updated if necessary.
    SDF_API
    void ReplaceTargetPath(const SdfPath& oldPath, const SdfPath& newPath);

    /// Removes the specified target path.
    ///
    /// Removes the given target path and any relational attributes for the
    /// given target path. If \p preserveTargetOrder is \c true, Erase() is
    /// called on the list editor instead of RemoveItemEdits(). This preserves
    /// the ordered items list.
    SDF_API
    void RemoveTargetPath(const SdfPath& path, bool preserveTargetOrder = false);

    /// @}

    /// Get whether loading the target of this relationship is necessary
    /// to load the prim we're attached to
    SDF_API
    bool GetNoLoadHint(void) const;

    /// Set whether loading the target of this relationship is necessary
    /// to load the prim we're attached to
    SDF_API
    void SetNoLoadHint(bool noload);

private:
    SdfPath _CanonicalizeTargetPath(const SdfPath& path) const;

    SdfPath _MakeCompleteTargetSpecPath(const SdfPath& srcPath) const;

    SdfSpecHandle _GetTargetSpec(const SdfPath& path) const;

    // Allow access to _GetTarget() for the  relational attribute c'tor
    friend class SdfAttributeSpec;

    // Allow access to retrieve relationship spec for this API object.
    friend class Sdf_PyRelationshipAccess;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_RELATIONSHIP_SPEC_H
