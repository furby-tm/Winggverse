#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/layerStackIdentifier.h"
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
#ifndef FORGE_USD_PCP_LAYER_STACK_IDENTIFIER_H
#define FORGE_USD_PCP_LAYER_STACK_IDENTIFIER_H

/// \file pcp/layerStackIdentifier.h

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/usd/ar/resolverContext.h"

#include <boost/operators.hpp>

#include <iosfwd>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// \class PcpLayerStackIdentifier
///
/// Arguments used to identify a layer stack.
///
/// Objects of this type are immutable.
///
class PcpLayerStackIdentifier :
    boost::totally_ordered<PcpLayerStackIdentifier> {
public:
    typedef PcpLayerStackIdentifier This;

    /// Construct with all empty pointers.
    PCP_API
    PcpLayerStackIdentifier();

    /// Construct with given pointers.  If all arguments are \c TfNullPtr
    /// then the result is identical to the default constructed object.
    PCP_API
    PcpLayerStackIdentifier(const SdfLayerHandle& rootLayer_,
                            const SdfLayerHandle& sessionLayer_ = TfNullPtr,
                            const ArResolverContext& pathResolverContext_ =
                                ArResolverContext());

    // XXX: Allow assignment because there are clients using this
    //      as a member that themselves want to be assignable.
    PCP_API
    PcpLayerStackIdentifier& operator=(const PcpLayerStackIdentifier&);

    // Validity.
#if !defined(doxygen)
    typedef const size_t This::*UnspecifiedBoolType;
#endif
    PCP_API
    operator UnspecifiedBoolType() const;

    // Comparison.
    PCP_API
    bool operator==(const This &rhs) const;
    PCP_API
    bool operator<(const This &rhs) const;

    // Hashing.
    struct Hash {
        size_t operator()(const This & x) const
        {
            return x.GetHash();
        }
    };
    size_t GetHash() const
    {
        return _hash;
    }

public:
    /// The root layer.
    const SdfLayerHandle rootLayer;

    /// The session layer (optional).
    const SdfLayerHandle sessionLayer;

    /// The path resolver context used for resolving asset paths. (optional)
    const ArResolverContext pathResolverContext;

private:
    size_t _ComputeHash() const;

private:
    const size_t _hash;
};


/// \class PcpLayerStackIdentifierStr
///
/// A "string"-based version of PcpLayerStackIdentifier.  These are used in
/// places where they should be stable wrt layer lifetimes.  This is done by
/// storing layer identifiers as strings rather than SdfLayerHandles.
///
class PcpLayerStackIdentifierStr :
    boost::totally_ordered<PcpLayerStackIdentifierStr> {
public:
    typedef PcpLayerStackIdentifierStr This;

    /// Construct with given identifier strings and context.  If all arguments
    /// are empty strings and default-constructed ArResolverContext, then the
    /// result is identical to the default constructed object.
    PCP_API
    explicit PcpLayerStackIdentifierStr(
        std::string const &rootLayerId = std::string(),
        std::string const &sessionLayerId = std::string(),
        ArResolverContext const &resolverContext = ArResolverContext());

    /// Allow implicit conversion from PcpLayerStackIdentifier
    PCP_API
    PcpLayerStackIdentifierStr(PcpLayerStackIdentifier const &lsid);

    // Validity.
#if !defined(doxygen)
    typedef const size_t This::*UnspecifiedBoolType;
#endif
    PCP_API
    operator UnspecifiedBoolType() const;

    // Comparison.
    PCP_API
    bool operator==(const This &rhs) const;
    PCP_API
    bool operator<(const This &rhs) const;

    // Hashing.
    struct Hash {
        size_t operator()(const This & x) const
        {
            return x.GetHash();
        }
    };
    size_t GetHash() const
    {
        return _hash;
    }

public:
    /// The root layer.
    std::string rootLayerId;

    /// The session layer (optional).
    std::string sessionLayerId;

    /// The path resolver context used for resolving asset paths. (optional)
    ArResolverContext pathResolverContext;

private:
    size_t _ComputeHash() const;

private:
    size_t _hash;
};


inline
size_t
hash_value(const PcpLayerStackIdentifier& x)
{
    return x.GetHash();
}

inline
size_t
hash_value(const PcpLayerStackIdentifierStr& x)
{
    return x.GetHash();
}

PCP_API
std::ostream& operator<<(std::ostream&, const PcpLayerStackIdentifier&);
PCP_API
std::ostream& operator<<(std::ostream&, const PcpLayerStackIdentifierStr&);

/// Manipulator to cause the next PcpLayerStackIdentifier or
/// PcpLayerStackIdentifierStr written to the ostream to write the base name of
/// its layers, rather than the full identifier.
PCP_API
std::ostream& PcpIdentifierFormatBaseName(std::ostream&);

/// Manipulator to cause the next PcpLayerStackIdentifier or
/// PcpLayerStackIdentifierStr written to the ostream to write the real path of
/// its layers, rather than the identifier.
PCP_API
std::ostream& PcpIdentifierFormatRealPath(std::ostream&);

/// Manipulator to cause the next PcpLayerStackIdentifier or
/// PcpLayerStackIdentifierStr written to the ostream to write the identifier of
/// its layers.  This is the default state; this manipulator is only to nullify
/// one of the above manipulators.
PCP_API
std::ostream& PcpIdentifierFormatIdentifier(std::ostream&);

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_LAYER_STACK_IDENTIFIER_H
