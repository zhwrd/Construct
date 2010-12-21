#ifndef CONSTRUCT_AUDIODRIVERS_AUDIODRIVER_H_
#define CONSTRUCT_AUDIODRIVERS_AUDIODRIVER_H_

#include <stdint.h>
#include <cstdlib>
#include <iostream>

namespace construct {
namespace audiodrivers {

typedef double* (*AudioWorkCallback) (void* context, int num_samples);

struct AudioDriverSettings {
  AudioDriverSettings() {
    sample_rate = 44100;
    sample_size = 16;
    num_channels = 2;
    num_samples = 512;
  }
  uint32_t sample_rate;
  uint32_t sample_size;
  uint32_t num_channels;
  uint32_t num_samples;
};

class AudioDriver {
 public:
  AudioDriver();
  virtual ~AudioDriver();

  virtual void Open(AudioDriverSettings& requested,
                    AudioDriverSettings& obtained) {
    playback_settings_ = obtained;
  }
  void Start() { DoStart(); }
  void Stop() { DoStop(); }

  /*
  void set_playback_settings(const AudioDriverSettings& settings) {
    playback_settings_ = settings;
  }
  const AudioDriverSettings& get_playback_settings() const { 
    return playback_settings_;
  }
  */
  void set_callback(AudioWorkCallback callback, void* context) {
    callback_ = callback;
    callback_context_ = context;
  }
 
 protected:
  double* callback(int num_samples) { 
    return callback_(callback_context_, num_samples);
  }
  virtual void DoStart();
  virtual void DoStop();

  void Quantize16Mono(const double* source, int16_t* destination,
                      uint32_t num_samples);
  void Quantize16Stereo(const double* source, int16_t* destination,
                        uint32_t num_samples);

  AudioDriverSettings playback_settings_;

 private:
  AudioWorkCallback callback_;
  void* callback_context_;

};

} // namespace audiodrivers
} // namespace construct

#endif
