#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ndr/node.h"
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

#ifndef FORGE_USD_NDR_NODE_H
#define FORGE_USD_NDR_NODE_H

/// \file ndr/node.h

#include "forge/forge.h"
#include "forge/usd/ndr/api.h"
#include "forge/base/tf/token.h"
#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/nodeDiscoveryResult.h"
#include "forge/usd/ndr/property.h"

FORGE_NAMESPACE_BEGIN

/// \class NdrNode
///
/// Represents an abstract node. Describes information like the name of the
/// node, what its inputs and outputs are, and any associated metadata.
///
/// In almost all cases, this class will not be used directly. More specialized
/// nodes can be created that derive from `NdrNode`; those specialized nodes can
/// add their own domain-specific data and methods.
///
class NdrNode
{
public:
    /// Constructor.
    NDR_API
    NdrNode(const NdrIdentifier& identifier,
            const NdrVersion& version,
            const std::string& name,
            const TfToken& family,
            const TfToken& context,
            const TfToken& sourceType,
            const std::string& definitionURI,
            const std::string& implementationURI,
            NdrPropertyUniquePtrVec&& properties,
            const NdrTokenMap& metadata = NdrTokenMap(),
            const std::string &sourceCode = std::string());

    /// Destructor.
    NDR_API
    virtual ~NdrNode();

    /// \name The Basics
    /// @{

    /// Return the identifier of the node.
    const NdrIdentifier& GetIdentifier() const { return _identifier; }

    /// Return the version of the node
    NdrVersion GetVersion() const { return _version; }

    /// Gets the name of the node.
    const std::string& GetName() const { return _name; }

    /// Gets the name of the family that the node belongs to. An empty token
    /// will be returned if the node does not belong to a family.
    const TfToken& GetFamily() const { return _family; }

    /// Gets the context of the node.
    ///
    /// The context is the context that the node declares itself as having (or,
    /// if a particular node does not declare a context, it will be assigned a
    /// default context by the parser).
    ///
    /// As a concrete example from the `Sdr` library, a shader with a specific
    /// source type may perform different duties vs. another shader with the
    /// same source type. For example, one shader with a source type of
    /// `SdrArgsParser::SourceType` may declare itself as having a context of
    /// 'pattern', while another shader of the same source type may say it is
    /// used for lighting, and thus has a context of 'light'.
    const TfToken& GetContext() const { return _context; }

    /// Gets the type of source that this node originated from.
    ///
    /// Note that this is distinct from `GetContext()`, which is the type that
    /// the node declares itself as having.
    ///
    /// As a concrete example from the `Sdr` library, several shader parsers
    /// exist and operate on different types of shaders. In this scenario, each
    /// distinct type of shader (OSL, Args, etc) is considered a different
    /// _source_, even though they are all shaders. In addition, the shaders
    /// under each source type may declare themselves as having a specific
    /// context (shaders can serve different roles). See `GetContext()` for
    /// more information on this.
    const TfToken& GetSourceType() const { return _sourceType; }

    /// Gets the URI to the resource that provided this node's
    /// definition. Could be a path to a file, or some other resource
    /// identifier. This URI should be fully resolved.
    ///
    /// \sa NdrNode::GetResolvedImplementationURI()
    const std::string& GetResolvedDefinitionURI() const { return _definitionURI; }

    /// Gets the URI to the resource that provides this node's
    /// implementation. Could be a path to a file, or some other resource
    /// identifier. This URI should be fully resolved.
    ///
    /// \sa NdrNode::GetResolvedDefinitionURI()
    const std::string& GetResolvedImplementationURI() const { return _implementationURI; }

    /// Returns  the source code for this node. This will be empty for most
    /// nodes. It will be non-empty only for the nodes that are constructed
    /// using \ref NdrRegistry::GetNodeFromSourceCode(), in which case, the
    /// source code has not been parsed (or even compiled) yet.
    ///
    /// An unparsed node with non-empty source-code but no properties is
    /// considered to be invalid. Once the node is parsed and the relevant
    /// properties and metadata are extracted from the source code, the node
    /// becomes valid.
    ///
    /// \sa NdrNode::IsValid
    const std::string &GetSourceCode() const { return _sourceCode; }

    /// Whether or not this node is valid. A node that is valid indicates that
    /// the parser plugin was able to successfully parse the contents of this
    /// node.
    ///
    /// Note that if a node is not valid, some data like its name, URI, source
    /// code etc. could still be available (data that was obtained during the
    /// discovery process). However, other data that must be gathered from the
    /// parsing process will NOT be available (eg, inputs and outputs).
    NDR_API
    virtual bool IsValid() const { return _isValid; }

    /// Gets a string with basic information about this node. Helpful for
    /// things like adding this node to a log.
    NDR_API
    virtual std::string GetInfoString() const;

    /// @}


    /// \name Inputs and Outputs
    /// An input or output is also generically referred to as a "property".
    /// @{

    /// Get an ordered list of all the input names on this node.
    NDR_API
    const NdrTokenVec& GetInputNames() const;

    /// Get an ordered list of all the output names on this node.
    NDR_API
    const NdrTokenVec& GetOutputNames() const;

    /// Get an input property by name. `nullptr` is returned if an input with
    /// the given name does not exist.
    NDR_API
    NdrPropertyConstPtr GetInput(const TfToken& inputName) const;

    /// Get an output property by name. `nullptr` is returned if an output with
    /// the given name does not exist.
    NDR_API
    NdrPropertyConstPtr GetOutput(const TfToken& outputName) const;

    /// @}


    /// \name Metadata
    /// The metadata returned here is a direct result of what the parser plugin
    /// is able to determine about the node. See the documentation for a
    /// specific parser plugin to get help on what the parser is looking for to
    /// populate these values.
    /// @{

    /// All metadata that came from the parse process. Specialized nodes may
    /// isolate values in the metadata (with possible manipulations and/or
    /// additional parsing) and expose those values in their API.
    NDR_API
    const NdrTokenMap& GetMetadata() const;

    /// @}

protected:
    NdrNode& operator=(const NdrNode&) = delete;

    bool _isValid;
    NdrIdentifier _identifier;
    NdrVersion _version;
    std::string _name;
    TfToken _family;
    TfToken _context;
    TfToken _sourceType;
    std::string _definitionURI;
    std::string _implementationURI;
    NdrPropertyUniquePtrVec _properties;
    NdrTokenMap _metadata;
    std::string _sourceCode;

    NdrPropertyPtrMap _inputs;
    NdrTokenVec _inputNames;
    NdrPropertyPtrMap _outputs;
    NdrTokenVec _outputNames;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_NDR_NODE_H
