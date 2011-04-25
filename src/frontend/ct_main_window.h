#ifndef SRC_FRONTEND_CT_MAINWINDOW_H_
#define SRC_FRONTEND_CT_MAINWINDOW_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <frontend/ct_oscilloscope.h>

namespace construct {
namespace frontend {

class CtMainWindow {
 public:
  CtMainWindow();
  virtual ~CtMainWindow();

  bool Initialize();
  void Draw();
  void AddOscilloscope(core::UnitGenerator* unitgenerator);

 private:
  int width_;
  int height_;
  CtOscilloscope* oscilloscope_;
};

} // namespace construct
} // namespace frontend

#endif
