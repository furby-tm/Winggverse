#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/glf/bindingMap.h"
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
#ifndef FORGE_IMAGING_GLF_BINDING_MAP_H
#define FORGE_IMAGING_GLF_BINDING_MAP_H

/// \file glf/bindingMap.h

#include "forge/forge.h"
#include "forge/imaging/glf/api.h"
#include "forge/imaging/garch/glApi.h"
#include "forge/base/tf/refBase.h"
#include "forge/base/tf/stringUtils.h"
#include "forge/base/tf/token.h"
#include "forge/base/tf/weakBase.h"

#include "forge/base/tf/hashmap.h"

FORGE_NAMESPACE_BEGIN


class GlfBindingMap : public TfRefBase, public TfWeakBase {
public:
    typedef TfHashMap<TfToken, int, TfToken::HashFunctor> BindingMap;

    GlfBindingMap()
      : _samplerBindingBaseIndex(0)
      , _uniformBindingBaseIndex(0)
      { }

    GLF_API
    int GetSamplerUnit(std::string const &name);
    GLF_API
    int GetSamplerUnit(TfToken const & name);

    // If GetAttributeIndex is called with an unknown
    // attribute token they return -1
    GLF_API
    int GetAttributeIndex(std::string const & name);
    GLF_API
    int GetAttributeIndex(TfToken const & name);

    GLF_API
    int GetUniformBinding(std::string const & name);
    GLF_API
    int GetUniformBinding(TfToken const & name);

    GLF_API
    bool HasUniformBinding(std::string const & name) const;
    GLF_API
    bool HasUniformBinding(TfToken const & name) const;

    int GetNumSamplerBindings() const {
        return (int)_samplerBindings.size();
    }

    void ClearAttribBindings() {
        _attribBindings.clear();
    }

    /// \name Sampler and UBO Bindings
    ///
    /// Sampler units and uniform block bindings are reset and will be
    /// assigned sequentially starting from the specified baseIndex.
    /// This allows other subsystems to claim sampler units and uniform
    /// block bindings before additional indices are assigned by this
    /// binding map.
    ///
    /// @{

    void ResetSamplerBindings(int baseIndex) {
        _samplerBindings.clear();
        _samplerBindingBaseIndex = baseIndex;
    }

    void ResetUniformBindings(int baseIndex) {
        _uniformBindings.clear();
        _uniformBindingBaseIndex = baseIndex;
    }

    /// @}

    void AddAttribBinding(TfToken const &name, int location) {
        _attribBindings[name] = location;
    }

    BindingMap const &GetAttributeBindings() const {
        return _attribBindings;
    }

    GLF_API
    void AssignSamplerUnitsToProgram(GLuint program);

    GLF_API
    void AssignUniformBindingsToProgram(GLuint program);

    GLF_API
    void AddCustomBindings(GLuint program);

    GLF_API
    void Debug() const;

private:
    void _AddActiveAttributeBindings(GLuint program);
    void _AddActiveUniformBindings(GLuint program);
    void _AddActiveUniformBlockBindings(GLuint program);

    BindingMap _attribBindings;
    BindingMap _samplerBindings;
    BindingMap _uniformBindings;

    int _samplerBindingBaseIndex;
    int _uniformBindingBaseIndex;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GLF_BINDING_MAP_H
