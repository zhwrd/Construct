#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <core/player.h>
#include <audiodrivers/coreaudio_out.h>
#include <frontend/qgl_construct.h>
#include <QApplication>
#include "config.h"

int main(int argc, char* argv[]) {
  using namespace construct;

  QApplication app(argc, argv);

  audiodrivers::AudioDriverSettings settings;
  settings.sample_rate = 48000;
  settings.num_channels = 2;

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
  player.Initialize();
  std::cout << "Player initialized." << std::endl;
  audio_out.Start();
  std::cout << "Output device started." << std::endl;

  frontend::QGLConstruct main_window;
  main_window.show();

  int result = app.exec();
  audio_out.Close();
  return result;
}
