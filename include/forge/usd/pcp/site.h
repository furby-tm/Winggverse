#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/site.h"
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
#ifndef FORGE_USD_PCP_SITE_H
#define FORGE_USD_PCP_SITE_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/pcp/layerStackIdentifier.h"
#include "forge/usd/sdf/path.h"
#include "forge/usd/sdf/types.h"
#include "forge/base/tf/declarePtrs.h"

#include <boost/operators.hpp>
#include <iosfwd>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(PcpLayerStack);
class PcpLayerStackSite;

/// \class PcpSite
///
/// A site specifies a path in a layer stack of scene description.
///
class PcpSite : boost::totally_ordered<PcpSite>
{
public:
    PcpLayerStackIdentifier layerStackIdentifier;
    SdfPath path;

    PCP_API
    PcpSite();

    PCP_API
    PcpSite( const PcpLayerStackIdentifier &, const SdfPath & path );
    PCP_API
    PcpSite( const PcpLayerStackPtr &, const SdfPath & path );
    PCP_API
    PcpSite( const SdfLayerHandle &, const SdfPath & path );
    PCP_API
    explicit PcpSite( const PcpLayerStackSite & );

    PCP_API
    bool operator==(const PcpSite &rhs) const;

    PCP_API
    bool operator<(const PcpSite &rhs) const;

    struct Hash {
        PCP_API
        size_t operator()(const PcpSite &) const;
    };
};

/// \class PcpSiteStr
///
/// A "string-based" version of PcpSite.  This stores layer identifiers as
/// strings rather than SdfLayerHandles, making it stable wrt layer lifetimes.
///
class PcpSiteStr : boost::totally_ordered<PcpSiteStr>
{
public:
    PcpLayerStackIdentifierStr layerStackIdentifierStr;
    SdfPath path;

    PCP_API
    PcpSiteStr();

    PCP_API
    PcpSiteStr( const PcpLayerStackIdentifierStr &, const SdfPath & path );
    PCP_API
    PcpSiteStr( const PcpLayerStackIdentifier &, const SdfPath & path );
    PCP_API
    PcpSiteStr( const SdfLayerHandle &, const SdfPath & path );
    PCP_API
    PcpSiteStr(PcpLayerStackSite const &);
    PCP_API
    PcpSiteStr(PcpSite const &);

    PCP_API
    bool operator==(const PcpSiteStr &rhs) const;

    PCP_API
    bool operator<(const PcpSiteStr &rhs) const;

    struct Hash {
        PCP_API
        size_t operator()(const PcpSiteStr &) const;
    };
};

/// \class PcpLayerStackSite
///
/// A site specifies a path in a layer stack of scene description.
///
class PcpLayerStackSite : boost::totally_ordered<PcpLayerStackSite>
{
public:
    PcpLayerStackRefPtr layerStack;
    SdfPath path;

    PCP_API
    PcpLayerStackSite();

    PCP_API
    PcpLayerStackSite( const PcpLayerStackRefPtr &, const SdfPath & path );

    PCP_API
    bool operator==(const PcpLayerStackSite &rhs) const;

    PCP_API
    bool operator<(const PcpLayerStackSite &rhs) const;

    struct Hash {
        PCP_API
        size_t operator()(const PcpLayerStackSite &) const;
    };
};

PCP_API
std::ostream& operator<<(std::ostream&, const PcpSite&);
PCP_API
std::ostream& operator<<(std::ostream&, const PcpSiteStr&);
PCP_API
std::ostream& operator<<(std::ostream&, const PcpLayerStackSite&);

static inline
size_t
hash_value(const PcpSite& site)
{
    return PcpSite::Hash()(site);
}

static inline
size_t
hash_value(const PcpSiteStr& site)
{
    return PcpSiteStr::Hash()(site);
}

static inline
size_t
hash_value(const PcpLayerStackSite& site)
{
    return PcpLayerStackSite::Hash()(site);
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_SITE_H
