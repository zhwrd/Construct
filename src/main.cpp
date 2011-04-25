#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <core/player.h>
#include <audiodrivers/coreaudio_out.h>
#include <frontend/ct_main_window.h>
#include "config.h"

int main(int argc, char* argv[]) {
  using namespace construct;

  audiodrivers::AudioDriverSettings settings;
  settings.sample_rate = 48000;
  settings.num_channels = 1;

  audiodrivers::CoreAudioOut audio_out;
  audio_out.set_playback_settings(settings);
  audio_out.Open();
  std::cout << "Output device initialized." << std::endl;

  core::PlayerTimeInfo time_info;
  time_info.sample_rate = settings.sample_rate;
  time_info.num_channels = settings.num_channels;

  core::Player player;
  player.set_driver(audio_out);
  player.set_time_info(time_info);

  core::Oscillator* osc = player.CreateOscillator(440, 0.25);

  std::cout << "Player initialized." << std::endl;
  audio_out.Start();
  std::cout << "Output device started." << std::endl;

  // Initialize SDL
  frontend::CtMainWindow main_window;
  if (!main_window.Initialize()) {
    return 1;
  }
  main_window.AddOscilloscope(osc);

  for (int i = 0; i < 10000; ++i) {
    main_window.Draw();
  }
  std::cout << "DONE" << std::endl;

  audio_out.Close();
  return 0;
}
