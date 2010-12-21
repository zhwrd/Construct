#include "audio_buffer.h"
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
  for (int i = 0; i < num_samples_*num_channels_; ++i) {
    buffer_[i] = 0;
  }
}

} // namespace core
} // namespace construct
