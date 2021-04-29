#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/layerTree.h"
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
#ifndef FORGE_USD_SDF_LAYER_TREE_H
#define FORGE_USD_SDF_LAYER_TREE_H

/// \file sdf/layerTree.h

#include "forge/forge.h"
#include "forge/usd/sdf/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/sdf/layerOffset.h"

#include <boost/noncopyable.hpp>
#include <vector>

FORGE_NAMESPACE_BEGIN

// Layer tree forward declarations.
class SdfLayerTree;
typedef TfRefPtr<SdfLayerTree> SdfLayerTreeHandle;
typedef std::vector<SdfLayerTreeHandle> SdfLayerTreeHandleVector;

SDF_DECLARE_HANDLES(SdfLayer);

/// \class SdfLayerTree
///
/// A SdfLayerTree is an immutable tree structure representing a sublayer
/// stack and its recursive structure.
///
/// Layers can have sublayers, which can in turn have sublayers of their
/// own.  Clients that want to represent that hierarchical structure in
/// memory can build a SdfLayerTree for that purpose.
///
/// We use TfRefPtr<SdfLayerTree> as handles to LayerTrees, as a simple way
/// to pass them around as immutable trees without worrying about lifetime.
///
class SdfLayerTree : public TfRefBase, public TfWeakBase, boost::noncopyable {
public:
    /// Create a new layer tree node.
    SDF_API
    static SdfLayerTreeHandle
    New( const SdfLayerHandle & layer,
         const SdfLayerTreeHandleVector & childTrees,
         const SdfLayerOffset & cumulativeOffset = SdfLayerOffset() );

    /// Returns the layer handle this tree node represents.
    SDF_API const SdfLayerHandle & GetLayer() const;

    /// Returns the cumulative layer offset from the root of the tree.
    SDF_API const SdfLayerOffset & GetOffset() const;

    /// Returns the children of this tree node.
    SDF_API const SdfLayerTreeHandleVector & GetChildTrees() const;

private:
    SdfLayerTree( const SdfLayerHandle & layer,
                  const SdfLayerTreeHandleVector & childTrees,
                  const SdfLayerOffset & cumulativeOffset );

private:
    const SdfLayerHandle _layer;
    const SdfLayerOffset _offset;
    const SdfLayerTreeHandleVector _childTrees;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_LAYER_TREE_H
