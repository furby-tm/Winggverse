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

/**
 * @file
 * @ingroup wm
 */

#ifndef WINGG_WM_TEST_HYDRA_ENGINE_GL_TEST_WINDOW_H
#define WINGG_WM_TEST_HYDRA_ENGINE_GL_TEST_WINDOW_H

#include "WM_api.h"

#include <forge/forge.h>

#include <forge/base/gf/frustum.h>
#include <forge/base/gf/matrix4d.h>
#include <forge/base/gf/vec3f.h>

#include <forge/imaging/hdPh/api.h>
#include <forge/imaging/hgi/hgi.h>
#include <forge/imaging/hd/driver.h>
#include <forge/imaging/glf/drawTarget.h>

#include <string>

/** forwards -> */
class HdEngineGLTestWindow;

/**
 * -------------------------------------------------------------
 *  TEST MANAGER
 * ------------------------------------------------------------- */
class HdEngineGLTestManager {

 public:

  WINGG_WM_API
  HdEngineGLTestManager();

  WINGG_WM_API
  virtual ~HdEngineGLTestManager();


  WINGG_WM_API
  int GetWidth() const;

  WINGG_WM_API
  int GetHeight() const;


  WINGG_WM_API
  void RunTest(int argc, char *argv[]);

  WINGG_WM_API
  void PreparePixarScene();

  WINGG_WM_API
  void PrepareHydraEngine();

  virtual void InitTest() = 0;
  virtual void DrawTest() = 0;
  virtual void OffscreenTest() = 0;


  WINGG_WM_API
  virtual void MousePress(int button, int x, int y, int mod_keys);

  WINGG_WM_API
  virtual void MouseRelease(int button, int x, int y, int mod_keys);

  WINGG_WM_API
  virtual void MouseMove(int x, int y, int mod_keys);

  WINGG_WM_API
  virtual void KeyRelease(int key);


  WINGG_WM_API
  bool WriteToFile(std::string const &attachment, std::string const &filename) const;


 protected:

  void SetCameraRotate(float rx, float ry);
  void SetCameraTranslate(GfVec3f t);
  forge::GfVec3f GetCameraTranslate() const;


  forge::GfMatrix4d GetViewMatrix() const;
  forge::GfMatrix4d GetProjectionMatrix() const;


  forge::GfFrustum GetFrustum() const;
  forge::GfVec2i GetMousePos() const;


 private:

  HdEngineGLTestWindow *m_widget;

  forge::HgiUniquePtr m_hgi;

  float          m_rotate[2];
  forge::GfVec3f m_translate;

  int  m_mouse_pos[2];
  bool m_mouse_but[3];
};



/**
 * -------------------------------------------------------------
 *  TEST WINDOW
 * ------------------------------------------------------------- */
class HdEngineGLTestWindow : public GarchGLDebugWindow {

 public:

  typedef HdEngineGLTestWindow This;
  

  WINGG_WM_API
  HdEngineGLTestWindow(HdEngineGLTestManager *unitTest, int width, int height);

  WINGG_WM_API
  virtual ~HdEngineGLTestWindow();


  void OffscreenTest();
  bool WriteToFile(std::string const &attachment, std::string const &filename);
  void StartTimer();


  virtual void OnInitializeGL();
  virtual void OnUninitializeGL();
  virtual void OnIdle();
  virtual void OnPaintGL();
  virtual void OnKeyRelease(int key);
  virtual void OnMousePress(int button, int x, int y, int mod_keys);
  virtual void OnMouseRelease(int button, int x, int y, int mod_keys);
  virtual void OnMouseMove(int x, int y, int mod_keys);

 private:
  HdEngineGLTestManager *m_manager;
  pxr::GlfDrawTargetRefPtr m_draw_target;
  bool m_animate;
};

#endif  /*  WINGG_WM_TEST_HYDRA_ENGINE_GL_TEST_WINDOW_H */
