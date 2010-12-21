#include "audio_buffer.h"
#include <utility/dsp.h>
#include <cstdlib>

namespace construct {
namespace core {

AudioBuffer::AudioBuffer(int num_samples, int num_channels)
  : num_samples_(num_samples), num_channels_(num_channels) {
  buffer_ = (double*)malloc(num_samples_*num_channels_*sizeof(*buffer_));
}

AudioBuffer::~AudioBuffer() {
  free(buffer_);
}

void AudioBuffer::Clear() {
  utility::dsp::Clear(buffer_, num_samples_*num_channels_);
}

} // namespace core
} // namespace construct
