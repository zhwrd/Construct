#include "sdl_out.h"

namespace construct {
namespace audiodrivers {

SDLOut::SDLOut() : AudioDriver() {

}

SDLOut::~SDLOut() {
  Close();
}

bool SDLOut::Open() {
  if (opened()) {
    Close();
  }
  AudioDriverSettings requested = playback_settings_;
  AudioDriverSettings obtained;
  SDL_AudioSpec desired_format;
  SDL_AudioSpec obtained_format;
  desired_format.freq = requested.sample_rate;
  desired_format.format = ToSDLFormat(requested.sample_size);
  desired_format.channels = requested.num_channels;
  desired_format.samples = requested.num_samples;
  desired_format.callback = Process;
  desired_format.userdata = this;

  if (SDL_OpenAudio(&desired_format, &obtained_format) < 0) {
    return false;
  }

  obtained.sample_rate = obtained_format.freq;
  obtained.num_channels = obtained_format.channels;
  obtained.num_samples = obtained_format.samples;
  obtained.sample_size = ToSampleSize(obtained_format.format);

  playback_settings_ = obtained;
  samples_ = (int16_t*)malloc(obtained.num_samples*sizeof(*samples_));
  opened_ = true;
  return opened_;
}

void SDLOut::Close() {
  if (opened()) {
    Stop();
    SDL_CloseAudio();
    free(samples_);
    opened_ = false;
  }
}

bool SDLOut::Start() {
  if (opened()) {
    SDL_PauseAudio(0);
    started_ = true;
  }
  return started_;
}

void SDLOut::Stop() {
  if (started()) {
    SDL_PauseAudio(1);
    started_ = false;
  }
}

void SDLOut::set_playback_settings(const AudioDriverSettings& settings) {
  bool was_opened = opened();
  bool was_started = started();
  Close();
  playback_settings_ = settings;
  if (was_opened) {
    std::cout << "sdlout wasopened" << std::endl;
    Open();
    if (was_started) {
      std::cout << "sdlout wasstarted" << std::endl;
      Start();
    }
  }
}

Uint16 SDLOut::ToSDLFormat(int sample_size) {  
  if (sample_size == 8) {
    return AUDIO_S8;
  } else if (sample_size == 16) {
    return AUDIO_S16SYS;
  }
  return AUDIO_S8;
}

int SDLOut::ToSampleSize(Uint16 sdl_format) {
  if (sdl_format == AUDIO_S8) {
    return 8;
  } else if (sdl_format == AUDIO_S16SYS) {
    return 16;
  }
  return 8;
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
