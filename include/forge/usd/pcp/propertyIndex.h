#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/propertyIndex.h"
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
#ifndef FORGE_USD_PCP_PROPERTY_INDEX_H
#define FORGE_USD_PCP_PROPERTY_INDEX_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/errors.h"
#include "forge/usd/pcp/iterator.h"
#include "forge/usd/pcp/node.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/propertySpec.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

// Forward declarations:
class PcpCache;

/// \class Pcp_PropertyInfo
///
/// Private helper structure containing information about a property in the
/// property stack.
///
struct Pcp_PropertyInfo
{
    Pcp_PropertyInfo() { }
    Pcp_PropertyInfo(const SdfPropertySpecHandle& prop, const PcpNodeRef& node)
        : propertySpec(prop), originatingNode(node) { }

    SdfPropertySpecHandle propertySpec;
    PcpNodeRef originatingNode;
};

/// \class PcpPropertyIndex
///
/// PcpPropertyIndex is an index of all sites in scene description that
/// contribute opinions to a specific property, under composition
/// semantics.
///
class PcpPropertyIndex
{
public:
    /// Construct an empty property index.
    PCP_API
    PcpPropertyIndex();

    /// Copy-construct a property index.
    PCP_API
    PcpPropertyIndex(const PcpPropertyIndex &rhs);

    /// Swap the contents of this property index with \p index.
    PCP_API
    void Swap(PcpPropertyIndex& index);

    /// Returns true if this property index contains no opinions, false
    /// otherwise.
    PCP_API
    bool IsEmpty() const;

    /// Returns range of iterators that encompasses properties in this
    /// index's property stack.
    ///
    /// By default, this returns a range encompassing all properties in the
    /// index. If \p localOnly is specified, the range will only include
    /// properties from local nodes in its owning prim's graph.
    PCP_API
    PcpPropertyRange GetPropertyRange(bool localOnly = false) const;

    /// Return the list of errors local to this property.
    PcpErrorVector GetLocalErrors() const {
        return _localErrors ? *_localErrors.get() : PcpErrorVector();
    }

    /// Returns the number of local properties in this prim index.
    PCP_API
    size_t GetNumLocalSpecs() const;

private:
    friend class PcpPropertyIterator;
    friend class Pcp_PropertyIndexer;

    // The property stack is a list of Pcp_PropertyInfo objects in
    // strong-to-weak order.
    std::vector<Pcp_PropertyInfo> _propertyStack;

    /// List of errors local to this property, encountered during computation.
    /// NULL if no errors were found (the expected common case).
    std::unique_ptr<PcpErrorVector> _localErrors;
};

/// Builds a property index for the property at \p path,
/// internally computing and caching an owning prim index as necessary.
/// \p allErrors will contain any errors encountered.
PCP_API
void
PcpBuildPropertyIndex( const SdfPath& propertyPath,
                       PcpCache *cache,
                       PcpPropertyIndex *propertyIndex,
                       PcpErrorVector *allErrors );

/// Builds a prim property index for the property at \p propertyPath.
/// \p allErrors will contain any errors encountered.
PCP_API
void
PcpBuildPrimPropertyIndex( const SdfPath& propertyPath,
                           const PcpCache& cache,
                           const PcpPrimIndex& owningPrimIndex,
                           PcpPropertyIndex *propertyIndex,
                           PcpErrorVector *allErrors );

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_PROPERTY_INDEX_H
