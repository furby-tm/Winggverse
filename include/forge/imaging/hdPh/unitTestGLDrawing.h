#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/unitTestGLDrawing.h"
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
#ifndef FORGE_IMAGING_HD_PH_UNIT_TEST_GLDRAWING_H
#define FORGE_IMAGING_HD_PH_UNIT_TEST_GLDRAWING_H

#include "forge/base/gf/frustum.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/forge.h"
#include "forge/imaging/hdPh/api.h"

#include <string>

FORGE_NAMESPACE_BEGIN

class HdPh_UnitTestWindow;

/// \class HdPh_UnitTestGLDrawing
///
/// A helper class for unit tests which need to perform GL drawing.
///
class HdPh_UnitTestGLDrawing {
 public:
  HDPH_API
  HdPh_UnitTestGLDrawing();
  HDPH_API
  virtual ~HdPh_UnitTestGLDrawing();

  HDPH_API
  int GetWidth() const;
  HDPH_API
  int GetHeight() const;
  HDPH_API
  void RunTest(int argc, char *argv[]);

  virtual void InitTest() = 0;
  HDPH_API virtual void UninitTest();
  virtual void DrawTest() = 0;       // interactive mode
  virtual void OffscreenTest() = 0;  // offscreen mode (automated test)

  HDPH_API
  virtual void MousePress(int button, int x, int y, int modKeys);
  HDPH_API
  virtual void MouseRelease(int button, int x, int y, int modKeys);
  HDPH_API
  virtual void MouseMove(int x, int y, int modKeys);
  HDPH_API
  virtual void KeyRelease(int key);

  HDPH_API
  virtual void Idle();

  HDPH_API
  bool WriteToFile(std::string const &attachment, std::string const &filename) const;

 protected:
  HDPH_API
  virtual void ParseArgs(int argc, char *argv[]);

  void SetCameraRotate(float rx, float ry)
  {
    _rotate[0] = rx;
    _rotate[1] = ry;
  }
  void SetCameraTranslate(GfVec3f t)
  {
    _translate = t;
  }
  GfVec3f GetCameraTranslate() const
  {
    return _translate;
  }
  HDPH_API
  GfMatrix4d GetViewMatrix() const;
  HDPH_API
  GfMatrix4d GetProjectionMatrix() const;
  HDPH_API
  GfFrustum GetFrustum() const;

  GfVec2i GetMousePos() const
  {
    return GfVec2i(_mousePos[0], _mousePos[1]);
  }

 private:
  HdPh_UnitTestWindow *_widget;
  float _rotate[2];
  GfVec3f _translate;

  int _mousePos[2];
  bool _mouseButton[3];
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_UNIT_TEST_GLDRAWING_H
