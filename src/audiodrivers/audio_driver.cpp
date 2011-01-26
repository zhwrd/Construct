#include "audio_driver.h"

namespace construct {
namespace audiodrivers {

AudioDriver::AudioDriver() :  callback_(NULL), callback_context_(NULL),
                              opened_(false), started_(false) {
}

AudioDriver::~AudioDriver() {

}

void AudioDriver::Quantize16Mono( const double* source,
                                  int16_t* destination,
                                  int num_samples) {
  do {
    *destination++ = source[0]*kMax16Amplitude;
    ++source;
  } while (--num_samples);
}

void AudioDriver::Quantize16Stereo( const double* source,
                                    int16_t* destination,
                                    int num_samples) {
  do {
    *destination++ = source[0]*kMax16Amplitude;
    *destination++ = source[1]*kMax16Amplitude;
    source += 2;
  } while (--num_samples);
}

} // namespace audiodrivers
} // namespace construct
