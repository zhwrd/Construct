#ifndef SRC_FRONTEND_CT_INPUT_EVENT_H_
#define SRC_FRONTEND_CT_INPUT_EVENT_H_

namespace construct {
namespace frontend {

enum KeyboardModifier {
  NO_KEY = 0x00000000,
  SHIFT = 0x00000001,
  CONTROL = 0x00000002,
  ALT = 0x00000004
};

struct CtInputEvent {
  CtInputEvent() : modifiers(NO_KEY) {}
  KeyboardModifier modifiers;
};

} // namespace frontend
} // namespace construct

#endif
