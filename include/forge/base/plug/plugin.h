#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/plugin.h"
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
#ifndef FORGE_BASE_PLUG_PLUGIN_H
#define FORGE_BASE_PLUG_PLUGIN_H

#include "forge/forge.h"
#include "forge/base/plug/api.h"

#include "forge/base/js/types.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/refPtr.h"
#include "forge/base/tf/weakPtr.h"

#include <atomic>
#include <string>
#include <utility>
#include <vector>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_AND_REF_PTRS(PlugPlugin);

class Plug_RegistrationMetadata;
class TfType;

/// \class PlugPlugin
///
/// Defines an interface to registered plugins.
///
/// Plugins are registered using the interfaces in \c PlugRegistry.
///
/// For each registered plugin, there is an instance of
/// \c PlugPlugin which can be used to load and unload
/// the plugin and to retrieve information about the
/// classes implemented by the plugin.
///
class PlugPlugin : public TfRefBase, public TfWeakBase {
public:
    PLUG_API virtual ~PlugPlugin();

    /// Loads the plugin.
    /// This is a noop if the plugin is already loaded.
    PLUG_API bool Load();

    /// Returns \c true if the plugin is currently loaded.  Resource
    /// plugins always report as loaded.
    PLUG_API bool IsLoaded() const;

#ifdef FORGE_PYTHON_SUPPORT_ENABLED
    /// Returns \c true if the plugin is a python module.
    PLUG_API bool IsPythonModule() const;
#endif // FORGE_PYTHON_SUPPORT_ENABLED

    /// Returns \c true if the plugin is resource-only.
    PLUG_API bool IsResource() const;

    /// Returns the dictionary containing meta-data for the plugin.
    PLUG_API JsObject GetMetadata();

    /// Returns the metadata sub-dictionary for a particular type.
    PLUG_API JsObject GetMetadataForType(const TfType &type);

    /// Returns the dictionary containing the dependencies for the plugin.
    PLUG_API JsObject GetDependencies();

    /// Returns true if \p type is declared by this plugin.
    /// If \p includeSubclasses is specified, also returns true if any
    /// subclasses of \p type have been declared.
    PLUG_API bool DeclaresType(const TfType& type, bool includeSubclasses = false) const;

    /// Returns the plugin's name.
    std::string const &GetName() const {
        return _name;
    }

    /// Returns the plugin's filesystem path.
    std::string const &GetPath() const {
        return _path;
    }

    /// Returns the plugin's resources filesystem path.
    std::string const &GetResourcePath() const {
        return _resourcePath;
    }

    /// Build a plugin resource path by returning a given absolute path or
    /// combining the plugin's resource path with a given relative path.
    PLUG_API std::string MakeResourcePath(const std::string& path) const;

    /// Find a plugin resource by absolute or relative path optionally
    /// verifying that file exists.  If verification fails an empty path
    /// is returned.  Relative paths are relative to the plugin's resource
    /// path.
    PLUG_API std::string FindPluginResource(const std::string& path, bool verify = true) const;

private:
    enum _Type {
        LibraryType,
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
        PythonType,
#endif // FORGE_PYTHON_SUPPORT_ENABLED
        ResourceType
    };

    // Private ctor, plugins are constructed only by PlugRegistry.
    PLUG_LOCAL
    PlugPlugin(const std::string & path,
               const std::string & name,
               const std::string & resourcePath,
               const JsObject & plugInfo,
               _Type type);

    PLUG_LOCAL
    static PlugPluginPtr _GetPluginForType(const TfType & type);

    PLUG_LOCAL
    static void _RegisterAllPlugins();
    PLUG_LOCAL
    static PlugPluginPtr _GetPluginWithName(const std::string& name);
    PLUG_LOCAL
    static PlugPluginPtrVector _GetAllPlugins();

    template <class PluginMap>
    PLUG_LOCAL
    static std::pair<PlugPluginPtr, bool>
    _NewPlugin(const Plug_RegistrationMetadata &metadata,
               _Type pluginType,
               const std::string& pluginCreationPath,
               PluginMap *allPluginsByNamePtr);

    PLUG_LOCAL
    static std::pair<PlugPluginPtr, bool>
    _NewDynamicLibraryPlugin(const Plug_RegistrationMetadata& metadata);

#ifdef FORGE_PYTHON_SUPPORT_ENABLED
    PLUG_LOCAL
    static std::pair<PlugPluginPtr, bool>
    _NewPythonModulePlugin(const Plug_RegistrationMetadata& metadata);
#endif // FORGE_PYTHON_SUPPORT_ENABLED

    PLUG_LOCAL
    static std::pair<PlugPluginPtr, bool>
    _NewResourcePlugin(const Plug_RegistrationMetadata& metadata);

    PLUG_LOCAL
    bool _Load();

    PLUG_LOCAL
    void _DeclareAliases( TfType t, const JsObject & metadata );
    PLUG_LOCAL
    void _DeclareTypes();
    PLUG_LOCAL
    void _DeclareType(const std::string &name, const JsObject &dict);
    PLUG_LOCAL
    static void _DefineType( TfType t );

    struct _SeenPlugins;
    PLUG_LOCAL
    bool _LoadWithDependents(_SeenPlugins * seenPlugins);

    PLUG_LOCAL
    static void _UpdatePluginMaps( const TfType & baseType );

    PLUG_LOCAL
    static constexpr char const *_GetPluginTypeDisplayName(_Type type);

private:
    std::string _name;
    std::string _path;
    std::string _resourcePath;
    JsObject _dict;
    void *_handle;      // the handle returned by ArchLibraryOpen() is a void*
    std::atomic<bool> _isLoaded;
    _Type _type;

    friend class PlugRegistry;
};

/// Find a plugin's resource by absolute or relative path optionally
/// verifying that file exists.  If \c plugin is \c NULL or verification
/// fails an empty path is returned.  Relative paths are relative to the
/// plugin's resource path.
PLUG_API
std::string
PlugFindPluginResource(const PlugPluginPtr& plugin,
                       const std::string& path, bool verify = true);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_PLUGIN_H
