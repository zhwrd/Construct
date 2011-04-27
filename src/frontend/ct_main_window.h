#ifndef SRC_FRONTEND_CT_MAINWINDOW_H_
#define SRC_FRONTEND_CT_MAINWINDOW_H_

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

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

 protected:
  void Draw();
  void OnMouseMove(const CtMouseEvent& event);

 private:
  int width_;
  int height_;
};

} // namespace frontend
} // namespace construct

#endif
