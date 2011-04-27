#include "construct_app.h"
#include <iostream>
#include <frontend/ct_mouse_event.h>
#include <frontend/ct_oscilloscope.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

namespace construct {

ConstructApp::ConstructApp() {
  finished_ = false;
  width_ = 800;
  height_ = 400;
}

ConstructApp::~ConstructApp() {

}

bool ConstructApp::Initialize() {
  audiodrivers::AudioDriverSettings settings;
  settings.sample_rate = 48000;
  settings.num_channels = 1;

  audio_out_ = new audiodrivers::CoreAudioOut() ;
  audio_out_->set_playback_settings(settings);
  audio_out_->Open();
  std::cout << "Output device initialized." << std::endl;

  core::PlayerTimeInfo time_info;
  time_info.sample_rate = settings.sample_rate;
  time_info.num_channels = settings.num_channels;

  player_ = new core::Player();
  player_->set_driver(*audio_out_);
  player_->set_time_info(time_info);
  core::Oscillator* osc;
  //osc = player_->CreateOscillator(440, 0.25);
  osc = player_->CreateOscillator(392.00, 0.25);
  osc = player_->CreateOscillator(261.63*2, 0.25);
  osc = player_->CreateOscillator(261.63, 0.25);

  std::cout << "Player initialized." << std::endl;

  // Initialize SDL
  InitializeSDL();

  // Initialize GUI
  window_ = new frontend::CtWidget();
  window_->resize(width_, height_);

  frontend::CtOscilloscope* ct_osc = new frontend::CtOscilloscope();
  ct_osc->set_unitgenerator(osc);
  window_->add_child(ct_osc);
  
  return true;
}

int ConstructApp::Execute() {
  SDL_Event event;
  audio_out_->Start();
  std::cout << "Output device started." << std::endl;
  while (!finished_) {
    while (SDL_PollEvent(&event)) {
      OnEvent(&event);
    }
    glClear(GL_COLOR_BUFFER_BIT);
    window_->redraw();
    SDL_GL_SwapBuffers();
  }
  audio_out_->Close();
  return 0;
}

void ConstructApp::OnEvent(SDL_Event* event) {
  frontend::CtMouseEvent mouse_event;
  switch (event->type) {
    case SDL_QUIT:
      finished_ = true;
      break;
    case SDL_MOUSEMOTION:
      mouse_event.x = event->motion.xrel;
      mouse_event.y = event->motion.yrel;
      mouse_event.global_x = event->motion.x;
      mouse_event.global_y = event->motion.y;
      window_->OnMouseMove(mouse_event);
      break;
  }
}

bool ConstructApp::InitializeSDL() {
  // Initialize SDL
  const SDL_VideoInfo* info = NULL;
  int bpp = 0;
  int flags = 0;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    std::cout << "Failed to initialize SDL." << std::endl;
    return false;
  }

  info = SDL_GetVideoInfo();
  if (!info) {
    std::cout << "Failed to get video info." << std::endl;
    return false;
  }
  bpp = info->vfmt->BitsPerPixel;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_Surface* drawContext;
  flags = SDL_OPENGL;
  drawContext = SDL_SetVideoMode(width_, height_, bpp, flags);

  // Intialize OpenGL
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width_, 0, height_, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  return true;
}

} // namespace construct
