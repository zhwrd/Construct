#include "audiodriver.h"

namespace construct {
namespace audiodrivers {

AudioDriver::AudioDriver() : callback_(NULL), callback_context_(NULL) {
}

AudioDriver::~AudioDriver() {

}

void AudioDriver::DoStart() {

}

void AudioDriver::DoStop() {

}

void AudioDriver::Quantize16Mono( const double* source,
                                  int16_t* destination,
                                  uint32_t num_samples) {
  do {
    *destination++ = source[0];
    ++source;
  } while (--num_samples);
}

void AudioDriver::Quantize16Stereo( const double* source,
                                    int16_t* destination,
                                    uint32_t num_samples) {
  do {
    *destination++ = source[0];
    *destination++ = source[1];
    source += 2;
  } while (--num_samples);
}

} // namespace audiodrivers
} // namespace construct
