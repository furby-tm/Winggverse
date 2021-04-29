#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/editTarget.h"
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
#ifndef FORGE_USD_USD_EDIT_TARGET_H
#define FORGE_USD_USD_EDIT_TARGET_H

#include "forge/forge.h"
#include "forge/usd/usd/api.h"
#include "forge/usd/pcp/layerStackIdentifier.h"
#include "forge/usd/pcp/mapFunction.h"
#include "forge/usd/pcp/node.h"
#include "forge/usd/sdf/layer.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/primSpec.h"

FORGE_NAMESPACE_BEGIN


TF_DECLARE_WEAK_PTRS(UsdStage);

/// \class UsdEditTarget
///
/// Defines a mapping from scene graph paths to Sdf spec paths in a
/// SdfLayer where edits should be directed, or up to where to perform partial
/// composition.
///
/// A UsdEditTarget can represent an arbitrary point in a composition graph for
/// the purposes of placing edits and resolving values.  This enables editing
/// and resolving across references, classes, variants, and payloads.
///
/// In the simplest case, an EditTarget represents a single layer in a stage's
/// local LayerStack.  In this case, the mapping that transforms scene graph
/// paths to spec paths in the layer is the identity function.  That is, the
/// UsdAttribute path '/World/Foo.avar' would map to the SdfPropertySpec path
/// '/World/Foo.avar'.
///
/// For a more complex example, suppose '/World/Foo' in 'Shot.usda' is a
/// reference to '/Model' in 'Model.usda'.  One can construct a UsdEditTarget
/// that maps scene graph paths from the 'Shot.usda' stage across the reference
/// to the appropriate paths in the 'Model.usda' layer.  For example, the
/// UsdAttribute '/World/Foo.avar' would map to the SdfPropertySpec
/// '/Model.avar'.  Paths in the stage composed at 'Shot.usda' that weren't
/// prefixed by '/World/Foo' would not have a valid mapping to 'Model.usda'.
///
/// EditTargets may also work for any other kind of arc or series of arcs.
/// This allows for editing across variants, classes, and payloads, or in a
/// variant on the far side of a reference, for example.
///
/// In addition to mapping scene paths to spec paths for editing, EditTargets
/// may also be used to identify points in the composition graph for partial
/// composition.  Though it doesn't currently exist, a UsdCompose API that takes
/// UsdEditTarget arguments may someday be provided.
///
/// For convenience and deployment ease, SdfLayerHandles will implicitly convert
/// to UsdEditTargets.  A UsdEditTarget constructed in this way means direct
/// opinions in a layer in a stage's local LayerStack.
///
class UsdEditTarget
{
public:

    /// Construct a null EditTarget.  A null EditTarget will return paths
    /// unchanged when asked to map paths.
    USD_API
    UsdEditTarget();

    /// Constructor.  Allow implicit conversion from SdfLayerHandle.
    /// EditTargets constructed in this way specify layers in the scene's local
    /// LayerStack.  This lets clients pass layers directly in this common case
    /// without explicitly having to construct a \a UsdEditTarget instance.
    /// To automatically supply the appropriate layer offset for the given
    /// layer, see UsdStage::GetEditTargetForLayer().
    USD_API
    UsdEditTarget(const SdfLayerHandle &layer,
                  SdfLayerOffset offset = SdfLayerOffset());

    /// Convenience implicit conversion from SdfLayerRefPtr.  See above
    /// constructor for more information.
    USD_API
    UsdEditTarget(const SdfLayerRefPtr &layer,
                  SdfLayerOffset offset = SdfLayerOffset());

    /// Construct an EditTarget with \a layer and \a node.  The mapping
    /// will be used to map paths from the scene into the \a layer's namespace
    /// given the \a PcpNodeRef \a node's mapping.
    USD_API
    UsdEditTarget(const SdfLayerHandle &layer, const PcpNodeRef &node);

    /// Convenience constructor taking SdfLayerRefPtr.  See above
    /// constructor for more information.
    USD_API
    UsdEditTarget(const SdfLayerRefPtr &layer, const PcpNodeRef &node);

    /// Convenience constructor for editing a direct variant in a local
    /// LayerStack.  The \p varSelPath must be a prim variant selection path
    /// (see SdfPath::IsPrimVariantSelectionPath()).
    USD_API
    static UsdEditTarget
    ForLocalDirectVariant(const SdfLayerHandle &layer,
                          const SdfPath &varSelPath);

    /// Equality comparison.
    USD_API
    bool operator==(const UsdEditTarget &other) const;

    /// Inequality comparison.
    bool operator!=(const UsdEditTarget &other) const {
        return !(*this == other);
    }

    /// Return true if this EditTarget is null.  Null EditTargets map
    /// paths unchanged, and have no layer or LayerStack identifier.
    bool IsNull() const { return *this == UsdEditTarget(); }

    /// Return true if this EditTarget is valid, false otherwise.  Edit
    /// targets are considered valid when they have a layer.
    bool IsValid() const { return _layer; }

    /// Return the layer this EditTarget contains.
    const SdfLayerHandle &GetLayer() const { return _layer; }

    /// Map the provided \a scenePath into a SdfSpec path for the
    /// EditTarget's layer, according to the EditTarget's mapping.  Null edit
    /// targets and EditTargets for which \a IsLocalLayer are true return
    /// scenePath unchanged.
    USD_API
    SdfPath MapToSpecPath(const SdfPath &scenePath) const;

    /// Convenience function for getting the PrimSpec in the edit
    /// target's layer for \a scenePath.  This is equivalent to
    /// target.GetLayer()->GetPrimAtPath(target.MapToSpecPath(scenePath)) if
    /// target has a valid layer.  If this target IsNull or there is no valid
    /// mapping from \a scenePath to a SdfPrimSpec path in the layer, return
    /// null.
    USD_API
    SdfPrimSpecHandle
    GetPrimSpecForScenePath(const SdfPath &scenePath) const;

    USD_API
    SdfPropertySpecHandle
    GetPropertySpecForScenePath(const SdfPath &scenePath) const;

    USD_API
    SdfSpecHandle
    GetSpecForScenePath(const SdfPath &scenePath) const;

    /// Returns the PcpMapFunction representing the map from source
    /// specs (including any variant selections) to the stage.
    const PcpMapFunction &
    GetMapFunction() const { return _mapping; }

    /// Return a new EditTarget composed over \a weaker.  This is
    /// typically used to make an EditTarget "explicit".  For example, an edit
    /// target with a layer but with no mapping and no LayerStack identifier
    /// indicates a layer in the local LayerStack of a composed scene.
    /// However, an EditTarget with the same layer but an explicit identity
    /// mapping and the LayerStack identifier of the composed scene may be
    /// desired.  This can be obtained by composing a partial (e.g. layer only)
    /// EditTarget over an explicit EditTarget with layer, mapping and layer
    /// stack identifier.
    USD_API
    UsdEditTarget ComposeOver(const UsdEditTarget &weaker) const;

private:

    UsdEditTarget(const SdfLayerHandle &layer,
                  const PcpMapFunction &mapping);

    SdfLayerHandle _layer;
    PcpMapFunction _mapping;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_USD_EDIT_TARGET_H
