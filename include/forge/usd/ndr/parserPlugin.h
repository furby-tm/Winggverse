#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ndr/parserPlugin.h"
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

#ifndef FORGE_USD_NDR_PARSER_PLUGIN_H
#define FORGE_USD_NDR_PARSER_PLUGIN_H

/// \file ndr/parserPlugin.h

#include "forge/forge.h"
#include "forge/usd/ndr/api.h"
#include "forge/base/tf/type.h"
#include "forge/base/tf/weakBase.h"
#include "forge/base/tf/weakPtr.h"
#include "forge/usd/ndr/declare.h"

FORGE_NAMESPACE_BEGIN

// Forward declarations
struct NdrNodeDiscoveryResult;

/// Register a parser plugin with the plugin system.
#define NDR_REGISTER_PARSER_PLUGIN(ParserPluginClass)                   \
TF_REGISTRY_FUNCTION(TfType)                                            \
{                                                                       \
    TfType::Define<ParserPluginClass, TfType::Bases<NdrParserPlugin>>() \
        .SetFactory<NdrParserPluginFactory<ParserPluginClass>>();       \
}

/// \class NdrParserPlugin
///
/// Interface for parser plugins.
///
/// Parser plugins take a `NdrNodeDiscoveryResult` from the discovery process
/// and creates a full `NdrNode` instance (or, in the case of a real-world
/// scenario, a specialized node that derives from `NdrNode`). The parser that
/// is selected to run is ultimately decided by the registry, and depends on the
/// `NdrNodeDiscoveryResult`'s `discoveryType` member. A parser plugin's
/// `GetDiscoveryTypes()` method is how this link is made. If a discovery result
/// has a `discoveryType` of 'foo', and `SomeParserPlugin` has 'foo' included
/// in its `GetDiscoveryTypes()` return value, `SomeParserPlugin` will parse
/// that discovery result.
///
/// Another kind of 'type' within the parser plugin is the 'source type'. The
/// discovery type simply acts as a way to link a discovery result to a parser
/// plugin. On the other hand, a 'source type' acts as an umbrella type that
/// groups all of the discovery types together. For example, if a plugin handled
/// discovery types 'foo', 'bar', and 'baz' (which are all related because they
/// are all handled by the same parser), they may all be grouped under one
/// unifying source type. This type is available on the node via
/// `NdrNode::GetSourceType()`.
///
/// \section create How to Create a Parser Plugin
/// There are three steps to creating a parser plugin:
/// <ul>
///     <li>
///         Implement the parser plugin interface. An example parser plugin is
///         available in the plugin folder under `sdrOsl`. The `Parse()` method
///         should return the specialized node that derives from `NdrNode` (and
///         this node should also be constructed with its specialized
///         properties). Examples of a specialized node and property class are
///         `SdrShaderNode` and `SdrShaderProperty`.
///     </li>
///     <li>
///         Register your new plugin with the registry. The registration macro
///         must be called in your plugin's implementation file:
///         \code{.cpp}
///         NDR_REGISTER_PARSER_PLUGIN(<YOUR_PARSER_PLUGIN_CLASS_NAME>)
///         \endcode
///         This macro is available in parserPlugin.h.
///     </li>
///     <li>
///         In the same folder as your plugin, create a `plugInfo.json` file.
///         This file must be formatted like so, substituting
///         `YOUR_LIBRARY_NAME`, `YOUR_CLASS_NAME`, and `YOUR_DISPLAY_NAME`:
///         \code{.json}
///         {
///             "Plugins": [{
///                 "Type": "library",
///                 "Name": "YOUR_LIBRARY_NAME",
///                 "Root": "@PLUG_INFO_ROOT@",
///                 "LibraryPath": "@PLUG_INFO_LIBRARY_PATH@",
///                 "ResourcePath": "@PLUG_INFO_RESOURCE_PATH@",
///                 "Info": {
///                     "Types": {
///                         "YOUR_CLASS_NAME" : {
///                             "bases": ["NdrParserPlugin"],
///                             "displayName": "YOUR_DISPLAY_NAME"
///                         }
///                     }
///                 }
///             }]
///         }
///         \endcode
///
///         The SDR ships with one parser plugin, the `SdrOslParserPlugin`. Take
///         a look at its plugInfo.json file for example values for
///         `YOUR_LIBRARY_NAME`, `YOUR_CLASS_NAME`, and `YOUR_DISPLAY_NAME`. If
///         multiple parser plugins exist in the same folder, you can continue
///         adding additional plugins under the `Types` key in the JSON. More
///         detailed information about the plugInfo.json format can be found in
///         the documentation for the `plug` library (in forge/base).
///     </li>
/// </ul>
class NdrParserPlugin : public TfWeakBase
{
public:
    NDR_API
    NdrParserPlugin();
    NDR_API
    virtual ~NdrParserPlugin();

    /// Takes the specified `NdrNodeDiscoveryResult` instance, which was a
    /// result of the discovery process, and generates a new `NdrNode`.
    /// The node's name, source type, and family must match.
    NDR_API
    virtual NdrNodeUniquePtr Parse(
        const NdrNodeDiscoveryResult& discoveryResult) = 0;

    /// Returns the types of nodes that this plugin can parse.
    ///
    /// "Type" here is the discovery type (in the case of files, this will
    /// probably be the file extension, but in other systems will be data that
    /// can be determined during discovery). This type should only be used to
    /// match up a `NdrNodeDiscoveryResult` to its parser plugin; this value is
    /// not exposed in the node's API.
    NDR_API
    virtual const NdrTokenVec& GetDiscoveryTypes() const = 0;

    /// Returns the source type that this parser operates on.
    ///
    /// A source type is the most general type for a node. The parser plugin is
    /// responsible for parsing all discovery results that have the types
    /// declared under `GetDiscoveryTypes()`, and those types are collectively
    /// identified as one "source type".
    NDR_API
    virtual const TfToken& GetSourceType() const = 0;

    /// Gets an invalid node based on the discovery result provided. An invalid
    /// node is a node that has no properties, but may have basic data found
    /// during discovery.
    NDR_API
    static NdrNodeUniquePtr GetInvalidNode(const NdrNodeDiscoveryResult& dr);
};


/// \cond
/// Factory classes should be hidden from the documentation.

class NdrParserPluginFactoryBase : public TfType::FactoryBase
{
public:
    virtual NdrParserPlugin* New() const = 0;
};

template <class T>
class NdrParserPluginFactory : public NdrParserPluginFactoryBase
{
public:
    virtual NdrParserPlugin* New() const
    {
        return new T;
    }
};

/// \endcond

FORGE_NAMESPACE_END

#endif // FORGE_USD_NDR_PARSER_PLUGIN_H
