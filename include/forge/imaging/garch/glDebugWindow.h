#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/garch/glDebugWindow.h"
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
#ifndef FORGE_IMAGING_GARCH_GL_DEBUG_WINDOW_H
#define FORGE_IMAGING_GARCH_GL_DEBUG_WINDOW_H

#include "forge/forge.h"
#include "forge/imaging/garch/api.h"
#include <string>

FORGE_NAMESPACE_BEGIN


class Garch_GLPlatformDebugWindow;

/// \class GarchGLDebugWindow
///
/// Platform specific minimum GL widget for unit tests.
///
class GarchGLDebugWindow {
public:
    GARCH_API
    GarchGLDebugWindow(const char *title, int width, int height);
    GARCH_API
    virtual ~GarchGLDebugWindow();

    GARCH_API
    void Init();
    GARCH_API
    void Run();
    GARCH_API
    void ExitApp();

    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }

    enum Buttons {
        MyButton1 = 0,
        MyButton2 = 1,
        MyButton3 = 2
    };
    enum ModifierKeys {
        NoModifiers = 0,
        Shift = 1,
        Alt   = 2,
        Ctrl  = 4
    };

    GARCH_API
    virtual void OnInitializeGL();
    GARCH_API
    virtual void OnUninitializeGL();
    GARCH_API
    virtual void OnResize(int w, int h);
    GARCH_API
    virtual void OnIdle();
    GARCH_API
    virtual void OnPaintGL();
    GARCH_API
    virtual void OnKeyRelease(int key);
    GARCH_API
    virtual void OnMousePress(int button, int x, int y, int modKeys);
    GARCH_API
    virtual void OnMouseRelease(int button, int x, int y, int modKeys);
    GARCH_API
    virtual void OnMouseMove(int x, int y, int modKeys);

private:
    Garch_GLPlatformDebugWindow *_private;
    std::string _title;
    int _width, _height;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GARCH_GL_DEBUG_WINDOW_H
