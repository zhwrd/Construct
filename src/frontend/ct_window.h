#ifndef SRC_FRONTEND_CT_WINDOW_H_
#define SRC_FRONTEND_CT_WINDOW_H_

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "frontend/ct_widget.h"
#include "frontend/ct_mouse_event.h"

namespace construct {
namespace frontend {

class CtWindow : public CtWidget {
 public:
	explicit CtWindow(CtWidget* parent = NULL);
  virtual ~CtWindow();

 protected:
  void Draw();
  void OnMouseMove(const CtMouseEvent& event);
	void OnMousePress(const CtMouseEvent& event);
	void OnMouseRelease(const CtMouseEvent& event);

 private:
	inline bool in_exit_button(int mx, int my) {
		if (my - y() > height() && 
				my - y() < height() + window_bar_size_ &&
				mx - x() > 0 &&
				mx - x() < window_bar_size_) {
			return true;
		}
		return false;
	}	
	inline bool in_move_bar(int mx, int my) {
		if (my - y() > height() &&
				my - y() < height() + window_bar_size_ &&
				mx - x() > window_bar_size_ &&
				mx - x() < width()) {
			return true;
		}
		return false;
	}
	int window_bar_size_;
	bool exit_pressed_;
	bool move_pressed_;
	CtMouseEvent move_event_;

};

} // namespace frontend
} // namespace construct

#endif
