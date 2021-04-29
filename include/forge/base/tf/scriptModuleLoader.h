#line 1 "C:/Users/tyler/dev/WINGG/forge/base/tf/scriptModuleLoader.h"
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
#ifndef FORGE_BASE_TF_SCRIPT_MODULE_LOADER_H
#define FORGE_BASE_TF_SCRIPT_MODULE_LOADER_H

#include "forge/forge.h"

#include "forge/base/tf/api.h"
#include "forge/base/tf/hash.h"
#include "forge/base/tf/singleton.h"
#include "forge/base/tf/token.h"
#include "forge/base/tf/weakBase.h"

// XXX: This include is a hack to avoid build errors due to
// incompatible macro definitions in pyport.h on macOS.
#include <locale>
#include <boost/python/dict.hpp>

#include <deque>
#include "forge/base/tf/hashmap.h"
#include "forge/base/tf/hashset.h"
#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN

/// \class TfScriptModuleLoader
///
/// Provides low-level facilities for shared libraries with script bindings to
/// register themselves with their dependences, and provides a mechanism
/// whereby those script modules will be loaded when necessary. Currently,
/// this is when one of our script modules is loaded, when TfPyInitialize is
/// called, and when Plug opens shared libraries.
///
/// Generally, user code will not make use of this.
///
class TfScriptModuleLoader : public TfWeakBase {

  public:

    typedef TfScriptModuleLoader This;

    /// Return the singleton instance.
    TF_API static This &GetInstance() {
        return TfSingleton<This>::GetInstance();
    }

    /// Register a library named \a name and with script module \a moduleName
    /// and libraries which must be loaded first \a predecessors. The script
    /// module will be loaded when necessary. This should generally not be
    /// called by user code.
    TF_API
    void RegisterLibrary(TfToken const &name, TfToken const &moduleName,
                         std::vector<TfToken> const &predecessors);

    /// Load all the script modules for any libraries registered using \a
    /// RegisterLibrary if necessary. Loads the modules in dependency order as
    /// defined in \a RegisterLibrary.
    TF_API
    void LoadModules();

    /// Load all the script modules for any libraries registered using \a
    /// RegisterLibrary that depend on library \a name.
    TF_API
    void LoadModulesForLibrary(TfToken const &name);

    /// Return a list of all currently known modules in a valid dependency
    /// order.
    TF_API
    std::vector<std::string> GetModuleNames() const;

    /// Return a python dict containing all currently known modules under
    /// their canonical names.
    TF_API
    boost::python::dict GetModulesDict() const;

    /// Write a graphviz dot-file for the dependency graph of all. currently
    /// known libraries/modules to \a file.
    TF_API
    void WriteDotFile(std::string const &file) const;

  private:

    struct _LibInfo {
        _LibInfo() {}
        std::vector<TfToken> predecessors, successors;
    };

    typedef TfHashMap<TfToken, _LibInfo, TfToken::HashFunctor>
    _TokenToInfoMap;

    typedef TfHashMap<TfToken, TfToken, TfToken::HashFunctor>
    _TokenToTokenMap;

    typedef TfHashSet<TfToken, TfToken::HashFunctor>
    _TokenSet;

    TfScriptModuleLoader();
    virtual ~TfScriptModuleLoader();
    friend class TfSingleton<This>;

    void _AddSuccessor(TfToken const &lib, TfToken const &successor);
    void _LoadModulesFor(TfToken const &name);
    void _LoadUpTo(TfToken const &name);
    void _GetOrderedDependenciesRecursive(TfToken const &lib,
                                          TfToken::HashSet *seenLibs,
                                          std::vector<TfToken> *result) const;
    void _GetOrderedDependencies(std::vector<TfToken> const &input,
                                 std::vector<TfToken> *result) const;
    void _TopologicalSort(std::vector<TfToken> *result) const;

    bool _HasTransitiveSuccessor(TfToken const &predecessor,
                                 TfToken const &successor) const;

    _TokenToInfoMap _libInfo;
    _TokenToTokenMap _libsToModules;
    _TokenSet _loadedSet;

    // This is only used to handle reentrant loading requests.
    std::deque<TfToken> _remainingLoadWork;
};

TF_API_TEMPLATE_CLASS(TfSingleton<TfScriptModuleLoader>);

FORGE_NAMESPACE_END

#endif // FORGE_BASE_TF_SCRIPT_MODULE_LOADER_H
