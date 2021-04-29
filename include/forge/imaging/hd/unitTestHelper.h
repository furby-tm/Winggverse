#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/unitTestHelper.h"
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
#ifndef FORGE_IMAGING_HD_UNIT_TEST_HELPER_H
#define FORGE_IMAGING_HD_UNIT_TEST_HELPER_H

#include "forge/forge.h"
#include "forge/imaging/hd/engine.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hd/renderPassState.h"
#include "forge/imaging/hd/unitTestDelegate.h"
#include "forge/imaging/hd/unitTestNullRenderDelegate.h"

#include "forge/base/gf/vec4d.h"
#include "forge/base/gf/matrix4d.h"

#include <vector>

FORGE_NAMESPACE_BEGIN


/// \class Hd_TestDriver
///
/// A unit test driver that exercises the core engine.
///
/// \note This test driver does NOT assume OpenGL is available; in the even
/// that is is not available, all OpenGL calls become no-ops, but all other work
/// is performed as usual.
///
class Hd_TestDriver final {
public:
    Hd_TestDriver();
    Hd_TestDriver(HdReprSelector const &reprToken);
    ~Hd_TestDriver();

    /// Draw
    void Draw(bool withGuides=false);

    /// Draw with external renderPass
    void Draw(HdRenderPassSharedPtr const &renderPass, bool withGuides);

    /// Set camera to renderpass
    void SetCamera(GfMatrix4d const &modelViewMatrix,
                   GfMatrix4d const &projectionMatrix,
                   GfVec4d const &viewport);

    /// Set cull style
    void SetCullStyle(HdCullStyle cullStyle);

    /// Returns the renderpass
    HdRenderPassSharedPtr const &GetRenderPass();

    /// Returns the renderPassState
    HdRenderPassStateSharedPtr const &GetRenderPassState() const {
        return _renderPassState;
    }

    /// Returns the UnitTest delegate
    HdUnitTestDelegate& GetDelegate() { return *_sceneDelegate; }

    /// Switch repr
    void SetRepr(HdReprSelector const &reprSelector);

private:

    void _Init(HdReprSelector const &reprSelector);

    HdEngine _engine;
    Hd_UnitTestNullRenderDelegate _renderDelegate;
    HdRenderIndex       *_renderIndex;
    HdUnitTestDelegate *_sceneDelegate;
	SdfPath _cameraId;
    HdRenderPassSharedPtr _renderPass;
    HdRenderPassStateSharedPtr _renderPassState;
    HdRprimCollection          _collection;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_UNIT_TEST_HELPER_H
