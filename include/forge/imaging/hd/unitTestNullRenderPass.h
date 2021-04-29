#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/unitTestNullRenderPass.h"
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
#ifndef FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_PASS_H
#define FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_PASS_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"

#include "forge/imaging/hd/renderPass.h"

FORGE_NAMESPACE_BEGIN

///
/// \class Hd_UnitTestNullRenderPass
/// Implements the sync part of the render pass, but not the draw part, for
/// core hydra unit tests.
class Hd_UnitTestNullRenderPass : public HdRenderPass
{
public:
    Hd_UnitTestNullRenderPass(HdRenderIndex *index,
                              HdRprimCollection const &collection)
        : HdRenderPass(index, collection)
        {}
    virtual ~Hd_UnitTestNullRenderPass() {}

    void _Execute(HdRenderPassStateSharedPtr const &renderPassState,
                  TfTokenVector const &renderTags) override {}
};

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HD_UNIT_TEST_NULL_RENDER_PASS_H
