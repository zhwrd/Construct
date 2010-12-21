#include "sdlout.h"
#include <iostream>

namespace construct {
namespace audiodrivers {

SDLOut::SDLOut() : AudioDriver() {

}

SDLOut::~SDLOut() {
  DoStop();
}

void SDLOut::DoStart() {
  SDL_AudioSpec desired_format;
  SDL_AudioSpec obtained_format;
  desired_format.freq = 44100;
  desired_format.format = AUDIO_S16SYS;
  desired_format.channels = 1;
  desired_format.samples = 512;
  desired_format.callback = Process;
  desired_format.userdata = this;

  if (SDL_OpenAudio(&desired_format, &obtained_format) < 0) {
    exit(1);
  }

  int samples = obtained_format.samples;
  samples_ = (int16_t*)malloc(samples*sizeof(*samples_));

  SDL_PauseAudio(0);
}

void SDLOut::DoStop() {
  SDL_CloseAudio();
  free(samples_);
}

void SDLOut::FillBuffer(Uint8* output_buffer, int buffer_size) {
  Quantize16Mono(callback(buffer_size/2), samples_, buffer_size/2);
  for (int i = 0; i < buffer_size; i += 2) {
    output_buffer[i] = samples_[i/2]&0x00FF;
    output_buffer[i+1] = (samples_[i/2]>>8)&0x00FF;
  }
}

void SDLOut::Process(void* arg, Uint8* output_buffer, int buffer_size) {
  SDLOut* driver = static_cast<SDLOut*>(arg); 
  driver->FillBuffer(output_buffer, buffer_size);
}

} // namespace audiodrivers
} // namespace construct
