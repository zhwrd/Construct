#ifndef CONSTRUCT_AUDIODRIVERS_AUDIODRIVER_H_
#define CONSTRUCT_AUDIODRIVERS_AUDIODRIVER_H_

#include <stdint.h>
#include <cstdlib>
#include <iostream>

namespace construct {
namespace audiodrivers {

typedef double* (*AudioWorkCallback) (void* context, int num_samples);
int const kMaxWorkSamples = 65536;
int const kMax16Amplitude = 32767;

struct AudioDriverSettings {
  AudioDriverSettings() {
    sample_rate = 44100;
    sample_size = 16;
    num_channels = 2;
    num_samples = 512;
  }
  int sample_rate;
  int sample_size;
  int num_channels;
  int num_samples;
};

class AudioDriver {
 public:
  AudioDriver();
  virtual ~AudioDriver();

  virtual bool Open() = 0;
  virtual void Close() = 0;
  virtual bool Start() = 0;
  virtual void Stop() = 0;

  virtual void set_callback(AudioWorkCallback callback, void* context) {
    callback_ = callback;
    callback_context_ = context;
  }
  virtual void set_playback_settings(const AudioDriverSettings& settings) {
    playback_settings_ = settings;
  }
  const AudioDriverSettings& playback_settings() const { 
    return playback_settings_;
  }

  virtual bool opened() { return opened_; }
  virtual bool started() { return started_; }
 
 protected:
  double* callback(int num_samples) { 
    return callback_(callback_context_, num_samples);
  }

  void Quantize16Mono(const double* source, int16_t* destination,
                      int num_samples);
  void Quantize16Stereo(const double* source, int16_t* destination,
                        int num_samples);

  AudioDriverSettings playback_settings_;
  bool opened_;
  bool started_;

 private:
  AudioWorkCallback callback_;
  void* callback_context_;

};

} // namespace audiodrivers
} // namespace construct

#endif
