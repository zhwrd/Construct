#ifndef SRC_CONSTRUCT_APP_H_
#define SRC_CONSTRUCT_APP_H_

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <core/player.h>
#include <audiodrivers/coreaudio_out.h>
#include <frontend/ct_widget.h>

namespace construct {

class ConstructApp {
 public:
  ConstructApp();
  ~ConstructApp();

  bool Initialize();

  int Execute();

 private:
  void OnEvent(SDL_Event* event);
  bool InitializeSDL();

  audiodrivers::AudioDriver* audio_out_;
  core::Player* player_;
  frontend::CtWidget* window_;
  bool finished_;
  int width_;
  int height_;

};

} // namespace construct

#endif
