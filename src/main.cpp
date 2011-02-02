#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <core/player.h>
#include <audiodrivers/coreaudio_out.h>

int main(int argc, char* argv[]) {
  using namespace construct;

  audiodrivers::AudioDriverSettings settings;
  settings.sample_rate = 48000;
  settings.num_channels = 2;

  audiodrivers::CoreAudioOut audio_out;
  audio_out.set_playback_settings(settings);
  audio_out.Open();

  core::PlayerTimeInfo time_info;
  time_info.sample_rate = settings.sample_rate;
  time_info.num_channels = settings.num_channels;

  core::Player player;
  player.set_driver(audio_out);
  player.set_time_info(time_info);
  player.Initialize();
  std::cout << "Initialized" << std::endl;
  audio_out.Start();

  char c = getchar();
  return 0;
}
