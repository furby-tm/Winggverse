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

#include <forge/imaging/garch/glApi.h>

#include "forge/imaging/garch/glDebugWindow.h"
#include "forge/imaging/glf/contextCaps.h"
#include "forge/imaging/glf/diagnostic.h"

#include "forge/base/gf/frustum.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/rotation.h"
#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec4d.h"

#include <cstdlib>
#include <iostream>

USING_NAMESPACE_DIRECTIVES(forge, std)

/**
 * -------------------------------------------------------------
 *  TEST WINDOW
 * ------------------------------------------------------------- */

HdEngineGLTestWindow::HdEngineGLTestWindow(HdEngineGLTestManager *unitTest, int w, int h)
    : GarchGLDebugWindow("WINGG | WM TEST | HydraEngineGL", w, h),
      m_unit_test(unitTest),
      _animate(false)
{
}

HdEngineGLTestWindow::~HdEngineGLTestWindow()
{
}

/* virtual */
void HdEngineGLTestWindow::OnInitializeGL()
{
  GarchGLApiLoad();
  GlfSharedGLContextScopeHolder sharedContext;
  GlfRegisterDefaultDebugOutputMessageCallback();
  GlfContextCaps::InitInstance();

  const auto &caps = GlfContextCaps::GetInstance();
  GlfGLContextSharedPtr context = GlfGLContext::GetCurrentGLContext();

  std::cout << glGetString(GL_VENDOR)   << "\n";
  std::cout << glGetString(GL_RENDERER) << "\n";
  std::cout << glGetString(GL_VERSION)  << "\n";

  GarchGLApiLoad();

  m_draw_target = GlfDrawTarget::New(GfVec2i(GetWidth(), GetHeight()));
  m_draw_target->Bind();
  m_draw_target->AddAttachment("color", GL_RGBA, GL_FLOAT, GL_RGBA);
  m_draw_target->AddAttachment("depth", GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, GL_DEPTH24_STENCIL8);
  m_unit_test->InitTest();

  m_draw_target->Unbind();
}

/* virtual */
void HdEngineGLTestWindow::OnUninitializeGL()
{
  m_draw_target = GlfDrawTargetRefPtr();
  m_unit_test->UninitTest();
}

/* virtual */
void HdEngineGLTestWindow::OnPaintGL()
{
  GLF_GROUP_FUNCTION();

  GLint restoreReadFbo = 0;
  GLint restoreDrawFbo = 0;
  glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &restoreReadFbo);
  glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &restoreDrawFbo);
  taskController->SetPresentationOutput(HgiTokens->OpenGL, VtValue(static_cast<uint32_t>(restoreDrawFbo)));

  GLuint vao;
  glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT);
  glFrontFace(GL_CW);
  glDisable(GL_BLEND);

  /** For points width */
  glEnable(GL_PROGRAM_POINT_SIZE);

  {
    TF_PY_ALLOW_THREADS_IN_SCOPE();
    engine->Execute(renderIndex.get(), &tasks);
  }

  if (GlfContextCaps::GetInstance().coreProfile) {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
  } else {
    glPopAttrib(); /* GL_ENABLE_BIT | GL_POLYGON_BIT | GL_DEPTH_BUFFER_BIT */
  }

  glBindFramebuffer(GL_READ_FRAMEBUFFER, restoreReadFbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, restoreDrawFbo);
}

void HdEngineGLTestWindow::OffscreenTest()
{
  m_draw_target->Bind();
  m_draw_target->SetSize(GfVec2i(GetWidth(), GetHeight()));

  m_unit_test->OffscreenTest();

  m_draw_target->Unbind();
}

void HdEngineGLTestWindow::StartTimer()
{
  _animate = true;
}

/* virtual */
void HdEngineGLTestWindow::OnIdle()
{
  if (_animate) {
    m_unit_test->Idle();
  }
}

bool HdEngineGLTestWindow::WriteToFile(std::string const &attachment, std::string const &filename)
{
  m_draw_target->Unbind();
  bool ret = m_draw_target->WriteToFile(attachment, filename);
  m_draw_target->Bind();
  return ret;
}

/* virtual */
void HdEngineGLTestWindow::OnKeyRelease(int key)
{
  switch (key) {
    case 'q':
      ExitApp();
      return;
  }
  m_unit_test->KeyRelease(key);
}

/* virtual */
void HdEngineGLTestWindow::OnMousePress(int button, int x, int y, int modKeys)
{
  m_unit_test->MousePress(button, x, y, modKeys);
}

/* virtual */
void HdEngineGLTestWindow::OnMouseRelease(int button, int x, int y, int modKeys)
{
  m_unit_test->MouseRelease(button, x, y, modKeys);
}

/* virtual */
void HdEngineGLTestWindow::OnMouseMove(int x, int y, int modKeys)
{
  m_unit_test->MouseMove(x, y, modKeys);
}

/**
 * -------------------------------------------------------------
 *  TEST MANAGER
 * ------------------------------------------------------------- */

HdEngineGLTestManager::HdEngineGLTestManager() : m_rotate(NULL)
{
  m_rotate[0] = 0;
  m_rotate[1] = 0;

  m_translate[0] = 0;
  m_translate[1] = 0;
  m_translate[2] = 0;

  m_mouse_pos[0] = 0;
  m_mouse_pos[1] = 0;

  m_mouse_but[0] = false;
  m_mouse_but[1] = false;
  m_mouse_but[2] = false;
}

HdEngineGLTestManager::~HdEngineGLTestManager()
{
}

int HdEngineGLTestManager::GetWidth() const
{
  return m_widget->GetWidth();
}

int HdEngineGLTestManager::GetHeight() const
{
  return m_widget->GetHeight();
}

bool HdEngineGLTestManager::WriteToFile(std::string const &attachment,
                                        std::string const &filename) const
{
  return m_widget->WriteToFile(attachment, filename);
}



void HdEngineGLTestManager::RunTest(int argc, char *argv[])
{
  bool offscreen = false;
  bool animate = false;

  m_widget = new HdEngineGLTestWindow(this, 640, 480);

  m_widget->Init();
  m_widget->StartTimer();
  m_widget->Run();

  PreparePixarScene();
  PrepareHydraEngine();
}

void HdEngineGLTestManager::PreparePixarScene()
{
  TfToken defaultPlugin = HdRendererPluginRegistry::GetInstance().GetDefaultPluginId();
  auto stage = UsdStage::Open("...");
}

void HdEngineGLTestManager::PrepareHydraEngine()
{
  /** Create the Hydra Graphics Interface. */
  m_hgi = Hgi::CreatePlatformDefaultHgi();

  /** Create the Hydra driver. */
  HdDriver hdriver;
  m_driver.name   = HgiTokens->renderDriver;
  m_driver.driver = VtValue{hgi.get()};
  
  /** Create the Hydra Engine. */
  auto engine = std::make_unique<HdEngine>();
  
  /** Establish scene and root sdf paths. */
  SdfPath sceneDelegateId{"/sceneDelegate"};
  SdfPath rootPath;

  /** Prepare Renderable Prim collections. */
  HdRprimCollection renderCollection;
  HdRprimCollection intersectCollection;
  
  /** Prepare Hydra Picking. */
  auto selection        = std::make_shared<HdSelection>();
  auto selectionTracker = std::make_shared<HdxSelectionTracker>();
  selectionTracker->SetSelection(selection);
  
  /** Prepare Hydra Plugin. Forge->Phoenix :: Pixar->Storm. */
  auto &registry = HdRendererPluginRegistry::GetInstance();
  auto renderDelegate = registry.CreateRenderDelegate(defaultPlugin);
  
  /** Setup a render index to driver our task controller. */
  std::unique_ptr<HdRenderIndex> renderIndex;
  renderIndex.reset(HdRenderIndex::New(renderDelegate.Get(), {&hdriver}));
  auto sceneDelegate  = std::make_unique<UsdImagingDelegate>(renderIndex.get(), sceneDelegateId);
  auto taskController = std::make_unique<HdxTaskController>(renderIndex.get(), sceneDelegateId.AppendChild(TfToken{"taskController"}));
  
  /** Setup the scene delegate with stage data root and a default camera. */
  sceneDelegate->Populate(stage->GetPseudoRoot());
  const auto cameraPath = sceneDelegate->ConvertCachePathToIndexPath(SdfPath{"..."});
  taskController->SetCameraPath(cameraPath);
  const SdfPathVector roots = {sceneDelegate->ConvertCachePathToIndexPath(stage->GetPseudoRoot().GetPath())};
  
  /** Prepare Renderable Prim selector and collection. */
  HdReprSelector    reprSelection(HdReprTokens->smoothHull);
  HdRprimCollection rprimCollection(HdTokens->geometry, reprSelection);
  rprimCollection.SetRootPaths(roots);
  taskController->SetCollection(rprimCollection);

  /** Apply some render tags. */
  taskController->SetRenderTags({HdRenderTagTokens->geometry, HdRenderTagTokens->guide, HdRenderTagTokens->proxy, HdRenderTagTokens->render});
  
  /** Inform the Hydra engine of our context. */
  engine->SetTaskContextData(HdxTokens->selectionState, VtValue{selectionTracker});
  
  /** Prepare the viewport, set to our window bounds. */
  taskController->SetRenderBufferSize({m_widget->GetWidth(), m_widget->GetHeight()});
  CameraUtilFraming framing(GfRect2i{GfVec2i{0, 0}, m_widget->GetWidth(), m_widget->GetHeight()});
  taskController->SetFraming(framing);
  
  /** Get all of our rendering tasks. */
  auto tasks = taskController->GetRenderingTasks();
}

/* virtual */
void HdEngineGLTestManager::MousePress(int button, int x, int y, int modKeys)
{
  m_mouse_but[button] = true;
  m_mouse_pos[0] = x;
  m_mouse_pos[1] = y;
}

/* virtual */
void HdEngineGLTestManager::MouseRelease(int button, int x, int y, int modKeys)
{
  m_mouse_but[button] = false;
}

/* virtual */
void HdEngineGLTestManager::MouseMove(int x, int y, int modKeys)
{
  int dx = x - m_mouse_pos[0];
  int dy = y - m_mouse_pos[1];

  if (modKeys & GarchGLDebugWindow::Alt) {
    if (m_mouse_but[0]) {
      m_rotate[1] += dx;
      m_rotate[0] += dy;
    }
    else if (m_mouse_but[1]) {
      m_translate[0] += 0.1 * dx;
      m_translate[1] -= 0.1 * dy;
    }
    else if (m_mouse_but[2]) {
      m_translate[2] += 0.1 * dx;
    }
  }

  m_mouse_pos[0] = x;
  m_mouse_pos[1] = y;
}

/* virtual */
void HdEngineGLTestManager::KeyRelease(int key)
{}

void HdEngineGLTestManager::SetCameraRotate(float rx, float ry)
{
  m_rotate[0] = rx;
  m_rotate[1] = ry;
}

void HdEngineGLTestManager::SetCameraTranslate(GfVec3f t)
{
  m_translate = t;
}

GfVec3f HdEngineGLTestManager::GetCameraTranslate() const
{
  return m_translate;
}

GfVec2i HdEngineGLTestManager::GetMousePos() const
{
  return GfVec2i(m_mouse_pos[0], m_mouse_pos[1]);
}

GfMatrix4d HdEngineGLTestManager::GetViewMatrix() const
{
  GfMatrix4d viewMatrix;
  viewMatrix.SetIdentity();
  // rotate from z-up to y-up
  viewMatrix *= GfMatrix4d().SetRotate(GfRotation(GfVec3d(1.0, 0.0, 0.0), -90.0));
  viewMatrix *= GfMatrix4d().SetRotate(GfRotation(GfVec3d(0, 1, 0), m_rotate[1]));
  viewMatrix *= GfMatrix4d().SetRotate(GfRotation(GfVec3d(1, 0, 0), m_rotate[0]));
  viewMatrix *= GfMatrix4d().SetTranslate(GfVec3d(m_translate[0], m_translate[1], m_translate[2]));

  return viewMatrix;
}

GfMatrix4d HdEngineGLTestManager::GetProjectionMatrix() const
{
  return GetFrustum().ComputeProjectionMatrix();
}

GfFrustum HdEngineGLTestManager::GetFrustum() const
{
  int width = GetWidth();
  int height = GetHeight();
  double aspectRatio = double(width) / height;

  GfFrustum frustum;
  frustum.SetPerspective(45.0, aspectRatio, 1, 100000.0);
  return frustum;
}