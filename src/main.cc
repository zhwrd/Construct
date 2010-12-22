#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_opengl.h>

#include <core/player.h>
#include <audiodrivers/sdlout.h>

// Video
int width = 100;
int height = 100;

void initialize_video();
void initialize_sdl();

int main(int argc, char* argv[]) {
  initialize_sdl();

  // Audio
  construct::core::Player player;
  construct::audiodrivers::SDLOut audio_out;
  construct::audiodrivers::AudioDriverSettings settings;
  settings.num_channels = 1;
  audio_out.set_playback_settings(settings);
  audio_out.Open();

  player.set_driver(audio_out);
  player.Initialize();
  std::cout << "Initialized" << std::endl;
  audio_out.Start();

  char c = getchar();
  return 0;
}

void initialize_video() {
  const SDL_VideoInfo* info = NULL;
  int bpp = 0;
  int flags = 0;
  
  info = SDL_GetVideoInfo();
  if (!info) {
    exit(1);
  }
  bpp = info->vfmt->BitsPerPixel;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_Surface* drawContext;
  flags = SDL_OPENGL;
  drawContext = SDL_SetVideoMode(width, height, bpp, flags);

  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void initialize_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    exit(1);
  }
  //initialize_video();
}

