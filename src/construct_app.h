#ifndef SRC_CONSTRUCT_APP_H_
#define SRC_CONSTRUCT_APP_H_

#include <core/player.h>
#include <audiodrivers/coreaudio_out.h>
#include <frontend/ct_main_window.h>

namespace construct {

class ConstructApp {
 public:
  ConstructApp();
  ~ConstructApp();

  bool Initialize();
  int Execute();

 private:
  void OnEvent(SDL_Event* event);

  audiodrivers::AudioDriver* audio_out_;
  core::Player* player_;
  frontend::CtMainWindow* window_;
  bool finished_;

};

} // namespace construct

#endif
