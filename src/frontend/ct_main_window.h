#ifndef SRC_FRONTEND_CT_MAINWINDOW_H_
#define SRC_FRONTEND_CT_MAINWINDOW_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <frontend/ct_oscilloscope.h>
#include <frontend/ct_widget.h>

namespace construct {
class ConstructApp;
namespace frontend {

class CtMainWindow : public CtWidget {
 public:
  friend class construct::ConstructApp;
  CtMainWindow();
  virtual ~CtMainWindow();

  bool Initialize();
  void AddOscilloscope(core::UnitGenerator* unitgenerator);
  void Draw();

 protected:
  void OnMouseMove(const CtMouseEvent& event);

 private:
  int width_;
  int height_;
  CtOscilloscope* oscilloscope_;
};

} // namespace frontend
} // namespace construct

#endif
