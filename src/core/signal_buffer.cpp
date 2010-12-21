#include "signal_buffer.h"
#include <utility/dsp.h>
#include <cstdlib>

namespace construct {
namespace core {

SignalBuffer::SignalBuffer(uint32_t num_samples, uint32_t num_channels)
  : num_samples_(num_samples), num_channels_(num_channels) {
  buffer_ = (double*)malloc(num_samples_*num_channels_*sizeof(*buffer_));
}

SignalBuffer::~SignalBuffer() {
  free(buffer_);
}

void SignalBuffer::Clear() {
  utility::dsp::Clear(buffer_, num_samples_*num_channels_);
}

} // namespace core
} // namespace construct
