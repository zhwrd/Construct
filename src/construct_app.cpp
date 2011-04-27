#include "construct_app.h"
#include <iostream>

namespace construct {

ConstructApp::ConstructApp() {
  finished_ = false;
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
  core::Oscillator* osc = player_->CreateOscillator(440, 0.25);

  std::cout << "Player initialized." << std::endl;

  // Initialize SDL
  window_ = new frontend::CtMainWindow();
  window_->Initialize();
  window_->AddOscilloscope(osc);
  
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
    window_->Draw();
  }
  audio_out_->Close();
}

void ConstructApp::OnEvent(SDL_Event* event) {
  switch (event->type) {
    case SDL_QUIT:
      finished_ = true;
      break;
  }
}

} // namespace construct