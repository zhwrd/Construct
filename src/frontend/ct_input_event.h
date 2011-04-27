#ifndef SRC_FRONTEND_CT_INPUT_EVENT_H_
#define SRC_FRONTEND_CT_INPUT_EVENT_H_

namespace construct {
namespace frontend {

enum KeyboardModifier {
  NO_KEY = 0x00000000,
  SHIFT = 0x02000000,
  CONTROL = 0x04000000,
  ALT = 0x08000000
};

struct CtInputEvent {
  CtInputEvent() : modifiers(NO_KEY) {}
  KeyboardModifier modifiers;
};

} // namespace frontend
} // namespace construct

#endif
