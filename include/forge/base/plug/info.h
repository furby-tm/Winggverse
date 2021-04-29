#line 1 "C:/Users/tyler/dev/WINGG/forge/base/plug/info.h"
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
#ifndef FORGE_BASE_PLUG_INFO_H
#define FORGE_BASE_PLUG_INFO_H

#include "forge/forge.h"
#include "forge/base/arch/attributes.h"
#include "forge/base/js/value.h"

#include <functional>
#include <memory>
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

class JsValue;

/// Data describing the plugin itself.
class Plug_RegistrationMetadata {
public:
    enum Type {
        UnknownType,
        LibraryType,
#ifdef FORGE_PYTHON_SUPPORT_ENABLED
        PythonType,
#endif // FORGE_PYTHON_SUPPORT_ENABLED
        ResourceType
    };

    Plug_RegistrationMetadata() : type(UnknownType) { }
    Plug_RegistrationMetadata(const JsValue&,
                              const std::string& valuePathname,
                              const std::string& locationForErrorReporting);

    Type type;
    std::string pluginName;
    std::string pluginPath;
    JsObject plugInfo;
    std::string libraryPath;
    std::string resourcePath;
};

/// A task arena for reading plug info.
class Plug_TaskArena {
public:
    class Synchronous { };  // For single-threaded debugging.
    Plug_TaskArena();
    Plug_TaskArena(Synchronous);
    ~Plug_TaskArena();

    /// Schedule \p fn to run.
    template <class Fn>
    void Run(Fn const &fn);

    /// Wait for all scheduled tasks to complete.
    void Wait();

private:
    class _Impl;
    std::unique_ptr<_Impl> _impl;
};

/// Reads several plugInfo files, recursively loading any included files.
/// \p addPlugin is invoked each time a plugin is found.  The order in
/// which plugins is discovered is undefined.  \p addPlugin is invoked
/// by calling \c Run() on \p taskArena.
///
/// \p addVisitedPath is called each time a plug info file is found;  if it
/// returns \c true then the file is processed, otherwise it is ignored.
/// Clients should return \c true or \c false the first time a given path
/// is passed and \c false all subsequent times.
void
Plug_ReadPlugInfo(
    const std::vector<std::string>& pathnames,
    bool pathsAreOrdered,
    const std::function<bool (const std::string&)>& addVisitedPath,
    const std::function<void (const Plug_RegistrationMetadata&)>& addPlugin,
    Plug_TaskArena* taskArena);

/// Sets the paths to the bootstrap plugInfo JSON files, also any diagnostic
/// messages that should be reported when plugins are registered (if any).
/// The priority order of elements of the path is honored if pathsAreOrdered.
/// Defined in registry.cpp.
void Plug_SetPaths(const std::vector<std::string>&,
                   const std::vector<std::string>&,
                   bool pathsAreOrdered);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_PLUG_INFO_H
