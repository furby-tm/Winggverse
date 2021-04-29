#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/garch/glPlatformDebugWindowWindows.h"
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
#ifndef FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_WINDOW_WINDOWS_H
#define FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_WINDOW_WINDOWS_H

#include "forge/forge.h"
#include <Windows.h>

FORGE_NAMESPACE_BEGIN


class GarchGLDebugWindow;

/// \class Garch_GLPlatformDebugWindow
///
class Garch_GLPlatformDebugWindow
{
public:
    Garch_GLPlatformDebugWindow(GarchGLDebugWindow *w);

    void Init(const char *title, int width, int height, int nSamples=1);
    void Run();
    void ExitApp();

private:
    static Garch_GLPlatformDebugWindow *_GetWindowByHandle(HWND);
    static LRESULT WINAPI _MsgProc(HWND hWnd, UINT msg,
                                   WPARAM wParam, LPARAM lParam);

    bool _running;
    GarchGLDebugWindow *_callback;
    HWND  _hWND;
    HDC   _hDC;
    HGLRC _hGLRC;
    static LPCTSTR _className;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_GARCH_GL_PLATFORM_DEBUG_WINDOW_WINDOWS_H
