#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/sceneExtCompInputSource.h"
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
#ifndef FORGE_IMAGING_HD_SCENE_EXT_COMP_INPUT_SOURCE_H
#define FORGE_IMAGING_HD_SCENE_EXT_COMP_INPUT_SOURCE_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/extCompInputSource.h"

#include "forge/base/vt/value.h"

FORGE_NAMESPACE_BEGIN

///
/// An Hd Buffer Source Computation that is used to bind an ExtComputation input
/// to a value provided by the scene delegate.
///
class Hd_SceneExtCompInputSource : public Hd_ExtCompInputSource {
public:
    /// Constructs the computation, binding inputName to the provided value.
    HD_API
    Hd_SceneExtCompInputSource(const TfToken &inputName, const VtValue &value);

    HD_API
    virtual ~Hd_SceneExtCompInputSource() = default;

    /// Set the state of the computation to resolved and returns true.
    HD_API
    virtual bool Resolve() override;

    /// Returns the value associated with this input.
    HD_API
    virtual const VtValue &GetValue() const override;

protected:
    /// Returns if this computation binding is valid.
    virtual bool _CheckValid() const override;

private:
    VtValue _value;

    // No copying, assignment or default construction.
    Hd_SceneExtCompInputSource()                                       = delete;
    Hd_SceneExtCompInputSource(const Hd_SceneExtCompInputSource &)     = delete;
    Hd_SceneExtCompInputSource &operator = (const Hd_SceneExtCompInputSource &)
                                                                       = delete;
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_SCENE_EXT_COMP_INPUT_SOURCE_H
