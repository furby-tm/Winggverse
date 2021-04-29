#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/unitTestUtils.h"
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
//
#ifndef FORGE_IMAGING_HDX_UNIT_TEST_UTILS_H
#define FORGE_IMAGING_HDX_UNIT_TEST_UTILS_H

#include "forge/forge.h"

#include "forge/base/gf/frustum.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec2i.h"

#include "forge/imaging/garch/glApi.h"
#include "forge/imaging/hdx/pickTask.h"
#include "forge/imaging/hdx/selectionTracker.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

class HdEngine;
class HdRprimCollection;

namespace HdxUnitTestUtils
{
    HdSelectionSharedPtr TranslateHitsToSelection(
        TfToken const& pickTarget,
        HdSelection::HighlightMode highlightMode,
        HdxPickHitVector const& allHits);

    // For a drag-select from start to end, with given pick radius, what size
    // ID buffer should we ask for?
    GfVec2i CalculatePickResolution(
        GfVec2i const& start, GfVec2i const& end, GfVec2i const& pickRadius);

    GfMatrix4d ComputePickingProjectionMatrix(
        GfVec2i const& start, GfVec2i const& end, GfVec2i const& screen,
        GfFrustum const& viewFrustum);

    class Marquee {
    public:
        Marquee();
        ~Marquee();

        void InitGLResources();
        void DestroyGLResources();
        void Draw(float width, float height,
                  GfVec2f const& startPos, GfVec2f const& endPos);

    private:
        GLuint _vbo;
        GLuint _program;
    };
}

FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_UNIT_TEST_UTILS_H
