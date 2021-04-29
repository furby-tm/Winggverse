#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImagingGL/unitTestGLDrawing.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_GL_UNIT_TEST_GLDRAWING_H
#define FORGE_USD_IMAGING_USD_IMAGING_GL_UNIT_TEST_GLDRAWING_H

#include "forge/forge.h"
#include "forge/base/gf/vec4d.h"
#include "forge/base/vt/dictionary.h"

#include "forge/base/tf/declarePtrs.h"

#include "forge/usdImaging/usdImagingGL/engine.h"

#include <string>
#include <vector>

FORGE_NAMESPACE_BEGIN


class UsdImagingGL_UnitTestWindow;

/// \class UsdImagingGL_UnitTestGLDrawing
///
/// A helper class for unit tests which need to perform GL drawing.
///
class UsdImagingGL_UnitTestGLDrawing {
public:
    UsdImagingGL_UnitTestGLDrawing();
    virtual ~UsdImagingGL_UnitTestGLDrawing();

    int GetWidth() const;
    int GetHeight() const;

    bool IsEnabledTestLighting() const { return _testLighting; }
    bool IsEnabledSceneLights() const { return _sceneLights; }
    bool IsEnabledCameraLight() const { return _cameraLight; }
    bool IsEnabledIdRender() const { return _testIdRender; }

    bool IsShowGuides() const { return _showGuides; }
    bool IsShowRender() const { return _showRender; }
    bool IsShowProxy() const { return _showProxy; }
    bool ShouldClearOnce() const { return _clearOnce; }
    bool PresentDisabled() const { return _presentDisabled; }

    UsdImagingGLDrawMode GetDrawMode() const { return _drawMode; }

    std::string const & GetStageFilePath() const { return _stageFilePath; }
    std::string const & GetOutputFilePath() const { return _outputFilePath; }

    std::string const & GetCameraPath() const { return _cameraPath; }
    std::vector<GfVec4d> const & GetClipPlanes() const { return _clipPlanes; }
    std::vector<double> const& GetTimes() const { return _times; }
    GfVec4f const & GetClearColor() const { return _clearColor; }
    GfVec3f const & GetTranslate() const { return _translate; }
    VtDictionary const &GetRenderSettings() const { return _renderSettings; }
    TfToken const & GetRendererAov() const { return _rendererAov; }
    std::string const &GetPerfStatsFile() const { return _perfStatsFile; }
    float GetPixelAspectRatio() const { return _pixelAspectRatio; }
    GfRange2f const & GetDisplayWindow() const { return _displayWindow; }
    GfRect2i const & GetDataWindow() const { return _dataWindow; }
    UsdImagingGLCullStyle GetCullStyle() const { return _cullStyle; }

    void RunTest(int argc, char *argv[]);

    virtual void InitTest() = 0;
    virtual void DrawTest(bool offscreen) = 0;
    virtual void ShutdownTest() { }

    virtual void MousePress(int button, int x, int y, int modKeys);
    virtual void MouseRelease(int button, int x, int y, int modKeys);
    virtual void MouseMove(int x, int y, int modKeys);
    virtual void KeyRelease(int key);

    bool WriteToFile(std::string const & attachment, std::string const & filename) const;

protected:
    float _GetComplexity() const { return _complexity; }
    bool _ShouldFrameAll() const { return _shouldFrameAll; }
    TfToken _GetRenderer() const { return _renderer; }

    HdRenderIndex *_GetRenderIndex(UsdImagingGLEngine *engine) {
        return engine->_GetRenderIndex();
    }

    void _Render(UsdImagingGLEngine *engine,
                 const UsdImagingGLRenderParams &params) {
        SdfPathVector roots(1, SdfPath::AbsoluteRootPath());
        engine->RenderBatch(roots, params);
    }

private:
    struct _Args;
    void _Parse(int argc, char *argv[], _Args* args);

private:
    UsdImagingGL_UnitTestWindow *_widget;
    bool _testLighting;
    bool _sceneLights;
    bool _cameraLight;
    std::string _cameraPath;
    bool _testIdRender;

    std::string _stageFilePath;
    std::string _outputFilePath;

    float _complexity;
    TfToken _renderer;

    std::vector<double> _times;

    std::vector<GfVec4d> _clipPlanes;

    UsdImagingGLDrawMode _drawMode;
    bool _shouldFrameAll;
    UsdImagingGLCullStyle _cullStyle;
    GfVec4f _clearColor;
    GfVec3f _translate;
    float _pixelAspectRatio;
    GfRange2f _displayWindow;
    GfRect2i _dataWindow;
    VtDictionary _renderSettings;
    TfToken _rendererAov;
    std::string _perfStatsFile;
    std::string _traceFile;

    bool _showGuides;
    bool _showRender;
    bool _showProxy;
    bool _clearOnce;
    bool _presentDisabled;
};


FORGE_NAMESPACE_END

#endif // FORGE_USD_IMAGING_USD_IMAGING_GL_UNIT_TEST_GLDRAWING_H
