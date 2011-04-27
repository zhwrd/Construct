#ifndef SRC_FRONTEND_CT_WINDOW_H_
#define SRC_FRONTEND_CT_WINDOW_H_

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <frontend/ct_widget.h>

namespace construct {
namespace frontend {

class CtWindow : public CtWidget {
 public:
  CtWindow();
  virtual ~CtWindow();

  bool Initialize();

 protected:
  void Draw();
  void OnMouseMove(const CtMouseEvent& event);
};

} // namespace frontend
} // namespace construct

#endif
