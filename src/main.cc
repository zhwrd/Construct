#include <iostream>
#include <cmath>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_opengl.h>
#include <audiodrivers/sdlout.h>

// Audio
construct::audiodrivers::SDLOut* audio_out;
construct::audiodrivers::AudioDriverSettings settings;
int sample_size = 16;
int sample_rate = 44100;
double freq = 440.0;
double* g_waveform = NULL;
double* g_waveout = NULL;
int g_length = 0;
int position = 0;

// Video
int width = 100;
int height = 100;

double* synth(void* context, int num_samples);
void initialize_video();
void initialize_audio();
void initialize_sdl();
void create_wavetable();

double* synth(void* context, int num_samples) {
  for (int i = 0; i < num_samples; ++i) {
    g_waveout[i] = (pow(2, 15) - 1)*g_waveform[position];
    ++position;
    position %= g_length;
  }
  return g_waveout;
}

int main(int argc, char* argv[]) {
  initialize_sdl();
  initialize_audio();
  create_wavetable();
  audio_out->Start();
  char c = getchar();
  return 0;
}

void create_wavetable() {
  double length = settings.sample_rate/freq;
  double omega = 3.14159*2/length;
  g_length = (int)length;
  g_waveform = (double*)malloc(g_length*sizeof(double));
  for (int i = 0; i < g_length; ++i) {
    g_waveform[i] = sin(omega*i);
  }
}

void initialize_audio() {
  using namespace construct::audiodrivers;
  settings.num_channels = 1;
  audio_out = new SDLOut();
  audio_out->set_callback(synth, NULL);
  audio_out->set_playback_settings(settings);
  audio_out->Open();
  settings = audio_out->playback_settings();
  g_waveout = (double*)malloc(settings.num_samples*sizeof(*g_waveout));
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

