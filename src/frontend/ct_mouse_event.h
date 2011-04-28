#ifndef SRC_FRONTEND_CT_MOUSE_EVENT_H_
#define SRC_FRONTEND_CT_MOUSE_EVENT_H_

#include <frontend/ct_input_event.h>

namespace construct {
namespace frontend {

enum MouseButton {
  NO_BUTTON = 0x00000000,
  LEFT_BUTTON = 0x00000001,
  RIGHT_BUTTON = 0x00000002,
  MIDDLE_BUTTON = 0x00000004,
};

struct CtMouseEvent : public CtInputEvent {
  CtMouseEvent() : x(0), y(0), x_rel(0), y_rel(0), 
                   buttons(NO_BUTTON) {}
  int x;
  int y;
  int x_rel;
  int y_rel;
  MouseButton buttons;
};

} // namespace frontend
} // namespace construct

#endif

