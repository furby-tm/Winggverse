#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/pathTranslation.h"
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
#ifndef FORGE_USD_PCP_PATH_TRANSLATION_H
#define FORGE_USD_PCP_PATH_TRANSLATION_H

/// \file pcp/pathTranslation.h
/// Path translation.

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"

FORGE_NAMESPACE_BEGIN

class PcpMapFunction;
class PcpNodeRef;
class SdfPath;

/// Translates \p pathInNodeNamespace from the namespace of the prim index node
/// \p sourceNode to the namespace of the prim index's root node. This applies
/// all necessary namespace translations.
///
/// If the path is successfully translated and \p pathWasTranslated is supplied,
/// it will be set to \c true. In some cases, paths may fail to translate
/// because they fall outside the set of paths that are allowed by nodes in the
/// prim index. For instance, for a referenced model, paths referring to
/// locations outside that model will not be translated. In these cases, this
/// function will return an empty SdfPath and \p pathWasTranslated will be set
/// to \c false.
///
/// In Sd/Csd terminology, this is forward path translation from the
/// namespace of the prim spec represented by \p sourceNode to the composed
/// scene namespace.
PCP_API
SdfPath
PcpTranslatePathFromNodeToRoot(
    const PcpNodeRef& sourceNode,
    const SdfPath& pathInNodeNamespace,
    bool* pathWasTranslated = 0);

/// Translates \p pathInRootNamespace from the namespace of the root of the
/// prim index that \p destNode belongs to to the namespace of \p destNode
/// itself. This applies all necessary namespace translations.
///
/// If the path is successfully translated and \p pathWasTranslated is supplied,
/// it will be set to \c true. In some cases, paths may fail to translate
/// because they fall outside the set of paths that are allowed by nodes in the
/// prim index. For instance, for a referenced model, paths referring to
/// locations outside that model will not be translated. In these cases, this
/// function will return an empty SdfPath and \p pathWasTranslated will be set
/// to \c false.
///
/// In Sd/Csd terminology, this is reverse path translation from the
/// namespace of the composed scene to the namespace of the prim spec
/// represented by \p destNode.
PCP_API
SdfPath
PcpTranslatePathFromRootToNode(
    const PcpNodeRef& destNode,
    const SdfPath& pathInRootNamespace,
    bool* pathWasTranslated = 0);

/// Same as \a PcpTranslatePathFromRootToNode, but explicitly for use when
/// translating paths intended for use as attribute connections or relationship
/// targets. The primary difference is that variant selections will never
/// be included in the translated path. This is functionally equivalent to
/// calling StripAllVariantSelections() on the result of the referenced
/// function, but is more efficient.
PCP_API
SdfPath
PcpTranslateTargetPathFromRootToNode(
    const PcpNodeRef& destNode,
    const SdfPath& pathInRootNamespace,
    bool* pathWasTranslated = 0);

/// Convenience function like \a PcpTranslatePathFromRootToNode, but
/// takes a function rather than a node.
PCP_API
SdfPath
PcpTranslatePathFromRootToNodeUsingFunction(
    const PcpMapFunction &mapToRoot,
    const SdfPath &pathInRootNamespace,
    bool *pathWasTranslated = 0);

/// Convenience function like \a PcpTranslatePathFromNodeToRoot, but
/// takes a function rather than a node.
PCP_API
SdfPath
PcpTranslatePathFromNodeToRootUsingFunction(
    const PcpMapFunction &mapToRoot,
    const SdfPath &pathInNodeNamespace,
    bool *pathWasTranslated = 0);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_PATH_TRANSLATION_H
